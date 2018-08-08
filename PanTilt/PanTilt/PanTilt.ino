#include <Servo.h>

const unsigned long BAUD_RATE = 9600;


// servo
Servo servo_1;
Servo servo_2;
const unsigned int SERVO_PAN  = 1;
const unsigned int SERVO_TILT = 2;
const unsigned int MIN_SERVO_ANGLE = 2;
const unsigned int MAX_SERVO_ANGLE = 125;
const unsigned char MOTOR_PIN_1 = 9;
const unsigned char MOTOR_PIN_2 = 10;


void setup() {
  Serial.begin(BAUD_RATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  servo_1.attach(MOTOR_PIN_1);
  servo_1.write(45);
  servo_2.attach(MOTOR_PIN_2);
  servo_2.write(45);
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
  unsigned int value;

  if (Serial.available()) {
    value = Serial.parseInt();  // reading position value
    c = Serial.read();  // reading in oder to remove the stop sign from serial com buffer

    if (c == 'P') {
      value = writeServo(value, SERVO_PAN);
    } else if (c == 'T') {
      value = writeServo(value, SERVO_TILT);
    } else {
      return;
    }

    /*
       Write back to serial com the two actual
       position of the servo motors (pan and tilts)
    */
    Serial.print(value);
    Serial.print(c); // this is the stop sign

  }

}
