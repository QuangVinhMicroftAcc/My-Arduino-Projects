#include <Ultrasonic.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"
LiquidCrystal_I2C lcd(0x27, 16, 2);

int trigPin = 3;
int echoPin = 2;
int sPin = 5;
Ultrasonic ultrasonic(trigPin, echoPin);
Servo aservo;
int distance = 0;
const int IN = 7;
const int TYPE = DHT11;

byte customChar[] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

DHT dht(IN, TYPE);
void setup() {
  dht.begin();
  Serial.begin(9600);
  aservo.attach(sPin);
  aservo.write(0);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar);
  lcd.setCursor(0,0);
  lcd.print("Temperature and");
  lcd.setCursor(4,1);
  lcd.print("Humidity");
  delay(1000);
  lcd.clear();
}

void loop() {
  distance = ultrasonic.read();
  aservo.write(0);
  Serial.println(distance);
  float a = dht.readHumidity();
  float d = dht.readTemperature();

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(6,0);
  lcd.print(d);
  lcd.setCursor(11,0);
  lcd.write(0);
  lcd.setCursor(12, 0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.setCursor(5,1);
  lcd.print(a);
  lcd.setCursor(10,1);
  lcd.print("%");
  if (distance < 30) {
    lcd.clear();
    aservo.write(90);
    lcd.setCursor(0,0);
    lcd.print("Opened bin");
    delay(3000);
    lcd.setCursor(0,0);
    lcd.print("Closed bin");
    aservo.write(0);
    delay(1000);
    lcd.clear();
  }
  delay(100);
}