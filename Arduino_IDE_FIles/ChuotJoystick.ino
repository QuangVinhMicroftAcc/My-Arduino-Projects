// MAX 960
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int xStick = A0;
const int yStick = A1;
const int xStick2 = A6;
const int yStick2 = A7;
const int bPin = 3;
const int switchPin = 6;
float xo = 0;
float yo = 0;

int a;
void setup() {
  Serial.print("ANC_102");
  pinMode(bPin, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  Serial.begin(74880);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,1);
  lcd.print("LOADING...");
  delay(5);
  lcd.clear();
}
void loop() {
  lcd.setCursor(6,0);
  lcd.print(" ");
  lcd.setCursor(6,1);
  lcd.print(" ");
  lcd.setCursor(13,0);
  lcd.print(" ");
  lcd.setCursor(13,1);
  lcd.print(" ");
  lcd.setCursor(0,0);
  lcd.print("X:");
  lcd.setCursor(3,0);
  lcd.print(analogRead(xStick));
  lcd.setCursor(0,1);
  lcd.print("Y:");
  lcd.setCursor(3,1);
  lcd.print(analogRead(yStick));
  a = map(analogRead(yStick), 0, 1023, 0, 180);
  xo = analogRead(xStick) / 10;
  yo = analogRead(yStick) / 10;
  xo = xo - 49.3;
  yo = yo - 48.4;
  lcd.setCursor(7,0);
  lcd.print("X:");
  lcd.setCursor(10,0);
  lcd.print(analogRead(xStick2));
  lcd.setCursor(7,1);
  lcd.print("Y:");
  lcd.setCursor(10,1);
  lcd.print(analogRead(yStick2));
  Serial.print(analogRead(xStick));
  Serial.print(" ");
  Serial.print(analogRead(yStick));
  Serial.print(" ");
  if (digitalRead(bPin) == LOW) {
    Serial.print(123);
  }
  else {
    Serial.print(456);
  }
  Serial.print(" ");
  Serial.print(analogRead(xStick2));
  Serial.print(" ");
  Serial.print(analogRead(yStick2));
  Serial.print(" ");
  if (digitalRead(switchPin) == LOW) {
    Serial.println(123);
  }
  else {
    Serial.println(456);
  } 
}