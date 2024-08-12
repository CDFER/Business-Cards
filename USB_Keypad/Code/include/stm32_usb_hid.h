#include <Arduino.h>
#include "usbd_hid_consumer_if.h"
#include "usb_hid_keys.h"
#include "ascii_to_hid_map.h"

// Check if USB HID is enabled
#if !defined(USBCON) || !defined(USBD_USE_HID_COMPOSITE)
#error "USB HID not enabled"
#else

// Define media key constants
#define VOLUME_UP 0xE9
#define VOLUME_DOWN 0xEA
#define VOLUME_MUTE 0xE2
#define MEDIA_PLAY_PAUSE 0xCD
#define MEDIA_STOP 0xB7
#define MEDIA_NEXT 0xB5
#define MEDIA_PREV 0xB6

// MediaKeyboard class
class MediaKeyboard {
  public:
	// Constructor
	MediaKeyboard(void) {}

	// Initialize the media keyboard
	void begin(void) {
		HID_Composite_Init(HID_CONSUMER);
	}

	// De-initialize the media keyboard
	void end(void) {
		HID_Composite_DeInit(HID_CONSUMER);
	}

	// Send a media key press
	void mediaPress(uint8_t key) {
		uint8_t mediaKeys[3] = { 0x02, key, 0x00 };
		HID_Composite_consumer_sendReport(mediaKeys, 3);
	}

	// Release a media key press
	void mediaRelease() {
		delay(20);
		uint8_t mediaKeys[3] = { 0x00, 0x00, 0x00 };
		HID_Composite_consumer_sendReport(mediaKeys, 3);
	}

	// Send a keyboard key press
	void keyPress(uint8_t key) {
		uint8_t keys[8] = { 0x00, 0x00, key, 0x00, 0x00, 0x00, 0x00, 0x00 };
		HID_Composite_keyboard_sendReport(keys, 8);
	}

	// Send a keyboard key press with modifier
	void keyPress(uint8_t modifier, uint8_t key) {
		uint8_t keys[8] = { modifier, 0x00, key, 0x00, 0x00, 0x00, 0x00, 0x00 };
		HID_Composite_keyboard_sendReport(keys, 8);
	}

	// Release a keyboard key press
	void keyRelease() {
		delay(20);
		uint8_t keysR[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
		HID_Composite_keyboard_sendReport(keysR, 8);
	}

	// Send a single character
	void sendChar(uint8_t c) {
		if (c > 127) return;  // ignore characters above 127
		if (c < 32) return;	  // ignore control characters

		c -= 32;  // offset to ignore the first 32 symbols in ASCII table

		keyPress(ascii_to_hid_key_map[c][0], ascii_to_hid_key_map[c][1]);
		keyRelease();
		delay(20);
	}

	// Send a string of characters
	void sendString(char* str) {
		uint8_t l = strlen(str);
		for (uint8_t i = 0; i < l; i++) {
			sendChar(str[i]);
		}
	}
};
#endif
