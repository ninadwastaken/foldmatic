#include <Servo.h>


const int resetPin = 13;
int resetState;
// constants for ultrasonics
// 1 = shirt sensor
// 2 = pant sensor

const int trigPin1 = 10;
const int echoPin1 = 11;

long duration1;
int distance1;

const int trigPin2 = 5;
const int echoPin2 = 6;

long duration2;
int distance2;

// constants for motors

const int motorPin1 = 2;
const int motorPin2 = 3;
const int motorPin3 = 4;

Servo servo1;
Servo servo2;
Servo servo3;

// order of motor rotations

int sleevelessFolds[] = {3};
int sleevedFolds[] = {1, 2, 3};
int pantFolds[] = {1, 2};

// other variables

int foldTime = 1000;
int foldAngle = 359;

// const int switchPin = 13;
// const int buzzerPin = 12;

const int maxDistance = 10;

int coveredSensors;
int switch_state;

bool foldFlag = true;




void setup() {
  // starts serial
  // Serial.begin(9600);

  // sets up ultrasonics
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);  
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // sets up servos
  servo1.attach(motorPin1);
  servo2.attach(motorPin2);
  servo3.attach(motorPin3);

  // pinMode(switchPin, INPUT);
  // pinMode(buzzerPin, OUTPUT);

  pinMode(resetPin, INPUT);

}

void loop() {
  resetState = digitalRead(resetPin);
  if (resetState == HIGH) {
    foldFlag = true;
  }

  if (foldFlag == true) {
    coveredSensors = detectSensors();
    rotateMotors(coveredSensors);
  }
}

void rotate(int motor, int degrees) {
  if (motor == 1){
    servo1.write(0);
    servo1.write(degrees);
    delay(1000);
    servo1.write(0);
  }
  else if (motor == 3){
    servo3.write(degrees);
    servo3.write(0);
    delay(1000);
    servo3.write(degrees);
  }
  // else if (motor == 4){
  //   servo4.write(0);
  //   servo4.write(degrees);
  //   delay(1000);
  //   servo4.write(0);
  // }
  else if (motor == 2){
    servo2.write(0);
    servo2.write(degrees);
    delay(1000);
    servo2.write(0);
  }

}

int runUltrasonic(int n) {
  if(n == 1) {
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);

    duration1 = pulseIn(echoPin1, HIGH);
    distance1 = duration1 * 0.034 / 2;

    return distance1;
  }
  if(n == 2) {
    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);

    duration2 = pulseIn(echoPin2, HIGH);
    distance2 = duration2 * 0.034 / 2;

    return distance2;
  }
}

int detectSensors() {
  int sensedDistance1 = runUltrasonic(1);
  int sensedDistance2 = runUltrasonic(2);
  // Serial.println(sensedDistance1);
  // Serial.println(sensedDistance2);

  if (sensedDistance1 <= maxDistance) {
    return 1;
  }
  if (sensedDistance2 <= maxDistance) {
    return 2;
  }
  return 0;
}

void rotateMotors(int n) {
  int l;
  int currMotor;
  if (n == 0) {
    l = sizeof(sleevelessFolds) / sizeof(sleevelessFolds[0]);
    for (int i = 0; i < l; i++) {
      currMotor = sleevelessFolds[i];
      rotate(currMotor, foldAngle);
      delay(2000);
    }
  } 
  else if (n == 1) {
    l = sizeof(sleevedFolds) / sizeof(sleevedFolds[0]);
    for (int i = 0; i < l; i++) {
      currMotor = sleevedFolds[i];
      rotate(currMotor, foldAngle);
      delay(2000);
    }
  }
  else if (n == 2) {
    l = sizeof(pantFolds) / sizeof(pantFolds[0]);
    for (int i = 0; i < l; i++) {
      currMotor = pantFolds[i];
      rotate(currMotor, foldAngle);
      delay(2000);
    }
  }
  foldFlag = false;
}
