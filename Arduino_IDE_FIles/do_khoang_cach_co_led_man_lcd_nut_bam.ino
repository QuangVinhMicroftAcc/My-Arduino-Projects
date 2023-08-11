#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

int trigPin = 3;
int echoPin = 2;
Ultrasonic ultrasonic(trigPin, echoPin);
int distance;
int y;
const int tiny = 8;
const int low = 9;
const int med = 10;
const int high = 11;
const int bt = 12;

void setup() {
  Serial.begin(9600);
  pinMode(tiny, OUTPUT);
  pinMode(low, OUTPUT);
  pinMode(med, OUTPUT);
  pinMode(high, OUTPUT);
  pinMode(bt, INPUT_PULLUP);
  digitalWrite(tiny, LOW);
  digitalWrite(low, LOW);
  digitalWrite(med, LOW);
  digitalWrite(high, LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Last saved value");
  lcd.setCursor(0,1);
  lcd.print("NONE");
}

void loop() {
  distance = ultrasonic.read();
  y = map(distance, 0, 320, 8, 11);
  digitalWrite(y, HIGH);
  Serial.println(distance);
  switch (y) {
    case 8: {
      digitalWrite(tiny, HIGH);
      digitalWrite(low, LOW);
      digitalWrite(med, LOW);
      digitalWrite(high, LOW);
      break;
    }
    case 9: {
      digitalWrite(tiny, LOW);
      digitalWrite(low, HIGH);
      digitalWrite(med, LOW);
      digitalWrite(high, LOW);
      break;
    }
    case 10: {
      digitalWrite(tiny, LOW);
      digitalWrite(low, LOW);
      digitalWrite(med, HIGH);
      digitalWrite(high, LOW);
      break;
    }
    case 11: {
      digitalWrite(tiny, LOW);
      digitalWrite(low, LOW);
      digitalWrite(med, LOW);
      digitalWrite(high, HIGH);
      break;
    }
  }
  if (digitalRead(bt) == LOW) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Last saved value");
    lcd.setCursor(0,1);
    lcd.print(distance);
  }
  delay(100);
}