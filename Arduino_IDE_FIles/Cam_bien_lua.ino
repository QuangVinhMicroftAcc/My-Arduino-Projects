#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int fPin = A0;
const int ledPin = 13;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
  Serial.println(analogRead(fPin));
  if (analogRead(fPin) > 30 && 100 > analogRead(fPin)) {
    lcd.setCursor(0,0);
    lcd.print("Flame detected! ");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin ,LOW);
    delay(500);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("No flame         ");
    digitalWrite(ledPin, LOW);
  }
}