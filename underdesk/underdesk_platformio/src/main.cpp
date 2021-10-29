
////////////////////////////////////////////// INCLUDED LIBRARIES

#include <Arduino.h>
#include <SimpleRotary.h>
#include "HID-Project.h"
#include <FastLED.h>

////////////////////////////////////////////// PINOUT
//          Key Pin layout
//    Rotary, 16, 8, 7, 15, 6
//      LED Strip Pin 10
//////////////////////////////////////////////  KEY PINS

// Pin A (CCW), Pin B (CW), Button Pin
SimpleRotary rotary(2,3,A0);

#define KEY_PIN1 16
#define KEY_PIN2 8
#define KEY_PIN3 7
#define KEY_PIN4 15
#define KEY_PIN5 6

//////////////////////////////////////////////  LED SECTION

// How many leds in your strip?
#define NUM_LEDS 1
#define BRIGHTNESS 255
#define COLOR_ORDER GRB
#define LED_TYPE WS2812

//Data pin to WS2812 LED strip
#define DATA_PIN 10

// Define the array of leds
CRGB leds[NUM_LEDS];
////////////////////////////////////////////// MAIN SETUP

void setup() 
{
  Keyboard.begin();
  Consumer.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  Serial.begin(9600);

  pinMode(6,  INPUT_PULLUP);
  pinMode(7,  INPUT_PULLUP);
  pinMode(8,  INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
}

////////////////////////////////////////////// MAIN LOOP

void loop() 
{
  uint8_t thisSpeed = 10;
    uint8_t deltaHue= 10;
    uint8_t thisHue = beat8(thisSpeed,255); 
    fill_rainbow(leds, NUM_LEDS, thisHue, deltaHue);            
    FastLED.show();
  
  byte i;

  // 0 = not turning, 1 = CW, 2 = CCW
  i = rotary.rotate();
      
  if( i == 1 ) // MEDIA VOLUME UP
      {
      Consumer.write(MEDIA_VOLUME_UP);
      delay(50);
      }

  if( i == 2 ) // MEDIA VOLUME DOWN
      {
      Consumer.write(MEDIA_VOLUME_DOWN);
      delay(50);
      }     
  
  if(digitalRead(6)==LOW)// F20
      {
      Keyboard.write(KEY_F20);
//      leds[0] = CRGB::Red;
//      FastLED.show();
      delay(50);
      }
      
  if(digitalRead(15)==LOW)// F21
      {
      Keyboard.write(KEY_F21);
//      leds[0] = CRGB::Green;
//      FastLED.show();
      delay(50);
      }
      
  if(digitalRead(7)==LOW)// F22
      {
      Keyboard.write(KEY_F22);
//      leds[0] = CRGB::Blue;
//      FastLED.show();
      delay(50);
      }
  
  if(digitalRead(8)==LOW)// F23
      {
      Keyboard.write(KEY_F23);
//      leds[0] = CRGB::Black;
//      FastLED.show();
      delay(50);
      }

  if(digitalRead(16)==LOW)// F24
      {
      Keyboard.write(KEY_F24);
      delay(50);
//      leds[0] = CRGB::Red;
//      FastLED.show();
//      delay(75);
//      leds[0] = CRGB::Green;
//      FastLED.show();
//      delay(75);
//      leds[0] = CRGB::Blue;
//      FastLED.show();
//      delay(75);
//      leds[0] = CRGB::Black;
//      FastLED.show();
//      delay(75);
      }
  
  if(digitalRead(A0)==LOW)// TOGGLE MUTE
      {
      Consumer.write(MEDIA_VOL_MUTE);
      delay(200);
      }
      
}