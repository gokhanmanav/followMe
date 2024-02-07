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

//Variable
fm fm1(BTN_1,LED_1,1);
fm fm2(BTN_2,LED_2,2);
fm fm3(BTN_3,LED_3,3);
fm fm4(BTN_4,LED_4,4);
/* Main Code */
void setup(){

}
void loop(){

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