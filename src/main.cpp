#include <Arduino.h>
#include <SoftRcPulseOut.h> 

SoftRcPulseOut servoControl1;
SoftRcPulseOut servoControl2;

const int servoPin1 = PB2;           // Servo at Arduino digital
const int servoPin2 = PB4;           // Servo at Arduino digital
const int servoDefaultAngle = 0;  // Servo default angle
const int servoTargetAngle = 70;  // Servo target angle
int servo1Angle = 0;
int servo2Angle = 0;
const int servoDelay = 500;       // Servo delay time in ms
const int servoRefresh = 20;      // Servo refresh ms


const int prPin = A3;       // Photoresistor at Arduino analog pin A0
int prValue;				        // Store value from photoresistor (0-1023)
const int prLaunch = 700;   // Value of Photoresistor action

int launchStatus = 1;
bool actionDone = false;

void setup() {
  // Photoresistor setup
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

  pinMode(prPin, INPUT);          // Set PhotoResistor pin
  servoControl1.attach(servoPin1);  // Set Servo pin1
  servoControl2.attach(servoPin2);  // Set Servo pin2

  //Servo setup
  servoControl1.write(servoDefaultAngle); // Set servo to default position
  servoControl2.write(servoDefaultAngle); // Set servo to default position
  delay(500); // Delay after reset (waiting for position)
}

void loop() {
  prValue = analogRead(prPin); // Read pResistor

  if (prValue > prLaunch){	
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);

    if(!actionDone){
      if(launchStatus == 1){
        servo1Angle = servoTargetAngle;
        launchStatus = 2;
      }else if(launchStatus == 2){
        servo2Angle = servoTargetAngle;
        launchStatus = 1;
      }
      actionDone = true;  
    }
  } else {
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);

    if(servo1Angle != servoDefaultAngle){
      servo1Angle = servoDefaultAngle;
    }
    if(servo2Angle != servoDefaultAngle){
      servo2Angle = servoDefaultAngle;
    }
    actionDone = false;
  }
  
  servoControl1.write(servo1Angle);   // tell servo1 to go to position in variable 'servoAngle' 
  servoControl2.write(servo2Angle);   // tell servo2 to go to position in variable 'servoAngle' 
  delay(servoRefresh);                // waits 20ms for for refresh period 
  SoftRcPulseOut::refresh(1);         // generates the servo pulse
}