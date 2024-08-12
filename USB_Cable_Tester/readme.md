**USB Cable Tester**
=====================================
![PCB Render](<USB Cable Tester.jpg>)
![PCB in Real life](DSC05738.JPG)

### Overview

The USB Cable Tester is a simple, battery-powered device for testing USB cables. It uses a set of Schottky diodes and a polyfuse for protection and 0603 green LEDs as indicators.

### Features

* Tests USB cables for continuity and polarity
* Battery-powered (CR1220 Coincell)
* Protected by diodes and fuses
* Indicates test results with 0603 green LEDs

### Assembly

* Assemble the device according to the provided schematic and PCB layout
* Use a CR1220 Coincell battery for power

### Usage

* Plug the USB Cable in on the left side, then plug the other end on the right side.
* The LEDs will indicate if the cable is functioning correctly

### Issues with V1

* Solder beading (causing shorts) on USB 24-pin Connector

### Improvements for V2

* Add additional test features (e.g. resistance testing)
* Use a more compact PCB design (for short cables)
* Use better LED binning or boost voltage