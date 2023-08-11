#include <Ultrasonic.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 3;
const int echoPin = 2;
const int lPin = A0;
const int ledPin = 13;
int distance;

Ultrasonic cbsa(trigPin, echoPin);

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int lights = analogRead(lPin);
  lcd.setCursor(0,0);
  Serial.print("Light: ");
  Serial.println(lights);
  if (lights < 220) {
    distance = cbsa.read();
    Serial.print("Hypersonic: ");
    Serial.println(distance);
    if (distance <= 50) {
      lcd.print("Lights on ");
      digitalWrite(ledPin, HIGH);
    }
    else {
      lcd.print("Lights off");
      digitalWrite(ledPin, LOW);
    }
  }
  else {
    lcd.print("Lights off");
    digitalWrite(ledPin, LOW);
  }
  Serial.println("");
  delay(100);
}