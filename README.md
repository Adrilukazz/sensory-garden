# sensory-garden
## About
These files are from a product design project I did involving use of some electronic components with Arduino! It was hard to work through as it was the first time I ever used Arduino so I'd like to share what I have for anyone doing a similar project as I did.

YouTube video of my product - (soon)

## Hardware & Stuff
Arduino Nano 328P chip (clone) Type-C
0.96-inch OLED Screen Module SSD1306
3.7v 300mA 502035 Lithium-Ion Battery
MFRC-522 Mini RFID Module

## Software & Resources
* Arduino IDE - [Official site for Arduino IDE Software](https://www.arduino.cc/en/software)
* Arduino Library - [RFID Library for MFRC522 by miguelbalboa](https://github.com/miguelbalboa/rfid)
* Arduino Library - [Monochrome Graphics Library for monochrome displays](https://github.com/olikraus/u8g2)
* Image2ccp - [Converting Image to Byte Arrays](https://javl.github.io/image2cpp/)
* (Some) Icon animations - [Icons8 Copyright Free Icons](https://icons8.com/icons/set/popular--animated)

## Tutorials
* Arduino OLED monochrome Tutorial [Arduino & Monochrome Animation Screen Tutorial by upir ](https://www.youtube.com/watch?v=o3PhC_VJdXo)

## Pins & Connections
*Typical pin connections

| RFID          | Screen      | Battery | NANO    | NANO    | NANO    |
|---------------|-------------|---------|---------|---------|---------|
| MFRC522 [1]   | SSD1306 [2] | Li-I [3]|   [1]   |   [2]   |   [3]   |
| GND           | GND         | RED     | GND     | GND     | 5V      |
| RST           | VCC (3V3)   | BLACK   | D9      | 3V3     | GND     |
| (SPI SS) SDA  | SCL         |         | D10     | A5      |         |
| (SPI) MOSI    | SDA         |         | D11     | A4      |         |
| (SPI) MISO    |             |         | D12     |         |         |
| (SPI) SCK     |             |         | D13     |         |         |
| 3V3           |             |         | 3V3     |         |         |

## Functioning
(unfinished)
