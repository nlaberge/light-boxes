#include "WaveBoxes.h"

WaveBoxes::WaveBoxes(Boxes bxs){
  boxes = bxs;
};

void WaveBoxes::runFullPeriodOffset() {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box b = boxes.get_box(i);
    uint8_t sinBeat_offset = beatsin8(15, b.servo_min, b.servo_max, 0, i*(255/boxes.num_boxes));
    b.set_servo(sinBeat_offset);
  }
}

void WaveBoxes::runHalfPeriodOffset() {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box b = boxes.get_box(i);
    uint8_t sinBeat_offset = beatsin8(15, b.servo_min, b.servo_max, 0, i*(128/boxes.num_boxes));
    b.set_servo(sinBeat_offset);
  }
}

void WaveBoxes::setModeBoxes(WaveMode waveMode) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box *b = boxes.get_box_ref(i);
    b->setWaveMode(waveMode);
  }
}

void WaveBoxes::tickBoxFromInfo(Box box) {
  BoxInfo* boxInfo = box.get_box_info();
  
  switch (boxInfo->waveMode)
  {
  case Open:
    box.set_servo(box.servo_max);
    break;
  
  case Closed:
    box.set_servo(box.servo_min);
    break;
  }
}

void WaveBoxes::tickBoxesFromInfo(Boxes boxes) {
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    tickBoxFromInfo(boxes.get_box(i));
  }
  
}