//ARDUINO LINE FOLLOWING CAR//
// YOU HAVE TO INSTALL THE AFMOTOR LIBRARY BEFORE UPLOAD THE CODE//
// GO TO SKETCH >> INCLUDE LIBRARY >> ADD .ZIP LIBRARY >> SELECT AF MOTOR ZIP FILE //
 
//including the libraries
//#include <AFMotor.h>
#include <Servo.h>
#include <IRremote.h>
#include <IRremote.hpp>
#include <IRremoteInt.h>
#include <Arduino.h>

Servo leftw;
Servo rightw;

const int receiver = 11;
int button = 0;
int state = LOW;
int powerState = LOW;

//defining pins and variables
#define lirpin A4
#define rirpin A5



void forward(){
  leftw.writeMicroseconds(2000);
  rightw.writeMicroseconds(1000);
}

void turnleft(){
  rightw.writeMicroseconds(1000);
  leftw.writeMicroseconds(1000);
}

void turnright(){
  rightw.writeMicroseconds(2000);
  leftw.writeMicroseconds(2000);
}

void stop(){
  leftw.writeMicroseconds(1500);
  rightw.writeMicroseconds(1500);
}

void backward(){
  leftw.writeMicroseconds(1000);
  rightw.writeMicroseconds(2000);
}


void setup() {
  //declaring pin types
  pinMode(lirpin,INPUT);
  pinMode(rirpin,INPUT);
  //begin serial communication
  Serial.begin(9600);
  leftw.attach(13);
  rightw.attach(12);
  
}

int left;
int right;

void loop(){
  //printing values of the sensors to the serial monitor

  if (left==1 && right==1){
    forward();
  }
  // line detected by left sensor
  else if (left==1 && right==0){
    turnleft();
  }
  // line detected by right sensor
  else if (left==0 && right==1){
    turnright();
  }
  // line detected by none
  else if (left==0 && right==0){
    backward();
  }
}



