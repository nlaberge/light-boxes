#pragma once
#include "Arduino.h"
#include <FastLED.h>
#include "Box.h"

class Boxes {
public:
  Box* b0;
  Box* b1;
  Box* b2;
  Box* b3;
  Box* b4;
  Box* b5;
  int num_boxes;
  Boxes(){
    
  }
  Boxes(Box* a,Box* b,Box* c,Box* d,Box* e,Box* f){
    b0=a;
    b1=b;
    b2=c;
    b3=d;
    b4=e;
    b5=f;
    num_boxes = 6;
  }
  Box get_box(int box_num){
    //returns a copy of the box!
    switch (box_num)
    {
    case 0:
      return (*b0);
      break;
    case 1:
      return (*b1);
      break;
    case 2:
      return (*b2);
      break;
    case 3:
      return (*b3);
      break;
    case 4:
      return (*b4);
      break;
    case 5:
      return (*b5);
      break;
    }
 
  }

  Box* get_box_ref(int box_num){
    // returns a ref to the box!
    switch (box_num)
    {
    case 0:
      return b0;
      break;
    case 1:
      return b1;
      break;
    case 2:
      return b2;
      break;
    case 3:
      return b3;
      break;
    case 4:
      return b4;
      break;
    case 5:
      return b5;
      break;
    }
  }

  void initialize_boxes(){
    BoxInfo* boxInfoRef = &(b0->boxInfo );
    int* indexRef = &((*boxInfoRef).boxIndex);
    *indexRef = 0;

    boxInfoRef = &(b1->boxInfo);
    indexRef = &((*boxInfoRef).boxIndex);
    *indexRef = 1;

    boxInfoRef = &(b2->boxInfo);
    indexRef = &((*boxInfoRef).boxIndex);
    *indexRef = 2;

    boxInfoRef = &(b3->boxInfo);
    indexRef = &((*boxInfoRef).boxIndex);
    *indexRef = 3;

    boxInfoRef = &(b4->boxInfo);
    indexRef = &((*boxInfoRef).boxIndex);
    *indexRef = 4;

    boxInfoRef = &(b5->boxInfo);
    indexRef = &((*boxInfoRef).boxIndex);
    *indexRef = 5;
  }


  bool is_all_closed(){
    for (int i = 0; i < num_boxes; i++)
    {
      Box box = get_box(i);
      if (box.read_servo()>box.servo_min)
      {
        return false;
      }
    return true;
    }
    
  }
};