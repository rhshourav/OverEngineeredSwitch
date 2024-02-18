#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  // initialize with the I2C addr 0x3D (for the 128x64)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  // Clear the buffer
  display.clearDisplay();
}

void loop() {
  // Generate random relay statuses
  bool relay1Status = HIGH; // 0 or 1
  bool relay2Status = HIGH;
  bool relay3Status = HIGH;
  bool relay4Status = HIGH;
  bool relay5Status = HIGH;

  // Update the display based on the relay status
  display.clearDisplay();
  
  // Draw relay 1 status
  if(relay1Status == HIGH) {
    display.fillCircle(20, 20, 10, SSD1306_WHITE);
  } else {
    display.drawCircle(20, 20, 10, SSD1306_WHITE);
  }
  
  // Draw relay 2 status
  if(relay2Status == HIGH) {
    display.fillCircle(40, 20, 10, SSD1306_WHITE);
  } else {
    display.drawCircle(40, 20, 10, SSD1306_WHITE);
  }
  
  // Draw relay 3 status
  if(relay3Status == HIGH) {
    display.fillCircle(60, 20, 10, SSD1306_WHITE);
  } else {
    display.drawCircle(60, 20, 10, SSD1306_WHITE);
  }
  
  // Draw relay 4 status
  if(relay4Status == HIGH ) {
    display.fillCircle(80, 20, 10, SSD1306_WHITE);
  } else {
    display.drawCircle(80, 20, 10, SSD1306_WHITE);
  }
  
  // Draw relay 5 status
  if(relay5Status == HIGH) {
    display.fillCircle(100, 20, 10, SSD1306_WHITE);
  } else {
    display.drawCircle(100, 20, 10, SSD1306_WHITE);
  }
  
  display.display();

  // You may want to add a delay here to prevent flickering
  delay(1000);
}