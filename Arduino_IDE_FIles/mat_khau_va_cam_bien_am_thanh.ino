#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
char str[4] = {' ',' ',' ',' '};
char mk[4] = {'6','6','1','1'};
int l, counter = 0;
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//Create an object of keypad(
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

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
void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  l = 0;
  lcd.setCursor(0,1);
  lcd.print("Password:");
  Serial.begin(9600);
  lcd.createChar(0,speaker);
  lcd.createChar(1,small);
  lcd.createChar(2,med);
  lcd.createChar(3,big);
}
  
void loop(){
  db = map(volume,1024,20,49.5,90);
  char key = keypad.getKey();
  if (key) {
    if (l == 0) {
      str[0] = key;
      lcd.setCursor(10,1);
      lcd.print(key);
      delay(500);
    }
    if (l == 1) {
      str[1] = key;
      lcd.setCursor(11,1);
      lcd.print(key);
      delay(500);
    }
    if (l == 2) {
      str[2] = key;
      lcd.setCursor(12,1);
      lcd.print(key);
      delay(500);
    }
    if (l == 3) {
      str[3] = key;
      lcd.setCursor(13,1);
      lcd.print(key);
      delay(500);
      counter = 1;
    }
    l++;
  }
  else {
    if (counter == 1) {
      if (str[0] == mk[0] && str[1] == mk[1] && str[2] == mk[2] && str[3] == mk[3]) {
        lcd.setCursor(0,1);
        lcd.print("Correct code  ");
      }
      else {
        lcd.setCursor(0,1);
        lcd.print("Incorrect code");
      }
    }
  }
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
