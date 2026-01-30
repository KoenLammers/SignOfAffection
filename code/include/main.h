#include <Arduino.h>
#include <SPI.h>
#include "Adafruit_EPD.h"
#include <generated/images_index.h>
#include <stdlib.h>

// Wiring (your current pins)
#define EPD_SCLK_PIN 16
#define EPD_MOSI_PIN 15
#define EPD_MISO_PIN -1
#define EPD_CS        5
#define EPD_DC        6
#define EPD_RESET     7
#define EPD_BUSY      4
#define SRAM_CS      -1

#define WAKEUP_INTERVAL_HOURS 4
#define WAKEUP_INTERVAL_US (WAKEUP_INTERVAL_HOURS * 60 * 60 * 1000000ULL)

void testText();

// tiny subclass to fix xram offset for this panel
class SSD1680_Fixed : public Adafruit_SSD1680 {
public:
  SSD1680_Fixed(int16_t DC, int16_t RST, int16_t CS, int16_t SRCS, int16_t BUSY = -1, SPIClass* spi = &SPI)
    : Adafruit_SSD1680(296, 128, DC, RST, CS, SRCS, BUSY, spi) {}

  void begin(bool reset = true) {
    _xram_offset = 0;                // fix offset to match panel mapping
    Adafruit_SSD1680::begin(reset);
  }
};
