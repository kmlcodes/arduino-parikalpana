#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

// OLED oled TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 oled(-1);

void setup() {
  // initialize and clear oled
  oled.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  oled.clearDisplay();
 
}

void loop() {
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.print("Hello, world!");

  // update oled with all of the above graphics
  oled.display();
}
