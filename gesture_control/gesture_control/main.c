////////////////////////////////////////////////////////////////////////
//** ENGR-2350 Lab5 - Roll and Angle-Based Turn Control
//** Names: Jenna Connelly
//** Section: 1
//** Side: B
//** Seat: 30
////////////////////////////////////////////////////////////////////////

#include "engr2350_mspm0.h"
#include <math.h>
#include <stdlib.h>   // for abs()

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void GPIOInit();
void timerInit();
void I2CInit();
uint8_t readCMPS12Register(uint8_t reg);
uint16_t readCMPS12Bearing();
uint16_t readSRF08Range();
void startSRF08Ranging();
float wrapAngle(float angle);

// I2C Addresses
#define CMPS12_ADDR 0x60
#define SRF08_ADDR  0x70

// CMPS12 Register Addresses
#define CMPS12_BEARING_HIGH 0x02  // Bearing (0-3599 in tenths of degrees)
#define CMPS12_BEARING_LOW  0x03
#define CMPS12_PITCH_REG    0x04
#define CMPS12_ROLL_REG     0x05

// SRF08 Register Addresses
#define SRF08_COMMAND_REG 0x00
#define SRF08_RANGE_HIGH  0x02
#define SRF08_RANGE_LOW   0x03

// GPIO Configuration
#define SLIDE_SWITCH_PIN GPIO_PIN22  // PA22 for mode selection

Timers_TimerConfig t8cfg;
Timers_CompareConfig t8c1cfg;
Timers_TimerConfig t6cfg;
Timers_CaptureConfig t6c1cfg;
Timers_TimerConfig t0cfg;

// Encoder variables - signed and volatile for ISR/main sharing
volatile int32_t enc_total_events_L, enc_total_events_R;
volatile int32_t enc_segment_events_L, enc_segment_events_R;
volatile int32_t enc_counts_track_L, enc_counts_track_R;
volatile int32_t enc_counts_L, enc_counts_R;
volatile uint8_t enc_flag_L, enc_flag_R;
volatile uint32_t enc_counts_sum_L, enc_counts_sum_R;
volatile uint8_t enc_events_sum_L, enc_events_sum_R;
volatile uint32_t enc_counts_avg_L, enc_counts_avg_R;

// Control loop flag
volatile bool flag_50ms = 0;
uint8_t ranger_cycle_counter = 0;  // For 100ms ranger timing

// Sensor readings
int8_t pitch = 0;
int8_t roll = 0;
uint16_t range_cm = 0;
uint16_t compass_bearing = 0;  // 0-3599 (tenths of degrees)
uint8_t range_sample_counter = 0;

// Control mode
bool use_roll_control = true;       // true = Part A (roll), false = Part B (angle)
bool prev_use_roll_control = true;  // track mode transitions
uint16_t angle_mode_counter = 0;    // counter for periodic compass sync

// Heading calculation variables (from encoders)
float rel_heading_rad = 0.0f;     // relative heading of the car from encoders, in radians
float measured_heading = 0.0f;    // encoder-based heading, in tenths of degrees (0-3599)
float desired_heading = 0.0f;     // commanded heading, 0-3599
float heading_error = 0.0f;
float prev_heading_error = 0.0f;

// roll-based steering offset in ANGLE mode (tenths of degrees)
// desired_heading = compass_bearing + heading_offset (wrapped)
float heading_offset = 0.0f;

// Control Variables - SHARED
float desired_speed = 0.0f;
float desired_speed_modified = 0.0f;

// Control Variables for LEFT WHEEL
float measured_speed_L = 0.0f;
float speed_error_L = 0.0f;
float error_sum_L = 0.0f;
float corrected_speed_L = 0.0f;
uint16_t pwm_compare_value_L = 0;

// Control Variables for RIGHT WHEEL
float measured_speed_R = 0.0f;
float speed_error_R = 0.0f;
float error_sum_R = 0.0f;
float corrected_speed_R = 0.0f;
uint16_t pwm_compare_value_R = 0;

// Control Constants
const float Kp_speed = 0.5f;
const float Ki_speed = 0.025f;      // Halved from 0.05 due to 50ms period
const float Kp_heading = 0.0125f;   // slightly softer heading correction for driving
const float Kd_heading = 0.0f;      // not used (P-only)

// Speed / PWM limits
const float MIN_SPEED_THRESHOLD = 10.0f;
const float MAX_SPEED_THRESHOLD = 50.0f;
const uint16_t MIN_PWM_COMPARE = 100;
const uint16_t MAX_PWM_COMPARE = 900;
const uint16_t PWM_PERIOD = 1000;
const float ENCODER_CONVERSION_CONSTANT = 2000000.0f;
const float MAX_ERROR_SUM = 500.0f;

// Speed-dependent calibration
const float LOW_SPEED_LEFT_CAL  = 1.16f;
const float LOW_SPEED_RIGHT_CAL = 0.94f;
const float HIGH_SPEED_LEFT_CAL = 1.04f;
const float HIGH_SPEED_RIGHT_CAL = 0.96f;
const float SPEED_TRANSITION_THRESHOLD = 25.0f;

// Physical parameters
const float WHEEL_SEPARATION = 0.14f;                   // meters
const float ENCODER_DISTANCE_CONVERSION = 0.0009963f;   // meters per encoder count

// Pitch/Roll mapping constants
const float PITCH_DEADBAND = 5.0f;
const float PITCH_MAX = 30.0f;
const float ROLL_DEADBAND = 3.0f;
const float ROLL_MAX = 25.0f;

// Obstacle detection
const uint16_t OBSTACLE_THRESHOLD_CM = 25;

// Differential speed limits
const float MAX_DIFF = 20.0f;          // Max differential speed (%)
const float STOP_SPEED_THRESH = 1.0f;  // below this, treat as stopped

// Wrap tenths-of-degrees angle to [0, 3600)
float wrapAngle(float angle) {
    while (angle >= 3600.0f) angle -= 3600.0f;
    while (angle <    0.0f)  angle += 3600.0f;
    return angle;
}

int main() {
    sysInit();
    GPIOInit();
    timerInit();
    I2CInit();

    delay_cycles(32000000);

    GPIO_setPins(GPIOB, GPIO_PIN15 | GPIO_PIN16);

    printf("Lab 5 Part B - Gesture Control with Angle-Based Turning (FIXED + STEERING)\r\n");
    printf("Slide Switch: UP=Roll Control (Part A), DOWN=Angle Control (Part B)\r\n");
    printf("Sample\tMode\tPitch\tRoll\tBear\tRange\tDesSpd\tDiff\tDesHd\tMeasHd\tHdErr\tDesL\tDesR\tMeas_L\tMeas_R\tPWM_L\tPWM_R\r\n");

    uint16_t sample_count = 0;

    while(1) {
        if(flag_50ms) {
            flag_50ms = 0;
            sample_count++;

            // Read slide switch state
            use_roll_control = (GPIO_readPins(GPIOA, SLIDE_SWITCH_PIN) != 0);

            // ========== READ CMPS12 SENSORS ==========
            pitch = (int8_t)readCMPS12Register(CMPS12_PITCH_REG);
            roll  = (int8_t)readCMPS12Register(CMPS12_ROLL_REG);
            compass_bearing = readCMPS12Bearing();  // 0-3599 (tenths of degrees)

            // Clamp compass_bearing to valid range in case of glitches (e.g. 64262)
            if (compass_bearing >= 3600) {
                compass_bearing = compass_bearing % 3600;
            }

            // Detect mode switch: ROLL -> ANGLE
            if (!use_roll_control && prev_use_roll_control) {
                float compass_deg = (float)compass_bearing / 10.0f;
                rel_heading_rad = compass_deg * (float)M_PI / 180.0f;
                measured_heading = (float)compass_bearing;
                desired_heading  = (float)compass_bearing;
                heading_offset   = 0.0f;  // reset steering offset
                prev_heading_error = 0.0f;
                printf("MODE SWITCH -> ANGLE: synced to compass %.1f deg\r\n", compass_deg);
            }
            prev_use_roll_control = use_roll_control;

            // ========== READ SRF08 ULTRASONIC RANGE (every 100ms) ==========
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

            if(range_cm == 0) {
                range_cm = 100;
            }

            // ========== CALCULATE RELATIVE MEASURED HEADING FROM ENCODERS ==========
            int32_t delta_L = enc_segment_events_L;
            int32_t delta_R = enc_segment_events_R;

            enc_segment_events_L = 0;
            enc_segment_events_R = 0;

            // motors_active based on desired speed, not PWM
            bool motors_active = (fabs(desired_speed_modified) > 1.0f);

            if(motors_active && (delta_L != 0 || delta_R != 0)) {
                float distance_L = delta_L * ENCODER_DISTANCE_CONVERSION;
                float distance_R = delta_R * ENCODER_DISTANCE_CONVERSION;

                float delta_theta_rad = (distance_L - distance_R) / WHEEL_SEPARATION;

                rel_heading_rad += delta_theta_rad;

                if (rel_heading_rad >  (float)M_PI) rel_heading_rad -= 2.0f * (float)M_PI;
                if (rel_heading_rad < -(float)M_PI) rel_heading_rad += 2.0f * (float)M_PI;
            }

            float heading_deg = rel_heading_rad * (180.0f / (float)M_PI);
            measured_heading = wrapAngle(heading_deg * 10.0f);

            // Periodic drift correction using compass
            if (!use_roll_control) {
                angle_mode_counter++;
                if (angle_mode_counter >= 40) {
                    angle_mode_counter = 0;
                    float compass_heading = (float)compass_bearing;
                    float drift = compass_heading - measured_heading;
                    if (drift >  1800.0f) drift -= 3600.0f;
                    if (drift < -1800.0f) drift += 3600.0f;

                    if (fabs(drift) > 150.0f) {
                        float correction_deg = (drift * 0.05f) / 10.0f;
                        rel_heading_rad += correction_deg * (float)M_PI / 180.0f;

                        if (fabs(drift) > 300.0f) {
                            printf("DRIFT CORRECTION: drift=%.1f applying %.2f deg\r\n",
                                   drift, correction_deg);
                        }
                    }
                }
            } else {
                angle_mode_counter = 0;
            }

            // ========== CONVERT PITCH TO DESIRED SPEED ==========
            if(abs(pitch) < (int)PITCH_DEADBAND) {
                desired_speed = 0.0f;
            } else {
                if(pitch < 0) {
                    float normalized = ((-(float)pitch) - PITCH_DEADBAND) / (PITCH_MAX - PITCH_DEADBAND);
                    if(normalized > 1.0f) normalized = 1.0f;
                    desired_speed = -normalized * MAX_SPEED_THRESHOLD;
                } else {
                    float normalized = ((float)pitch - PITCH_DEADBAND) / (PITCH_MAX - PITCH_DEADBAND);
                    if(normalized > 1.0f) normalized = 1.0f;
                    desired_speed = normalized * MAX_SPEED_THRESHOLD;
                }
            }

            if(fabs(desired_speed) < MIN_SPEED_THRESHOLD) {
                desired_speed_modified = 0.0f;
            } else if(desired_speed > MAX_SPEED_THRESHOLD) {
                desired_speed_modified = MAX_SPEED_THRESHOLD;
            } else if(desired_speed < -MAX_SPEED_THRESHOLD) {
                desired_speed_modified = -MAX_SPEED_THRESHOLD;
            } else {
                desired_speed_modified = desired_speed;
            }

            // ========== OBSTACLE DETECTION ==========
            if(range_cm < OBSTACLE_THRESHOLD_CM && desired_speed_modified < 0.0f) {
                desired_speed_modified = 0.0f;
            }

            // ========== CALCULATE DIFFERENTIAL SPEED ==========
            float diff = 0.0f;

            if(use_roll_control) {
                // ===== PART A: ROLL-BASED TURNING =====
                if(abs(roll) > (int)ROLL_DEADBAND) {
                    float normalized_roll = (float)roll / ROLL_MAX;
                    if(normalized_roll > 1.0f)  normalized_roll = 1.0f;
                    if(normalized_roll < -1.0f) normalized_roll = -1.0f;
                    diff = normalized_roll * MAX_DIFF;
                }
                desired_heading = (float)compass_bearing;  // for display/logging

            } else {
                // ===== PART B: ANGLE-BASED TURNING (ROLL STEERS HEADING) =====

                bool motors_running = (fabs(desired_speed_modified) > STOP_SPEED_THRESH);
                (void)motors_running; // currently unused but kept for clarity

                // Use roll to adjust heading_offset relative to compass
                float roll_norm = (float)roll / ROLL_MAX;
                if (roll_norm > 1.0f)  roll_norm = 1.0f;
                if (roll_norm < -1.0f) roll_norm = -1.0f;

                if (abs(roll) > (int)ROLL_DEADBAND) {
                    const float OFFSET_RATE = 15.0f; // tenths of deg per 50ms at full roll (~30 deg/s)
                    heading_offset += roll_norm * OFFSET_RATE;

                    // limit offset to +/- 180 degrees
                    if (heading_offset >  1800.0f) heading_offset =  1800.0f;
                    if (heading_offset < -1800.0f) heading_offset = -1800.0f;
                }

                // Commanded heading = compass + user offset
                desired_heading = wrapAngle((float)compass_bearing + heading_offset);

                heading_error = desired_heading - measured_heading;
                if (heading_error >  1800.0f) heading_error -= 3600.0f;
                if (heading_error < -1800.0f) heading_error += 3600.0f;

                const float SMALL_ERROR_DEADBAND = 150.0f;  // ~15 degrees
                const float SPIN_DIFF            = 15.0f;   // in-place spin magnitude

                if (fabs(desired_speed_modified) < STOP_SPEED_THRESH) {
                    // Stopped: spin in place toward commanded heading
                    if (fabs(heading_error) < SMALL_ERROR_DEADBAND) {
                        diff = 0.0f;  // close enough, no jitter
                    } else {
                        diff = (heading_error > 0.0f) ? SPIN_DIFF : -SPIN_DIFF;
                    }
                    prev_heading_error = heading_error;

                } else {
                    // Moving: P correction with speed scaling
                    float speed_scale = fabs(desired_speed_modified) / 10.0f;
                    if (speed_scale < 0.5f) speed_scale = 0.5f;
                    if (speed_scale > 2.0f) speed_scale = 2.0f;

                    float P_term = Kp_heading * heading_error * speed_scale;
                    diff = P_term;

                    // Clamp to max differential
                    if (diff >  MAX_DIFF) diff =  MAX_DIFF;
                    if (diff < -MAX_DIFF) diff = -MAX_DIFF;

                    prev_heading_error = heading_error;

                    if (sample_count % 5 == 0) {
                        printf("PDBG: des=%.1f meas=%.1f err=%.1f P=%.2f diff=%.2f spd=%.1f\r\n",
                            desired_heading, measured_heading,
                            heading_error, P_term, diff, desired_speed_modified);
                    }
                }
            }

            // ***** NEW: Flip steering when driving backwards *****
            // This keeps "turn left/right" consistent in world coordinates
            if (desired_speed_modified < -STOP_SPEED_THRESH) {
                diff = -diff;
            }
            // *****************************************************

            // Apply differential to wheel speeds
            float desired_speed_L = desired_speed_modified - diff;
            float desired_speed_R = desired_speed_modified + diff;

            // ========== LEFT WHEEL CONTROL ==========
            if(fabs(desired_speed_L) < 0.1f) {
                pwm_compare_value_L = 0;
                error_sum_L = 0.0f;
                measured_speed_L = 0.0f;
                speed_error_L = 0.0f;
                corrected_speed_L = 0.0f;
            } else {
                if(desired_speed_L > 0) {
                    GPIO_clearPins(GPIOB, GPIO_PIN8);
                } else {
                    GPIO_setPins(GPIOB, GPIO_PIN8);
                }

                if(enc_counts_avg_L > 0 && enc_counts_avg_L < 2000000) {
                    measured_speed_L = ENCODER_CONVERSION_CONSTANT / (float)enc_counts_avg_L;
                } else {
                    measured_speed_L = 0.0f;
                }

                speed_error_L = fabs(desired_speed_L) - measured_speed_L;

                if(fabs(desired_speed_L) > MIN_SPEED_THRESHOLD) {
                    error_sum_L += speed_error_L;
                    if(error_sum_L >  MAX_ERROR_SUM) error_sum_L =  MAX_ERROR_SUM;
                    if(error_sum_L < -MAX_ERROR_SUM) error_sum_L = -MAX_ERROR_SUM;
                } else {
                    error_sum_L = 0.0f;
                }

                corrected_speed_L = fabs(desired_speed_L) + Kp_speed * speed_error_L + Ki_speed * error_sum_L;
                if(corrected_speed_L < 0.0f) corrected_speed_L = 0.0f;

                float left_cal = (fabs(desired_speed_L) < SPEED_TRANSITION_THRESHOLD) ?
                                 LOW_SPEED_LEFT_CAL : HIGH_SPEED_LEFT_CAL;

                pwm_compare_value_L = (uint16_t)((corrected_speed_L / 100.0f) * PWM_PERIOD * left_cal);
                if(pwm_compare_value_L < MIN_PWM_COMPARE) pwm_compare_value_L = MIN_PWM_COMPARE;
                if(pwm_compare_value_L > MAX_PWM_COMPARE) pwm_compare_value_L = MAX_PWM_COMPARE;
            }
            Timers_setCCRValue(TIMG8, TIMER_CCR_CCR1, pwm_compare_value_L);

            // ========== RIGHT WHEEL CONTROL ==========
            if(fabs(desired_speed_R) < 0.1f) {
                pwm_compare_value_R = 0;
                error_sum_R = 0.0f;
                measured_speed_R = 0.0f;
                speed_error_R = 0.0f;
                corrected_speed_R = 0.0f;
            } else {
                if(desired_speed_R > 0) {
                    GPIO_clearPins(GPIOB, GPIO_PIN0);
                } else {
                    GPIO_setPins(GPIOB, GPIO_PIN0);
                }

                if(enc_counts_avg_R > 0 && enc_counts_avg_R < 2000000) {
                    measured_speed_R = ENCODER_CONVERSION_CONSTANT / (float)enc_counts_avg_R;
                } else {
                    measured_speed_R = 0.0f;
                }

                speed_error_R = fabs(desired_speed_R) - measured_speed_R;

                if(fabs(desired_speed_R) > MIN_SPEED_THRESHOLD) {
                    error_sum_R += speed_error_R;
                    if(error_sum_R >  MAX_ERROR_SUM) error_sum_R =  MAX_ERROR_SUM;
                    if(error_sum_R < -MAX_ERROR_SUM) error_sum_R = -MAX_ERROR_SUM;
                } else {
                    error_sum_R = 0.0f;
                }

                corrected_speed_R = fabs(desired_speed_R) + Kp_speed * speed_error_R + Ki_speed * error_sum_R;
                if(corrected_speed_R < 0.0f) corrected_speed_R = 0.0f;

                float right_cal = (fabs(desired_speed_R) < SPEED_TRANSITION_THRESHOLD) ?
                                  LOW_SPEED_RIGHT_CAL : HIGH_SPEED_RIGHT_CAL;

                pwm_compare_value_R = (uint16_t)((corrected_speed_R / 100.0f) * PWM_PERIOD * right_cal);
                if(pwm_compare_value_R < MIN_PWM_COMPARE) pwm_compare_value_R = MIN_PWM_COMPARE;
                if(pwm_compare_value_R > MAX_PWM_COMPARE) pwm_compare_value_R = MAX_PWM_COMPARE;
            }
            Timers_setCCRValue(TIMG8, TIMER_CCR_CCR0, pwm_compare_value_R);

            printf("%u\t%s\t%d\t%d\t%u\t%u\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%u\t%u\r\n",
                   sample_count,
                   use_roll_control ? "ROLL" : "ANGL",
                   pitch, roll, compass_bearing, range_cm,
                   desired_speed_modified, diff,
                   desired_heading, measured_heading, heading_error,
                   desired_speed_L, desired_speed_R,
                   measured_speed_L, measured_speed_R,
                   pwm_compare_value_L, pwm_compare_value_R);
        }
    }
}

// ========== I2C FUNCTIONS ==========
void I2CInit() {
    GPIO_initPeripheralFunction(GPIOA, GPIO_PIN15, GPIO_PA15_PF_I2C1_SCL);
    GPIO_initPeripheralFunction(GPIOA, GPIO_PIN16, GPIO_PA16_PF_I2C1_SDA);
    GPIO_setOpenDrain(GPIOA, GPIO_PIN15 | GPIO_PIN16);

    I2C_ControllerConfig i2cConfig;
    i2cConfig.busclkRate = 32000000;
    i2cConfig.bitRate = 100000;
    i2cConfig.addrMode = I2C_ADDR_MODE_7BIT;

    I2C_initController(I2C1, &i2cConfig);
    delay_cycles(1600000);
}

uint8_t readCMPS12Register(uint8_t reg) {
    uint8_t data = 0;
    uint32_t result = I2C_readData(I2C1, CMPS12_ADDR, reg, &data, 1);
    if(result != 0) return 0;
    return data;
}

uint16_t readCMPS12Bearing() {
    uint8_t bearing_data[2] = {0, 0};
    uint32_t result = I2C_readData(I2C1, CMPS12_ADDR, CMPS12_BEARING_HIGH, bearing_data, 2);
    if(result != 0) return 0;
    return (bearing_data[0] << 8) | bearing_data[1];
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

// ========== GPIO INITIALIZATION ==========
void GPIOInit() {
    GPIO_initDigitalOutput(GPIOB, GPIO_PIN0 | GPIO_PIN8 | GPIO_PIN15 | GPIO_PIN16);
    GPIO_clearPins(GPIOB, GPIO_PIN15 | GPIO_PIN16);
    GPIO_clearPins(GPIOB, GPIO_PIN0 | GPIO_PIN8);

    GPIO_initPeripheralFunction(GPIOB, GPIO_PIN6 | GPIO_PIN7, 5);
    GPIO_initPeripheralFunction(GPIOB, GPIO_PIN10 | GPIO_PIN11, 5);

    GPIO_initDigitalInput(GPIOA, SLIDE_SWITCH_PIN);
    GPIO_setInternalResistor(GPIOA, SLIDE_SWITCH_PIN, GPIO_PULL_UP);
}

// ========== TIMER INITIALIZATION ==========
void timerInit() {
    // PWM Timer (TIMG8)
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

    // Encoder Timer (TIMG6)
    t6cfg.mode = TIMER_MODE_PERIODIC_UP;
    t6cfg.clksrc = TIMER_CLOCK_BUSCLK;
    t6cfg.clkdivratio = TIMER_CLOCK_DIVIDE_1;
    t6cfg.clkprescale = 0;
    t6cfg.period = 65535;
    Timers_initTimer(TIMG6, &t6cfg);

    t6c1cfg.ccrn = TIMER_CCR_CCR0 | TIMER_CCR_CCR1;
    t6c1cfg.edge = TIMER_CCR_EDGE_FALL;
    t6c1cfg.inputSel = TIMER_CCR_INPUT_CCPn;
    t6c1cfg.invertInput = false;
    Timers_initCapture(TIMG6, &t6c1cfg);
    Timers_enableInterrupt(TIMG6, TIMER_INTSRC_ZERO | TIMER_INTSRC_CCR0_UP | TIMER_INTSRC_CCR1_UP);
    NVIC_EnableIRQ(TIMG6_INT_IRQn);
    Timers_startTimer(TIMG6);

    // Control Loop Timer (TIMG0) - 50ms
    t0cfg.mode = TIMER_MODE_PERIODIC_UP;
    t0cfg.clksrc = TIMER_CLOCK_LFCLK;
    t0cfg.clkdivratio = TIMER_CLOCK_DIVIDE_1;
    t0cfg.clkprescale = 0;
    t0cfg.period = 1638;  // 50ms at 32.768 kHz
    Timers_initTimer(TIMG0, &t0cfg);
    Timers_enableInterrupt(TIMG0, TIMER_INTSRC_ZERO);
    NVIC_EnableIRQ(TIMG0_INT_IRQn);
    Timers_startTimer(TIMG0);
}

// ========== ENCODER INTERRUPT HANDLER ==========
void TIMG6_IRQHandler() {
    uint32_t ints = Timers_getPendingInterrupts(TIMG6);

    // Determine current motor directions
    bool left_forward  = (GPIO_readPins(GPIOB, GPIO_PIN8) == 0);
    bool right_forward = (GPIO_readPins(GPIOB, GPIO_PIN0) == 0);

    if(ints & TIMER_INTSRC_ZERO) {
        Timers_clearInterrupt(TIMG6, TIMER_INTSRC_ZERO);
        enc_counts_track_L += 65536;
        if(enc_counts_track_L >= 2000000) {
            enc_counts_track_L = 2000000;
            enc_counts_avg_L = 2000000;
        }
        enc_counts_track_R += 65536;
        if(enc_counts_track_R >= 2000000) {
            enc_counts_track_R = 2000000;
            enc_counts_avg_R = 2000000;
        }
    }

    if(ints & TIMER_INTSRC_CCR0_UP) {
        Timers_clearInterrupt(TIMG6, TIMER_INTSRC_CCR0_UP);

        uint16_t ccr_val = Timers_getCCRValue(TIMG6, TIMER_CCR_CCR0);
        enc_counts_L = enc_counts_track_L + ccr_val;
        enc_counts_track_L = -((int32_t)ccr_val);
        enc_flag_L = 1;
        enc_counts_sum_L += enc_counts_L;
        enc_events_sum_L++;
        if(enc_events_sum_L == 6) {
            enc_counts_avg_L = enc_counts_sum_L / 6;
            enc_events_sum_L = 0;
            enc_counts_sum_L = 0;
        }

        // Track signed events for heading calculation
        if(left_forward) {
            enc_total_events_L++;
            enc_segment_events_L++;
        } else {
            enc_total_events_L--;
            enc_segment_events_L--;
        }
    }

    if(ints & TIMER_INTSRC_CCR1_UP) {
        Timers_clearInterrupt(TIMG6, TIMER_INTSRC_CCR1_UP);

        uint16_t ccr_val = Timers_getCCRValue(TIMG6, TIMER_CCR_CCR1);
        enc_counts_R = enc_counts_track_R + ccr_val;
        enc_counts_track_R = -((int32_t)ccr_val);
        enc_flag_R = 1;
        enc_counts_sum_R += enc_counts_R;
        enc_events_sum_R++;
        if(enc_events_sum_R == 6) {
            enc_counts_avg_R = enc_counts_sum_R / 6;
            enc_events_sum_R = 0;
            enc_counts_sum_R = 0;
        }

        // Track signed events for heading calculation
        if(right_forward) {
            enc_total_events_R++;
            enc_segment_events_R++;
        } else {
            enc_total_events_R--;
            enc_segment_events_R--;
        }
    }
}

// ========== 50ms CONTROL LOOP INTERRUPT ==========
void TIMG0_IRQHandler() {
    Timers_getActiveInterrupt(TIMG0);
    flag_50ms = 1;
}
