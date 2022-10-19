#include "ColorBoxes.h"

ColorBoxes::ColorBoxes(Boxes bxs){
  boxes = bxs;
};

void ColorBoxes::staticRainbow() {
  CRGB rainbow_colors[boxes.num_boxes];
  fill_rainbow(rainbow_colors,boxes.num_boxes,0,255/boxes.num_boxes);
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    boxes.get_box(i).set_all(rainbow_colors[i]);
  }
}

void ColorBoxes::staticRainbow(Box box) {
  int box_iii = box.boxInfo.boxIndex;
  Serial.print(box_iii);
  CRGB rainbow_colors[boxes.num_boxes];
  fill_rainbow(rainbow_colors,boxes.num_boxes,0,255/boxes.num_boxes);
  box.set_all(rainbow_colors[box_iii]);
}

void ColorBoxes::setModeBoxes(ColorMode colorMode) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box *b = boxes.get_box_ref(i);
    b->setColorMode(colorMode);
  }
}

void ColorBoxes::cycleModeBoxes() {
  Box b = boxes.get_box(0);
  ColorMode colorMode = b.get_box_info()->colorMode;
  switch (colorMode)
  {
  case Black:
    setModeBoxes(StaticRainbow);
    break;
  case StaticRainbow:
    setModeBoxes(Black);
    break;
  default:
    setModeBoxes(StaticRainbow);
  }
}


void ColorBoxes::tickBoxFromInfo(Box box) {
  BoxInfo* boxInfo = box.get_box_info();
  
  switch (boxInfo->colorMode)
  {
  case Black:
    box.set_all(CRGB::Black);
    break;
  
  case StaticRainbow:
    staticRainbow(box);
    break;
  }
}

void ColorBoxes::tickBoxesFromInfo(Boxes boxes) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    tickBoxFromInfo(boxes.get_box(i));
  }
  
}

