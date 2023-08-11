#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int sensorPin = A0;
void setup() {
  Serial.begin(9600);
}
void loop() {
  int reading = analogRead(sensorPin);
  float voltage = reading * (5000 / 1024.0);
  float temperature = voltage / 10;
  Serial.print(temperature);
  Serial.print(" \xC2\xB0");
  Serial.println("C");
  delay(1000);
}