#include <Wire.h>
#include <FastLED.h>

uint8_t updateRow = 0;

struct ButtonPress
{
  uint8_t key;
  boolean pressed;
} buttonPress;

struct LedRow
{
  uint8_t row;
  CRGB col0;
  CRGB col1;
  CRGB col2;
  CRGB col3;
  CRGB col4;
  CRGB col5;
  CRGB col6;
  CRGB col7;
};

LedRow ledRow0;
LedRow ledRow1;
LedRow ledRow2;
LedRow ledRow3;

void setup() {
    Wire.begin(8);                // join i2c bus with address #8
    Wire.onRequest(requestEvent); // register event
    Wire.onReceive(receiveEvent); // register event
    Serial.begin(9600);  // start serial for output

    ledRow0.row = 0;
    ledRow0.col0 = CRGB::Red;
    ledRow0.col1 = CRGB::Blue;
    ledRow0.col2 = CRGB::Green;
    ledRow0.col3 = CRGB::White;
    ledRow0.col4 = CRGB::Purple;
    ledRow0.col5 = CRGB::Orange;
    ledRow0.col6 = CRGB::Magenta;
    ledRow0.col7 = CRGB::Cyan;

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

}

void loop() {
  delay(1);
}

void requestEvent() {

    switch (updateRow)
    {
    case 0:
        Wire.write((byte *)&ledRow0, sizeof ledRow0);
        break;
    case 1:
        Wire.write((byte *)&ledRow1, sizeof ledRow1);
        break;
    case 2:
        Wire.write((byte *)&ledRow2, sizeof ledRow2);
        break;
    case 3:
        Wire.write((byte *)&ledRow3, sizeof ledRow3);
        updateRow = -1;
        break;
    }
    updateRow = updateRow+1;
}

void receiveEvent() {
  Wire.readBytes((byte*) &buttonPress, sizeof buttonPress);
}