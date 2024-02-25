/*
  * This project's aim is to develop a randomize game for childs.
*/
#include "fm.h"
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

#define BTN_1 7
#define BTN_2 8
#define BTN_3 9
#define BTN_4 A1

#define LED_1 2
#define LED_2 3
#define LED_3 4
#define LED_4 5

#define BZR_ONE_BIP 1
#define BZR_TWO_BIP 2

#define BUZZER 6

#define ID_1 1
#define ID_2 2
#define ID_3 3
#define ID_4 4

//Variable
fm fm1(BTN_1, LED_1, ID_1);
fm fm2(BTN_2, LED_2, ID_2);
fm fm3(BTN_3, LED_3, ID_3);
fm fm4(BTN_4, LED_4, ID_4);
/* Main Code */
int i, last_i;
uint8_t selected_led;
void setup() {
  randomSeed(analogRead(0));
  digitalWrite(BUZZER,LOW);
  pinMode(BUZZER,OUTPUT);
  newGame();
}
void newGame(){
  fm::restart();
  i = 1;
  last_i = 2;
  buzzer_play(BZR_TWO_BIP);
  show();
}
void playMelodyFinish(){
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER);
  }
}
void show() {
  while (i <= last_i) {
    selected_led = fm::getSequence(i - 1);
    switch (selected_led) {
      case ID_1:
        fm1.led_control(true);
        break;
      case ID_2:
        fm2.led_control(true);
        break;
      case ID_3:
        fm3.led_control(true);
        break;
      case ID_4:
        fm4.led_control(true);
        break;
    }
    delay(750);
    i++;
    fm1.led_control(false);
    fm2.led_control(false);
    fm3.led_control(false);
    fm4.led_control(false);
    delay(750);
  }
  i = 1;
  buzzer_play(BZR_ONE_BIP);
}
void buzzer_play(uint8_t MODE){
  switch(MODE){
    case BZR_ONE_BIP:
      digitalWrite(BUZZER,HIGH);
      delay(250);
      digitalWrite(BUZZER, LOW);
      break;
    case BZR_TWO_BIP:
      digitalWrite(BUZZER,HIGH);
      delay(250);
      digitalWrite(BUZZER, LOW);
      delay(100);
      digitalWrite(BUZZER,HIGH);
      delay(250);
      digitalWrite(BUZZER, LOW);
      break;
  }
}
void loop() {
  uint8_t pressed_btn = 0;
  while (!pressed_btn) {
    if (fm1.getButtonVal()) {
      fm1.led_control(true);
      delay(200);
//      fm1.led_control(false);
      pressed_btn = ID_1;
      while (fm1.getButtonVal()) delay(200);
      fm1.led_control(false);
    } else if (fm2.getButtonVal()) {
      fm2.led_control(true);
      delay(200);
//      fm2.led_control(false);
      pressed_btn = ID_2;
      while (fm2.getButtonVal()) delay(200);
      fm2.led_control(false);
    } else if (fm3.getButtonVal()) {
      fm3.led_control(true);
      delay(200);
//      fm3.led_control(false);
      pressed_btn = ID_3;
      while (fm3.getButtonVal()) delay(200);
      fm3.led_control(false);
    } else if (fm4.getButtonVal()) {
      fm4.led_control(true);
      delay(200);
//      fm4.led_control(false);
      pressed_btn = ID_4;
      while (fm4.getButtonVal()) delay(200);
      fm4.led_control(false);
    }
  }

  if (fm::getSequence(i - 1) == pressed_btn) {
    if (i < last_i) {
      i++;
    } else if (last_i < MAX_SEQUENCE_SIZE - 1) {
      last_i++;
      i = 1;
      delay(1000);
      show();
    } else {
      // Finish Game
      while (1) {
        fm1.led_control(false);
        fm2.led_control(false);
        fm3.led_control(false);
        fm4.led_control(false);
        delay(250);
        fm1.led_control(true);
        fm2.led_control(true);
        fm3.led_control(true);
        fm4.led_control(true);
        delay(250);
      }
    }
  } else {
    // Game Over
    playMelodyFinish();
    while (!fm4.getButtonVal() && !fm3.getButtonVal() && !fm2.getButtonVal() && !fm1.getButtonVal()){
      fm1.led_control(true);
      delay(200);
      fm1.led_control(false);
      fm2.led_control(true);
      delay(200);
      fm2.led_control(false);
      fm3.led_control(true);
      delay(200);
      fm3.led_control(false);
      fm4.led_control(true);
      delay(200);
      fm4.led_control(false);
    }
    while (fm4.getButtonVal() || fm3.getButtonVal() || fm2.getButtonVal() || fm1.getButtonVal())delay(100);
    newGame();
  }
}
/* Main Code */

/* Test Code
void setup(){
  Serial.begin(9600);
  Serial.println("Follow Me");
  digitalWrite(BUZZER,LOW);
  pinMode(BUZZER,OUTPUT);
  delay(1000);
};

void loop(){
  if(fm1.getButtonVal()){
    Serial.println("Pressed BTN_1");
    fm1.led_control(true);
    digitalWrite(BUZZER,HIGH);
    delay(250);
    digitalWrite(BUZZER,LOW);
    delay(500);
    fm1.led_control(false);
    while(fm1.getButtonVal())delay(10);
  }else if(fm2.getButtonVal()){
    Serial.println("Pressed BTN_2");
    fm2.led_control(true);
    digitalWrite(BUZZER,HIGH);
    delay(350);
    digitalWrite(BUZZER,LOW);
    delay(500);
    fm2.led_control(false);
    while(fm2.getButtonVal())delay(10);
  }else if(fm3.getButtonVal()){
    Serial.println("Pressed BTN_3");
    fm3.led_control(true);
    digitalWrite(BUZZER,HIGH);
    delay(450);
    digitalWrite(BUZZER,LOW);
    delay(500);
    fm3.led_control(false);
    while(fm3.getButtonVal())delay(10);
  }else if(fm4.getButtonVal()){
    Serial.println("Pressed BTN_4");
    fm4.led_control(true);
    digitalWrite(BUZZER,HIGH);
    delay(550);
    digitalWrite(BUZZER,LOW);
    delay(500);
    fm4.led_control(false);
    while(fm4.getButtonVal())delay(10);
  }
}
Test Code */