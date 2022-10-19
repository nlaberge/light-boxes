#pragma once
#include "Arduino.h"
// #include "Box.h"
#include "Boxes.h"
#include <FastLED.h>
#include "LightBoxStructures.h"

class ColorBoxes {
  public:
    Boxes boxes;
    ColorBoxes(Boxes bxs);
    void staticRainbow();
    void staticRainbow(Box box) ;
    void setModeBoxes(ColorMode colorMode);
    void cycleModeBoxes();

    void tickBoxFromInfo(Box box);
    void tickBoxesFromInfo(Boxes boxes);
    void cycleMode(Box box);
  
  private:
};