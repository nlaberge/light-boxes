// #include <Servo.h>
#include <Adafruit_TiCoServo.h>
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#include <FastLED.h>
#include "Box.h"
#include "Boxes.h"
#include "LightBoxStructures.h"
#include  <Wire.h>

#include "ColorBoxes.h"
#include "WaveBoxes.h"
#include "BrightnessBoxes.h"
#include "Controller.h"

//________________

#define NUM_LEDS 24
#define NUM_BOXES 6
#define DATA_PIN 12
#define CLOCK_PIN 13

uint8_t updateRow = 0;

// Define the array of leds
CRGB leds[NUM_LEDS];
CRGB leds_prev[NUM_LEDS];

// Adafruit_TiCoServo myservo0;  // create servo object to control a servo
// Adafruit_TiCoServo myservo1;  // create servo object to control a servo
// Adafruit_TiCoServo myservo2;  // create servo object to control a servo
// Adafruit_TiCoServo myservo3;  // create servo object to control a servo
// Adafruit_TiCoServo myservo4;  // create servo object to control a servo
// Adafruit_TiCoServo myservo5;  // create servo object to control a servo

//construct box objects
Box box0(&leds[23],&leds[22],&leds[21],&leds[20],0); //furthest left
Box box1(&leds[19],&leds[18],&leds[17],&leds[16],1);
Box box2(&leds[15],&leds[14],&leds[13],&leds[12],2);
Box box3(&leds[11],&leds[10],&leds[9],&leds[8],3);
Box box4(&leds[7],&leds[6],&leds[5],&leds[4],4);
Box box5(&leds[3],&leds[2],&leds[1],&leds[0],5); //furthest right

//construct boxes object
Boxes boxes = Boxes(&box0,&box1,&box2,&box3,&box4,&box5);
// ColorBoxes colorboxes = ColorBoxes(boxes);
// WaveBoxes waveboxes = WaveBoxes(boxes);
// BrightnessBoxes brightnessboxes = BrightnessBoxes(boxes);
Controller controller = Controller(boxes);

void setup() {
  // Serial.begin(9600); // open the serial port at 9600 bps:
  FastLED.setBrightness(255);
  
  // myservo0.attach(2);  //flickering is caused by attaching servos to pins
  // myservo1.attach(3);  
  // myservo2.attach(5);  
  // myservo3.attach(6);
  // myservo4.attach(7); 
  // myservo5.attach(8);

  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR, DATA_RATE_MHZ(24)>(leds, NUM_LEDS);  // BGR ordering is typical

  // for i2c comms
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output

  
  controller.initialize_leds();
  boxes.initialize_boxes();
  controller.set_all(CRGB::Black); //set neotrellis black
  controller.tick();
}

bool check_if_array_is_equal(
  CRGB *array1,
  CRGB *array2,
  uint8_t array_length
) {
  for (uint8_t i = 0; i < array_length; i++) {
    if (array1[i] != array2[i]) {
      return false;
    }
  }
  return true;
}

CRGB deep_copy_array(
  CRGB *array1,
  CRGB *array2,
  uint8_t array_length
) {
  for (uint8_t i = 0; i < array_length; i++) {
    array2[i] = array1[i];
  }
}


void loop(){
  // CRGB c0 = (*box0.top_left);
  controller.tick();
  if (check_if_array_is_equal(leds, leds_prev, NUM_LEDS) == false) {
    deep_copy_array(leds, leds_prev, NUM_LEDS);
    FastLED.show();
  }
  Serial.println(boxes.get_box(0).servo_value);
}

void requestEvent(){
  // send trellis led information and servo information
    TrellisLeds trellisLeds = controller.get_leds();
    switch (updateRow)
    {
    case 0:
        Wire.write((byte *)&trellisLeds.row0, sizeof trellisLeds.row0);
        break;
    case 1:
        Wire.write((byte *)&trellisLeds.row1, sizeof trellisLeds.row1);
        break;
    case 2:
        Wire.write((byte *)&trellisLeds.row2, sizeof trellisLeds.row2);
        break;
    case 3:
        Wire.write((byte *)&trellisLeds.row3, sizeof trellisLeds.row3);
        updateRow = -1;
        break;
    }
    updateRow = updateRow+1;
}

void receiveEvent(int _) {
  //recieve button information
  ButtonPress buttonPress;
  Wire.readBytes((byte*) &buttonPress, sizeof buttonPress);
  controller.handle_button_event(buttonPress);
}