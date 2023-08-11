#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Arduino pin numbers
const int SW_pin = 2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(SW_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("X:              ");
  lcd.setCursor(3,0);
  lcd.print(analogRead(X_pin));
  lcd.setCursor(0,1);
  lcd.print("Y:              ");
  lcd.setCursor(3,1);
  lcd.print(analogRead(Y_pin));
  delay(100);
}
