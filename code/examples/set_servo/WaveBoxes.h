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
    void setModeBoxes(WaveMode waveMode);
    void cycleModeBoxes();
    void tickBoxFromInfo(Box box);
    void tickBoxesFromInfo(Boxes boxes);
    
  private:
};
