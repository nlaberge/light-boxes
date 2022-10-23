#include "ColorBoxes.h"

ColorBoxes::ColorBoxes(Boxes bxs){
  boxes = bxs;
};

DEFINE_GRADIENT_PALETTE( heatmap_gp ) {
  0,     0,    212,  255,   //cyan
  128,   255,  0,    170,   //pink
  255,   0,    212,  255}; //cyan

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
  CRGB rainbow_colors[boxes.num_boxes];
  fill_rainbow(rainbow_colors,boxes.num_boxes,0,255/boxes.num_boxes);
  box.set_all(rainbow_colors[box_iii]);
}

void ColorBoxes::setBoxToPalette(Box box, CRGBPalette16 palette, uint8_t offset){
  uint8_t box_index = box.boxInfo.boxIndex;
  uint8_t palIndex = ((255/boxes.num_boxes)*box_index)+offset;
  CRGB c = ColorFromPalette( palette, palIndex);
  box.set_all(c);
}

void ColorBoxes::setBoxesToPalette(CRGBPalette16 palette, uint8_t offset){
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box box = boxes.get_box(i);
    setBoxToPalette(box, palette, offset);
  }
}


void ColorBoxes::setModeBox(Box box, ColorMode colorMode) {
  Box *b = boxes.get_box_ref(box.get_box_info()->boxIndex);
  b->setColorMode(colorMode);
}

void ColorBoxes::setModeBoxes(ColorMode colorMode) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box b = boxes.get_box(i);
    setModeBox(b, colorMode);
  }
}

ColorMode ColorBoxes::cycleModeBox(Box box) {
  ColorMode colorMode = box.get_box_info()->colorMode;
  switch (colorMode)
  {
  case Black:
    setModeBox(box, StaticRainbow);
    return StaticRainbow;
    break;
  case StaticRainbow:
    setModeBox(box, Black);
    return Black;
    break;

  default:
    setModeBox(box, Black);
    return Black;
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
  case GradientPalette_cute:
    setBoxToPalette(box,heatmap_gp,0);
    break;
  }
}

void ColorBoxes::tickBoxesFromInfo(Boxes boxes) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    tickBoxFromInfo(boxes.get_box(i));
  }
}

