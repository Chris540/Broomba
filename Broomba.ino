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
byte maxCMDist = 40;
long duration1 = 0;
long duration2 = 0;
byte distInCM1 = 0;
byte distInCM2 = 0;
NewPing sonar1(trigger1, echo1, maxCMDist);
NewPing sonar2(trigger2, echo2, maxCMDist);

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
  Serial.println(ultrasonic_test1());
  Serial.print("Ultrasonic Sensor 2:");
  Serial.println(ultrasonic_test2());
  rotateCW(500);
  allStop();
  delay(2000);
}

void moveFoward (){
    analogWrite(motor1Pin1, 180);
    analogWrite(motor1Pin2, 0);
    analogWrite(motor2Pin1, 0);
    analogWrite(motor2Pin2, 180); 
}

void moveBackward (){
    analogWrite(motor1Pin1, 0);
    analogWrite(motor1Pin2, 180);
    analogWrite(motor2Pin1, 180);
    analogWrite(motor2Pin2, 0);
}

void rotateCW (int degree){
    analogWrite(motor1Pin1, 0);
    analogWrite(motor1Pin2, 180);
    analogWrite(motor2Pin1, 0);
    analogWrite(motor2Pin2, 180);
    delay(degree);
}

void rotateCCW (int degree){
    analogWrite(motor1Pin1, 180);
    analogWrite(motor1Pin2, 0);
    analogWrite(motor2Pin1, 180);
    analogWrite(motor2Pin2, 0);
    delay(degree);
}

void allStop(){
    analogWrite(motor1Pin1, 0);
    analogWrite(motor1Pin2, 0);
    analogWrite(motor2Pin1, 0);
    analogWrite(motor2Pin2, 0);
}

void finisher () {
  
}

byte ultrasonic_test1 () {
  return (sonar1.ping_cm());
}

byte ultrasonic_test2 () {
  return (sonar2.ping_cm());
}

