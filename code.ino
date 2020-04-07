#include "nRF24L01.h" // NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

#define MSG_NONE        0
#define MSG_GO          1
#define MSG_BACK        2
#define MSG_LEFT        3
#define MSG_RIGHT       4
#define MSG_TWLEFT      5
#define MSG_TWRIGHT     6
#define MSG_FIRE        7
#define MSG_CAM_ON      8
#define MSG_CAM_OFF     9
#define MSG_WHEEL_STOP  10
#define MSG_TOWER_STOP  11

#define Motor1A   2
#define Motor1B   3

#define Motor2A   4
#define Motor2B   5

#define Motor3A   6
#define Motor3B   7

#define FireIR    8

#define FireLED   A1
#define FireIS    A0

#define Life01    A2
#define Life02    A3
#define Life03    A4
#define Life04    A5

int ReceivedMessage[1] = {000}; // Used to store value received by the NRF24L01

RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the UNO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //pinMode(FireIS, OUTPUT);
  
  pinMode(Motor1A, OUTPUT);
  pinMode(Motor1B, OUTPUT);
  pinMode(Motor2A, OUTPUT);
  pinMode(Motor2B, OUTPUT);
  pinMode(Motor3A, OUTPUT);
  pinMode(Motor3B, OUTPUT);

  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, LOW);
  digitalWrite(Motor3A, LOW);
  digitalWrite(Motor3B, LOW);
  
  //pinMode(FireLED, OUTPUT);
  analogWrite(FireLED, 255);
  delay(1000);
  analogWrite(FireLED, 0);
  
  pinMode(FireIS, OUTPUT);
  digitalWrite(FireIS, LOW);

  analogWrite(Life01, 255);
  analogWrite(Life02, 255);
  analogWrite(Life03, 255);
  analogWrite(Life04, 255);

  radio.begin(); // Start the NRF24L01

  radio.openReadingPipe(1,pipe); // Get NRF24L01 ready to receive

  radio.startListening(); // Listen to see if information received
}

void loop() {
  //Serial.println("1111");
  while (radio.available())
  {
    radio.read(ReceivedMessage, 1); // Read information from the NRF24L01

    Serial.println(ReceivedMessage[0]);
    
    //Serial.println("1111");
    switch(ReceivedMessage[0]) {
      case MSG_NONE: {
        stopGo();
        break;
      }
      
      case MSG_GO: {
        go();
        break;
      }
      
      case MSG_BACK: {
        back();
        break;
      }
      
      case MSG_LEFT: {
        turnLeft();
        break;
      }
      
      case MSG_RIGHT: {
        turnRight();
        break;
      }
      
      case MSG_TWLEFT: {
        towerLeft();
        break;
      }
      
      case MSG_TWRIGHT: {
        towerRight();
        break;
      }
      
      case MSG_FIRE: {
        fire();
        break;
      }
      
      case MSG_CAM_ON: {
        camOn();
        break;
      }
      
      case MSG_CAM_OFF: {
        camOff();
        break;
      }
      
      case MSG_WHEEL_STOP: {
        stopWheel();
        break;
      }
      
      case MSG_TOWER_STOP: {
        stopTower();
        break;
      }

      default: {
        stopGo();
        break;
      }
    }
    //Serial.println("222");

  }
  
}

void stopGo()
{
  //Serial.println("stopGo");
  stopWheel();
  stopTower();
}

void stopWheel()
{
  //Serial.println("stopWheel");
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, LOW);
}

void stopTower()
{
  //Serial.println("stopTower");
  digitalWrite(Motor3A, LOW);
  digitalWrite(Motor3B, LOW);
}

void go()
{
  Serial.println("go");
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);
  
  digitalWrite(Motor2A, HIGH);
  digitalWrite(Motor2B, LOW);
}

void back()
{
  Serial.println("back");
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
  
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
}

void turnLeft()
{
  Serial.println("turnLeft");
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
  
  digitalWrite(Motor2A, HIGH);
  digitalWrite(Motor2B, LOW);
}

void turnRight()
{
  Serial.println("turnRight 0");
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);
  
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
  Serial.println("turnRight 1");
}

void towerLeft()
{
  Serial.println("towerLeft");
  digitalWrite(Motor3A, LOW);
  digitalWrite(Motor3B, HIGH);
}

void towerRight()
{
  Serial.println("towerRight");
  digitalWrite(Motor3A, HIGH);
  digitalWrite(Motor3B, LOW);
}

void fire()
{
  Serial.println("fire");
  digitalWrite(FireLED, HIGH);
  analogWrite(FireIS, 255);
  delay(200);
  
  digitalWrite(FireLED, LOW);
  analogWrite(FireIS, 0);
}

void camOn()
{
  Serial.println("camOn");
  
}

void camOff()
{
  Serial.println("camOff");
  
}

void testMotors() {
  // put your main code here, to run repeatedly:
  digitalWrite(Motor1A, HIGH);
  digitalWrite(Motor1B, LOW);
  delay(2000);
  
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, HIGH);
  delay(2000);
  
  digitalWrite(Motor1A, LOW);
  digitalWrite(Motor1B, LOW);
  delay(4000);
  
  digitalWrite(Motor2A, HIGH);
  digitalWrite(Motor2B, LOW);
  delay(2000);
  
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, HIGH);
  delay(2000);
  
  digitalWrite(Motor2A, LOW);
  digitalWrite(Motor2B, LOW);
  delay(2000);
  
  digitalWrite(Motor3A, HIGH);
  digitalWrite(Motor3B, LOW);
  delay(2000);
  
  digitalWrite(Motor3A, LOW);
  digitalWrite(Motor3B, HIGH);
  delay(2000);
  
  digitalWrite(Motor3A, LOW);
  digitalWrite(Motor3B, LOW);
  delay(2000);
}
