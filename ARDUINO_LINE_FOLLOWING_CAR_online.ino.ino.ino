#include <Arduino.h>
#include <Servo.h>


Servo servo; // ping servo

// wheels
Servo leftw;
Servo rightw;

// ping sensor
const int echopin = 10;
const int trigpin = 9;
int ping;
int inches = 0;
int cm = 0;
long inchesright = 0;
long inchesleft = 0;
long rightinches = 0;
long leftinches = 0;
//long rightinches1 = 0;
//long leftinches1 = 0;
//long shortright = 0;
//long shortleft = 0;

// blinker leds
const int farleft = 3;
const int middleleft = 2;
const int blueleft = A0; // ran out of digital pins

const int farright = 5;
const int middleright = 4;
const int blueright = A1;

const int brakeleft = 7;
const int brakeright = 6;

int leftblinkers[3] = {blueleft, middleleft, farleft};
int rightblinkers[3] = {blueright, middleright, farright};

// int pos = 0;
// int speed;
// unsigned long cwtime;
// unsigned long ccwtime;

bool isAvailable = true;

// infrared
const int lirpin = A4;
const int rirpin = A5;
int left;
int right;
int aleft;
int aright;


/* scrapped
int lastinches=0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;
unsigned long reverseStartTime = 0;
unsigned long currentTime = 0;
*/



// this function mostly copied from tinkercad but adjusted to fit for 4-pin ping sensor instead of tinkercad's 3-pin
long readUltrasonicDistance(int triggerPin = trigpin, int echoPin = echopin)
{
  //pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  //pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  return microseconds / 29 / 2;
}

long pinginches(){
  return microsecondsToInches(readUltrasonicDistance());
}

long pingcm(){
  return microsecondsToCentimeters(readUltrasonicDistance());
}

// >1500 --> counterclockwise
// <1500 --> clockwise

void turnright(long turntime=0){
  servo.write(90);
  

  Serial.println("driving right");
  rightw.writeMicroseconds(1600);
  leftw.writeMicroseconds(2000);

  // delay(500); // rotate right for 0.7 seconds 
  delay(turntime);
}
 
void turnleft(long turntime=0){
  servo.write(90);
  

  Serial.println("driving left");
  rightw.writeMicroseconds(1000);
  leftw.writeMicroseconds(1470);

  // delay(500); // rotate left for 0.5 seconds
  delay(turntime);
}

void stop(){
  servo.write(90);
  //digitalWrite(brakeleft, HIGH);
  //digitalWrite(brakeright, HIGH);
  leftw.write(1500);
  rightw.write(1500); // not fully stopped why?
}

void backward(long btime=0){
  servo.write(90);
  // blink brake leds for reversing?
  leftw.writeMicroseconds(1000);
  rightw.writeMicroseconds(2000);
  delay(btime);
}

void forward(long ftime=0){
  servo.write(90); // reset ping
  digitalWrite(brakeleft, LOW);
  digitalWrite(brakeright, LOW);
  leftw.writeMicroseconds(2000);
  rightw.writeMicroseconds(1000);
  delay(ftime);
}

// int rbrakestate = LOW;
void blinkright(){
  stop();
  //digitalWrite(brakeright, LOW);  
  //digitalWrite(brakeleft, LOW);
  for(int i=0; i<4; i++){ // do it 5 times
    for (int i=0; i<3; i++){
      digitalWrite(rightblinkers[i], HIGH);
      //digitalWrite(brakeright, !rbrakestate);
      //rbrakestate = !rbrakestate;
      //digitalWrite(brakeright, HIGH);
      delay(50);
    }

    for (int i=2; i>=0; i--){
      digitalWrite(rightblinkers[i], LOW);
      //digitalWrite(brakeright, LOW);
    }
    delay(150);
  }
}

void blinkleft(){
  stop();
  //digitalWrite(brakeright, LOW);
  //digitalWrite(brakeleft, LOW);
  for(int i=0; i<4; i++){ // do it 5 times
    for (int i=0; i<3; i++){
      digitalWrite(leftblinkers[i], HIGH);
      //digitalWrite(brakeleft, HIGH);
      delay(50);
    }

    for (int i=2; i>=0; i--){
      digitalWrite(leftblinkers[i], LOW);
      //digitalWrite(brakeleft, LOW);
    }
    delay(150);
  }
}

long checkright(){
  servo.write(15); // ping looks right
  delay(500); // wait for servo to move
    
  Serial.println("scanning right");
  rightinches = pinginches(); // checks right distance
  Serial.print("right is "); Serial.println(rightinches);

  return rightinches;
}

long checkleft(){
  servo.write(165); // ping looks left
  delay(500); // wait for servo to move
  
  Serial.println("scanning left");
  leftinches = pinginches(); // checks left distance
  Serial.print("left is "); Serial.println(leftinches);

  return leftinches;
}


/* scrapped functions: 

void righttoleft(long rlefttime){
  servo.write(90);
  int infront = pinginches();
  if (infront < 5){
    backward(750);
  }

  Serial.println("returning left");
  rightw.writeMicroseconds(500);
  leftw.writeMicroseconds(1500);

  delay(rlefttime);
}

void lefttoright(long lrighttime){
  servo.write(90);
  int infront = pinginches();
  if (infront < 5){
    backward(750);
  }

  Serial.println("returning right");
  rightw.writeMicroseconds(1500);
  leftw.writeMicroseconds(2500);

  delay(lrighttime); // rotate left for 0.7 seconds
}


long shortcheckleft(){
  servo.write(120); // ping looks left
  delay(250); // wait for servo to move
  
  Serial.println("scanning left");
  leftinches1 = pinginches(); // checks left distance
  Serial.print("left is "); Serial.println(leftinches);

  return leftinches;
}


long shortcheckright(){
  servo.write(60); // ping looks right
  delay(250); // wait to move
    
  Serial.println("scanning right");
  rightinches1 = pinginches(); // checks right distance
  Serial.print("right is "); Serial.println(rightinches);

  return rightinches;
}
*/

void goaroundfromleft(){
  turnleft(800);
  forward(2000);
  turnright(600); 
  forward(3000);
  //turnright(500);
  //forward(); // drive
}

void goaroundfromright(){
  turnright(800);
  forward(2000);
  turnleft(600);
  forward(3000); // drive
}


void setup() {
  Serial.begin(9600);

  servo.attach(A3);
  leftw.attach(13);
  rightw.attach(12);

  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(farleft, OUTPUT);
  pinMode(middleleft, OUTPUT);
  pinMode(blueleft, OUTPUT);

  pinMode(farright, OUTPUT);
  pinMode(middleright, OUTPUT);
  pinMode(blueright, OUTPUT);

  pinMode(brakeleft, OUTPUT);
  pinMode(brakeright, OUTPUT);

  pinMode(lirpin, INPUT);
  pinMode(rirpin, INPUT);

  servo.write(90); // start off in center
}

// >1500 --> counterclockwise
// <1500 --> clockwise


void loop() {
  Serial.println("restarting");
  forward();

  
  Serial.print("it has been this many ms: "); Serial.println(millis());
  inches = pinginches();

  left = digitalRead(lirpin);
  right = digitalRead(rirpin);

  //cm = pingcm();
  Serial.print("inches: "); Serial.println(inches);

  int leftorright = random(2); // making random variable to randomly choose right or left
  bool shouldbreak = false;

  if (inches < 8){
    if (inches < 4){
      Serial.println("too close");
      backward(1000);
    }
    
    Serial.println("obstacle detected, stopping");
    isAvailable = false; // assume not available space

    while (!isAvailable) { // while there is not an available turn
      stop();

     // shortright = shortcheckright();
      inchesright = checkright();

     // shortleft = shortcheckleft();
      inchesleft = checkleft();

      if (inchesright > inchesleft && inchesright > 9){ // if right was empty
        isAvailable=true;
        blinkright();
        goaroundfromright();
        break;
      }
      else if (inchesleft > inchesright && inchesleft > 9){ // if left was empty   
        isAvailable=true;  
        blinkleft();
        goaroundfromleft();
        break;
      }
      else if (inchesleft < 15 && inchesright < 15){ // if no available space
        Serial.println("cannot turn, reversing");
        backward(1000);
      }
      else {
        if (leftorright == 1){ //randomly chosen left
          isAvailable = true;
          blinkleft();  
          goaroundfromleft();
          break;
        }

        else if (leftorright == 0){ // randomly chosen right
          isAvailable=true;
          blinkright();
          goaroundfromright();
          break;
        }
      }
    }
  }

  // infrared readings for line following:
  else {
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

  delay(150); // give enough time for ping sensor to reset
}


conds(2000);
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



