#include <LiquidCrystal_I2C.h>
#include <Wire.h> //Thư viện giao tiếp I2C
LiquidCrystal_I2C lcd(0x27,16,2);
const int MPU_addr=0x68;  //Địa chỉ I2C của MPU6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ; //Các biến lấy giá trị
const int b1Pin = 2;
const int b2Pin = 3;

void setup()
{
  pinMode(b2Pin, INPUT_PULLUP);
  pinMode(b1Pin, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Tay VR Arduino");
  lcd.setCursor(3,1);
  lcd.print("WELCOME");
  Wire.begin();
  Wire.beginTransmission(MPU_addr); //Gửi tín hiệu đến địa chỉ MPU
  Wire.write(0x6B);  
  Wire.write(0);     //Đưa về 0 để bật MPU
  Wire.endTransmission(true); 
  Serial.begin(9600);
  delay(1500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Doing the job...");
}

void loop()
{
  Wire.beginTransmission(MPU_addr); //Gửi tín hiệu đến địa chỉ MPU
  Wire.write(0x3B);                 //Gửi giá trị lên MPU
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  //Đề nghị thanh ghi của MPU
  
  //Đọc dữ liệu
  AcX=Wire.read()<<8|Wire.read();  //Gia tốc trục x
  AcY=Wire.read()<<8|Wire.read();  //Gia tốc trục y
  AcZ=Wire.read()<<8|Wire.read();  //Gia tốc trục z
  Tmp=Wire.read()<<8|Wire.read();  //Nhiệt độ
  GyX=Wire.read()<<8|Wire.read();  //Góc nghiêng trục x
  GyY=Wire.read()<<8|Wire.read();  //Góc nghiêng trục y
  GyZ=Wire.read()<<8|Wire.read();  //Góc nghiêng trục z
  
  //Xuất ra Serial
  //Serial.print("AcX = "); Serial.print(AcX);
  //Serial.print(" | AcY = "); Serial.print(AcY);
  //Serial.print(" | AcZ = "); Serial.print(AcZ);
  //Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //Tính toán để đổi ra độ C
  Serial.print(AcX);
  Serial.print(" ");
  Serial.print(AcY*-1);
  Serial.print(" ");
  if (digitalRead(b1Pin) == LOW) {
    Serial.print("123");
  }
  else {
    Serial.print("456");
  }
  Serial.print(" ");
  if (digitalRead(b2Pin) == LOW) {
    Serial.println("123");
  }
  else {
    Serial.println("456");
  }
  //Serial.print(" | GyZ = "); Serial.println(GyZ);
  if (AcY > 1500 && AcX <= 3000 && AcX >= -3000) {
    lcd.setCursor(0,0);
    lcd.print("LEFT   ");
  }
  else if (AcY < -1500 && AcX <= 3000 && AcX >= -3000) {
    lcd.setCursor(0,0);
    lcd.print("RIGHT  ");
  }
  else if (AcX <= -3000) {
    lcd.setCursor(0,0);
    lcd.print("FORWARD");
  }
  else if (AcX >= 3000) {
    lcd.setCursor(0,0);
    lcd.print("BACK   ");
  }
  else {
    lcd.clear();
  }
  delay(100);
}