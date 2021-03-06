////////////////////////////////////////////// INCLUDED LIBRARIES

#include <Arduino.h>
#include <SimpleRotary.h>
#include "HID-Project.h"
#include <FastLED.h>

////////////////////////////////////////////// PINOUT
//          Key Pin layout
//     Rotary, 16, 8, 7, 15, 6
//          LED Strip Pin 10
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
#define NUM_LEDS 5
#define COLOR_ORDER GRB
#define LED_TYPE WS2812
#define FRAMES_PER_SECOND 120

//Data pin to WS2812 LED strip
#define DATA_PIN 10

// Define the array of leds
CRGB leds[NUM_LEDS];

////////////////////////////////////////////// WS2812B LED Rainbow Wave

CRGB Scroll(int pos) {
  CRGB color (0,0,0);
  if(pos < 85) {
    color.g = 0;
    color.r = ((float)pos / 85.0f) * 255.0f;
    color.b = 255 - color.r;
  } else if(pos < 170) {
    color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
    color.r = 255 - color.g;
    color.b = 0;
  } else if(pos < 256) {
    color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
    color.g = 255 - color.b;
    color.r = 0;
  }
  return color;
}

void Scroll();

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
  delay(3000);
}

//////////////////////////////////////////// MAIN LOOP

void loop() {
  for(int j = 0; j < 256; j++) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = Scroll((i * 256 / NUM_LEDS + j) % 256);      
    }

    FastLED.show();
    delay(1);
  
////////////////////////////////////////////// ROTARY INPUTS

  byte f;

  // 0 = not turning, 1 = CW, 2 = CCW
  f = rotary.rotate();
      
  if( f == 1 ) // MEDIA VOLUME UP
      {
      Consumer.write(MEDIA_VOLUME_UP);
      delay(50);
      }

  if( f == 2 ) // MEDIA VOLUME DOWN
      {
      Consumer.write(MEDIA_VOLUME_DOWN);
      delay(50);
      }     
        
  if(digitalRead(A0)==LOW)// TOGGLE MUTE
      {
      Consumer.write(MEDIA_VOL_MUTE);
      delay(200);
      }

////////////////////////////////////////////// KEY INPUTS

  if(digitalRead(6)==LOW)// F20
      {
      Keyboard.write(KEY_F20);
      delay(50);
      }
      
  if(digitalRead(15)==LOW)// F21
      {
      Keyboard.write(KEY_F21);
      delay(50);
      }
      
  if(digitalRead(7)==LOW)// F22
      {
      Keyboard.write(KEY_F22);
      delay(50);
      }
  
  if(digitalRead(8)==LOW)// F23
      {
      Keyboard.write(KEY_F23);
      delay(50);
      }
      
  if(digitalRead(16)==LOW)// F24
      {
      Keyboard.write(KEY_F24);
      delay(50);
      }
    }
}

void Scroll()
{
for(int j = 0; j < 256; j++) 
  {
    for(int i = 0; i < NUM_LEDS; i++) 
      {
      leds[i] = Scroll((i * 256 / NUM_LEDS + j) % 256);      
      }

    FastLED.show();
    delay(5);
  }
}