#include <Arduino.h>
#include <SoftRcPulseOut.h> 

SoftRcPulseOut servoControl1;
SoftRcPulseOut servoControl2;
SoftRcPulseOut servoControl3;
SoftRcPulseOut servoControl4;
SoftRcPulseOut servoControl5;

const int prPin = A3;        // Photoresistor at Arduino analog pin A0
const int prLaunch = 100;    // Value of Photoresistor action

const int servoPin1 = PB1;           // Servo 1
const int servoPin2 = PB2;           // Servo 2
const int servoPin3 = PB3;           // Servo 3
const int servoPin4 = PB4;           // Servo 4
const int servoPin5 = PB5;           // Servo 5
const int servo1DefaultAngle = 60;   // Servo 1 default angle
const int servo2DefaultAngle = 0;    // Servo 2 default angle
const int servo3DefaultAngle = 0;    // Servo 3 default angle
const int servo4DefaultAngle = 0;    // Servo 4 default angle
const int servo5DefaultAngle = 0;    // Servo 5 default angle
const int servo1TargetAngle = 0;     // Servo 1 target angle
const int servo2TargetAngle = 60;    // Servo 2 target angle
const int servo3TargetAngle = 60;    // Servo 3 target angle
const int servo4TargetAngle = 60;    // Servo 4 target angle
const int servo5TargetAngle = 60;    // Servo 5 target angle

int servo1Angle = 0;
int servo2Angle = 0;
int servo3Angle = 0;
int servo4Angle = 0;
int servo5Angle = 0;

const int servoRefresh = 20; // Servo refresh ms
int prValue;				         // Store value from photoresistor (0-1023)

int launchStatus = 1;
bool actionDone = false;

bool inited = false;

void setup() {
  // Photoresistor setup
  pinMode(prPin, INPUT);          // Set PhotoResistor pin

  // Servo setup
  servoControl1.attach(servoPin1);  // Set Servo pin1
  servoControl2.attach(servoPin2);  // Set Servo pin2
  servoControl2.attach(servoPin3);  // Set Servo pin3
  servoControl2.attach(servoPin4);  // Set Servo pin4
  servoControl2.attach(servoPin5);  // Set Servo pin5
}

void loop() {
  if(!inited){
    servo1Angle = servo1DefaultAngle;
    servo2Angle = servo2DefaultAngle;
    servo3Angle = servo3DefaultAngle;
    servo4Angle = servo4DefaultAngle;
    servo5Angle = servo5DefaultAngle;
    inited = true;
  }

  prValue = analogRead(prPin); // Read pResistor

  if (prValue < prLaunch){
    if(!actionDone){
      if(launchStatus == 1){
        servo1Angle = servo1TargetAngle;
      }else if(launchStatus == 2){
        servo2Angle = servo2TargetAngle;
      }else if(launchStatus == 3){
        servo3Angle = servo3TargetAngle;
      }else if(launchStatus == 4){
        servo4Angle = servo4TargetAngle;
      }else if(launchStatus == 5){
        servo5Angle = servo5TargetAngle;
      }
      actionDone = true;
    }
  } else {
    if(actionDone){
      servo1Angle = servo1DefaultAngle;
      servo2Angle = servo2DefaultAngle;
      servo3Angle = servo3DefaultAngle;
      servo4Angle = servo4DefaultAngle;
      servo5Angle = servo5DefaultAngle;

      if(launchStatus == 1){
        launchStatus = 2;
      }else if(launchStatus == 2){
        launchStatus = 3;
      }else if(launchStatus == 3){
        launchStatus = 4;
      }else if(launchStatus == 5){
        launchStatus = 1;
      }
    }
    
    actionDone = false;
  }
  
  servoControl1.write(servo1Angle);   // tell servo1 to go to position in variable 'servoAngle' 
  servoControl2.write(servo2Angle);   // tell servo2 to go to position in variable 'servoAngle' 
  servoControl3.write(servo3Angle);   // tell servo3 to go to position in variable 'servoAngle' 
  servoControl4.write(servo4Angle);   // tell servo4 to go to position in variable 'servoAngle' 
  servoControl5.write(servo5Angle);   // tell servo5 to go to position in variable 'servoAngle' 
  delay(servoRefresh);                // waits 20ms for for refresh period 
  SoftRcPulseOut::refresh(1);         // generates the servo pulse
}