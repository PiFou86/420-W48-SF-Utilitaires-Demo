#pragma once

#ifdef ARDUINO_AVR_UNO
#define SERIAL_SPEED 9600
#elif ESP32
#define SERIAL_SPEED 115200
#endif