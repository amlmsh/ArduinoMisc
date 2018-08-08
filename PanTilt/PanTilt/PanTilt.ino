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
const unsigned int MAX_SERVO_ANGLE = 125;
const unsigned char MOTOR_PIN_1 = 9;  // PAN
const unsigned char MOTOR_PIN_2 = 10;  // TILT
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


unsigned int writeServo(unsigned int position, int servo) {
  unsigned int targetPosition;

  if (position < MIN_SERVO_ANGLE) {
    targetPosition = MIN_SERVO_ANGLE;
  } else if (position > MAX_SERVO_ANGLE) {
    targetPosition = MAX_SERVO_ANGLE;
  } else {
    targetPosition = position;
  }

  if (servo == SERVO_PAN) {
    servo_1.write(targetPosition);
  } else {
    servo_2.write(targetPosition);
  }

  return targetPosition;

}


void serialEvent() {


}

void loop() {
  char c;


  if (Serial.available()) {
    valueA = Serial.parseInt();
    Serial.read();  // reading in oder to remove the stop sign from serial com buffer
    valueB = Serial.parseInt();
    Serial.read();// reading in order to remove the stop sign from serial com buffer
    delay(10);  // delay of 0.01 sec (might be removed)



    valueA = writeServo(valueA, SERVO_PAN);
    valueB = writeServo(valueB, SERVO_TILT);


    /*
       Write back to serial com the two actual
       position of the servo motors (pan and tilts)
    */
    Serial.print(valueA);
    Serial.print("X"); // this is the stop sign
    Serial.print(valueB);
    Serial.print("X"); // this is the stop sign

  }

}
