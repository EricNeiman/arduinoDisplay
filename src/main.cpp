#include "Arduino.h"

#include "Wire.h"
#include "Adafruit_BusIO_Register.h"
#include "Adafruit_SSD1306.h"
// This is only if you want to display graphics on the I2C screen
#include "Adafruit_GFX.h"


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

// #define LED_PIN D12

void led() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("LED ON");
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("LED OFF");
  delay(1000);
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin(SDA, SCL);

  // initialize the OLED object
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {aa`a
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();

  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello world!");
  display.display();
}

void loop() {
  led();
}
