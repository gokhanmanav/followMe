#include "fm.h"

fm::fm(uint8_t btn_pin, uint8_t led_pin,uint8_t id){
  // Assign private variable
  _btn_pin = btn_pin;
  _led_pin = led_pin;
  _id = id;

  //new member
  _member++;

  // Set configuration of pins
  pinMode(_btn_pin,INPUT_PULLUP);
  digitalWrite(_led_pin,LOW);
  pinMode(_led_pin,OUTPUT);
}

void fm::led_control(bool isOn){
  if(isOn){
    digitalWrite(_led_pin,HIGH);
  }else{
    digitalWrite(_led_pin,LOW);
  }
}

static void fm::restart(){
  _index=0;
  for (int i=0; i<MAX_SEQUENCE_SIZE-1; i++) {
    fm::setNextSequence();
  }
}

uint8_t fm::getId(){
  return _id;
}

static void fm::setNextSequence(){
  if(_index<MAX_SEQUENCE_SIZE){
    _sequence_numbers[_index]=random(1,_member+1);
    _index++;
  }
}

static uint8_t fm::getSequence(uint8_t i){
  if(i<MAX_SEQUENCE_SIZE)
    return _sequence_numbers[i];
  return 0;
}