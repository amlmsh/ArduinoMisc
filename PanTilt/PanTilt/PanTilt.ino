#include <Servo.h>

const unsigned long BAUD_RATE = 9600;
unsigned int valueA = 1;
unsigned int valueB = 1;
unsigned int valueTmp;
char cTmp;

// servo
Servo servo_1;
Servo servo_2;
const unsigned int SERVO_PAN  = 1;
const unsigned int SERVO_TILT = 2;
const unsigned int MIN_SERVO_ANGLE = 2;
const unsigned int MAX_SERVO_ANGLE = 180;
const unsigned char MOTOR_PIN_1 = 9;
const unsigned char MOTOR_PIN_2 = 10;
const unsigned int  MOTOR_PAUSE = 10;


void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  servo_1.attach(MOTOR_PIN_1);
  servo_1.write(45);
  servo_2.attach(MOTOR_PIN_2);
  servo_2.write(45);
  delay(MOTOR_PAUSE);
}


void writeServo(unsigned int position, int servo){
  unsigned int targetPosition;

  if (position < MIN_SERVO_ANGLE) {
    targetPosition = MIN_SERVO_ANGLE;
  } else if (position > MAX_SERVO_ANGLE) {
    targetPosition = MAX_SERVO_ANGLE;
  } else{
    targetPosition = position;
  }

  if(servo == SERVO_PAN){
    servo_1.write(targetPosition);
  }else{
    servo_2.write(targetPosition);
  }
}


void serialEvent() {
  char c;

  
  if (Serial.available()) {
    valueA = Serial.parseInt();
    valueB = Serial.parseInt();
    delay(10);

    /*
     * who knows why, but it is essential to read
     * out "out of nowwhere" data in order to 
     * clear the channel
     */
    while(Serial.available() > 0){
      c = Serial.read();
    }
    
    
    Serial.print(valueA);
    Serial.print("X");
    Serial.print(valueB);
    Serial.print("X");

    writeServo(valueA, SERVO_PAN);
    writeServo(valueB, SERVO_TILT);
  }

}

void loop() {

}
