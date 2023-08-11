#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x27,16,2);

Servo servo;

const int sPin = 8;
const int fPin = A1;
const int lPin = A0;
const int ledPin = 13;
void setup() {
  servo.attach(sPin);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
}

void loop() {
  Serial.print("Light: ");
  Serial.println(analogRead(lPin));
  if (analogRead(lPin) < 30) {
    lcd.setCursor(0,0);
    lcd.print("No light        ");
    flameCheck();
  }
  else if (analogRead(lPin) > 30 && 100 > analogRead(lPin)) {
    lcd.setCursor(0,0);
    lcd.print("Tiny light      ");
    flameCheck();
  }
  else if (analogRead(lPin) > 100 && 300 > analogRead(lPin)) {
    lcd.setCursor(0,0);
    lcd.print("Small light     ");
    flameCheck();
  }
  else if (analogRead(lPin) >= 300 && 530 > analogRead(lPin)) {
    lcd.setCursor(0,0);
    lcd.print("Medium light    ");
    flameCheck();
  }
  else if (analogRead(lPin) >= 530 && 700 > analogRead(lPin)) {
    lcd.setCursor(0,0);
    lcd.print("Bright light    ");
    flameCheck();
  }
  else if (analogRead(lPin) >= 700) {
    lcd.setCursor(0,0);
    lcd.print("Too bright      ");
    flameCheck();
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Unknown         ");
    digitalWrite(ledPin, LOW);
    flameCheck();
  }
}

void flameCheck() {
  if (analogRead(fPin) > 25 && 100 > analogRead(fPin)) {
    lcd.setCursor(0,1);
    lcd.print("Flame detected! ");
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin ,LOW);
    servo.write(180);
    delay(500);
  }
  else {
    lcd.setCursor(0,1);
    lcd.print("No flame         ");
    digitalWrite(ledPin, LOW);
      servo.write(0);
      delay(500);
  }
}