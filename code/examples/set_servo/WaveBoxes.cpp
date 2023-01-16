#include "WaveBoxes.h"

WaveBoxes::WaveBoxes(Boxes bxs){
  boxes = bxs;
};

void WaveBoxes::runFullPeriodOffset() {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box* b = boxes.get_box_ref(i);
    uint8_t sinBeat_offset = beatsin8(15, b->servo_min, b->servo_max, 0, i*(255/boxes.num_boxes));
    b->set_servo(sinBeat_offset);
  }
}

void WaveBoxes::runHalfPeriodOffset() {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box* b = boxes.get_box_ref(i);
    uint8_t sinBeat_offset = beatsin8(15, b->servo_min, b->servo_max, 0, i*(128/boxes.num_boxes));
    b->set_servo(sinBeat_offset);
  }
}

void WaveBoxes::mirrorBrightness() {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box* b = boxes.get_box_ref(i);
    CRGB* c = b->top_left; //use top left for brightness
    int brightness = c->getLuma();
    uint8_t theta = 0;
    theta = map(brightness, 0, 100,b->servo_min,b->servo_max);
    b->set_servo(theta);
  }
}

void WaveBoxes::setModeBox(Box box, WaveMode waveMode) {
  Box *b = boxes.get_box_ref(box.get_box_info()->boxIndex);
  b->setWaveMode(waveMode);
}

void WaveBoxes::setModeBoxes(WaveMode waveMode) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box b = boxes.get_box(i);
    setModeBox(b, waveMode);
  }
}

void WaveBoxes::cycleModeBoxes() {
  Box b = boxes.get_box(0);
  WaveMode waveMode = cycleModeBox(b);
  setModeBoxes(waveMode);
}

WaveMode WaveBoxes::cycleModeBox(Box b) {
  WaveMode waveMode = b.get_box_info()->waveMode;
  switch (waveMode)
  {
  case Open:
    setModeBox(b, Closed);
    return Closed;
    break;
  case Closed:
    setModeBox(b, Open);
    return Open;
    break;

  default:
    setModeBox(b, Open);
    return Open;
  }
}

void WaveBoxes::tickBoxFromInfo(Box* box) {
  BoxInfo* boxInfo = box->get_box_info();
  
  switch (boxInfo->waveMode)
  {
  case Open:
    box->set_servo(box->servo_max);
    break;
  
  case Closed:
    box->set_servo(box->servo_min);
    break;
  }
}

void WaveBoxes::tickBoxesFromInfo(Boxes boxes) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    tickBoxFromInfo(boxes.get_box_ref(i));
  }
}