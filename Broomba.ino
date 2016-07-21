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
unsigned int usTimeout = 5000;

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
  

}
