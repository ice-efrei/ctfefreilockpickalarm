# ctfefreilockpickalarm

## Overview

This Arduino sketch is designed to run a simple game with a timer, input buttons, a reset button, and an audio-visual feedback system. The game's core functionality revolves around a set of buttons that players interact with, a timer displayed on a TM1637 LED display, and a speaker for audio feedback. The game has states like standby, running, success, and game over.

This game is made to be implemented in a lock-picking challenge organized
by CTF EFREI. The lock-picking challenge case is designed and printed by EFREI 3D.

## Hardware Components

- Arduino Board
- TM1637 4-digit 7-segment display
- Push buttons
- Speaker
- Connecting wires

![ctf alarm schema](./images/ctfalarm_bb.png)

## Pin Configuration

- CLK (Clock) pin connected to Digital Pin 3
- DIO (Data Input Output) pin connected to Digital Pin 4
- BTN_RESET (Button Reset) connected to Digital Pin 12
- DEV_LED (Device LED) connected to Digital Pin 3
- Speaker connected to Digital Pin 11
- Game buttons connected to Digital Pins 7, 8, 9, and 10

## Functionality

1. **Setup**: Initializes serial communication, configures pin modes, and sets initial states.

2. **Game States**:
   - `gamereset()`: Resets the game.
   - `startgame()`: Starts the game timer.
   - `gameover()`: Triggers when the game timer expires.
   - `success()`: Triggers when all buttons are pressed correctly.

3. **Display Functions**:
   - `displaytime()`: Updates the timer display during the game.
   - `displaystandby()`: Shows a standby animation on the display when the game is not active.

4. **Loop Logic**:
   - Checks the state of each game button.
   - Manages the game's main states: waiting to start, running, and reset.
   - Triggers respective functions based on button states and timer.

5. **Timing**: Uses the `millis()` function to manage game timing.

6. **Serial Output**: Provides debug information through the serial port.

## How to Use

1. Connect all hardware components as per the pin configuration.
2. Upload the sketch to your Arduino board.
3. Press the reset button to start the game.
4. Interact with the game buttons as per the game logic.
5. Observe the timer on the TM1637 display and listen for audio signals.

## Game logic

Press the reset button (on pin 12) to reset the game when it's running or
to start the game when it's in standby mode. The standby mode is indicated
by a blinking animation on the display. The game starts when the reset button
is pressed. The timer starts counting down from 3 minutes. Within this time,
the player must press all four buttons.

## Conclusion

This sketch demonstrates basic game logic, handling of physical inputs, timing, and audio-visual output on an Arduino platform. It can be expanded or modified for various interactive projects.