/*
  * This project's aim is to develop a randomize game for childs.
*/
#include "fm.h"
#include "pitches.h" // Melodi için
// Nokia 5110 GLCD Ekran için Adafruid Lib. 2.0.3
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
// EEPROM
#include <EEPROM.h>

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int melody2[] = {
  NOTE_G3, NOTE_G3, NOTE_G3, NOTE_D4, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C5, NOTE_G4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C5, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_F4, NOTE_D4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int noteDurations2[] = {
 6, 6, 6, 1, 1, 6, 6, 6, 1, 2, 6, 6, 6, 1, 2, 6, 6, 6, 1
};

#define GLCD_CLK 10
#define GLCD_DIN A4
#define GLCD_DC 12 
#define GLCD_CS A2
#define GLCD_RST 13
#define GLCD_BL A3

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

#define E2PROM_ADR_SCOR 10

//Variable
fm fm1(BTN_1, LED_1, ID_1);
fm fm2(BTN_2, LED_2, ID_2);
fm fm3(BTN_3, LED_3, ID_3);
fm fm4(BTN_4, LED_4, ID_4);

// GLCD
Adafruit_PCD8544 display = Adafruit_PCD8544(GLCD_CLK, GLCD_DIN, GLCD_DC, GLCD_CS, GLCD_RST);
/* Main Code */
int i, last_i;
uint8_t selected_led;
uint16_t best_score = 0;
uint16_t score=0;
void setup() {
  EEPROM.get(E2PROM_ADR_SCOR,best_score);
  if(best_score > MAX_SEQUENCE_SIZE){
    best_score = 0;
    EEPROM.put(E2PROM_ADR_SCOR,best_score);
  }
  //IO
  digitalWrite(GLCD_BL,LOW);
  pinMode(GLCD_BL,OUTPUT);
  
  //GLCD
  display.begin();
  display.setContrast(50);
  display.clearDisplay();
  display.display();

  randomSeed(analogRead(0));
  digitalWrite(BUZZER,LOW);
  pinMode(BUZZER,OUTPUT);
  newGame();
}
void writeGLCDBest(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(15,5);
  display.print("Yeni Skor");

  display.setTextSize(3);
  display.setCursor(15,20);
  display.print(best_score);

  display.display();
}
void writeGLCD(){
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(10,5);
  display.print("Puan - Skor");

  display.drawLine(0,15,84,15,BLACK);

  display.setTextSize(2);
  display.setCursor(0,20);
  display.print(score);
  display.display();

  display.setTextSize(1);
  display.setCursor(40,20);
  display.print("-");

  display.setTextSize(2);
  display.setCursor(48,20);
  display.print(best_score);
  display.display();
}

void newGame(){
  score=0;
  fm::restart();
  i = 1;
  last_i = 2;
  buzzer_play(BZR_TWO_BIP);
  writeGLCD();
  show();
}
void playMelodyWin(){
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations2[thisNote];
    tone(BUZZER, melody2[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER);
  }
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
      score++;
      writeGLCD();
      show();
    } else {
      // Win Game
      playMelodyWin();
      while (!fm4.getButtonVal() && !fm3.getButtonVal() && !fm2.getButtonVal() && !fm1.getButtonVal()){
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
      while (fm4.getButtonVal() || fm3.getButtonVal() || fm2.getButtonVal() || fm1.getButtonVal())delay(100);
      newGame();
    }
  } else {
    // Game Over
    if(score>best_score){
      best_score = score;
      EEPROM.put(E2PROM_ADR_SCOR,best_score);
      writeGLCDBest();
      // Win Game
      playMelodyWin();
    }else{
      playMelodyFinish();
    }
    while (!fm4.getButtonVal() && !fm3.getButtonVal() && !fm2.getButtonVal() && !fm1.getButtonVal()){
      fm1.led_control(true);
      delay(200);
      fm1.led_control(false);
      fm2.led_control(true);
      delay(200);
      fm2.led_control(false);
      fm3.led_control(true);
      display.invertDisplay(true);
      delay(200);
      fm3.led_control(false);
      fm4.led_control(true);
      delay(200);
      fm4.led_control(false);
      display.invertDisplay(false);
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