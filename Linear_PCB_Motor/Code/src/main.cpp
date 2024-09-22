#include <Arduino.h>
#include <stm32_usb_hid.h>
#include <quotes.h>

// Create a MediaKeyboard object
MediaKeyboard keyboard;

// Define pin constants for input and output
const int volUpPin = PA0;
const int volDownPin = PA1;
const int muteMicPin = PA2;
const int copyPin = PA3;
const int pastePin = PA4;
const int playPausePin = PA5;
const int ejectPin = PA6;
const int screenShotPin = PA7;
const int ledPin = PC13;

// Enum for key modes
enum keyModes : uint8_t {
	MEDIA,		 // Media key mode
	KEYBOARD,	 // Keyboard key mode
	CTRL_COMBO,	 // Control + key combination mode
	STRING		 // String mode (e.g., for sending a random quote)
};

// Function to get a random quote from the quotes array in quotes.h
char* getRandomQuote() {
	int randomIndex = rand() % (sizeof(quotes) / sizeof(quotes[0]));
	return quotes[randomIndex];
}

void setup() {
	// Set up input pins with pull-up resistors
	pinMode(volUpPin, INPUT_PULLUP);
	pinMode(volDownPin, INPUT_PULLUP);
	pinMode(muteMicPin, INPUT_PULLUP);
	pinMode(copyPin, INPUT_PULLUP);
	pinMode(pastePin, INPUT_PULLUP);
	pinMode(playPausePin, INPUT_PULLUP);
	pinMode(ejectPin, INPUT_PULLUP);
	pinMode(screenShotPin, INPUT_PULLUP);

	// Set up output pin for LED
	pinMode(ledPin, OUTPUT);

	// Initialize the keyboard
	keyboard.begin();
}

// Update key function to handle different key modes
void updateKey(int pin, keyModes mode, int key) {
	if (digitalRead(pin) == LOW) {
		switch (mode) {
			case MEDIA:
				keyboard.mediaPress(key);
				keyboard.mediaRelease();
				break;
			case KEYBOARD:
				keyboard.keyPress(key);
				keyboard.keyRelease();
				break;
			case CTRL_COMBO:
				keyboard.keyPress(KEY_MOD_LCTRL, key);
				keyboard.keyRelease();
				break;
			case STRING:
				keyboard.sendString(getRandomQuote());
				keyboard.keyPress(KEY_ENTER);
				keyboard.keyRelease();
				break;
		}
		delay(200);	 // Repeat delay
	}
}

void loop() {
	// Update keys based on pin states
	updateKey(volUpPin, MEDIA, VOLUME_UP);
	updateKey(volDownPin, MEDIA, VOLUME_DOWN);
	updateKey(muteMicPin, MEDIA, VOLUME_MUTE);
	updateKey(copyPin, CTRL_COMBO, KEY_C);
	updateKey(pastePin, CTRL_COMBO, KEY_V);
	updateKey(playPausePin, MEDIA, MEDIA_PLAY_PAUSE);
	updateKey(ejectPin, STRING, 0);
	updateKey(screenShotPin, KEYBOARD, KEY_SYSRQ);
}
