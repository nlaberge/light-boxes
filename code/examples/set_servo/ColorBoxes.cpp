#include "ColorBoxes.h"

ColorBoxes::ColorBoxes(Boxes bxs){
  boxes = bxs;
};

// DEFINE_GRADIENT_PALETTE( gp_cute ) {
//   0,     0,    212,  255,   //cyan
//   127,   255,  0,    170,   //pink
//   255,   0,    212,  255}; //cyan
DEFINE_GRADIENT_PALETTE( gp_cute ) { // for st patricks day
  0,     0,    255,  0,   //green
  127,   0,  0,    0,   //black
  255,   0,    255,  0}; //green

CRGBPalette16  lavaPalette = CRGBPalette16(
  CRGB::DarkRed,  CRGB::Maroon,   CRGB::DarkRed,  CRGB::Maroon,
  CRGB::DarkRed,  CRGB::Orange,   CRGB::DarkRed,  CRGB::DarkRed,
  CRGB::DarkRed,  CRGB::Orange,  CRGB::Orange,      CRGB::Yellow,
  CRGB::Black,    CRGB::Orange,   CRGB::Red,      CRGB::DarkRed
);

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
  uint8_t palIndex = ((255/(boxes.num_boxes - 1))*box_index)+offset;
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

void ColorBoxes::setBoxToPaletteNoise(Box box, CRGBPalette16 myPal){
  uint16_t brightnessScale = 25;
  uint16_t indexScale = 25;
  // int i = 0;
  int i = box.boxInfo.boxIndex;
  uint8_t brightness = inoise8(i * brightnessScale, millis() / 5);
  uint8_t index = inoise8(i * indexScale, millis()/10);
  CRGB c = ColorFromPalette(myPal, index, brightness);
  // CRGB c = CRGB::Purple;
  box.set_all(c);
  // box.fade_all(250);
}

void ColorBoxes::setBoxesToPaletteNoise(CRGBPalette16 palette){
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box box = boxes.get_box(i);
    setBoxToPaletteNoise(box, palette);
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

void ColorBoxes::cycleModeBoxes() {
  Box b = boxes.get_box(0);
  ColorMode colorMode = cycleModeBox(b);
  setModeBoxes(colorMode);
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
    setModeBox(box, GradientPalette_cute);
    return GradientPalette_cute;
    break;
  case GradientPalette_cute:
    setModeBox(box, GradientPalette_cute_flow);
    return GradientPalette_cute_flow;
    break;
    case GradientPalette_cute_flow:
    setModeBox(box, Lava);
    return Lava;
    break;
  case Lava:
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
    setBoxToPalette(box,gp_cute,0);
    break;
  case GradientPalette_cute_flow:
    setBoxToPalette(box,gp_cute,millis()/20);
    break;
  case Lava:
    setBoxToPaletteNoise(box, lavaPalette);
    break;
  }
}

void ColorBoxes::tickBoxesFromInfo(Boxes boxes) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    tickBoxFromInfo(boxes.get_box(i));
  }
}

