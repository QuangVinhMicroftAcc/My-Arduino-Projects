#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int b1 = 10;
const int b2 = 9;
const int b3 = 8;
const int b4 = 7;
const int b_white = 12;
const int blue = 6;
const int green = 4;
const int red = 2;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);
  pinMode(b_white, INPUT_PULLUP);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(red, OUTPUT);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() {
  if (digitalRead(b1) == LOW) {
    lcd.setCursor(0,0);
    lcd.print("BLUE");
    digitalWrite(blue, HIGH);
  }
  else if (digitalRead(b2) == LOW) {
    lcd.setCursor(6,0);
    lcd.print("GREEN");
    digitalWrite(green, HIGH);
  }
  else if (digitalRead(b3) == LOW) {
    lcd.setCursor(13,0);
    lcd.print("RED");
    digitalWrite(red, HIGH);
  }
  else if (digitalRead(b4) == LOW) {
    lcd.clear();
    lcd.home();
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
  }
  else if (digitalRead(b_white) == LOW) {
    lcd.setCursor(0,0);
    lcd.print("BLUE  GREEN  RED");
    lcd.setCursor(6,1);
    lcd.print("WHITE");
    digitalWrite(blue, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(red, HIGH);
  }
}
