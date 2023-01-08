#pragma once
#include "Arduino.h"
#include "Box.h"
#include "Boxes.h"
#include <FastLED.h>

class WaveBoxes {
  public:
    Boxes boxes;
    WaveBoxes(Boxes bxs);
    void runFullPeriodOffset();
    void runHalfPeriodOffset();
    void setModeBox(Box box, WaveMode waveMode);
    void setModeBoxes(WaveMode waveMode);
    void cycleModeBoxes();
    WaveMode cycleModeBox(Box box);
    void tickBoxFromInfo(Box* box);
    void tickBoxesFromInfo(Boxes boxes);
    
  private:
};
