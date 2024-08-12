#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
// Change on line 2862 of Adafruit_NeoPixel.cpp
// uint32_t top = 90;  // 1.25µs
// uint32_t t0 = 79;   // 0.4µs was 62 (62-79)
// uint32_t t1 = 30;   // 0.8µs was 33

const int upButton = PA0;
const int downButton = PA1;
const int tempCoil = PA2;
const int tempMosfet = PA3;
const int neopixelBus = PB0;
const int hotplateGate = PA6;
const int debugLED = PC13;

const unsigned long debounceTime = 250;  // Debounce time in milliseconds

#define NUM_PIXELS 11
#define BRIGHTNESS 16

Adafruit_NeoPixel pixels(NUM_PIXELS, neopixelBus, NEO_GRB + NEO_KHZ800);


float coilTemp = 0;
float mosfetTemp = 0;
float targetTemp = 60.0;

volatile bool upButtonState = false;
volatile bool downButtonState = false;
volatile unsigned long upButtonLastPress = 0;
volatile unsigned long downButtonLastPress = 0;

float readThermistorTemperature(uint32_t thermistorPin) {
    int analogValue = analogRead(thermistorPin);
    float voltage = analogValue * 3.3 / 4095;
    float resistance = voltage * 47000 / (3.3 - voltage);  // Calculate thermistor resistance
    float temperature = 1 / (log(resistance / 47000) / 3950 + 1 / 298.15) - 273.15;
    return temperature;
}

uint32_t black = pixels.Color(0, 0, 0);
uint32_t green = pixels.Color(0, BRIGHTNESS, 0);
uint32_t red = pixels.Color(BRIGHTNESS, 0, 0);
uint32_t endGreen;

void drawTemp(float degC) {
    uint16_t intPosition = (degC / 90) * (10 * BRIGHTNESS);

    pixels.setPixelColor(0, black);

    for (uint16_t i = NUM_PIXELS - 1; i > 0; i--) {
        if (intPosition >= BRIGHTNESS) {
            pixels.setPixelColor(i, green);
            intPosition -= BRIGHTNESS;
        } else if (intPosition > 0) {
            endGreen = pixels.Color(0, intPosition, 0);
            pixels.setPixelColor(i, endGreen);
            intPosition = 0;
        } else {
            pixels.setPixelColor(i, black);
        }
    }
    pixels.show();
}

void drawTargetTemp(float degC) {
    uint16_t intPosition = NUM_PIXELS - ((degC / 90) * (NUM_PIXELS-1));

    pixels.clear();
    pixels.setPixelColor(intPosition, red);
    pixels.show();
}

enum ledStates : uint8_t { STARTUP,
                           TEMP,
                           TARGET,
                           TEMP_TO_TARGET,
                           TARGET_TO_TEMP };

ledStates ledState = STARTUP;
uint8_t stateCounter;

void updateLEDs() {
    switch (ledState) {
        case STARTUP:
            pixels.begin();
            pixels.clear();
            pixels.show();
            ledState = TEMP;
            break;

        case TEMP:
            drawTemp(coilTemp);
            break;

        case TARGET:
            drawTargetTemp(targetTemp);
            stateCounter++;
            if (stateCounter >= 100) {
                ledState = TARGET_TO_TEMP;
            }
            break;

        case TEMP_TO_TARGET:
            stateCounter = 0;
            ledState = TARGET;
            break;

        case TARGET_TO_TEMP:
            ledState = TEMP;
            break;

        default:
            break;
    }
}

void upButtonPressHandler() {
    unsigned long currentTime = millis();
    if (currentTime - upButtonLastPress > debounceTime) {
        upButtonState = true;
        upButtonLastPress = currentTime;
    }
}

void downButtonPressHandler() {
    unsigned long currentTime = millis();
    if (currentTime - downButtonLastPress > debounceTime) {
        downButtonState = true;
        downButtonLastPress = currentTime;
    }
}

void setup() {
    pinMode(debugLED, OUTPUT);
    pinMode(upButton, INPUT);
    pinMode(downButton, INPUT);
    pinMode(tempMosfet, INPUT);
    pinMode(tempCoil, INPUT);
    pinMode(hotplateGate, OUTPUT);
    pinMode(neopixelBus, OUTPUT);

    analogReadResolution(12);

    attachInterrupt(upButton, upButtonPressHandler, RISING);
    attachInterrupt(downButton, downButtonPressHandler, RISING);
}


void loop() {
    if (upButtonState || downButtonState) {
        if (upButtonState && targetTemp < 90.0) {
            targetTemp += 10.0;
        }

        if (downButtonState && targetTemp > 10.0) {
            targetTemp -= 10.0;
        }

        ledState = TEMP_TO_TARGET;
        upButtonState = false;
        downButtonState = false;
    }

    coilTemp = (coilTemp * 0.9) + (0.1 * readThermistorTemperature(tempCoil));
    mosfetTemp = readThermistorTemperature(tempMosfet);

    if (coilTemp < targetTemp && mosfetTemp < 50) {
        digitalWrite(hotplateGate, HIGH);
    } else {
        digitalWrite(hotplateGate, LOW);
    }

    if (mosfetTemp > 50) {
        digitalWrite(debugLED, HIGH);
    } else {
        digitalWrite(debugLED, LOW);
    }

    delay(10);  //for some reason leds can only be updated every 256ms otherwise timing is way off.
    updateLEDs();
}