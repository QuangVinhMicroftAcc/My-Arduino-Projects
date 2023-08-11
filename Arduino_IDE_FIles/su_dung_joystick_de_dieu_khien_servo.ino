#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2);

const int xStick = A0;
const int yStick = A1;
const int sPin = 6;
Servo as;

int a;
void setup() {
  as.attach(sPin);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  as.write(90);
}
void loop() {
  lcd.setCursor(6,0);
  lcd.print("  ");
  lcd.setCursor(6,1);
  lcd.print("  ");
  lcd.setCursor(0,0);
  lcd.print("X:");
  lcd.setCursor(3,0);
  lcd.print(analogRead(xStick));
  lcd.setCursor(0,1);
  lcd.print("Y:");
  lcd.setCursor(3,1);
  lcd.print(analogRead(yStick));
  a = map(analogRead(yStick), 0, 1023, 0, 180);
  as.write(a);
  delay(100);
}