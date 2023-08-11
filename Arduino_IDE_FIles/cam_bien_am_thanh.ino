#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte speaker[] = {
  B00001,
  B00011,
  B00111,
  B11111,
  B11111,
  B00111,
  B00011,
  B00001
};

byte small[] = {
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B00000,
  B00000,
  B00000
};

byte med[] = {
  B00000,
  B01000,
  B00100,
  B10100,
  B10100,
  B00100,
  B01000,
  B00000
};

byte big[] = {
  B00010,
  B01001,
  B00101,
  B10101,
  B10101,
  B00101,
  B01001,
  B00010
};

int db;
int volume = 0;
const int sensorPin = A0;
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0,speaker);
  lcd.createChar(1,small);
  lcd.createChar(2,med);
  lcd.createChar(3,big);
}
void loop() {
  db = map(volume,1024,20,49.5,90);
  lcd.setCursor(0,0);
  volume = analogRead(sensorPin);
  Serial.println(volume);
  delay(100);
  lcd.setCursor(3,0);
  lcd.write(0);
  if (volume >= 1024) {
    lcd.setCursor(4,0);
    lcd.print(" ");
  }
  if (volume >= 1000 && 1024 > volume) {
    lcd.setCursor(4,0);
    lcd.write(1);
  }
  if (volume >= 100 && 1000 > volume) {
    lcd.setCursor(4,0);
    lcd.write(2);
  }
  if (100 > volume) {
    lcd.setCursor(4,0);
    lcd.write(3);
  }
  lcd.setCursor(6,0);
  lcd.print(db);
  lcd.setCursor(8,0);
  lcd.print("dB");
  delay(100);
}