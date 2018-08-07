const unsigned long BAUD_RATE = 9600;
unsigned int valueA = 1;
unsigned int valueB = 1;
unsigned int valueTmp;
char cTmp;

void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

}


void serialEvent() {
  if (Serial.available()) {
    valueA = Serial.parseInt();
    valueB = Serial.parseInt();
    delay(10);
    Serial.print(valueA);
    Serial.print('X');
    Serial.print(valueB);
    Serial.print('X');
  }

}

void loop() {

}
