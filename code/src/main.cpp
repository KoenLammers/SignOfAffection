#include <main.h>
// Init display SSD1680
SSD1680_Fixed display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY, &SPI);

void showRandomImage() {
  if (IMAGE_COUNT == 0) return;
  uint16_t idx = random(IMAGE_COUNT);

  uint16_t w = images[idx].w;
  uint16_t h = images[idx].h;
  // tri-mode now provides two 1bpp masks: black + red
  const uint8_t *black = images[idx].black;
  const uint8_t *red = images[idx].red;

  display.clearBuffer();
  display.drawBitmap(0, 0, black, w, h, EPD_BLACK);
  display.drawBitmap(0, 0, red, w, h, EPD_RED);
  display.display();
}

void setup() {

  // Init usb Serail
  USBSerial.begin();
   vTaskDelay(portTICK_PERIOD_MS / 100);

  // Init SPI
  SPI.begin(EPD_SCLK_PIN, EPD_MISO_PIN, EPD_MOSI_PIN, EPD_CS);

  // Power up the display & wait until its done
  USBSerial.println("Starting display");
  display.begin();
  display.powerUp();

  USBSerial.println("Waiting");
  while (digitalRead(EPD_BUSY) == HIGH){
    vTaskDelay(portTICK_PERIOD_MS / 100);
  }

  // seed random
  randomSeed(micros());
  showRandomImage();

  display.powerDown();


  USBSerial.printf("Going to deep sleep for %d hours...\n", WAKEUP_INTERVAL_HOURS);

  USBSerial.end();

  // Set up timer wake-up
  esp_sleep_enable_timer_wakeup(WAKEUP_INTERVAL_US);

  // Enter deep sleep
  esp_deep_sleep_start();

}

void loop() {

}