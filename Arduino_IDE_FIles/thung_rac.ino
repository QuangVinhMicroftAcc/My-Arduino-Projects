#include <Ultrasonic.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int trigPin = 3;
int echoPin = 2;
int sensPin = 7;
int distance = 0;
int sPin = 9;
Ultrasonic us(trigPin, echoPin);
Servo aso;
void setup() {
  pinMode(sensPin, INPUT);
  Serial.begin(9600);
  aso.attach(sPin);
  aso.write(0);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Smart trash bin");
  lcd.setCursor(2,1);
  lcd.print("Fire sensor");
  delay(1500);
  lcd.clear();
}

void loop() {
  distance = us.read();
  aso.write(0);
  Serial.println(distance);

  if (digitalRead(sensPin) == LOW) {
    lcd.setCursor(0,0);
    lcd.print("Flame detected");
    lcd.setCursor(0,1);
    lcd.print("Go find water!");
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("No flame      ");
    lcd.setCursor(0,1);
    lcd.print("Feel safe ;)  ");
  }

  if (distance < 30) {
    lcd.clear();
    aso.write(90);
    lcd.setCursor(0,0);
    lcd.print("Opened bin");
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("Closed bin");
    aso.write(0);
    delay(1000);
    lcd.clear();
  }
  delay(100);
}