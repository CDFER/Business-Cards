**Linear_PCB_Motor**
================

![PCB Render](<USB Keypad.jpg>)
![PCB in Real Life](<DSC05812.JPG>)
![PCB Schematic](<USB Keypad.svg>)

### Overview

The USB MicroPad is an 8-button macro pad for various applications, from productivity shortcuts to copy and paste macros. It's implemented as a USB HID keyboard and HID media consumer controller, ensuring compatibility with major operating systems without additional drivers.

### Features

* 8 programmable buttons
* USB-C connector
* 3.3V LDO regulator with low dropout voltage
* STM32F103C8T6 microcontroller with 72MHz CPU
* Compatible with most operating systems as a USB HID device

### Specifications

#### STM32 Specifications

* **CPU**: Arm Cortex-M3 @ 72MHz
* **Flash**: 64KB
* **RAM**: 20KB
* **Package**: LQFP-48

#### Components

* **Microcontroller**: STM32F103C8T6
* **LDO Regulator**: XC6206P332MR
* **ESD Protection**: SRV05
* **Fuse**: 1.5A Resettable Fuse
* **USB Connector**: USB-C Receptacle

![Minifig Conversation](<DSC05815.JPG>)

### Issues with V1

* 3V3 LDO pinout incorrect
* Solder beading (causing shorts) on USB 24-pin Connector

### Improvements for V2

* Reduce 3V3 LED brightness (half brightness)
* Use a cheaper USB-C connector
* Consider better buttons
* Remove reset button?

### Assembly and Programming

* Program the STM32 microcontroller using an ST-Link V2