#include "Controller.h"
#include "Box.h"

Controller::Controller(Boxes bxs){
  boxes = bxs;
  trellisLeds = trellisLeds;
  NUM_ROWS = 4;
  NUM_COLS = 8;
};
void Controller::initialize_leds(){
    // trellis colors on startup

  ledRow0.row = 0;
  ledRow0.col0 = CRGB::Red;
  ledRow0.col1 = CRGB::Blue;
  ledRow0.col2 = CRGB::Green;
  ledRow0.col3 = CRGB::White;
  ledRow0.col4 = CRGB::Purple;
  ledRow0.col5 = CRGB::Orange;
  ledRow0.col6 = CRGB::Magenta;
  ledRow0.col7 = CRGB::Cyan;
  ledRow0.servo0 = 10; //servo values, which will be shifted up by SERVOMIN on trellis
  ledRow0.servo1 = 120;
  ledRow0.servo2 = 120;
  ledRow0.servo3 = 120;
  ledRow0.servo4 = 120;
  ledRow0.servo5 = 120;

  ledRow1.row = 1;
  ledRow1.col0 = CRGB::Red;
  ledRow1.col1 = CRGB::Blue;
  ledRow1.col2 = CRGB::Green;
  ledRow1.col3 = CRGB::White;
  ledRow1.col4 = CRGB::Purple;
  ledRow1.col5 = CRGB::Orange;
  ledRow1.col6 = CRGB::Magenta;
  ledRow1.col7 = CRGB::Cyan;

  ledRow2.row = 2;
  ledRow2.col0 = CRGB::Red;
  ledRow2.col1 = CRGB::Blue;
  ledRow2.col2 = CRGB::Green;
  ledRow2.col3 = CRGB::White;
  ledRow2.col4 = CRGB::Purple;
  ledRow2.col5 = CRGB::Orange;
  ledRow2.col6 = CRGB::Magenta;
  ledRow2.col7 = CRGB::Cyan;

  ledRow3.row = 3;
  ledRow3.col0 = CRGB::Red;
  ledRow3.col1 = CRGB::Blue;
  ledRow3.col2 = CRGB::Green;
  ledRow3.col3 = CRGB::White;
  ledRow3.col4 = CRGB::Purple;
  ledRow3.col5 = CRGB::Orange;
  ledRow3.col6 = CRGB::Magenta;
  ledRow3.col7 = CRGB::Cyan;

  trellisLeds.row0 = ledRow0;
  trellisLeds.row1 = ledRow1;
  trellisLeds.row2 = ledRow2;
  trellisLeds.row3 = ledRow3;
}

void Controller::tick(){
  switch (controller_mode)
  {
  case 0:
    mode_set_boxes();
    break;
  case 1:
    mode_play_notes();
    break;
  default:
    break;
  }
  
  update_servos();
  // ColorBoxes colorBoxes = ColorBoxes(boxes);
  // colorBoxes.tickBoxesFromInfo(boxes);
}

TrellisLeds Controller::get_leds(){
  return trellisLeds;
}

LedRow * Controller::get_row(int row){
  LedRow ledRow;
  //get row
  switch (row)
  {
  case 0:
    return &trellisLeds.row0;
    break;
  case 1:
    return &trellisLeds.row1;
    break;
  case 2:
    return &trellisLeds.row2;
    break;
  case 3:
    return &trellisLeds.row3;
    break;
  }
}

CRGB* Controller::get_led(LedRow* ledRowPointer, int col){
  switch (col)
  {
  case 0:
    return &(ledRowPointer->col0);
    break;
  case 1:
    return &(ledRowPointer->col1);
    break;
  case 2:
    return &(ledRowPointer->col2);
    break;
  case 3:
    return &(ledRowPointer->col3);
    break;
  case 4:
    return &(ledRowPointer->col4);
    break;
  case 5:
    return &(ledRowPointer->col5);
    break;
  case 6:
    return &(ledRowPointer->col6);
    break;
  case 7:
    return &(ledRowPointer->col7);
    break;
  }
}

uint8_t* Controller::get_servo(LedRow* ledRowPointer, int servo_index){
  switch (servo_index)
  {
  case 0:
    return &(ledRowPointer->servo0);
    break;
  case 1:
    return &(ledRowPointer->servo1);
    break;
  case 2:
    return &(ledRowPointer->servo2);
    break;
  case 3:
    return &(ledRowPointer->servo3);
    break;
  case 4:
    return &(ledRowPointer->servo4);
    break;
  case 5:
    return &(ledRowPointer->servo5);
    break;
  }
}

void Controller::set_led(int row, int col, CRGB c){
  LedRow* ledRow = get_row(row);
  CRGB* led = get_led(ledRow, col);
  * led = c; //Yessss
}

void Controller::update_servos(){
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    // get servo value
    Box box = boxes.get_box(i);
    uint8_t servo_value = (box.servo_value);
    // set servo in ledRow
    LedRow* ledRow = get_row(0); // only save servo information to row 0
    uint8_t* servo = get_servo(ledRow, i);
    * servo = servo_value; //TODO:  does this work? might need to make servo_value into pointer?
  }
}

void Controller::handle_mode_change(){
  // press 30 and 31 at same time to change mode forward
  if (button_pressed[30] && button_pressed[31])
  {
    controller_mode++;
  }
  // press 25 and 24 at same time to change mode backward
  if (button_pressed[25] && button_pressed[24])
  {
    controller_mode--;
  }
  // wrap around
  if (controller_mode > NUM_MODES - 1) 
  {
    controller_mode = 0;
  }
  else if (controller_mode < 0)
  {
    controller_mode = NUM_MODES - 1;
  }
}

void Controller::update_button_pressed(ButtonPress buttonPress){
  // update button_pressed array with new button press
  button_pressed[buttonPress.key] = buttonPress.pressed;
}

void Controller::set_row(int row, CRGB c){
  for (int col = 0; col < NUM_COLS; col++)
  {
    set_led(row,col, c);
  }
}
void Controller::set_col(int col, CRGB c){
  for (int row = 0; row < NUM_ROWS; row++)
  {
    set_led(row,col, c);
  }
}
void Controller::set_all(CRGB c){
  for (int row = 0; row < NUM_ROWS; row++)
  {
    set_row(row, c);
  }
}

void Controller::mirror_boxes(){
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box box = boxes.get_box(i);
    CRGB c = (*box.top_left);
    set_col(i+1,c);
  }
}


void Controller::mirror_boxes_to_row(int row){
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box box = boxes.get_box(i);
    CRGB c = (*box.top_left);
    set_led(row, i+1,c);
  }
}

void Controller::mirror_row_open_closed_status(int row){
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box box = boxes.get_box(i);
    int theta = box.read_servo();
    theta = map(theta, box.servo_min, box.servo_max,5,255);
    CRGB c = CRGB(theta, theta, theta);
    set_led(row, i+1,c);
  }
}

void Controller::handle_button_event(ButtonPress buttonPress){
  update_button_pressed(buttonPress);
  handle_mode_change();
  switch (controller_mode)
  {
  case 0:
    mode_set_boxes(buttonPress);
    break;
  case 1: 
    mode_play_notes(buttonPress);
    break;
  default:
    break;
  }
  
  // WaveBoxes waveBoxes = WaveBoxes(boxes);
  // waveBoxes.closeAll();
}


void Controller::mode_set_boxes(){
  ColorBoxes colorboxes = ColorBoxes(boxes);
  WaveBoxes waveboxes = WaveBoxes(boxes);
  BrightnessBoxes brightnessboxes = BrightnessBoxes(boxes);

  colorboxes.tickBoxesFromInfo(boxes);
  waveboxes.tickBoxesFromInfo(boxes);
  brightnessboxes.tickBoxesFromInfo(boxes);

  mirror_boxes_to_row(0);
  mirror_row_open_closed_status(1);

}

int Controller::get_button_row(ButtonPress buttonPress){
  return buttonPress.key/8;
}
int Controller::get_button_col(ButtonPress buttonPress){
  return buttonPress.key%8;
}


void Controller::mode_set_boxes(ButtonPress buttonPress){
  int bp_row = get_button_row(buttonPress);
  int bp_col = get_button_col(buttonPress);
  WaveBoxes waveBoxes = WaveBoxes(boxes);
  ColorBoxes colorBoxes = ColorBoxes(boxes);
  BrightnessBoxes brightnessBoxes = BrightnessBoxes(boxes);
  
  if (buttonPress.pressed)
  {
    if (bp_row==0) //handle top row (open/close, and on/off)
    {
      if (bp_col== 0 || bp_col== 7) //close or open all boxes
      {
        brightnessBoxes.cycleModeBoxes();
      }
      else
      {
        int box_i_to_update = bp_col-1;
        Box *box_to_update = boxes.get_box_ref(box_i_to_update);
        brightnessBoxes.cycleModeBox(*box_to_update); 
      }
    }
    if (bp_row==1) //handle second row (open/close)
    {
      if (bp_col== 0 || bp_col== 7) //close or open all boxes
      {
        if (boxes.is_all_closed()) 
        {
          waveBoxes.setModeBoxes(Open);
        }
        else
        {
          waveBoxes.setModeBoxes(Closed);
        }
      }
      else
      {
        int box_i_to_update = bp_col-1;
        Box* box_to_update = boxes.get_box_ref(box_i_to_update);
        waveBoxes.cycleModeBox(*box_to_update); 
      }
      
    }
    if (bp_row==2) //handle third row (cycle color forward)
    {
      if (bp_col== 0 || bp_col== 7)
      {
      colorBoxes.cycleModeBoxes();
      }
      else
      {
      colorBoxes.cycleModeBoxes();
      }
    }
  }
}


DEFINE_GRADIENT_PALETTE( gp_play ) {
  0,     255,    0,  0,   //?
  63,     237,    255,  0,   //?
  64,     0,    212,  255,   //?
  127,     53,    255,  0,   //?
  128,     0,    6,  255,   //?
  191,     255,    131,  0,   //?
  192,     255,    0,  224,   //?
  255,     134,    255,  0,   //?
};
  


void Controller::mode_play_notes(){
  CRGBPalette16 myPal = gp_play;
  // Set a color gradient to the trellis using set_led
  for (uint16_t i = 0; i < NUM_TRELLIS_LEDS; i++)
  {
    
    CRGB c = ColorFromPalette(myPal,i*(255/NUM_TRELLIS_LEDS));
    set_led(i/8,i%8,c);
  }

  //fade all of the boxes
  for (int i = 0; i < boxes.num_boxes; i++)
  {
    Box box = boxes.get_box(i);
    box.fade_all(1);
  }

  //open or close box by luminosity of top left led
  WaveBoxes waveBoxes = WaveBoxes(boxes);
  waveBoxes.mirrorBrightness();

  //loop through the currently pressed buttons. 
  //Light the nearest box according to position
  for (int i = 0; i < NUM_TRELLIS_LEDS; i++)
  {
    if (button_pressed[i])
    {
      int button_col = i%8;
      int box_i = 0;
      if (button_col == 0 || button_col == 1)
      {
        box_i = 0;
      }
      else if (button_col == 6 || button_col == 7)
      {
        box_i = 5;
      }
      else
      {
        box_i = button_col-1;
      }
      Box box = boxes.get_box(box_i);
      CRGB c = ColorFromPalette(myPal,i*(255/NUM_TRELLIS_LEDS));
      box.set_all(c);
    }
  }

}
  
void Controller::mode_play_notes(ButtonPress buttonPress){

  return;  
}

