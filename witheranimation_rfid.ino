#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Define pins for the RFID reader
#define RST_PIN 9
#define SS_PIN 10

// Initialisation
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE); // initialization for the used OLED display

// 'Frame 1wither', 50x50px
const unsigned char epd_bitmap_Frame_1wither [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x78, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x18, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x30, 
	0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x60, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x00, 
	0x00, 0xc0, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xe0, 
	0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x70, 0x0c, 0x00, 0x00, 0xf0, 0x00, 0x00, 
	0xf8, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x9c, 0x0f, 0x00, 0x00, 0xd0, 0x00, 0xe0, 0xef, 0x07, 
	0x00, 0x00, 0x90, 0x00, 0xf0, 0xe3, 0x03, 0x00, 0x00, 0x98, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 
	0x98, 0x41, 0x18, 0x30, 0x00, 0x00, 0x00, 0x98, 0xc1, 0xcf, 0x1f, 0x00, 0x00, 0x00, 0x18, 0x41, 
	0xe0, 0x0f, 0x00, 0x00, 0x00, 0x18, 0x61, 0x70, 0x00, 0x00, 0x00, 0x00, 0x18, 0xb1, 0x39, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0xf9, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 2wither', 50x50px
const unsigned char epd_bitmap_Frame_2wither [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x78, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x18, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x30, 
	0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x60, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x00, 
	0x00, 0xc0, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0xe0, 
	0x00, 0x00, 0x30, 0x0e, 0x00, 0x00, 0xe0, 0x00, 0x00, 0xf0, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 
	0x98, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x2c, 0x06, 0x00, 0x00, 0xd0, 0x00, 0xe0, 0xe7, 0x03, 
	0x00, 0x00, 0x90, 0x00, 0xe0, 0x23, 0x00, 0x00, 0x00, 0x98, 0x00, 0x30, 0x20, 0x00, 0x00, 0x00, 
	0x98, 0x01, 0x98, 0x30, 0x00, 0x00, 0x00, 0x98, 0xc1, 0x9f, 0x1f, 0x00, 0x00, 0x00, 0x18, 0xc1, 
	0xc7, 0x04, 0x00, 0x00, 0x00, 0x18, 0xc3, 0x60, 0x00, 0x00, 0x00, 0x00, 0x18, 0x42, 0x70, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0x62, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x18, 0xf2, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 3wither', 50x50px
const unsigned char epd_bitmap_Frame_3wither [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x78, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x18, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x30, 
	0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x60, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x00, 
	0x00, 0xc0, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xe0, 
	0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x70, 0x0c, 0x00, 0x00, 0xf0, 0x00, 0x00, 
	0xf8, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x9c, 0x0f, 0x00, 0x00, 0xd0, 0x00, 0xe0, 0xef, 0x07, 
	0x00, 0x00, 0x90, 0x00, 0xf0, 0xe3, 0x03, 0x00, 0x00, 0x98, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 
	0x98, 0x41, 0x18, 0x30, 0x00, 0x00, 0x00, 0x98, 0xc1, 0xcf, 0x1f, 0x00, 0x00, 0x00, 0x18, 0x41, 
	0xe0, 0x0f, 0x00, 0x00, 0x00, 0x18, 0x61, 0x70, 0x00, 0x00, 0x00, 0x00, 0x18, 0xb1, 0x39, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0xf9, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 4wither', 50x50px
const unsigned char epd_bitmap_Frame_4wither [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x1c, 
	0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x38, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0xc0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xe0, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x70, 0x00, 0x00, 
	0x10, 0x03, 0x00, 0x00, 0x70, 0x00, 0x00, 0x38, 0x06, 0x00, 0x00, 0x70, 0x00, 0x00, 0xfc, 0x07, 
	0x00, 0x00, 0x50, 0x00, 0x30, 0x8e, 0x07, 0x00, 0x00, 0x58, 0x00, 0xf0, 0xf3, 0x07, 0x00, 0x00, 
	0xd8, 0x00, 0x18, 0xf0, 0x03, 0x00, 0x00, 0xd8, 0xe0, 0x0f, 0x18, 0x00, 0x00, 0x00, 0x98, 0xe0, 
	0xe7, 0x1c, 0x00, 0x00, 0x00, 0x98, 0x30, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0xd8, 0x18, 0x38, 0x00, 
	0x00, 0x00, 0x00, 0xd8, 0xec, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xd8, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0x98, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 5wither', 50x50px
const unsigned char epd_bitmap_Frame_5wither [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x0f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf0, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x80, 0x03, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x0c, 
	0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x18, 0x00, 0x00, 
	0x00, 0xc0, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 
	0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 
	0xc0, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x70, 0x00, 0x00, 0x18, 0x03, 
	0x00, 0x00, 0x70, 0x00, 0x00, 0x3c, 0x06, 0x00, 0x00, 0x78, 0x00, 0x38, 0xe7, 0x07, 0x00, 0x00, 
	0x78, 0x10, 0xfc, 0x1b, 0x03, 0x00, 0x00, 0x78, 0x70, 0x0e, 0xf8, 0x03, 0x00, 0x00, 0x78, 0xf8, 
	0x33, 0xcc, 0x00, 0x00, 0x00, 0x78, 0x1c, 0x78, 0x0e, 0x00, 0x00, 0x00, 0x78, 0x0e, 0xdc, 0x07, 
	0x00, 0x00, 0x00, 0xf8, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xd8, 0xdf, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 6wither', 50x50px
const unsigned char epd_bitmap_Frame_6wither [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0xf0, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x1c, 
	0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x38, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x30, 0x00, 0x00, 
	0x00, 0xc0, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0xe0, 
	0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x70, 0x00, 0x00, 
	0x10, 0x03, 0x00, 0x00, 0x70, 0x00, 0x00, 0x38, 0x06, 0x00, 0x00, 0x70, 0x00, 0x00, 0xfc, 0x07, 
	0x00, 0x00, 0x50, 0x00, 0x30, 0x8e, 0x07, 0x00, 0x00, 0x58, 0x00, 0xf0, 0xf3, 0x07, 0x00, 0x00, 
	0xd8, 0x00, 0x18, 0xf0, 0x03, 0x00, 0x00, 0xd8, 0xe0, 0x0f, 0x18, 0x00, 0x00, 0x00, 0x98, 0xe0, 
	0xe7, 0x1c, 0x00, 0x00, 0x00, 0x98, 0x30, 0xf0, 0x0f, 0x00, 0x00, 0x00, 0xd8, 0x18, 0x38, 0x00, 
	0x00, 0x00, 0x00, 0xd8, 0xec, 0x0f, 0x00, 0x00, 0x00, 0x00, 0xd8, 0xff, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0x98, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 7wither', 50x50px
const unsigned char epd_bitmap_Frame_7wither [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x7f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x78, 0xc0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x06, 
	0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x18, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x30, 
	0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x60, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0xc0, 0x00, 0x00, 
	0x00, 0xc0, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0xe0, 
	0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x70, 0x0c, 0x00, 0x00, 0xf0, 0x00, 0x00, 
	0xf8, 0x0f, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x9c, 0x0f, 0x00, 0x00, 0xd0, 0x00, 0xe0, 0xef, 0x07, 
	0x00, 0x00, 0x90, 0x00, 0xf0, 0xe3, 0x03, 0x00, 0x00, 0x98, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 
	0x98, 0x41, 0x18, 0x30, 0x00, 0x00, 0x00, 0x98, 0xc1, 0xcf, 0x1f, 0x00, 0x00, 0x00, 0x18, 0x41, 
	0xe0, 0x0f, 0x00, 0x00, 0x00, 0x18, 0x61, 0x70, 0x00, 0x00, 0x00, 0x00, 0x18, 0xb1, 0x39, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0xf9, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 2576)
const int epd_bitmap_allArray_LEN = 7;
const unsigned char* epd_bitmap_allArray[7] = {
	epd_bitmap_Frame_1wither,
	epd_bitmap_Frame_2wither,
	epd_bitmap_Frame_3wither,
	epd_bitmap_Frame_4wither,
	epd_bitmap_Frame_5wither,
	epd_bitmap_Frame_6wither,
	epd_bitmap_Frame_7wither
};

int counter = 0; // counter for the currently displayed frame of the animation

const byte knownCardUIDs[][4] = {
  {0x43, 0x0F, 0x20, 0x2D},
  {0xFE, 0x09, 0xAE, 0x16},
  {0x4E, 0x96, 0x9E, 0x16},
  {0xCE, 0x7C, 0xB3, 0x16},
  {0xCE, 0xA7, 0x9B, 0x16},
};

// Number of known UIDs
const int numKnownCardUIDs = sizeof(knownCardUIDs) / sizeof(knownCardUIDs[0]);

// Function to compare UIDs
bool compareUID(byte* uid, const byte* knownUID) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != knownUID[i]) {
      return false;
    }
  }
  return true;
}

// Function to check if the read UID is known
bool isKnownUID(byte* uid) {
  for (int i = 0; i < numKnownCardUIDs; i++) {
    if (compareUID(uid, knownCardUIDs[i])) {
      return true;
    }
  }
  return false;
}

void setup(void) {
  SPI.begin();
  mfrc522.PCD_Init();
  u8g2.begin(); // start the u8g2 library
}

void loop(void) {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }

  if (isKnownUID(mfrc522.uid.uidByte)) {
      u8g2.setFont(u8g2_font_courB18_tf);
      u8g2.firstPage();
      do {
        u8g2.setCursor(20,35);
        u8g2.print(F("wither"));
      } while (u8g2.nextPage());
      delay(1000);

    // Display animation loop
    unsigned long startTime = millis();
     while (millis() - startTime < 5000) {
       u8g2.clearBuffer();					// clear the internal memory
       u8g2.drawXBMP(39, 7, 50, 50, epd_bitmap_allArray[counter]); // draw frame of the animation
        u8g2.sendBuffer();					// transfer internal memory to the display
	      counter = (counter + 1) % 7; // increase the counter, but always go between 0-27}
      }
    } else {
      u8g2.clearBuffer();
      u8g2.setFont(u8g2_font_courB18_tf);
      u8g2.firstPage();
      do {
        u8g2.setCursor(20,35);
        u8g2.print(F("wrong!"));
      } while (u8g2.nextPage());
      delay(1000);
    }
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
  }