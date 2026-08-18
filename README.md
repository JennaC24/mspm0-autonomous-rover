# mspm0-autonomous-rover
Autonomous maze-navigating robot built on the TI MSPM0G3507, with closed-loop PID motor control and gesture-based driving.

(Insert image of car here)

## Table of Contents
[The Problem](#The-Problem)\
[What I Built](#What-I-Built)\
[Control Modes](#Control-Modes)\
[System Design](#System-Design)\
[Hardware & Tools Used](#Hardware-&-Tools-Used)\
[How To Build & Run](#How-To-Build-&-Run)\
[Project Structure](#Project-Structure)\
[Results](#Results)\
[Challenges & What I Learned](#Challenges-&-What-I-Learned)\
[References](#References)\
[About Me](#About-Me)

## The Problem
Navigating an unknown maze environment without a pre-programmed route requires a robot to make real-time decisions using only onboard sensors — detecting obstacles, deciding which way to turn, and recognizing when it's stuck, all without any map or human input.

## What I Built
A robotic car with two operating modes: a manually-driven mode where a hand-held sensor board controls speed and steering through gesture (tilt), and a fully autonomous mode where the car navigates unknown maze environments on its own using ultrasonic sensing, physical bumpers, and a zig-zag wall-following strategy with stuck-corner detection.

## Control Modes
- Pitch --> Speed (shared across manual modes)
- Roll-based Turning (direct differential steering)
- Angle-based Turning (closed-loop heading control via encoders + P controller)
- Autonomous Navigation (ultrasonic + bumper-triggered zig-zag turning, with compass-health fallback and stuck-in-corner 180° recovery)

## System Design
[Insert I2C Schematic here] The CMPS12 compass and SRF08 ultrasonic ranger share a single I2C bus, with pull-up resistors on SDA/SCL. Six mechanical bumper switches provide a redundant, contact-based backup to ultrasonic obstacle detection. [Insert block diagram: Sensors → MSPM0G3507 → State Machine → PWM → Motors]

## Hardware  & Tools Used
- TI LP-MSPM0G3507 LaunchPad
- RPI-RSLK robotic car platform
- CMPS12 electronic compass (I2C)
- SRF08 ultrasonic ranger (I2C)
- 6x mechanical bumper switches
- Wheel encoders (quadrature)

[Insert your GPIO pin table here]\
Language: C. Toolchain: Code Composer Studio
### Hardware Setup for Gesture Based and Pitch/Roll Based Control
(not pictured is the handheld breadboard that utilizes a compass to control the car)\
<p align="center">
  <img src="Images/gesture-based-hardware.jpeg" alt="Gesture Based Hardware" width="500">
</p>

### Hardware Setup for Autonomous Navigation
<p align="center">
  <img src="Images/autonomous-hardware.jpeg" alt="Autonomous Hardware" width="500">
</p>

## How to Build & Run

## Project Structure

## Results

## Challenges & What I Learned
Talk about challenge regarding the car overturning during autonomous navigation and have to add a stop between each turn to prevent it. 

## References
Add the compass and the ranger datasheet
## About Me
Linkedin:\
Personal Email: jconnel24@gmail.com
Phone Number:
