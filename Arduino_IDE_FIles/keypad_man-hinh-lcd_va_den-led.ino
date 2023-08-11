#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27,16,2);
Servo servo;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
const int ledPin = 12;
const int ledWPin = 11;
const int servoPin = 10;
const int bPin = 13;
String passcode = "662011BCD";
String passtype;
int numPressed = 0;
int isp = 0;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//Create an object of keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  servo.attach(servoPin);
  servo.write(0);
  pinMode(ledPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("*: Clear all");
  lcd.setCursor(0, 1);
  lcd.print("Type your pass");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Password:");
  lcd.setCursor(0,1);
}
  
void loop(){
  char key = keypad.getKey();// Read the key
  if (key){
    if (key == '*') {
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      passtype = "";
      numPressed = 0;
    }
    else {
      lcd.print(key);
      passtype += key;
      numPressed++;
    }
  }
  if (digitalRead(bPin) == LOW) {
    servo.write(0);
  }
  if (numPressed == passcode.length()) {
    for (int i = 0; i <= passcode.length(); i++) {
      if (passtype[i] == passcode[i]) {
        lcd.clear();
        lcd.home();
        lcd.print("Char ");
        lcd.print(i);
        lcd.println(" OK");
        isp = 0;
      }
      else {
        digitalWrite(ledWPin, HIGH);
        lcd.setCursor(0,0);
        lcd.print("Go away! ");
        lcd.setCursor(0,1);
        lcd.print("Wrong!   ");
        servo.write(0);
        isp = 1;
      }
    }
    if (isp == 0) {
      lcd.clear();
      lcd.home();
      lcd.print("OK");
    }
    else if (isp == 1) {
      lcd.clear();
      lcd.home();
      lcd.print("not OK");
    }
    else {
      lcd.clear();
      lcd.home();
      lcd.print("UNKNOWN");
    }
  }
  delay(100);
}
