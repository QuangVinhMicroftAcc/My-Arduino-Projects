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

void setup(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  l = 0;
  lcd.setCursor(0,0);
  lcd.print("Password:");
}
  
void loop(){
  char key = keypad.getKey();
  if (key) {
    if (l == 0) {
      str[0] = key;
      lcd.setCursor(0,1);
      lcd.print(key);
      delay(500);
    }
    if (l == 1) {
      str[1] = key;
      lcd.setCursor(1,1);
      lcd.print(key);
      delay(500);
    }
    if (l == 2) {
      str[2] = key;
      lcd.setCursor(2,1);
      lcd.print(key);
      delay(500);
    }
    if (l == 3) {
      str[3] = key;
      lcd.setCursor(3,1);
      lcd.print(key);
      delay(500);
      counter = 1;
    }
    l++;
  }
  else {
    if (counter == 1) {
      if (str[0] == mk[0] && str[1] == mk[1] && str[2] == mk[2] && str[3] == mk[3]) {
        lcd.setCursor(0,0);
        lcd.print("Correct code");
        lcd.setCursor(0,1);
        lcd.print("Authorized");
      }
      else {
        lcd.setCursor(0,0);
        lcd.print("Incorrect code");
        lcd.setCursor(0,1);
        lcd.print("Try again!");
      }
    }
  }
}