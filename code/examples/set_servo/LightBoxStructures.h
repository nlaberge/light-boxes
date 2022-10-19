#pragma once
#include <FastLED.h>


enum ColorMode {
  Black,
  StaticRainbow,
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
};


// struct BoxesInfo
// {
//   BoxInfo b0;
//   BoxInfo b1;
//   BoxInfo b2;
//   BoxInfo b3;
//   BoxInfo b4;
//   BoxInfo b5;
// };


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
};

struct TrellisLeds {
    LedRow row0;
    LedRow row1;
    LedRow row2;
    LedRow row3;
};