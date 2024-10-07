**USB Cable Tester MK2**
=====================

![PCB Render](<USB Cable Tester.jpg>)
![PCB in Real Life](DSC05968.JPG)
![PCB Schematic](<USB Cable Tester.svg>)


### Overview

The USB Cable Tester is a simple, battery-powered device for testing USB cables. It utilizes Schottky diodes and a polyfuse for protection, and 0603 green LEDs for indicators.

### Features

* Tests USB cables for continuity
* Battery-powered (CR2032 Coincell)
* Protected by diodes and fuses
* Indicates test results with 0805 LEDs

### Assembly

* Assemble the device according to the provided schematic and PCB layout
* Use a CR2032 Coincell battery for power

### Usage

* Plug the USB cable into one side, then plug the other end into the other side
* The LEDs will indicate if the cable is functioning correctly

### Issues with V2

* Disconnected pins on USB 24-pin Connector (JLCPCB manufacturing defects on 30% of units, some can be fixed through reflowing)