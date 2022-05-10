#include <Arduino.h>
#include <SoftRcPulseOut.h>

const int ledStatusPin = A5;
const int ledStatusDelay = 500;

const int statusBtnPin1 = A0; // Define status btn1
const int statusBtnPin2 = A1; // Define status btn2
const int statusBtnPin3 = A2; // Define status btn3

const int prPin = A3;     // Photoresistor at Arduino analog pin A0
const int prLaunch = 100; // Value of Photoresistor action

const int servoPin1 = PB1;         // Servo 1
const int servoPin2 = PB2;         // Servo 2
const int servoPin3 = PB3;         // Servo 3
const int servoPin4 = PB4;         // Servo 4
const int servoPin5 = PB5;         // Servo 5
const int servo1DefaultAngle = 60; // Servo 1 default angle
const int servo2DefaultAngle = 0;  // Servo 2 default angle
const int servo3DefaultAngle = 0;  // Servo 3 default angle
const int servo4DefaultAngle = 0;  // Servo 4 default angle
const int servo5DefaultAngle = 0;  // Servo 5 default angle
const int servo1TargetAngle = 0;   // Servo 1 target angle
const int servo2TargetAngle = 60;  // Servo 2 target angle
const int servo3TargetAngle = 60;  // Servo 3 target angle
const int servo4TargetAngle = 60;  // Servo 4 target angle
const int servo5TargetAngle = 60;  // Servo 5 target angle

SoftRcPulseOut servoControl1;
SoftRcPulseOut servoControl2;
SoftRcPulseOut servoControl3;
SoftRcPulseOut servoControl4;
SoftRcPulseOut servoControl5;

const int servoRefresh = 20; // Servo refresh ms

int servo1Angle = 0;
int servo2Angle = 0;
int servo3Angle = 0;
int servo4Angle = 0;
int servo5Angle = 0;

int prValue = 1000; // Store value from photoresistor (0-1023)

int statusBtn1 = 0;
int statusBtn2 = 0;
int statusBtn3 = 0;

int launchStatus = 1;
int launchType = 1;
bool actionDone = false;

bool inited = false;

void setup()
{
  // Led status pin setup
  pinMode(ledStatusPin, OUTPUT); // Set Led status pin

  // Photoresistor setup
  pinMode(prPin, INPUT); // Set PhotoResistor pin

  // Status btn setup
  pinMode(statusBtnPin1, INPUT); // Set PhotoResistor pin
  pinMode(statusBtnPin2, INPUT); // Set PhotoResistor pin
  pinMode(statusBtnPin3, INPUT); // Set PhotoResistor pin

  // Servo setup
  servoControl1.attach(servoPin1); // Set Servo pin1
  servoControl2.attach(servoPin2); // Set Servo pin2
  servoControl2.attach(servoPin3); // Set Servo pin3
  servoControl2.attach(servoPin4); // Set Servo pin4
  servoControl2.attach(servoPin5); // Set Servo pin5
}

void loop()
{
  if (!inited)
  {
    servo1Angle = servo1DefaultAngle;
    servo2Angle = servo2DefaultAngle;
    servo3Angle = servo3DefaultAngle;
    servo4Angle = servo4DefaultAngle;
    servo5Angle = servo5DefaultAngle;

    statusBtn1 = digitalRead(statusBtnPin1); // Read status btn 1
    statusBtn2 = digitalRead(statusBtnPin2); // Read status btn 2
    statusBtn3 = digitalRead(statusBtnPin3); // Read status btn 3

    if (!statusBtn1 && !statusBtn2 && !statusBtn3)
    {
      launchType = 1;
    }
    else if (!statusBtn1 && !statusBtn2 && statusBtn3)
    {
      launchType = 2;
    }
    else if (!statusBtn1 && statusBtn2 && !statusBtn3)
    {
      launchType = 3;
    }
    else if (!statusBtn1 && statusBtn2 && statusBtn3)
    {
      launchType = 4;
    }
    else if (statusBtn1 && !statusBtn2 && !statusBtn3)
    {
      launchType = 5;
    }

    for (int x = 0; x <= launchType; x++)
    {
      digitalWrite(ledStatusDelay, HIGH);
      delay(1000);
      digitalWrite(ledStatusPin, LOW);
      delay(ledStatusDelay);
    }

    inited = true;
  }

  prValue = analogRead(prPin); // Read pResistor

  if (prValue < prLaunch)
  {
    if (!actionDone)
    {
      if (launchStatus == 1)
      {
        servo1Angle = servo1TargetAngle;
      }
      else if (launchStatus == 2)
      {
        servo2Angle = servo2TargetAngle;
      }
      else if (launchStatus == 3)
      {
        servo3Angle = servo3TargetAngle;
      }
      else if (launchStatus == 4)
      {
        servo4Angle = servo4TargetAngle;
      }
      else if (launchStatus == 5)
      {
        servo5Angle = servo5TargetAngle;
      }
      actionDone = true;
    }
  }
  else
  {
    if (actionDone)
    {
      servo1Angle = servo1DefaultAngle;
      servo2Angle = servo2DefaultAngle;
      servo3Angle = servo3DefaultAngle;
      servo4Angle = servo4DefaultAngle;
      servo5Angle = servo5DefaultAngle;

      if (launchStatus == 1)
      {
        if (launchType == 2)
        {
          launchStatus = 2;
        }
        else
        {
          launchStatus = 1;
        }
      }
      else if (launchStatus == 2)
      {
        if (launchType == 3)
        {
          launchStatus = 3;
        }
        else
        {
          launchStatus = 1;
        }
      }
      else if (launchStatus == 3)
      {
        if (launchType == 4)
        {
          launchStatus = 4;
        }
        else
        {
          launchStatus = 1;
        }
      }
      else if (launchStatus == 5)
      {
        if (launchType == 5)
        {
          launchStatus = 5;
        }
        else
        {
          launchStatus = 1;
        }
      }
    }

    actionDone = false;
  }

  servoControl1.write(servo1Angle); // tell servo1 to go to position in variable 'servoAngle'
  servoControl2.write(servo2Angle); // tell servo2 to go to position in variable 'servoAngle'
  servoControl3.write(servo3Angle); // tell servo3 to go to position in variable 'servoAngle'
  servoControl4.write(servo4Angle); // tell servo4 to go to position in variable 'servoAngle'
  servoControl5.write(servo5Angle); // tell servo5 to go to position in variable 'servoAngle'
  delay(servoRefresh);              // waits 20ms for for refresh period
  SoftRcPulseOut::refresh(1);       // generates the servo pulse
}