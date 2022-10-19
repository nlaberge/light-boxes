#include "BrightnessBoxes.h"

BrightnessBoxes::BrightnessBoxes(Boxes bxs){
    boxes = bxs;
  };


void BrightnessBoxes::setDimByServo(Box box){
  int theta = box.read_servo();
  theta = map(theta,box.servo_min,box.servo_max,255,0);
  box.fade_all(theta);
}

void BrightnessBoxes::setDimByServo() {
  // dims each box according to how closed the servo is
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box b = boxes.get_box(i);
    setDimByServo(b);
  }
}

void BrightnessBoxes::oscillateTopBottom() {
  // dims each box according to how closed the servo is
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box b = boxes.get_box(i);
    uint8_t sinBeat = beatsin8(15, 0, 255, 0, 0);
    uint8_t sinBeat_offset = beatsin8(15, 0, 255, 0, 255/2);

    b.fade_top_left(sinBeat);
    b.fade_top_right(sinBeat);
    b.fade_bottom_left(sinBeat_offset);
    b.fade_bottom_right(sinBeat_offset);
  }
  FastLED.show();
}

void BrightnessBoxes::oscillateAll() {
  // dims each box according to how closed the servo is
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box b = boxes.get_box(i);
    uint8_t sinBeat = beatsin8(15, 0, 255, 0, 0);

    b.fade_top_left(sinBeat);
    b.fade_top_right(sinBeat);
    b.fade_bottom_left(sinBeat);
    b.fade_bottom_right(sinBeat);
  }
  FastLED.show();
}

void BrightnessBoxes::oscillateRightLeft() {
  // dims each box according to how closed the servo is
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box b = boxes.get_box(i);
    uint8_t sinBeat = beatsin8(15, 0, 255, 0, 0);
    uint8_t sinBeat_offset = beatsin8(15, 0, 255, 0, 255/2);

    b.fade_top_left(sinBeat);
    b.fade_top_right(sinBeat_offset);
    b.fade_bottom_left(sinBeat);
    b.fade_bottom_right(sinBeat_offset);
  }
  FastLED.show();
}

void BrightnessBoxes::setModeBox(Box box, BrightnessMode brightnessMode) {
  Box *b = boxes.get_box_ref(box.get_box_info()->boxIndex);
  b->setBrightnessMode(brightnessMode);
}

void BrightnessBoxes::setModeBoxes(BrightnessMode brightnessMode) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box b = boxes.get_box(i);
    // b->cycleBrightnessMode();
    setModeBox(b, brightnessMode);\
  }
}


void BrightnessBoxes::cycleModeBoxes() {
  Box b = boxes.get_box(0);
  BrightnessMode brightnessMode = b.get_box_info()->brightnessMode;
  switch (brightnessMode)
  {
  case On:
    setModeBoxes(ByServo);
    break;
  case ByServo:
    setModeBoxes(On);
    break;

  default:
    setModeBoxes(On);
  }
}

void BrightnessBoxes::cycleModeBox(Box b) {
  BrightnessMode brightnessMode = b.get_box_info()->brightnessMode;
  switch (brightnessMode)
  {
  case On:
    setModeBox(b, ByServo);
    break;
  case ByServo:
    setModeBox(b, On);
    break;

  default:
    setModeBox(b, On);
  }
}

void BrightnessBoxes::tickBoxFromInfo(Box box) {
  BoxInfo* boxInfo = box.get_box_info();
  
  switch (boxInfo->brightnessMode)
  {
  case On:
    break;
  case Off:
    box.fade_all(255);
    break;
  case ByServo:
    setDimByServo(box);
    break;
  }
}

void BrightnessBoxes::tickBoxesFromInfo(Boxes boxes) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    tickBoxFromInfo(boxes.get_box(i));
  }
}