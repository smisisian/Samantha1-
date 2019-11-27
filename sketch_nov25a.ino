#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define  JoyXPin   A1
#define  JoyYPin   A0
#define  XCL       490
#define  XCU       510
#define  YCL       510
#define  YCU       530
#define  SDELAY    150
#define  FDELAY    10


Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_StepperMotor *MotorX = AFMS.getStepper (200, 1);
Adafruit_StepperMotor *MotorY = AFMS.getStepper (200, 2);



int ValueX, ValueY;
int DelayX, DelayY;
int CurrX = 0;
int PrevX = 0;
int CurrY = 0;
int PrevY = 0;
uint8_t DirX, DirY;



#define from adafruit_motor import stepper
#ifdef F_CPU
#undef F_CPU
#define F_CPU 1000000L
#endif

 


void setup() {
  Serial.begin(9600);

  AFMS.begin(200000);
  //TWBR=((F_CPU /4000001)-16) / 2;
  pinMode(JoyXPin, INPUT);
  pinMode(JoyYPin, INPUT);

}  // end of void setup

void loop()
{
  double meas = micros();
  ValueX = analogRead(JoyXPin);
  ValueY = analogRead(JoyYPin);
  CurrX = CurrY = millis();

  
  //x
  if ((ValueX > XCL) && (ValueX < XCU))
  {
    PrevX = CurrX;
  }
  else if (ValueX <= XCL)
  {
    DirX = BACKWARD;
    DelayX = map(ValueX, 0, XCL, FDELAY, SDELAY);
    //Serial.println(DelayX);
    void release();
  }
  else
  {
    DirX = FORWARD;
    DelayX = map(ValueX, XCU, 1023, SDELAY, FDELAY);
    void release();
  }
  if ((CurrX - PrevX) >= DelayX)
  {
    PrevX = CurrX;
    MotorX->onestep(DirX, SINGLE);
    void release();
  }
  Serial.println(micros() - meas);
  //MotorX->onestep(FORWARD,MICROSTEP);


  //y
  if ((ValueY > YCL) && (ValueY < YCU))
  {
    PrevY = CurrY;
  }
  else if (ValueY <= YCL)
  {
    DirY = BACKWARD;
    DelayY = map(ValueY, 0, YCL, FDELAY, SDELAY);
    //Serial.println(DelayY);
    void release();
  }
  else
  {
    DirY = FORWARD;
    DelayY = map(ValueY, YCU, 1023, SDELAY, FDELAY);
    void release();
  }
  if ((CurrY - PrevY) >= DelayY)
  {
    PrevY = CurrY;
    MotorY->onestep(DirY, SINGLE);
    void release();
  }
  Serial.println(micros() - meas);
  //MotorX->onestep(FORWARD,MICROSTEP);
}
