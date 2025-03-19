#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

const int analogPin = A0; // Analog pin for the sensor
const float VCC = 3.3; // Voltage supplied to the sensor
const float R1 = 4700.0; // Resistance of R1 in ohms
const float R2 = 10000.0; // Resistance of R2 in ohms
const float A = 3.8; // Intercept of linear equation for SPO2
const float B = -19.0; // Slope of linear equation for SPO2

void setup() {
  // Initialize the OLED display with I2C address 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display(); // Display initialization
  
  pinMode(analogPin, INPUT); // Set analog pin as input
}

void loop() {
  float rawValue = analogRead(analogPin); // Read the analog value from the sensor
  float voltage = (rawValue / 1023.0) * VCC; // Convert raw value to voltage
  
  // Calculate SPO2
  float ratio = (R1 * VCC / voltage - R1 - R2) / R2;
  float spo2 = A * ratio + B;
  
  // Display SPO2 value
  display.clearDisplay(); // Clear previous contents
  display.setTextSize(1); // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color
  display.setCursor(0,0); // Set cursor position
  display.print("Blood Oxygen:");
  display.setCursor(0,10);
  display.print(spo2);
  display.print("%");
  display.display(); // Display updated content
  
  delay(1000); // Delay for stability
}
