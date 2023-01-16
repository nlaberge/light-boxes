
#include "Box.h"

Box::Box(CRGB* a,CRGB* b,CRGB* c,CRGB* d,uint8_t servo_index){
  top_left=a;
  bottom_left=b;
  bottom_right=c;
  top_right=d;
  servo_index = servo_index;
  servo_value = 30;
  servo_max = 120; //100
  servo_min = 0; //30
  boxInfo = boxInfo;
  boxInfo.colorMode = StaticRainbow;
  boxInfo.waveMode = Open;
  boxInfo.brightnessMode = On;
};

void Box::set_top_right(CRGB color){
  (*top_right) = color;
}
void Box::set_bottom_right(CRGB color){
  (*bottom_right) = color;
}
void Box::set_top_left(CRGB color){
  (*top_left) = color;
}
void Box::set_bottom_left(CRGB color){
  (*bottom_left) = color;
}
void Box::set_all(CRGB color){
  set_top_right(color);
  set_bottom_right(color);
  set_top_left(color);
  set_bottom_left(color);
}

void Box::fade_top_right(int fade_by){
  fadeToBlackBy(&(*top_right), 1, fade_by);;
}
void Box::fade_bottom_right(int fade_by){
  fadeToBlackBy(&(*bottom_right), 1, fade_by);;
}
void Box::fade_top_left(int fade_by){
  fadeToBlackBy(&(*top_left), 1, fade_by);;
}
void Box::fade_bottom_left(int fade_by){
  fadeToBlackBy(&(*bottom_left), 1, fade_by);;
}
void Box::fade_all(int fade_by){
  fade_top_right(fade_by);
  fade_bottom_right(fade_by);
  fade_top_left(fade_by);
  fade_bottom_left(fade_by);
}




void Box::set_servo(int pos){
  servo_value = constrain(pos, servo_min, servo_max);
}

int Box::read_servo(){
  return servo_value;
}
BoxInfo* Box::get_box_info(){
  return &boxInfo;
}

void Box::setColorMode(ColorMode colorMode){
  BoxInfo* boxInfoRef = &boxInfo;
  ColorMode* modeRef = &((*boxInfoRef).colorMode);
  *modeRef = colorMode;
}
void Box::setWaveMode(WaveMode waveMode){
  BoxInfo* boxInfoRef = &boxInfo;
  WaveMode* modeRef = &((*boxInfoRef).waveMode);
  *modeRef = waveMode;
}

void Box::setBrightnessMode(BrightnessMode brightnessMode){
  BoxInfo* boxInfoRef = &boxInfo;
  BrightnessMode* modeRef = &((*boxInfoRef).brightnessMode);
  *modeRef = brightnessMode;
}
