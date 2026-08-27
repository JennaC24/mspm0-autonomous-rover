////////////////////////////////////////////////////////////////////////
//** ENGR-2350 Lab5 Part C - Autonomous Navigation
//** Names: Jenna Connelly
//** Section: 1
//** Side: B
//** Seat: 30
////////////////////////////////////////////////////////////////////////

#include "engr2350_mspm0.h"
#include <math.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function prototypes
void GPIOInit();
void timerInit();
void I2CInit();
uint8_t readCMPS12Register(uint8_t reg);
uint16_t readCMPS12Bearing();
uint16_t readSRF08Range();
void startSRF08Ranging();
void setMotorSpeed(float left_speed, float right_speed);
void stopMotors();

// I2C Addresses
#define CMPS12_ADDR 0x60
#define SRF08_ADDR  0x70

// CMPS12 Registers
#define CMPS12_BEARING_HIGH 0x02
#define CMPS12_BEARING_LOW  0x03

// SRF08 Registers
#define SRF08_COMMAND_REG 0x00
#define SRF08_RANGE_HIGH  0x02
#define SRF08_RANGE_LOW   0x03

// Navigation States
typedef enum {
    STATE_FORWARD,
    STATE_TURNING_LEFT,
    STATE_TURNING_RIGHT,
    STATE_TURNING_180,
    STATE_BACKUP_FROM_BUMP,
    STATE_ADJUSTING,
    STATE_TURN_PAUSE,   // <-- new pause state
    STATE_STOPPED
} NavState;

// Timer configurations
Timers_TimerConfig t8cfg;
Timers_CompareConfig t8c1cfg;
Timers_TimerConfig t0cfg;

// Control variables
volatile bool flag_50ms = 0;

// Sensor readings
uint16_t compass_bearing = 0;
uint16_t prev_compass_bearing = 0;
uint16_t range_cm = 100;
uint8_t range_sample_counter = 0;
uint8_t ranger_cycle_counter = 0;
bool compass_is_working = false;

// Bumper states
bool bmp1_pressed = false;
bool bmp2_pressed = false;
bool bmp3_pressed = false;
bool bmp4_pressed = false;
bool bmp5_pressed = false;
bool bmp6_pressed = false;

// Navigation state
NavState current_state = STATE_FORWARD;
uint16_t state_timer = 0;
uint8_t turn_count = 0;
bool next_turn_is_left = true;

// Stuck detection
uint8_t consecutive_turns = 0;
uint16_t last_turn_sample = 0;
const uint8_t MAX_CONSECUTIVE_TURNS = 2;  

// Target heading tracking
uint16_t target_bearing = 0;
bool heading_initialized = false;

// Navigation parameters
const float FORWARD_SPEED = 28.0f;
const float TURN_SPEED = 22.0f;
const float SLOW_SPEED = 18.0f;

// Distance thresholds
const uint16_t FRONT_WALL_NEAR = 18;
const uint16_t FRONT_WALL_CLOSE = 12;
const uint16_t SAFE_DISTANCE = 35;

// Turn parameters - ADJUST THESE FOR YOUR CAR
const uint16_t TURN_CYCLES_90  = 16;     
const uint16_t TURN_CYCLES_180 = 32;     
const uint16_t BACKUP_CYCLES   = 8;
const uint16_t HEADING_TOLERANCE = 200;
const uint16_t MIN_TURN_TIME   = 15;
const uint16_t PROGRESS_THRESHOLD = 50;   
const uint16_t TURN_PAUSE_CYCLES = 5;     

// Control parameters
const uint16_t PWM_PERIOD = 1000;
const uint16_t MIN_PWM_COMPARE = 120;
const uint16_t MAX_PWM_COMPARE = 900;

// Speed calibration
const float LEFT_CAL = 1.03f;
const float RIGHT_CAL = 0.96f;

int main() {
    sysInit();
    GPIOInit();
    timerInit();
    I2CInit();

    delay_cycles(32000000);

    // Turn on status LEDs
    GPIO_setPins(GPIOB, GPIO_PIN15 | GPIO_PIN16);

    printf("\r\n=== Lab 5 Part C - Zig-Zag Navigation ===\r\n");
    printf("Strategy: Alternating left-right turns\r\n");
    
    // Compass diagnostics
    printf("\n--- Compass Diagnostics ---\r\n");
    for(int i = 0; i < 10; i++) {
        compass_bearing = readCMPS12Bearing();
        printf("Reading %d: %u (%.1f deg)\r\n", i+1, compass_bearing, compass_bearing/10.0f);
        delay_cycles(8000000);
    }
    
    if(compass_bearing >= 3600 || compass_bearing == 3543) {
        printf("\n*** WARNING: Compass appears stuck at %u ***\r\n", compass_bearing);
        printf("Continuing with TIME-BASED turns...\r\n");
        compass_is_working = false;
    } else {
        printf("\n*** Compass appears functional ***\r\n");
        compass_is_working = true;
    }
    
    printf("\nPress any key to start...\r\n");
    getchar();

    // Initialize with current compass heading
    compass_bearing = readCMPS12Bearing();
    if(compass_bearing >= 3600) compass_bearing = 0;
    target_bearing = compass_bearing;
    heading_initialized = true;
    
    printf("\nStarting configuration:\r\n");
    printf("  Initial heading: %u (%.1f deg)\r\n", compass_bearing, compass_bearing/10.0f);
    printf("  Compass status: %s\r\n", compass_is_working ? "WORKING" : "USING TIME-BASED TURNS");
    printf("  Turn calibration: 90deg=%u cycles, 180deg=%u cycles\r\n", TURN_CYCLES_90, TURN_CYCLES_180);
    printf("\r\nSample\tState\tBearing\tTarget\tError\tRange\tTurns\tNextTurn\tBumpers\r\n");

    uint16_t sample_count = 0;

    while(1) {
        if(flag_50ms) {
            flag_50ms = 0;
            sample_count++;

            // ========== READ SENSORS ==========
            prev_compass_bearing = compass_bearing;
            compass_bearing = readCMPS12Bearing();
            if(compass_bearing >= 3600) compass_bearing = 0;
            
            // Check if compass is actually updating
            static uint8_t compass_check_counter = 0;
            compass_check_counter++;
            if(compass_check_counter > 20) {
                if(abs((int16_t)compass_bearing - (int16_t)prev_compass_bearing) > 5) {
                    compass_is_working = true;
                } else if(current_state == STATE_TURNING_LEFT || 
                         current_state == STATE_TURNING_RIGHT ||
                         current_state == STATE_TURNING_180) {
                    compass_is_working = false;
                }
                compass_check_counter = 0;
            }

            // Read bumpers (active LOW)
            bmp1_pressed = (GPIO_readPins(GPIOA, GPIO_PIN7) == 0);
            bmp2_pressed = (GPIO_readPins(GPIOA, GPIO_PIN14) == 0);
            bmp3_pressed = (GPIO_readPins(GPIOB, GPIO_PIN5) == 0);
            bmp4_pressed = (GPIO_readPins(GPIOB, GPIO_PIN21) == 0);
            bmp5_pressed = (GPIO_readPins(GPIOB, GPIO_PIN23) == 0);
            bmp6_pressed = (GPIO_readPins(GPIOB, GPIO_PIN25) == 0);
            
            bool any_bumper = bmp1_pressed || bmp2_pressed || bmp3_pressed || 
                             bmp4_pressed || bmp5_pressed || bmp6_pressed;

            // Read range every 100ms
            ranger_cycle_counter++;
            if(ranger_cycle_counter >= 2) {
                ranger_cycle_counter = 0;
                range_sample_counter++;
                if(range_sample_counter == 1) {
                    uint16_t new_range = readSRF08Range();
                    if(new_range > 0 && new_range < 600) {
                        range_cm = new_range;
                    }
                    startSRF08Ranging();
                    range_sample_counter = 0;
                }
            }

            // ========== CALCULATE HEADING ERROR ==========
            int16_t heading_error = (int16_t)compass_bearing - (int16_t)target_bearing;
            if(heading_error > 1800) heading_error -= 3600;
            if(heading_error < -1800) heading_error += 3600;

            // ========== STATE MACHINE ==========
            const char* state_names[] = {
                "FWD", "L-TURN", "R-TURN", "180", "BACKUP", "ADJUST", "PAUSE", "STOP"
            };

            // BUMPER OVERRIDE
            if(current_state == STATE_FORWARD && any_bumper) {
                current_state = STATE_BACKUP_FROM_BUMP;
                state_timer = 0;
                printf("\n>> BUMPER HIT! Backing up...\r\n");
            }

            switch(current_state) {
                
                case STATE_FORWARD: {
                    if(state_timer > PROGRESS_THRESHOLD && consecutive_turns > 0) {
                        printf("\n>> Drove forward for %u samples - resetting consecutive_turns\r\n", state_timer);
                        consecutive_turns = 0;
                    }
                    
                    if(range_cm < FRONT_WALL_NEAR) {
                        uint16_t dt = sample_count - last_turn_sample;

                        if(dt > PROGRESS_THRESHOLD) {
                            // We made good progress since the last turn; start a new corner sequence
                            printf("\n>> Good progress (%u samples) - starting new corner sequence\r\n", dt);
                            consecutive_turns = 0;
                        } else {
                            printf("\n>> Quick turn detected! Time since last: %u samples\r\n", dt);
                        }

                        // Count THIS turn as part of the sequence
                        consecutive_turns++;
                        printf(">> Consecutive turns in this corner = %u\r\n", consecutive_turns);

                        if(consecutive_turns >= MAX_CONSECUTIVE_TURNS) {
                            printf("\n>> STUCK IN CORNER! Turning 180 degrees (consecutive=%u)\r\n", consecutive_turns);
                            current_state = STATE_TURNING_180;
                            target_bearing = (target_bearing + 1800) % 3600;
                            printf(">> New target: %u deg\r\n", target_bearing/10);
                            state_timer = 0;
                            // After scheduling a 180, reset the sequence
                            consecutive_turns = 0;
                            break;
                        }
                        
                        // Otherwise do a normal 90-degree turn
                        turn_count++;
                        
                        if(next_turn_is_left) {
                            current_state = STATE_TURNING_LEFT;
                            target_bearing = (target_bearing >= 900) ? 
                                           (target_bearing - 900) : (target_bearing + 2700);
                            printf("\n>> WALL @ %ucm - Turn #%u LEFT to %u deg\r\n", 
                                   range_cm, turn_count, target_bearing/10);
                        } else {
                            current_state = STATE_TURNING_RIGHT;
                            target_bearing = (target_bearing + 900) % 3600;
                            printf("\n>> WALL @ %ucm - Turn #%u RIGHT to %u deg\r\n", 
                                   range_cm, turn_count, target_bearing/10);
                        }
                        
                        next_turn_is_left = !next_turn_is_left;
                        state_timer = 0;
                        break;
                    }
                    
                    if(abs(heading_error) > HEADING_TOLERANCE && compass_is_working) {
                        float correction = (float)heading_error / 2000.0f;
                        if(correction > 8.0f) correction = 8.0f;
                        if(correction < -8.0f) correction = -8.0f;
                        
                        setMotorSpeed(FORWARD_SPEED - correction, 
                                      FORWARD_SPEED + correction);
                    } else {
                        setMotorSpeed(FORWARD_SPEED, FORWARD_SPEED);
                    }
                    state_timer++;
                    break;
                }

                case STATE_TURNING_LEFT:
                    state_timer++;
                    
                    if(any_bumper) {
                        current_state = STATE_BACKUP_FROM_BUMP;
                        state_timer = 0;
                        printf("\n>> BUMPER during LEFT turn - backing up\r\n");
                        break;
                    }
                    
                    setMotorSpeed(-TURN_SPEED, TURN_SPEED);

                    if(state_timer > MIN_TURN_TIME) {
                        bool turn_done = false;

                        if(compass_is_working && abs(heading_error) < HEADING_TOLERANCE) {
                            printf(">> LEFT turn complete - compass aligned (error=%d)\r\n", heading_error);
                            turn_done = true;
                        } else if(state_timer >= TURN_CYCLES_90) {
                            if(compass_is_working) {
                                printf(">> LEFT turn timeout (error=%d)\r\n", heading_error);
                            } else {
                                printf(">> LEFT turn complete - time-based (%u cycles)\r\n", state_timer);
                            }
                            turn_done = true;
                        }

                        if(turn_done) {
                            // Turn just finished
                            last_turn_sample = sample_count;
                            current_state = STATE_TURN_PAUSE;   // go to pause instead of FWD
                            state_timer = 0;
                        }
                    }
                    break;

                case STATE_TURNING_RIGHT:
                    state_timer++;
                    
                    if(any_bumper) {
                        current_state = STATE_BACKUP_FROM_BUMP;
                        state_timer = 0;
                        printf("\n>> BUMPER during RIGHT turn - backing up\r\n");
                        break;
                    }
                    
                    setMotorSpeed(TURN_SPEED, -TURN_SPEED);

                    if(state_timer > MIN_TURN_TIME) {
                        bool turn_done = false;

                        if(compass_is_working && abs(heading_error) < HEADING_TOLERANCE) {
                            printf(">> RIGHT turn complete - compass aligned (error=%d)\r\n", heading_error);
                            turn_done = true;
                        } else if(state_timer >= TURN_CYCLES_90) {
                            if(compass_is_working) {
                                printf(">> RIGHT turn timeout (error=%d)\r\n", heading_error);
                            } else {
                                printf(">> RIGHT turn complete - time-based (%u cycles)\r\n", state_timer);
                            }
                            turn_done = true;
                        }

                        if(turn_done) {
                            last_turn_sample = sample_count;
                            current_state = STATE_TURN_PAUSE;   // pause after turn
                            state_timer = 0;
                        }
                    }
                    break;

                case STATE_TURNING_180:
                    state_timer++;
                    
                    setMotorSpeed(TURN_SPEED, -TURN_SPEED);

                    if(state_timer >= TURN_CYCLES_180) {
                        printf(">> 180 turn complete - %u cycles\r\n", state_timer);
                        printf(">> Target heading: %u deg\r\n", target_bearing/10);
                        last_turn_sample = sample_count;
                        current_state = STATE_TURN_PAUSE;   // pause after 180
                        state_timer = 0;
                        // don't touch consecutive_turns here
                    } else if(state_timer % 10 == 0) {
                        printf(">> 180 progress: %u/%u cycles\r\n", state_timer, TURN_CYCLES_180);
                    }
                    break;

                case STATE_BACKUP_FROM_BUMP: {
                    state_timer++;
                    
                    setMotorSpeed(-SLOW_SPEED, -SLOW_SPEED);
                    
                    if(state_timer > BACKUP_CYCLES) {
                        uint16_t dt = sample_count - last_turn_sample;

                        if(dt > PROGRESS_THRESHOLD) {
                            printf("\n>> After bump - Good progress (%u samples), starting new corner sequence\r\n", dt);
                            consecutive_turns = 0;
                        } else {
                            printf("\n>> After bump - Quick turn! Time since last: %u samples\r\n", dt);
                        }

                        consecutive_turns++;
                        printf(">> After bump - Consecutive turns in this corner = %u\r\n", consecutive_turns);
                        
                        if(consecutive_turns >= MAX_CONSECUTIVE_TURNS) {
                            printf("\n>> After bump - STUCK! Turning 180 (consecutive=%u)\r\n", consecutive_turns);
                            current_state = STATE_TURNING_180;
                            target_bearing = (target_bearing + 1800) % 3600;
                            printf(">> New target: %u deg\r\n", target_bearing/10);
                            consecutive_turns = 0;  // reset after scheduling 180
                        } else {
                            turn_count++;
                            
                            if(next_turn_is_left) {
                                current_state = STATE_TURNING_LEFT;
                                target_bearing = (target_bearing >= 900) ? 
                                               (target_bearing - 900) : (target_bearing + 2700);
                                printf("\n>> After bump - Turn #%u LEFT to %u deg\r\n", 
                                       turn_count, target_bearing/10);
                            } else {
                                current_state = STATE_TURNING_RIGHT;
                                target_bearing = (target_bearing + 900) % 3600;
                                printf("\n>> After bump - Turn #%u RIGHT to %u deg\r\n", 
                                       turn_count, target_bearing/10);
                            }
                            
                            next_turn_is_left = !next_turn_is_left;
                        }
                        state_timer = 0;
                    }
                    break;
                }

                case STATE_TURN_PAUSE:
                    // Short pause after any turn
                    state_timer++;
                    stopMotors();
                    if(state_timer >= TURN_PAUSE_CYCLES) {
                        state_timer = 0;
                        current_state = STATE_FORWARD;
                        printf(">> Pause complete, resuming FORWARD\r\n");
                    }
                    break;

                case STATE_ADJUSTING:
                    state_timer++;
                    
                    if(heading_error > 100) {
                        setMotorSpeed(SLOW_SPEED, -SLOW_SPEED/2);
                    } else if(heading_error < -100) {
                        setMotorSpeed(-SLOW_SPEED/2, SLOW_SPEED);
                    } else {
                        current_state = STATE_FORWARD;
                    }
                    
                    if(state_timer > 20) {
                        current_state = STATE_FORWARD;
                    }
                    break;

                case STATE_STOPPED:
                    stopMotors();
                    break;
            }

            // Logging every 4 samples
            if(sample_count % 4 == 0) {
                printf("%u\t%s\t%u\t%u\t%d\t%u\t%u\t%s\t%c%c%c%c%c%c\r\n",
                       sample_count,
                       state_names[current_state],
                       compass_bearing,
                       target_bearing,
                       heading_error,
                       range_cm,
                       turn_count,
                       next_turn_is_left ? "LEFT" : "RIGHT",
                       bmp1_pressed ? '1' : '-',
                       bmp2_pressed ? '2' : '-',
                       bmp3_pressed ? '3' : '-',
                       bmp4_pressed ? '4' : '-',
                       bmp5_pressed ? '5' : '-',
                       bmp6_pressed ? '6' : '-');
            }
        }
    }
}

void setMotorSpeed(float left_speed, float right_speed) {
    if(left_speed >= 0) {
        GPIO_setPins(GPIOB, GPIO_PIN8);
    } else {
        GPIO_clearPins(GPIOB, GPIO_PIN8);
        left_speed = -left_speed;
    }

    if(right_speed >= 0) {
        GPIO_setPins(GPIOB, GPIO_PIN0);
    } else {
        GPIO_clearPins(GPIOB, GPIO_PIN0);
        right_speed = -right_speed;
    }

    if(left_speed > 0.1f && left_speed < 10.0f) left_speed = 10.0f;
    if(right_speed > 0.1f && right_speed < 10.0f) right_speed = 10.0f;

    uint16_t pwm_left = (uint16_t)((left_speed / 100.0f) * PWM_PERIOD * LEFT_CAL);
    uint16_t pwm_right = (uint16_t)((right_speed / 100.0f) * PWM_PERIOD * RIGHT_CAL);

    if(left_speed < 0.1f) {
        pwm_left = 0;
    } else {
        if(pwm_left < MIN_PWM_COMPARE) pwm_left = MIN_PWM_COMPARE;
        if(pwm_left > MAX_PWM_COMPARE) pwm_left = MAX_PWM_COMPARE;
    }
    
    if(right_speed < 0.1f) {
        pwm_right = 0;
    } else {
        if(pwm_right < MIN_PWM_COMPARE) pwm_right = MIN_PWM_COMPARE;
        if(pwm_right > MAX_PWM_COMPARE) pwm_right = MAX_PWM_COMPARE;
    }

    Timers_setCCRValue(TIMG8, TIMER_CCR_CCR1, pwm_left);
    Timers_setCCRValue(TIMG8, TIMER_CCR_CCR0, pwm_right);
}

void stopMotors() {
    Timers_setCCRValue(TIMG8, TIMER_CCR_CCR0, 0);
    Timers_setCCRValue(TIMG8, TIMER_CCR_CCR1, 0);
}

void I2CInit() {
    GPIO_initPeripheralFunction(GPIOA, GPIO_PIN15, GPIO_PA15_PF_I2C1_SCL);
    GPIO_initPeripheralFunction(GPIOA, GPIO_PIN16, GPIO_PA16_PF_I2C1_SDA);
    GPIO_setOpenDrain(GPIOA, GPIO_PIN15 | GPIO_PIN16);

    I2C_ControllerConfig i2cConfig;
    i2cConfig.busclkRate = 32000000;
    i2cConfig.bitRate = 100000;
    i2cConfig.addrMode = I2C_ADDR_MODE_7BIT;

    I2C_initController(I2C1, &i2cConfig);
    delay_cycles(3200000);
    
    printf("Testing compass communication...\r\n");
    for(int i = 0; i < 5; i++) {
        uint16_t test_bearing = readCMPS12Bearing();
        printf("  Attempt %d: bearing = %u (%.1f deg)\r\n", i+1, test_bearing, test_bearing/10.0f);
        delay_cycles(16000000);
    }
}

uint8_t readCMPS12Register(uint8_t reg) {
    uint8_t data = 0;
    uint32_t result = I2C_readData(I2C1, CMPS12_ADDR, reg, &data, 1);
    if(result != 0) {
        printf("I2C ERROR reading register 0x%02X, result=%u\r\n", reg, result);
        return 0;
    }
    return data;
}

uint16_t readCMPS12Bearing() {
    uint8_t bearing_data[2] = {0, 0};
    uint32_t result = I2C_readData(I2C1, CMPS12_ADDR, CMPS12_BEARING_HIGH, bearing_data, 2);
    
    if(result != 0) {
        static uint8_t error_count = 0;
        error_count++;
        if(error_count % 20 == 1) {
            printf("I2C ERROR reading bearing, result=%u (error #%u)\r\n", result, error_count);
        }
        return compass_bearing;
    }
    
    uint16_t bearing = (bearing_data[0] << 8) | bearing_data[1];
    
    if(bearing >= 3600) {
        static uint8_t invalid_count = 0;
        invalid_count++;
        if(invalid_count % 20 == 1) {
            printf("INVALID bearing: %u (raw bytes: 0x%02X 0x%02X)\r\n", 
                   bearing, bearing_data[0], bearing_data[1]);
        }
        return compass_bearing;
    }
    
    return bearing;
}

void startSRF08Ranging() {
    uint8_t cmd = 0x51;
    I2C_writeData(I2C1, SRF08_ADDR, SRF08_COMMAND_REG, &cmd, 1);
}

uint16_t readSRF08Range() {
    uint8_t range_data[2] = {0, 0};
    uint32_t result = I2C_readData(I2C1, SRF08_ADDR, SRF08_RANGE_HIGH, range_data, 2);
    if(result != 0) return range_cm;
    return (range_data[0] << 8) | range_data[1];
}

void GPIOInit() {
    GPIO_initDigitalOutput(GPIOB, GPIO_PIN0 | GPIO_PIN8 | GPIO_PIN15 | GPIO_PIN16);
    GPIO_clearPins(GPIOB, GPIO_PIN15 | GPIO_PIN16);
    GPIO_clearPins(GPIOB, GPIO_PIN0 | GPIO_PIN8);

    GPIO_initPeripheralFunction(GPIOB, GPIO_PIN6 | GPIO_PIN7, 5);
    
    GPIO_initDigitalInput(GPIOA, GPIO_PIN7 | GPIO_PIN14);
    GPIO_initDigitalInput(GPIOB, GPIO_PIN5 | GPIO_PIN21 | GPIO_PIN23 | GPIO_PIN25);
    GPIO_setInternalResistor(GPIOA, GPIO_PIN7 | GPIO_PIN14, GPIO_PULL_UP);
    GPIO_setInternalResistor(GPIOB, GPIO_PIN5 | GPIO_PIN21 | GPIO_PIN23 | GPIO_PIN25, GPIO_PULL_UP);
}

void timerInit() {
    t8cfg.mode = TIMER_MODE_PERIODIC_UP;
    t8cfg.clksrc = TIMER_CLOCK_BUSCLK;
    t8cfg.clkdivratio = TIMER_CLOCK_DIVIDE_1;
    t8cfg.clkprescale = 0;
    t8cfg.period = 1000 - 1;
    Timers_initTimer(TIMG8, &t8cfg);

    t8c1cfg.ccrn = TIMER_CCR_CCR0 | TIMER_CCR_CCR1;
    t8c1cfg.action = TIMER_CCR_ACTION_ZERO_SET | TIMER_CCR_ACTION_UPCOMPARE_CLEAR;
    t8c1cfg.value = 0;
    t8c1cfg.invertOutput = false;
    Timers_initCompare(TIMG8, &t8c1cfg);
    Timers_startTimer(TIMG8);

    t0cfg.mode = TIMER_MODE_PERIODIC_UP;
    t0cfg.clksrc = TIMER_CLOCK_LFCLK;
    t0cfg.clkdivratio = TIMER_CLOCK_DIVIDE_1;
    t0cfg.clkprescale = 0;
    t0cfg.period = 1638;
    Timers_initTimer(TIMG0, &t0cfg);
    Timers_enableInterrupt(TIMG0, TIMER_INTSRC_ZERO);
    NVIC_EnableIRQ(TIMG0_INT_IRQn);
    Timers_startTimer(TIMG0);
}

void TIMG0_IRQHandler() {
    Timers_getActiveInterrupt(TIMG0);
    flag_50ms = 1;
}
