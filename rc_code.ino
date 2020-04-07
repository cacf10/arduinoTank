#include "nRF24L01.h" //NRF24L01 library created by TMRh20 https://github.com/TMRh20/RF24
#include "RF24.h"
#include "SPI.h"

//switch LEFT
#define LSwitchPin 8 // Arcade switch is connected to Pin 8 on NANO
#define LXPin A1 // Arcade x is connected to Pin A1 on NANO
#define LYPin A0 // Arcade y is connected to Pin A0 on NANO


//switch RIGHT
#define RSwitchPin 7 // Arcade switch is connected to Pin 7 on NANO
#define RXPin A2 // Arcade switch is connected to Pin 8 on NANO
#define RYPin A3 // Arcade switch is connected to Pin 8 on NANO


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

#define JFLAG_NONE    0
#define JFLAG_SET     1

int SentMessage[1] = {000}; // Used to store value before being sent through the NRF24L01

RF24 radio(9,10); // NRF24L01 used SPI pins + Pin 9 and 10 on the NANO

const uint64_t pipe = 0xE6E6E6E6E6E6; // Needs to be the same for communicating between 2 NRF24L01 


void setup(void){
  Serial.begin(9600);
  
  pinMode(LSwitchPin, INPUT_PULLUP); // Define the arcade switch NANO pin as an Input using Internal Pullups
  digitalWrite(LSwitchPin,HIGH); // Set Pin to HIGH at beginning
  
  pinMode(RSwitchPin, INPUT_PULLUP); // Define the arcade switch NANO pin as an Input using Internal Pullups
  digitalWrite(RSwitchPin,HIGH); // Set Pin to HIGH at beginning
  
  radio.begin(); // Start the NRF24L01
  radio.openWritingPipe(pipe); // Get NRF24L01 ready to transmit
}

void loop(void){
  int value = 0; 
  int stickFlagL = JFLAG_NONE;
  int stickFlagR = JFLAG_NONE;
  
  value = analogRead(LXPin); 
  Serial.print("LX:"); 
  Serial.println(value, DEC); 

  if(value > 600) {
    stickFlagL = JFLAG_SET;
    sendMsg(MSG_LEFT);
    return;
  } else if(value < 400) {
    stickFlagL = JFLAG_SET;
    sendMsg(MSG_RIGHT);
    return;
  }
  
  value = analogRead(LYPin); 
  Serial.print(" | LY:"); 
  Serial.println(value, DEC); 

  if(value > 600) {
    stickFlagL = JFLAG_SET;
    sendMsg(MSG_GO);
    return;
  } else if(value < 400) {
    stickFlagL = JFLAG_SET;
    sendMsg(MSG_BACK);
    return;
  }
 
  if (digitalRead(LSwitchPin) == LOW){ // If Switch is Activated
    Serial.println("LSwitch");
    stickFlagL = JFLAG_SET;
    sendMsg(MSG_CAM_ON);
    return;
  }
  else {
//    SentMessage[0] = 000;
//    radio.write(SentMessage, 1);
  }

  if (JFLAG_NONE == stickFlagL) {
    sendMsg(MSG_WHEEL_STOP);
  }
  
  value = analogRead(RXPin); 
  Serial.print("RX:"); 
  Serial.println(value, DEC); 

  if(value > 600) {
    stickFlagR = JFLAG_SET;
    sendMsg(MSG_TWRIGHT);
    return;
  } else if(value < 400) {
    stickFlagR = JFLAG_SET;
    sendMsg(MSG_TWLEFT);
    return;
  }
  
  value = analogRead(RYPin); 
  Serial.print(" | RY:"); 
  Serial.println(value, DEC); 
 
  if (digitalRead(RSwitchPin) == LOW){ // If Switch is Activated
    stickFlagR = JFLAG_SET;
    Serial.println("RSwitch");
    sendMsg(MSG_FIRE);
    return;
  }
  else {
//    SentMessage[0] = 000;
//    radio.write(SentMessage, 1);
  }

  if (JFLAG_NONE == stickFlagR) {
    sendMsg(MSG_TOWER_STOP);
  }

  if((JFLAG_NONE == stickFlagL) && (JFLAG_NONE == stickFlagR)) {
    sendMsg(MSG_NONE);
    return;
  }

  //delay(100);
}

void sendMsg(int msgType)
{
  Serial.println(msgType);
  SentMessage[0] = msgType;
  radio.write(SentMessage, 1); // Send value through 
}
