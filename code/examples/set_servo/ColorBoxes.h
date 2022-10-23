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
    void setBoxToPalette(Box box, CRGBPalette16 myPal, uint8_t offset);
    void setBoxesToPalette(CRGBPalette16 palette, uint8_t offset);
    void setModeBox(Box box, ColorMode colorMode);
    void setModeBoxes(ColorMode colorMode);
    void cycleModeBoxes();
    ColorMode cycleModeBox(Box box);
    void tickBoxFromInfo(Box box);
    void tickBoxesFromInfo(Boxes boxes);

  private:
};