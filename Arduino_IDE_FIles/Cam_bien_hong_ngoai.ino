const int sPin = 8;
void setup() {
  Serial.begin(9600);
  pinMode(sPin, INPUT_PULLUP);
}

void loop() {
  Serial.print("Analog: ");
  Serial.println(analogRead(sPin));
  Serial.print("Digital: ");
  Serial.println(digitalRead(sPin));
  delay(100);
}