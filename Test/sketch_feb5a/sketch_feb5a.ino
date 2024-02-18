#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <time.h>

// WiFi credentials
char ssid[] = "****";
char pass[] = "******";
//Initing Display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
// Define NTP client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "bd.pool.ntp.org");  // NTP server in Bangladesh

// Define OLED display
//SSD1306Wire display(0x3c, SDA, SCL);

unsigned long lastDisplayTime = 0;
const unsigned long displayInterval = 1000;//300000;  // 5 minutes in milliseconds
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


String getCurrentTime() {
  // Get current time in 12-hour format
  int h = timeClient.getHours();
  int m = timeClient.getMinutes();
  String period = (h < 12) ? "AM" : "PM";
  if (h == 0) {
    h = 12;  // 12 AM
  } else if (h > 12) {
    h = h - 12;
  }
  String timeString = String(h) + ":" + (m < 10 ? "0" : "") + String(m);
  return timeString;
}

String getCurrentSeconds() {
  // Get current seconds
  int s = timeClient.getSeconds();
  return (s < 10 ? "0" : "") + String(s);
}

String getCurrentPeriod() {
  // Get current AM/PM period
  int h = timeClient.getHours();
  return (h < 12) ? "AM" : "PM";
}
String getCurrentDate() {
  // Get current epoch time
  unsigned long epochTime = timeClient.getEpochTime();

  // Convert epoch time to struct tm
  struct tm *timeInfo;
  time_t rawtime = (time_t)epochTime;
  timeInfo = localtime(&rawtime);

  // Format the date
  char formattedDate[20];
  strftime(formattedDate, 20, "%Y-%m-%d", timeInfo);

  return String(formattedDate);
}
void setup() {
  // Connect to WiFi
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }

  // Initialize OLED display
//  display.init();
   display.display();
  delay(2000);  // Pause for 2 seconds

  // Get current time from NTP server
  timeClient.begin();
  timeClient.setTimeOffset(21600);   // GMT+6:00 for Bangladesh Standard Time
  timeClient.update();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastDisplayTime >= displayInterval) {
    lastDisplayTime = currentMillis;
// Display current time and date on OLED
    display.clearDisplay();
    display.fillScreen(SSD1306_BLACK); // Fill the display with black color
    display.setTextSize(3);
    display.setTextColor(SSD1306_WHITE);
    int16_t x1, y1;
    uint16_t w, h;
    display.getTextBounds(getCurrentTime(), 0, 0, &x1, &y1, &w, &h);
    display.setCursor((SCREEN_WIDTH - w) / 2, 5);
    display.println(getCurrentTime());
    display.setTextSize(2);
    display.getTextBounds(getCurrentTime(), 0, 0, &x1, &y1, &w, &h);
    display.setCursor((SCREEN_WIDTH - w) / 2, 30);
    display.println(getCurrentSeconds() + " " + getCurrentPeriod());
    display.setTextSize(2);
    display.getTextBounds(getCurrentDate(), 0, 0, &x1, &y1, &w, &h);
    display.setCursor((SCREEN_WIDTH - w) / 2, 50);
    display.println(getCurrentDate());
    display.display();

  // Other code running here
}}
