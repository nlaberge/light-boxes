#pragma once
#include "Arduino.h"
#include <Adafruit_TiCoServo.h>
#include "LightBoxStructures.h"
#include <FastLED.h>

class Box {
public:
  CRGB* top_left;
  CRGB* top_right;
  CRGB* bottom_left;
  CRGB* bottom_right;
  uint8_t servo_index;
  uint8_t servo_value;
  uint8_t servo_max;
  uint8_t servo_min;
  BoxInfo boxInfo;
  Box(CRGB* a,CRGB* b,CRGB* c,CRGB* d, uint8_t servo_index);
  void set_top_right(CRGB color);
  void set_bottom_right(CRGB color);
  void set_top_left(CRGB color);
  void set_bottom_left(CRGB color);
  void set_all(CRGB color);

  void fade_top_right(int fade_by);
  void fade_bottom_right(int fade_by);
  void fade_top_left(int fade_by);
  void fade_bottom_left(int fade_by);
  void fade_all(int fade_by);
  void detach_servo();
  void attach_servo();
  void set_servo(int pos);
  int read_servo();
  BoxInfo* get_box_info();
  
  void setColorMode(ColorMode colorMode);
  void setWaveMode(WaveMode waveMode);
  void setBrightnessMode(BrightnessMode brightnessMode);
private:
};