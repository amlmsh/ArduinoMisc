
#include <Servo.h>
#include <math.h>

// number of simulation steps
static int nmbSteps;


// global free parameter of the recurrent neural network
static double E;
static double F;
static double P;
static double W;

// activity values of the single neurons
static double a_1;
static double a_2;
static double a_3;
static double o_1;
static double o_2;
static double o_3;

// connectivity values of the recurrent neural network
static double a;
static double b;


// servo
Servo servo_1;
Servo servo_2;
unsigned int servoAngle_1;
unsigned int servoAngle_2;
unsigned int servoAngleTmp_1;
unsigned int servoAngleTmp_2;
const unsigned int MIN_SERVO_ANGLE = 2;
const unsigned int MAX_SERVO_ANGLE = 180;
const unsigned char MOTOR_PIN_1 = 9;
const unsigned char MOTOR_PIN_2 = 10;
const unsigned int  MOTOR_PAUSE = 10;



void setup() {
  // put your setup code here, to run once:

  //Serial.begin(9600);
  servo_1.attach(MOTOR_PIN_1);
  servo_1.write(45);
  servo_2.attach(MOTOR_PIN_2);
  servo_2.write(45);
  delay(MOTOR_PAUSE);

  getCommandLine();
  setConnectivityParameters();
  resetNeuronActivities();

  servoAngle_1 = 45;
}

void loop() {
  // put your main code here, to run repeatedly:
  updateNeuronActivities();

  int c_1, c_2;
  o_1 = sigmoide(a_1);
  o_2 = sigmoide(a_2);
  c_1 = (o_1 * 60) + 20;
  c_2 = (o_2 * 60) + 20;

  /*
  for (int i = 0; i < c_1; i++) {
    Serial.print(" ");
  } Serial.println("*");
  for (int i = 0; i < c_2; i++) {
    Serial.print(" ");
  } Serial.println("#");
  */

  servoAngleTmp_1 = ((o_1 * 100) - 25) * 1.8;
  servoAngle_1 = servoAngleTmp_1;
  if (servoAngle_1 < MIN_SERVO_ANGLE) {
    servoAngle_1 = MIN_SERVO_ANGLE;
  } else if (servoAngle_1 > MAX_SERVO_ANGLE) {
    servoAngle_1 = MAX_SERVO_ANGLE;
  }

  servo_1.write(servoAngle_1);


  servoAngleTmp_2 = ((o_2 * 100) - 25) * 1.8;
  servoAngle_2 = servoAngleTmp_2;
  
  if (servoAngle_2 < MIN_SERVO_ANGLE) {
    servoAngle_2 = MIN_SERVO_ANGLE;
  } else if (servoAngle_2 > MAX_SERVO_ANGLE) {
    servoAngle_2 = MAX_SERVO_ANGLE;
  }

  servo_2.write(servoAngle_2);

  
  delay(MOTOR_PAUSE);


}

void getCommandLine() {
  E = 0.08;
  F = 0.1;
  P = -10.0;
  W = 20.0;
  nmbSteps = 5000;
  return;
}

double sigmoide(double x) {
  double y;
  y = 1.0 / (1 + exp(-x));
  return y;
}

void resetNeuronActivities() {
  a_1 = 0.0002;
  a_2 = 0.003;
  a_3 = 0.001;
}

void setConnectivityParameters() {
  a = (1.0 + E) * 4.0 * cos(F);
  b = (1.0 + E) * 4.0 * sin(F);
}

void updateNeuronActivities() {
  a_1 = a * sigmoide(a_1) + b * sigmoide(a_2) - 0.5 * (a + b);
  a_2 = a * sigmoide(a_2) - b * sigmoide(a_1) + 0.5 * (b - a);
  a_3 = W * sigmoide(a_2) + P;
}




