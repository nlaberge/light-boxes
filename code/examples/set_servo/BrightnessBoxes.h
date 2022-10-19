#pragma once
#include "Arduino.h"
#include "Box.h"
#include "Boxes.h"
#include <FastLED.h>

class BrightnessBoxes {
  public:
    Boxes boxes;
    BrightnessBoxes(Boxes bxs);
    void setDimByServo();
    void setDimByServo(Box box);
    void oscillateTopBottom();
    void oscillateRightLeft();
    void oscillateAll();
    void setModeBox(Box box, BrightnessMode brightnessMode);
    void setModeBoxes(BrightnessMode brightnessMode);
    void cycleModeBoxes();
    void cycleModeBox(Box box);
    void tickBoxFromInfo(Box box);
    void tickBoxesFromInfo(Boxes boxes);
  private:
};

