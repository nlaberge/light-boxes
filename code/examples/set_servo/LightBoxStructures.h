#pragma once
#include <FastLED.h>


enum ColorMode {
  Black,
  StaticRainbow,
  GradientPalette_cute,
  GradientPalette_cute_flow,
  Lava,
};

enum WaveMode {
  Closed,
  Open,
};

enum BrightnessMode {
  Off,
  On,
  ByServo,
};

struct BoxInfo
{
  int boxIndex;
  ColorMode colorMode; 
  WaveMode waveMode;
  BrightnessMode brightnessMode;
  int servoPin;
};


struct ButtonPress
{
  uint8_t key;
  boolean pressed;
};

struct LedRow
{
  uint8_t row;
  CRGB col0;
  CRGB col1;
  CRGB col2;
  CRGB col3;
  CRGB col4;
  CRGB col5;
  CRGB col6;
  CRGB col7;
  uint8_t servo0; //servo values, which will be shifted up by SERVOMIN on trellis
  uint8_t servo1;
  uint8_t servo2;
  uint8_t servo3;
  uint8_t servo4;
  uint8_t servo5;
};

struct TrellisLeds {
    LedRow row0;
    LedRow row1;
    LedRow row2;
    LedRow row3;
};

