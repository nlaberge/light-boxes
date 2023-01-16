#pragma once
#include "Arduino.h"
#include "Boxes.h"
#include "LightBoxStructures.h"
#include <FastLED.h>
#include "ColorBoxes.h"
#include "BrightnessBoxes.h"
#include "WaveBoxes.h"

class Controller {
  public:
    Boxes boxes;
    TrellisLeds trellisLeds;
    uint8_t NUM_TRELLIS_LEDS = 32;
    LedRow ledRow0;
    LedRow ledRow1;
    LedRow ledRow2;
    LedRow ledRow3;
    uint8_t NUM_ROWS;
    uint8_t NUM_COLS;
    uint8_t controller_mode = 0;
    uint8_t NUM_MODES = 2;
    boolean button_pressed[32]; // boolean array of which buttons are pressed
    Controller(Boxes bxs);
    void initialize_leds();
    void tick();
    TrellisLeds get_leds();
    LedRow* get_row(int row);
    CRGB* get_led(LedRow* ledRowPointer, int col);
    uint8_t* get_servo(LedRow* ledRowPointer, int servo_index);
    void update_servos();
    void handle_mode_change();
    void update_button_pressed(ButtonPress buttonPress);
    void set_led(int row, int col, CRGB c);
    void set_row(int row, CRGB c);
    void set_col(int col, CRGB c);
    void set_all(CRGB c);
    void mirror_boxes();
    void mirror_boxes_to_row(int row);
    void mirror_row_open_closed_status(int row);
    void handle_button_event(ButtonPress buttonPress);
    void mode_set_boxes();
    void mode_set_boxes(ButtonPress buttonPress);
    void mode_play_notes();
    void mode_play_notes(ButtonPress buttonPress);
    int get_button_row(ButtonPress buttonPress);
    int get_button_col(ButtonPress buttonPress);


  private:
};
