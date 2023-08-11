#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); // or 0x3F
float x = 10.53;
float y = 19.25;
int i, counter = 0;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
int count = 0;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
char str[4] = {' ', ' ', ' ', ' '};
char mk[4] = {'6','6','1','1'};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//Create an object of keypad(
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int buzzer = 13;
void setup(){
  Serial.begin(9600);
  lcd.init();                    
  lcd.backlight();
  pinMode(buzzer, OUTPUT);
}
  
void loop(){
  char key = keypad.getKey();// Read the key
  if(key) {
    lcd.setCursor(0,0);
    lcd.print("Nhap mat khau:");
    if(i == 0) {
      str[0] = key;
      lcd.setCursor(0,1);
      lcd.print(str[0]);
      delay(1000);
    }
    if(i == 1) {
      str[1] = key;
      lcd.setCursor(1,1);
      lcd.print(str[1]);
      delay(1000);
    }
    if(i == 2) {
      str[2] = key;
      lcd.setCursor(2,1);
      lcd.print(str[2]);
      delay(1000);
    }
    if(i == 3) {
      str[3] = key;
      lcd.setCursor(3,1);
      lcd.print(str[3]);
      delay(1000);
      count = 4;
    }
    i++;
  }
  if (count == 4) {
    if(str[0] == mk[0] && str[1] == mk[1] && str[2] == mk[2] && str[3] == mk[3]) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("correct");
      digitalWrite(buzzer, HIGH);
      delay(5000);
      i=0;
      count =0;
      digitalWrite(buzzer, LOW);
    }
    else {
      lcd.clear();
      lcd.setCursor(4,0);
      lcd.print("Incorrect");
      lcd.setCursor(2,1);
      lcd.print("Nhap lai mk");
      delay(1000);
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("Nhap mk");
      count = 0;
      i = 0;
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
  }
    switch(key){
      case 'A':
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tu dang khoa");
        delay(5000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Tu da khoa");
        lcd.setCursor(0,1);
        lcd.print("Cam on 🙂");
        delay(2000);
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("Nhap mk");
        count = 0;
        i = 0;
        digitalWrite(buzzer, HIGH);
        delay(3000);
        digitalWrite(buzzer, LOW);
        delay(3000);
        break;
    }
}