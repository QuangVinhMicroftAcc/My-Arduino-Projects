#include <Ultrasonic.h>

int trigPin = 3;
int echoPin = 2;
Ultrasonic ultrasonic(trigPin, echoPin);
int distance;
int y;
const int tiny = 8;
const int low = 9;
const int med = 10;
const int high = 11;

void setup() {
  Serial.begin(9600);
  pinMode(tiny, OUTPUT);
  pinMode(low, OUTPUT);
  pinMode(med, OUTPUT);
  pinMode(high, OUTPUT);
  digitalWrite(tiny, LOW);
  digitalWrite(low, LOW);
  digitalWrite(med, LOW);
  digitalWrite(high, LOW);
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
  delay(100);
}