#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int lPin = A0;
const int ledPin = 13;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
  Serial.println(analogRead(lPin));
  if (analogRead(lPin) < 30) {
    lcd.setCursor(0,0);
    lcd.print("No light        ");
  }
  else if (analogRead(lPin) > 30 && 100 > analogRead(lPin)) {
    lcd.setCursor(0,0);
    lcd.print("Tiny light     ");
  }
  else if (analogRead(lPin) > 100 && 300 > analogRead(lPin)) {
    lcd.setCursor(0,0);
    lcd.print("Small light    ");
  }
  else if (analogRead(lPin) >= 300 && 530 > analogRead(lPin)) {
    lcd.setCursor(0,0);
    lcd.print("Medium light   ");
  }
  else if (analogRead(lPin) >= 530 && 700 > analogRead(lPin)) {
    lcd.setCursor(0,0);
    lcd.print("Bright light  ");
  }
  else if (analogRead(lPin) >= 700) {
    lcd.setCursor(0,0);
    lcd.print("Too bright");
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Unknown         ");
    digitalWrite(ledPin, LOW);
  }
}