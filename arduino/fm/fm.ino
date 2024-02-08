/*
  * This project's aim is to develop a randomize game for childs.
*/
#include"fm.h"

#define BTN_1 7
#define BTN_2 8
#define BTN_3 12
#define BTN_4 13

#define LED_1 5
#define LED_2 6
#define LED_3 9
#define LED_4 10

#define ID_1 1
#define ID_2 2
#define ID_3 3
#define ID_4 4

//Variable
fm fm1(BTN_1,LED_1,ID_1);
fm fm2(BTN_2,LED_2,ID_2);
fm fm3(BTN_3,LED_3,ID_3);
fm fm4(BTN_4,LED_4,ID_4);
/* Main Code */
int i=1;
uint8_t selected_led;
void setup(){
  Serial.begin(9600);
  Serial.println("FollowMe");
  randomSeed(analogRead(0));
  fm::restart();
}
void loop(){
  if(i<MAX_SEQUENCE_SIZE){
    selected_led = fm::getSequence(i-1);
    i++;
    Serial.print(selected_led);
    Serial.print(" ");
    switch (selected_led) {
      case ID_1:
        fm1.led_control(true);
        fm2.led_control(false);
        fm3.led_control(false);
        fm4.led_control(false);
      break;
      case ID_2:
        fm1.led_control(false);
        fm2.led_control(true);
        fm3.led_control(false);
        fm4.led_control(false);
      break;
      case ID_3:
        fm1.led_control(false);
        fm2.led_control(false);
        fm3.led_control(true);
        fm4.led_control(false);
      break;
      case ID_4:
        fm1.led_control(false);
        fm2.led_control(false);
        fm3.led_control(false);
        fm4.led_control(true);
      break;
    }
    delay(1000);
  }else{
    i=1;
    Serial.println();
  }
}
/* Main Code */

/* Test Code
int i=1;
void setup(){
  Serial.begin(9600);
  Serial.println("Follow Me");
  delay(1000);
  randomSeed(analogRead(0));
};

void loop(){
  fm::setNextSequence();
  for(int j=0;j<i;j++){
    if(j<MAX_SEQUENCE_SIZE){
      Serial.print(fm::getSequence(j));
      Serial.print(" ");
    }else{
      continue;
    }
  }
  Serial.println();
  if(i<MAX_SEQUENCE_SIZE)
  i++;
  delay(1000);
}
Test Code */