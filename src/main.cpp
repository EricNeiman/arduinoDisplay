#include "Arduino.h"

#include "Wire.h"
#include "Adafruit_BusIO_Register.h"
#include "Adafruit_SSD1306.h"
// This is only if you want to display graphics on the I2C screen
#include "Adafruit_GFX.h"
#include "WiFi.h"
#include "time.h"

// I2C Screen dimensions
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Default I2C pins for Arduino ESP32
// #define SCL A5
// #define SDA A4

// Custom I2C pins for testing
#define SCL D2
#define SDA D3

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Network credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// NTP Server details
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -18000; // EST timezone offset in seconds
const int daylightOffset_sec = 3600; // Change if you have daylight savings

void led() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED ON");
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED OFF");
  delay(1000);
}

void displayTime() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  char timeStr[9];
  sprintf(timeStr, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  display.println(timeStr);
  display.display();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  Wire.begin(SDA, SCL);

  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();

  // Display Text
  display.setTextSize(2);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  display.println("Hello!");
  display.setCursor(0,24);
  display.println("World!");
  display.display();
}

void fullScreenScroll() {
    // Scroll full screen
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println("Full");
  display.println("screen");
  display.println("scrolling!");
  display.display();
  display.startscrollright(0x00, 0x07);
  delay(4000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x07);
  delay(4000);
  display.stopscroll();
  delay(1000);
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  display.clearDisplay();
}

void loopDisplay() {
  fullScreenScroll();
}

void loop() {
  displayTime();
  delay(1000);
  // led();
  // loopDisplay();
}