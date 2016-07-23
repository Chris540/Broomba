#include <NewPing.h>

//Broomba Code
//Created July 20, 2016
//Terrible Hacks
// Kenneth Wong, Chris Choi, Nicholas Manna

//digital pins
#define servoPin   3
#define echo1      4
#define trigger1   5
#define motor1Pin1 6
#define echo2      7
#define trigger2   8
#define motor1Pin2 9
#define motor2Pin1 10
#define motor2Pin2 11

//analog pins
#define lightSensor1 14
#define lightSensor2 15

//global variables
//for ultrasonic sensors
unsigned int usTimeout = 5000;
byte maxCMDist = 70; //cm
long duration1 = 0;
long duration2 = 0;
int distInCM1 = 0;
int distInCM2 = 0;
NewPing sonar1(trigger1, echo1, maxCMDist);
NewPing sonar2(trigger2, echo2, maxCMDist);
//flag for anti-stuck
unsigned int stuck = false;

void setup() {
  Serial.begin(9600);
  pinMode(servoPin, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trigger1, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(trigger2, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(lightSensor1, INPUT);
  pinMode(lightSensor2, INPUT);

}

void loop() {
  delay(50);
  Serial.print("Ultrasonic Sensor 1:");
  Serial.println(ultrasonic1());
  Serial.print("Ultrasonic Sensor 2:");
  Serial.println(ultrasonic2());
  trackTarget();
  if (distInCM1 == 0) {
    if (distInCM2 == 0) {
      Serial.println("No Target, Move Forward");
      moveForward(100,0,0,100);
    }
    else {
        Serial.println("Rotate Slow CW");
        rotateCW(0,75,0,75,5);
    }
  }
  else {
    if (distInCM2 == 0) {
        Serial.println("Rotate Slow CCW");
        rotateCCW(75,0,75,0,5);
    }
  }
  if (distInCM1 != 0 && distInCM2 != 0) {
    if (abs(distInCM1 - distInCM2) < 10 && distInCM1 < 40) {
      Serial.println("Target Detected AND CLOSE");
      finisher();
    }
    else if (abs(distInCM1 - distInCM2) < 10){
      Serial.println("Target Detected");
      moveForward(200,0,0,200);
    }
  }
}

//for both forward do m11=180 m12=0, m21=0, m22=180
void moveForward (int m11, int m12, int m21, int m22){
    analogWrite(motor1Pin1, m11);
    analogWrite(motor1Pin2, m12);
    analogWrite(motor2Pin1, m21);
    analogWrite(motor2Pin2, m22);
    stuck = 0; 
}
//for both backward do m11=0 m12=180, m21=180, m22=0
void moveBackward (int m11, int m12, int m21, int m22){
    analogWrite(motor1Pin1, m11);
    analogWrite(motor1Pin2, m12);
    analogWrite(motor2Pin1, m21);
    analogWrite(motor2Pin2, m22); 
    stuck = 0; 
}
//for rotating clockwise do m11=0 m12=180, m21=0, m22=180
void rotateCW (int m11, int m12, int m21, int m22, int degree){
    analogWrite(motor1Pin1, m11);
    analogWrite(motor1Pin2, m12);
    analogWrite(motor2Pin1, m21);
    analogWrite(motor2Pin2, m22); 
    delay(degree);
    stuck++;
    if (stuck > 15){
      moveBackward(0,150,150,0);
      delay(150);
      stuck = 0;
    }
}
//for rotating clockwise do m11=180 m12=0, m21=180, m22=0
void rotateCCW (int m11, int m12, int m21, int m22, int degree){
    analogWrite(motor1Pin1, m11);
    analogWrite(motor1Pin2, m12);
    analogWrite(motor2Pin1, m21);
    analogWrite(motor2Pin2, m22); 
    delay(degree);
    stuck++;
    if (stuck > 15){
      moveBackward(0,150,150,0);
      delay(150);
      stuck = 0;
    }
}

void allStop(){
    analogWrite(motor1Pin1, 0);
    analogWrite(motor1Pin2, 0);
    analogWrite(motor2Pin1, 0);
    analogWrite(motor2Pin2, 0);
}

void finisher () {
  Serial.println("Difference Threshold < 5, full speed ahead");
  moveForward(255,0,0,255);
  delay(400);
  moveBackward(0,150,150,0);
  delay(100); 
}

byte ultrasonic1 () {
  return (sonar1.ping_cm());
}

byte ultrasonic2 () {
  return (sonar2.ping_cm());
}

void trackTarget(){
  distInCM1 = ultrasonic1();
  distInCM2 = ultrasonic2();
}

