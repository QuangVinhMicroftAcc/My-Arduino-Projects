/*
  This thing could become a kind of Operating System that is homemade :)
  For mode variable:
    0 = NONE
    1 = Menu's start
    2 = Menu's directory choosing
    3 = Menu's Mode choosing
    4 = System information
    5 = Fire checker
    6 = Menu's Utilities choosing
    7 = Gas checker

  For special characters:
    0 = enabled;
    1 = disabled;
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <IRremote.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int hallwayLed = 0;
int ModeDir = 1;
int FireCheck = 1;
int fireState = 0;
int mode = 0;
int GasCheck = 1;
int GasState = 0;
int idle_count = 0;
int livingRoomLed = 0;
const int gasPin = 3;
const int sdPin = 2;
const int firePin = 4;
const int ledPin = 5;
const int readerPin = A0;
const int livingRoomPin = 8;
const int hallwayPin = 9;
const int bedroom1Pin = 11;
const int bedroom2Pin = 7;
const int kitchenPin = 12;
IRrecv remt(readerPin);
decode_results res;

byte enabled[] = {
  B00000,
  B00000,
  B00001,
  B00010,
  B10100,
  B01000,
  B00000,
  B00000
};
byte disabled[] = {
  B00000,
  B00000,
  B10001,
  B01010,
  B00100,
  B01010,
  B10001,
  B00000
};

void setup() {
  pinMode(sdPin, OUTPUT);
  pinMode(kitchenPin, OUTPUT);
  pinMode(bedroom2Pin, OUTPUT);
  pinMode(bedroom1Pin, OUTPUT);
  pinMode(hallwayPin, OUTPUT);
  pinMode(livingRoomPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(firePin, INPUT);
  pinMode(gasPin, INPUT);
  Serial.begin(9600);
  remt.enableIRIn();
  lcd.init();
  lcd.backlight();
  lcd.createChar(0,enabled);
  lcd.createChar(1,disabled);
  lcd.setCursor(1, 0);
  lcd.print("Control Panel");
  lcd.setCursor(1, 1);
  lcd.print("Welcome, user!"); 
  delay(1000);
  lcd.setCursor(0,0);
  lcd.print("+:Navigate up");
  lcd.setCursor(0,1);
  lcd.print("-:Navigate down");
  delay(1000);
  lcd.clear();
  mode = 0;
  FireCheck = 1;
  ModeDir = 1;
  GasCheck = 1;
  GasState = 0;
  idle_count = 0;
  livingRoomLed = 0;
  hallwayLed = 0;
}

void loop() {
  if (remt.decode(&res)) {
    idle_count = 0;
    int val = res.value;  // Nhận giá trị hiện tại
    Serial.println(val);
    remt.resume(); // Nhận giá trị tiếp theo
    if (val == -23971 || val == -11233 || val == 741 || val == 743 || val == -19240) {  // Power (On/Off)
      lcd.setCursor(0, 0);
    }
    if (val == -7651) {  // Menu
      mode = 1;
    }
    if (val == 8925) {  // Test
      lcd.setCursor(0, 0);
    }
    if (val == -15811 || val == 19899) {  // Return
      lcd.setCursor(0, 0);
      if (mode == 1 || mode == 2) {
        lcd.clear();
        mode = 0;
      }
      if (mode == 3 || mode == 6) {
        lcd.clear();
        mode = 2;
      }
      if (mode == 4) {
        lcd.clear();
        mode = 3;
      }
      if (mode == 5) {
        lcd.clear();
        mode = 3;
      }
      if (mode == 7) {
        lcd.clear();
        mode = 3;
      }
    }
    if (val == -22441) {  // Play
      lcd.setCursor(0, 0);
    }
    if (val == 765 || val == 19227) {  // Plus/Increase
      lcd.setCursor(0, 0);
    }
    if (val == 15355 || val == 13551 || val == -26521) {  // Minus/Decrease
      lcd.setCursor(0, 0);
    }
    if (val == -8161 || val == -21065 || val == -8997 || val == -16069) {  // Previous
      lcd.setCursor(0, 0);
    }
    if (val == -28561 || val == -17025 || val == 12413) {  // Next
      lcd.setCursor(0, 0);
    }
    if (val == -20401) {  // Clear
      lcd.setCursor(0, 0);
    }
    if (val == 26775 || val == -6789 || val == -18016) {  // 0
      lcd.setCursor(0, 0);
    }
    if (val == 12495 || val == 4141 || val == -16833) {  // 1
      lcd.setCursor(0, 0);
      if (mode == 0) {
        if (digitalRead(livingRoomPin) == HIGH) {
          lcd.clear();
          lcd.setCursor(2,0);
          lcd.print("Living room");
          lcd.setCursor(1,1);
          lcd.print("light disabled");
          digitalWrite(livingRoomPin, LOW);
          delay(1500);
          lcd.clear();
        }
        else {
          lcd.clear();
          lcd.setCursor(2,0);
          lcd.print("Living room");
          lcd.setCursor(1,1);
          lcd.print("light enabled");
          digitalWrite(livingRoomPin, HIGH);
          delay(1500);
          lcd.clear();
        }
      }
      if (mode == 2) {
        lcd.clear();
        delay(1000);
        mode = 3;
        delay(500);
      }
    }
    if (val == 6375 || val == -7717 || val == 18733) {  // 2 (The button is weird btw)
      lcd.setCursor(0, 0);
      if (mode == 2) {
        lcd.clear();
        delay(1000);
        mode = 6;
      }
      if (mode == 0) {
        lcd.clear();
        if (digitalRead(hallwayPin) == LOW) {
          lcd.setCursor(4,0);
          lcd.print("Hallway");
          lcd.setCursor(1,1);
          lcd.print("light enabled");
          digitalWrite(hallwayPin, HIGH);
        }
        else {
          lcd.setCursor(4,0);
          lcd.print("Hallway");
          lcd.setCursor(1,1);
          lcd.print("light disabled");
          digitalWrite(hallwayPin, LOW);
        }
      }
    }
    if (val == 539 || val == 31365 || val == 18529) {  // 3
      lcd.setCursor(0, 0);
      if (mode == 3) {
        lcd.clear();
        delay(1000);
        mode = 5;
      }
      if (mode == 0) {
        lcd.clear();
        if (digitalRead(bedroom1Pin) == LOW) {
          lcd.setCursor(3,0);
          lcd.print("Bedroom 1");
          lcd.setCursor(1,1);
          lcd.print("light enabled");
          digitalWrite(bedroom1Pin, HIGH);
          delay(1000);
          lcd.clear();
        }
        else {
          lcd.setCursor(3,0);
          lcd.print("Bedroom 1");
          lcd.setCursor(1,1);
          lcd.print("light disabled");
          digitalWrite(bedroom1Pin, LOW);
          delay(1000);
          lcd.clear();
        }
      }
    }
    if (val == 4335 || val == 20221 || val == -18464 || val == 25979 || val == 13692) {  // 4
      lcd.setCursor(0, 0);
      if (mode == 6) {
        if (FireCheck == 1) {
          FireCheck = 0;
        }
        else {
          FireCheck = 1;
        }
      }
      if (mode == 0) {
        lcd.clear();
        if (digitalRead(bedroom2Pin) == LOW) {
          lcd.setCursor(3,0);
          lcd.print("Bedroom 2");
          lcd.setCursor(1,1);
          lcd.print("light enabled");
          digitalWrite(bedroom2Pin, HIGH);
          delay(1000);
          lcd.clear();
        }
        else {
          lcd.setCursor(3,0);
          lcd.print("Bedroom 2");
          lcd.setCursor(1,1);
          lcd.print("light disabled");
          digitalWrite(bedroom2Pin, LOW);
          delay(1000);
          lcd.clear();
        }
      }
    }
    if (val == 14535 || val == 15547 || val == -21948) {  // 5
      lcd.setCursor(0, 0);
      if (mode == 3) {
        lcd.clear();
        delay(1000);
        mode = 4;
      }
      if (mode == 6) {
        if (GasCheck == 1) {
          GasCheck = 0;
        }
        else {
          GasCheck = 1;
        }
      }
      if (mode == 0) {
        lcd.clear();
        if (digitalRead(kitchenPin) == LOW) {
          lcd.setCursor(4,0);
          lcd.print("Kitchen");
          lcd.setCursor(1,1);
          lcd.print("light enabled");
          digitalWrite(kitchenPin, HIGH);
          delay(1000);
          lcd.clear();
        }
        else {
          lcd.setCursor(4,0);
          lcd.print("Kitchen");
          lcd.setCursor(1,1);
          lcd.print("light disabled");
          digitalWrite(kitchenPin, LOW);
          delay(1000);
          lcd.clear();
        }
      }
    }
    if (val == 23205 || val == -6241 || val == 3464) {  // 6
      lcd.setCursor(0, 0);
      if (mode == 3) {
        lcd.clear();
        delay(1000);
        mode = 7;
      }
    }
    if (val == 17085 || val == -521 || val == 2016) {  // 7
      lcd.setCursor(0, 0);
    }
    if (val == 19125 || val == 14509 || val == 5499) {  // 8
      lcd.setCursor(0, 0);
    }
    if (val == 21165 || val == -2774 || val == -997) {  // 9
      lcd.setCursor(0, 0);
    }
  }
  if (FireCheck == 1) {
    if (digitalRead(firePin) == LOW) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(sdPin, HIGH);
      fireState = 1;
      delay(500);
      digitalWrite(ledPin, LOW);
      digitalWrite(sdPin, LOW);
      delay(400);
    }
    if (digitalRead(firePin) == HIGH) {
      digitalWrite(ledPin, LOW);
      digitalWrite(sdPin, LOW);
      fireState = 0;
    }
  }
  if (GasCheck == 1) {
    if (digitalRead(gasPin) == LOW) {
      digitalWrite(ledPin, HIGH);
      digitalWrite(sdPin, HIGH);
      GasState = 1;
      delay(500);
      digitalWrite(ledPin, LOW);
      digitalWrite(sdPin, LOW);
      delay(400);
    }
    else {
      digitalWrite(ledPin, LOW);
      digitalWrite(sdPin, LOW);
      GasState = 0;
    }
  }

  if (mode == 0) {  // Normal screen when nothing is chosen
    lcd.setCursor(0, 0);
    lcd.print("Press nums light");
    lcd.setCursor(0, 1);
    lcd.print("Raining:");
    lcd.setCursor(9, 1);
    lcd.print("NONE");
  }
  if (mode == 1) {  // Menu mode start
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("2 DIR TOTAL");
    delay(1500);
    mode = 2;
  }
  if (mode == 2) {  // Menu mode choosing (directory)
    lcd.setCursor(0, 0);
    lcd.print("1:Mode          ");
    lcd.setCursor(0, 1);
    lcd.print("2:Utilities     ");
  }
  if (mode == 3) {  // Menu mode choosing (mode)
    if (ModeDir == 1) {
      lcd.setCursor(0, 0);
      lcd.print("5:Sysinfo");
      lcd.setCursor(0, 1);
      lcd.print("3:Flame?   6:Gas?");
      delay(500);
    }
    else {
      lcd.setCursor(3,0);
      lcd.print("ModeDir is");
      lcd.setCursor(4,1);
      lcd.print("disabled");
    }
  }
  if (mode == 4) { // System information
    lcd.setCursor(2, 0);
    lcd.print("ARDUINO UNO");
    lcd.setCursor(0, 1);
    lcd.print("OSVersion: 0.1.2");
  }
  if (mode == 5) { // Fire checker
    if (FireCheck == 1) {
      if (fireState == 1) {
        lcd.clear();
        lcd.setCursor(1,0);
        lcd.print("FLAME detected");
      }
      else {
        lcd.clear();
        lcd.setCursor(4,0);
        lcd.print("No flame");
      }
    }
    else {
      lcd.setCursor(1,0);
      lcd.print("FlameCheck is");
      lcd.setCursor(4,1);
      lcd.print("disabled");
    }
  } 
  if (mode == 6) { // Menu mode choosing (Utilities)
    lcd.setCursor(0,0);
    lcd.print("4:FlameCheck ");
    lcd.setCursor(15,0);
    if (FireCheck == 1) {
      lcd.write(0);
    }
    else {
      lcd.write(1);
    }
    lcd.setCursor(0,1);
    lcd.print("5:GasCheck");
    lcd.setCursor(15,1);
    if (GasCheck == 1) {
      lcd.write(0);
    }
    else {
      lcd.write(1);
    }
  }
  if (mode == 7) {
    if (GasCheck == 1) {
      lcd.clear();
      if (GasState == 0) {
        lcd.setCursor(5,0);
        lcd.print("No gas");
      }
      else {
        lcd.setCursor(2,0);
        lcd.print("Gas DETECTED");
      }
    }
    else {
      lcd.setCursor(2,0);
      lcd.print("GasCheck is");
      lcd.setCursor(4,1);
      lcd.print("disabled");
    }
  }

  if (idle_count == 50 && mode != 0) {
    mode = 0;
  }
  idle_count++;
  delay(100);
}