#ifndef _FM_H
#include <stdint.h>
#include <Arduino.h>
#define MAX_SEQUENCE_SIZE 5
class fm{
  public:
    static void restart();
    static void setNextSequence();
    static uint8_t getSequence(uint8_t i);

    fm(uint8_t btn_pin, uint8_t led_pin, uint8_t id);
    void led_control(bool isOn);

    uint8_t getId();
  private:
    uint8_t _id;
    uint8_t _btn_pin,_led_pin;
    inline static uint8_t _member;
    inline static uint8_t _index;
    inline static uint8_t _sequence_numbers[MAX_SEQUENCE_SIZE];
};
#elif
#define _FM_H
#endif