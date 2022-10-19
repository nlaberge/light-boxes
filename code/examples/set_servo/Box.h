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
  Adafruit_TiCoServo* servo;
  uint8_t servo_max;
  uint8_t servo_min;
  BoxInfo boxInfo;
  Box(CRGB* a,CRGB* b,CRGB* c,CRGB* d,Adafruit_TiCoServo  * s);
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
  void set_servo(int pos);
  int read_servo();
  BoxInfo* get_box_info();

  void cycleColorMode();
  void cycleWaveMode();
  
  void setColorMode(ColorMode colorMode);
  void setWaveMode(WaveMode waveMode);
  void setBrightnessMode(BrightnessMode brightnessMode);

private:
};