#include <Servo.h>

// constants for ultrasonics
// 1 = shirt sensor
// 2 = pant sensor

const int trigPin1 = 9;
const int echoPin1 = 10;

long duration1;
long distance1;

const int trigPin2 = 5;
const int echoPin2 = 6;

long duration2;
long distance2;

// constants for motors

const int motorPin1 = 1;
const int motorPin2 = 2;
const int motorPin3 = 3;
const int motorPin4 = 4;
const int motorPin5 = 7;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;

// order of motor rotations

int sleevelessFolds[] = {1, 2, 3};
int sleevedFolds[] = {3, 4, 5};
int pantFolds[] = {2, 3, 4};

// other variables

int foldTime = 100;
int foldAngle = 150;

const int switchPin = 13;
const int buzzerPin = 12;

const int maxDistance = 10;

int coveredSensors;
int switch_state;

bool foldFlag = true;




void setup() {
  // starts serial
  Serial.begin(9600);

  // sets up ultrasonics
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);  
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // sets up servos
  servo1.attach(motorPin1);
  servo2.attach(motorPin2);
  servo3.attach(motorPin3);
  servo4.attach(motorPin4);
  servo5.attach(motorPin5);

  pinMode(switchPin, INPUT);
  pinMode(buzzerPin, OUTPUT);

}

void loop() {
  switch_state = digitalRead(switchPin);
  if (switch_state == HIGH) {
    coveredSensors = detectSensors();

  } 
  
}

void rotate(int motor, int degrees, int time) {
  int skip = time / degrees;

  for (int pos = 0; pos <= degrees; pos += 1) {
    if (motor == 1) {
      servo1.write(pos);
    }
    else if (motor == 2) {
      servo2.write(pos);
    }
    else if (motor == 3) {
      servo3.write(pos);
    }
    else if (motor == 4) {
      servo4.write(pos);
    }
    else if (motor == 5) {
      servo5.write(pos);

    delay(skip);
    }
  }
}

long runUltrasonic(int n) {
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
  long sensedDistance1 = runUltrasonic(1);
  long sensedDistance2 = runUltrasonic(2);
  int ans = 0;

  if (sensedDistance1 <= maxDistance) {
    ans += 1;
  }
  if (sensedDistance2 <= maxDistance) {
    ans += 2;
  }
  return ans;
}

void rotateMotors(int n) {
  int l;
  int currMotor;
  if (n == 0) {
    l = sizeof(sleevelessFolds) / sizeof(sleevelessFolds[0]);
    for (int i = 0; i < l; i++) {
      currMotor = sleevelessFolds[i];
      rotate(currMotor, foldAngle, foldTime);
    }
  } 
  else if (n == 1) {
    l = sizeof(sleevedFolds) / sizeof(sleevedFolds[0]);
    for (int i = 0; i < l; i++) {
      currMotor = sleevedFolds[i];
      rotate(currMotor, foldAngle, foldTime);
    }
  }
  else if (n == 2) {
    l = sizeof(pantFolds) / sizeof(pantFolds[i]);
    for (int i = 0; i < l; i++) {
      currMotor = pantFolds[i];
      rotate(currMotor, foldAngle, foldTime);
    }
  }
}
