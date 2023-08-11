#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);
const int sensor = A0;
float value;
float rValue;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  value = analogRead(sensor);
  rValue = (value/1000)-(-0.01)-0.03;
  lcd.setCursor(0,0);
  lcd.print(rValue);
  Serial.println(rValue);
  delay(500);
  if (rValue > 0.13) {
    lcd.setCursor(0,1);
    lcd.print("You have alcohol");
    delay(400);
    lcd.setCursor(0,1);
    lcd.print("                ");
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("You're in troubl");
    delay(300);
    lcd.setCursor(0,1);
    lcd.print("ou're in trouble");
    delay(300);
    lcd.setCursor(0,1);
    lcd.print("u're in trouble!");
  }
  else {
    lcd.setCursor(0,1);
    lcd.print("You're safe     ");
  }
}
