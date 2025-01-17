#include <SPI.h>
#include <MFRC522.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Define pins for the RFID reader
#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// 'Frame 1seeds', 50x50px
const unsigned char epd_bitmap_Frame_1seeds [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x0e, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x66, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x70, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x86, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x83, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x06, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 
	0x0c, 0x00, 0x00, 0x00, 0x18, 0x04, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x3f, 0x04, 0x30, 0x18, 0x00, 
	0x00, 0xc0, 0x7f, 0x0c, 0x30, 0x18, 0x00, 0x00, 0xe0, 0x6c, 0x0c, 0x20, 0x10, 0x00, 0x00, 0x30, 
	0xc6, 0x18, 0x20, 0x30, 0x00, 0x00, 0x18, 0xc3, 0x18, 0x60, 0x30, 0x00, 0x00, 0x0c, 0x83, 0x10, 
	0x60, 0x30, 0x00, 0x00, 0x86, 0x81, 0x30, 0x40, 0x30, 0x00, 0x00, 0x83, 0x81, 0x60, 0xc0, 0x10, 
	0x00, 0x00, 0xc3, 0x80, 0x61, 0x80, 0x19, 0x00, 0x80, 0xc1, 0x80, 0xc1, 0x80, 0x1d, 0x00, 0x80, 
	0x60, 0x80, 0x81, 0x03, 0x0f, 0x00, 0xc0, 0x60, 0x80, 0x01, 0x8f, 0x07, 0x00, 0x40, 0x20, 0x80, 
	0x01, 0xfc, 0x01, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 0x00, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 
	0x00, 0x00, 0x20, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x30, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x40, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x60, 0x00, 
	0x00, 0x00, 0x00, 0x20, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x60, 0x18, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0xc0, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0d, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x0f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 2seeds', 50x50px
const unsigned char epd_bitmap_Frame_2seeds [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x3a, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x70, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xc3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x02, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x06, 0x18, 0x18, 0x00, 0x00, 0x00, 0x70, 0x06, 0x30, 0x18, 0x00, 
	0x00, 0x00, 0xfe, 0x0c, 0x30, 0x30, 0x00, 0x00, 0x80, 0xf3, 0x0c, 0x20, 0x30, 0x00, 0x00, 0xe0, 
	0x98, 0x09, 0x60, 0x20, 0x00, 0x00, 0x30, 0x8c, 0x19, 0x60, 0x20, 0x00, 0x00, 0x18, 0x0e, 0x11, 
	0xc0, 0x20, 0x00, 0x00, 0x0c, 0x06, 0x31, 0xc0, 0x20, 0x00, 0x00, 0x06, 0x03, 0x61, 0x80, 0x31, 
	0x00, 0x00, 0x83, 0x01, 0xc1, 0x00, 0x13, 0x00, 0x80, 0xc1, 0x00, 0x81, 0x01, 0x1e, 0x00, 0x80, 
	0xc0, 0x00, 0x01, 0x03, 0x0e, 0x00, 0xc0, 0x60, 0x00, 0x01, 0xfe, 0x07, 0x00, 0x60, 0x60, 0x00, 
	0x01, 0xf8, 0x01, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 0x00, 0x00, 0x20, 0x30, 0x80, 0x01, 0x00, 
	0x00, 0x00, 0x30, 0x30, 0x80, 0x01, 0x00, 0x00, 0x00, 0x30, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x10, 0x10, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x20, 0x00, 
	0x00, 0x00, 0x00, 0x30, 0x0c, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x60, 0x06, 0x1c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 3seeds', 50x50px
const unsigned char epd_bitmap_Frame_3seeds [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x1e, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xc4, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x61, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x06, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x86, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x06, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 
	0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x18, 0x00, 
	0x00, 0x00, 0xfc, 0x0c, 0x30, 0x18, 0x00, 0x00, 0x00, 0xff, 0x09, 0x20, 0x10, 0x00, 0x00, 0xc0, 
	0x61, 0x19, 0x20, 0x10, 0x00, 0x00, 0x70, 0x38, 0x1b, 0x20, 0x30, 0x00, 0x00, 0x38, 0x1c, 0x13, 
	0x60, 0x30, 0x00, 0x00, 0x0c, 0x0c, 0x33, 0x60, 0x30, 0x00, 0x00, 0x06, 0x06, 0x23, 0xc0, 0x10, 
	0x00, 0x00, 0x03, 0x03, 0x63, 0xc0, 0x18, 0x00, 0x80, 0x81, 0x01, 0xc3, 0x80, 0x0d, 0x00, 0xc0, 
	0xc0, 0x00, 0x83, 0x01, 0x0f, 0x00, 0xc0, 0x60, 0x00, 0x03, 0x87, 0x07, 0x00, 0x60, 0x60, 0x00, 
	0x01, 0xfc, 0x01, 0x00, 0x20, 0x30, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30, 0x30, 0x80, 0x01, 0x00, 
	0x00, 0x00, 0x30, 0x10, 0x80, 0x01, 0x00, 0x00, 0x00, 0x10, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x30, 0x00, 
	0x00, 0x00, 0x00, 0x10, 0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x06, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x60, 0x03, 0x0c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x83, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 4seeds', 50x50px
const unsigned char epd_bitmap_Frame_4seeds [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x1f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x78, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xe3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0c, 
	0x0c, 0x00, 0x00, 0x00, 0x10, 0x06, 0x18, 0x18, 0x00, 0x00, 0x00, 0x3f, 0x06, 0x30, 0x18, 0x00, 
	0x00, 0x80, 0x7f, 0x04, 0x30, 0x30, 0x00, 0x00, 0xe0, 0x6c, 0x0c, 0x60, 0x30, 0x00, 0x00, 0x30, 
	0xc6, 0x0c, 0x60, 0x20, 0x00, 0x00, 0x18, 0xc2, 0x18, 0x40, 0x20, 0x00, 0x00, 0x0c, 0x83, 0x10, 
	0xc0, 0x20, 0x00, 0x00, 0x86, 0x81, 0x30, 0x80, 0x21, 0x00, 0x00, 0x83, 0x81, 0x61, 0x80, 0x33, 
	0x00, 0x00, 0xc3, 0x80, 0xc1, 0x00, 0x1f, 0x00, 0x80, 0xc1, 0x80, 0x81, 0x01, 0x1e, 0x00, 0x80, 
	0x60, 0x80, 0x01, 0x07, 0x0e, 0x00, 0xc0, 0x60, 0x80, 0x01, 0xfe, 0x07, 0x00, 0x40, 0x20, 0x80, 
	0x01, 0xf8, 0x01, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 0x00, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 
	0x00, 0x00, 0x20, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x30, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x40, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x60, 0x00, 
	0x00, 0x00, 0x00, 0x20, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x60, 0x18, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0xc0, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0d, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x07, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 5seeds', 50x50px
const unsigned char epd_bitmap_Frame_5seeds [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x80, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x80, 0x79, 0x80, 0x03, 0x00, 0x00, 0x00, 0x80, 
	0xe1, 0x01, 0x07, 0x00, 0x00, 0x00, 0x80, 0x81, 0x07, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0e, 
	0x18, 0x00, 0x00, 0x00, 0x0f, 0x03, 0x18, 0x10, 0x00, 0x00, 0xc0, 0x1f, 0x03, 0x30, 0x30, 0x00, 
	0x00, 0xe0, 0x33, 0x06, 0x20, 0x60, 0x00, 0x00, 0x30, 0x33, 0x06, 0x60, 0x60, 0x00, 0x00, 0x18, 
	0x61, 0x0c, 0xc0, 0x60, 0x00, 0x00, 0x8c, 0x61, 0x18, 0x80, 0x61, 0x00, 0x00, 0x86, 0x40, 0x18, 
	0x80, 0x63, 0x00, 0x00, 0xc2, 0x40, 0x30, 0x00, 0x67, 0x00, 0x00, 0x43, 0xc0, 0x60, 0x00, 0x3c, 
	0x00, 0x80, 0x41, 0xc0, 0xc0, 0x01, 0x38, 0x00, 0x80, 0x61, 0x80, 0x80, 0x03, 0x18, 0x00, 0x80, 
	0x20, 0x80, 0x00, 0x0e, 0x0e, 0x00, 0xc0, 0x20, 0x80, 0x00, 0xf8, 0x03, 0x00, 0x40, 0x30, 0x80, 
	0x00, 0x00, 0x00, 0x00, 0x40, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x80, 0x00, 0x00, 
	0x00, 0x00, 0x60, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x60, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x20, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x60, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x60, 0x20, 0x40, 0x00, 
	0x00, 0x00, 0x00, 0x60, 0x20, 0x60, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0xc0, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0x80, 0x31, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x1f, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x01, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 6seeds', 50x50px
const unsigned char epd_bitmap_Frame_6seeds [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x1f, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x78, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xe3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0c, 
	0x0c, 0x00, 0x00, 0x00, 0x10, 0x06, 0x18, 0x18, 0x00, 0x00, 0x00, 0x3f, 0x06, 0x30, 0x18, 0x00, 
	0x00, 0x80, 0x7f, 0x04, 0x30, 0x30, 0x00, 0x00, 0xe0, 0x6c, 0x0c, 0x60, 0x30, 0x00, 0x00, 0x30, 
	0xc6, 0x0c, 0x60, 0x20, 0x00, 0x00, 0x18, 0xc2, 0x18, 0x40, 0x20, 0x00, 0x00, 0x0c, 0x83, 0x10, 
	0xc0, 0x20, 0x00, 0x00, 0x86, 0x81, 0x30, 0x80, 0x21, 0x00, 0x00, 0x83, 0x81, 0x61, 0x80, 0x33, 
	0x00, 0x00, 0xc3, 0x80, 0xc1, 0x00, 0x1f, 0x00, 0x80, 0xc1, 0x80, 0x81, 0x01, 0x1e, 0x00, 0x80, 
	0x60, 0x80, 0x01, 0x07, 0x0e, 0x00, 0xc0, 0x60, 0x80, 0x01, 0xfe, 0x07, 0x00, 0x40, 0x20, 0x80, 
	0x01, 0xf8, 0x01, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 0x00, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 
	0x00, 0x00, 0x20, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x30, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x40, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x60, 0x00, 
	0x00, 0x00, 0x00, 0x20, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x60, 0x18, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0xc0, 0x08, 0x18, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0d, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x07, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 7seeds', 50x50px
const unsigned char epd_bitmap_Frame_7seeds [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x1e, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xc4, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x61, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x06, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x86, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x06, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 
	0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x30, 0x18, 0x00, 
	0x00, 0x00, 0xfc, 0x0c, 0x30, 0x18, 0x00, 0x00, 0x00, 0xff, 0x09, 0x20, 0x10, 0x00, 0x00, 0xc0, 
	0x61, 0x19, 0x20, 0x10, 0x00, 0x00, 0x70, 0x38, 0x1b, 0x20, 0x30, 0x00, 0x00, 0x38, 0x1c, 0x13, 
	0x60, 0x30, 0x00, 0x00, 0x0c, 0x0c, 0x33, 0x60, 0x30, 0x00, 0x00, 0x06, 0x06, 0x23, 0xc0, 0x10, 
	0x00, 0x00, 0x03, 0x03, 0x63, 0xc0, 0x18, 0x00, 0x80, 0x81, 0x01, 0xc3, 0x80, 0x0d, 0x00, 0xc0, 
	0xc0, 0x00, 0x83, 0x01, 0x0f, 0x00, 0xc0, 0x60, 0x00, 0x03, 0x87, 0x07, 0x00, 0x60, 0x60, 0x00, 
	0x01, 0xfc, 0x01, 0x00, 0x20, 0x30, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30, 0x30, 0x80, 0x01, 0x00, 
	0x00, 0x00, 0x30, 0x10, 0x80, 0x01, 0x00, 0x00, 0x00, 0x10, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x18, 0x08, 
	0x60, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x30, 0x00, 
	0x00, 0x00, 0x00, 0x10, 0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x06, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x60, 0x03, 0x0c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0x06, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x83, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 8seeds', 50x50px
const unsigned char epd_bitmap_Frame_8seeds [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x3a, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x72, 0x70, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xc3, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0x81, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x02, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x06, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 
	0x0c, 0x00, 0x00, 0x00, 0x00, 0x06, 0x18, 0x18, 0x00, 0x00, 0x00, 0x70, 0x06, 0x30, 0x18, 0x00, 
	0x00, 0x00, 0xfe, 0x0c, 0x30, 0x30, 0x00, 0x00, 0x80, 0xf3, 0x0c, 0x20, 0x30, 0x00, 0x00, 0xe0, 
	0x98, 0x09, 0x60, 0x20, 0x00, 0x00, 0x30, 0x8c, 0x19, 0x60, 0x20, 0x00, 0x00, 0x18, 0x0e, 0x11, 
	0xc0, 0x20, 0x00, 0x00, 0x0c, 0x06, 0x31, 0xc0, 0x20, 0x00, 0x00, 0x06, 0x03, 0x61, 0x80, 0x31, 
	0x00, 0x00, 0x83, 0x01, 0xc1, 0x00, 0x13, 0x00, 0x80, 0xc1, 0x00, 0x81, 0x01, 0x1e, 0x00, 0x80, 
	0xc0, 0x00, 0x01, 0x03, 0x0e, 0x00, 0xc0, 0x60, 0x00, 0x01, 0xfe, 0x07, 0x00, 0x60, 0x60, 0x00, 
	0x01, 0xf8, 0x01, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 0x00, 0x00, 0x20, 0x30, 0x80, 0x01, 0x00, 
	0x00, 0x00, 0x30, 0x30, 0x80, 0x01, 0x00, 0x00, 0x00, 0x30, 0x10, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x10, 0x10, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x10, 0x18, 0x60, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x20, 0x00, 
	0x00, 0x00, 0x00, 0x30, 0x0c, 0x30, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0c, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x60, 0x06, 0x1c, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x03, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
// 'Frame 9seeds', 50x50px
const unsigned char epd_bitmap_Frame_9seeds [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x0e, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x66, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x70, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x86, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x83, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x06, 0x0c, 0x06, 0x00, 0x00, 0x00, 0x00, 0x04, 0x18, 
	0x0c, 0x00, 0x00, 0x00, 0x18, 0x04, 0x18, 0x0c, 0x00, 0x00, 0x00, 0x3f, 0x04, 0x30, 0x18, 0x00, 
	0x00, 0xc0, 0x7f, 0x0c, 0x30, 0x18, 0x00, 0x00, 0xe0, 0x6c, 0x0c, 0x20, 0x10, 0x00, 0x00, 0x30, 
	0xc6, 0x18, 0x20, 0x30, 0x00, 0x00, 0x18, 0xc3, 0x18, 0x60, 0x30, 0x00, 0x00, 0x0c, 0x83, 0x10, 
	0x60, 0x30, 0x00, 0x00, 0x86, 0x81, 0x30, 0x40, 0x30, 0x00, 0x00, 0x83, 0x81, 0x60, 0xc0, 0x10, 
	0x00, 0x00, 0xc3, 0x80, 0x61, 0x80, 0x19, 0x00, 0x80, 0xc1, 0x80, 0xc1, 0x80, 0x1d, 0x00, 0x80, 
	0x60, 0x80, 0x81, 0x03, 0x0f, 0x00, 0xc0, 0x60, 0x80, 0x01, 0x8f, 0x07, 0x00, 0x40, 0x20, 0x80, 
	0x01, 0xfc, 0x01, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 0x00, 0x00, 0x60, 0x30, 0x80, 0x01, 0x00, 
	0x00, 0x00, 0x20, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x80, 0x00, 0x00, 0x00, 0x00, 
	0x30, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x40, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x60, 0x00, 
	0x00, 0x00, 0x00, 0x20, 0x10, 0x20, 0x00, 0x00, 0x00, 0x00, 0x60, 0x18, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0xc0, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x0d, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x80, 
	0x0f, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 3312)
const int epd_bitmap_allArray_LEN = 9;
const unsigned char* epd_bitmap_allArray[9] = {
	epd_bitmap_Frame_1seeds,
	epd_bitmap_Frame_2seeds,
	epd_bitmap_Frame_3seeds,
	epd_bitmap_Frame_4seeds,
	epd_bitmap_Frame_5seeds,
	epd_bitmap_Frame_6seeds,
	epd_bitmap_Frame_7seeds,
	epd_bitmap_Frame_8seeds,
	epd_bitmap_Frame_9seeds
};

int counter = 0; // counter for the currently displayed frame of the animation

const byte knownCardUIDs[][4] = {
  {0x43, 0x43, 0xDB, 0x0C},
  {0x9E, 0xBF, 0x32, 0x1F},
  {0xBE, 0x40, 0x98, 0x16},
  {0x5E, 0x76, 0xA1, 0x16},
  {0x2E, 0x0E, 0x41, 0x1F},
};

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

  // Verify if the card UID matches the known card UID
  if (isKnownUID(mfrc522.uid.uidByte)) {
      u8g2.setFont(u8g2_font_courB18_tf);
      u8g2.firstPage();
      do {
        u8g2.setCursor(32,35);
        u8g2.print(F("seed"));
      } while (u8g2.nextPage());
      delay(1000);

    // Display animation loop
    unsigned long startTime = millis();
     while (millis() - startTime < 5000) {
       u8g2.clearBuffer();					// clear the internal memory
       u8g2.drawXBMP(39, 7, 50, 50, epd_bitmap_allArray[counter]); // draw frame of the animation
        u8g2.sendBuffer();					// transfer internal memory to the display
	      counter = (counter + 1) % 9; // increase the counter, but always go between 0-27
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
  