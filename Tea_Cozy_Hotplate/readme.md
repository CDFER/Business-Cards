**Tea Cozy Hotplate**
=====================================

![PCB Render](<Tea Cozy Hotplate.jpg>)
![alt text](DSC05820.JPG)

### Overview

The Tea Cozy Hotplate is a temperature-controlled hotplate designed to keep your cup of tea at the perfect temperature. It features a compact design, precise temperature control, and a user-friendly interface.

### Features

* Temperature control with ±2°C accuracy
* Compact design fits most tea cups
* User-friendly interface with Adressable LED indicators
* Powered via USB-C connector (5V, 1.4A)
* STM32F103C8T6 microcontroller with 72MHz CPU

### Specifications

#### STM32 Specifications

* **CPU**: Arm Cortex-M3 @ 72Mhz
* **Flash**: 64KB
* **Ram**: 20KB
* **Package**: LQFP-48

#### Components

* **Microcontroller**: STM32F103C8T6
* **LDO Regulator**: XC6206P332MR
* **ESD Protection**: SRV05
* **Fuse**: 2 x 1.5A Resettable Fuses
* **USB Connector**: USB-C Receptacle
* **Heating Element**: ~3.75Ohm Spiral PCB Coil
* **Temperature Sensor**: 47kOhm NTC Thermistor

### Assembly and Programming

* Program the STM32 microcontroller using an ST-Link V2

![alt text](DSC05822.JPG)

### Issues with V1

* 3V3 LDO pinout incorrect

### Improvements for V2

* 3V3 LED is too bright (maybe half brightness)
* Move to cheaper USB-C connector
* Lower Resistance PCB Coil
* Multi-Zone Heater?
* Remove reset button?

![alt text](DSC05823.JPG)

## JLCPCB Heater Coil (1mm PCB with 1oz/ft^2)

Trace: 2.8m length, 0.55mm width, 1oz/ft^2

Calculated resistance = 2.47 Ohm (assuming 0.000017 Ohm.mm)

Real World resistance = 3.75 Ohm (calculated to be 0.0000258 Ohm.mm)