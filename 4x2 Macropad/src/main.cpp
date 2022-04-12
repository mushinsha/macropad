////////////////////////////////////////////// 
//INCLUDED LIBRARIES

#include "HID-Project.h"
#include <FastLED.h>

////////////////////////////////////////////// 
//     8-Key Pinout (Keycap side up)
//            9 6 5 2 
//            8 7 4 3 
//         LED Strip Pin 10
////////////////////////////////////////////// 
//     10-Key Pinout (Keycap side up)
//           2 5 8 9 16
//           3 4 6 7 10
//         LED Strip Pin 14
//////////////////////////////////////////////  
//KEY PINS

#define KEY_PIN1 2
#define KEY_PIN2 3
#define KEY_PIN3 4
#define KEY_PIN4 5
#define KEY_PIN5 6
#define KEY_PIN6 7
#define KEY_PIN7 8
#define KEY_PIN8 9

//////////////////////////////////////////////  
//LED SECTION

// How many leds in your strip?
#define NUM_LEDS 8
#define BRIGHTNESS 255
#define COLOR_ORDER GRB
#define LED_TYPE WS2812

//Data pin to WS2812 LED strip
#define DATA_PIN 10

// Define the array of leds
CRGB leds[NUM_LEDS];
////////////////////////////////////////////// 
//MAIN SETUP

void setup() 
{
  Keyboard.begin();
  Consumer.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);

  pinMode(2,  INPUT_PULLUP);
  pinMode(3,  INPUT_PULLUP);
  pinMode(4,  INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
}

////////////////////////////////////////////// 
//MAIN RAINBOW LOOP

void loop() {
  for(int j = 0; j < 256; j++) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = Scroll((i * 256 / NUM_LEDS + j) % 256);      
    } 

    FastLED.show();
    delay(1);  

////////////////////////////////////////////// 
//TOP ROW KEYSTROKE LOOP

  if(digitalRead(2)==LOW)// F13
      {
      Keyboard.write(KEY_F13);
      delay(50);
      }

  if(digitalRead(5)==LOW)// F14
      {
      Keyboard.write(KEY_F14);
      delay(75);
      }

  if(digitalRead(8)==LOW)// F15
      {
      Keyboard.write(KEY_F15);
      delay(50);
      }

  if(digitalRead(9)==LOW)// F23
      {
      Keyboard.write(KEY_F23);
      delay(50);
      }

////////////////////////////////////////////// 
//BOTTOM ROW KEYSTROKE LOOP

  if(digitalRead(3)==LOW)// F16
      {
      Keyboard.write(KEY_F16);
      delay(50);
      }
      
  if(digitalRead(4)==LOW)// F17
      {
      Keyboard.write(KEY_F17);
      delay(50);
      }
  
  if(digitalRead(6)==LOW)// F18
      {
      Keyboard.write(KEY_F18);
      delay(100);
      }

  if(digitalRead(7)==LOW)// F24
      {
      Keyboard.write(KEY_F24);
      delay(50);
      }
  }
}

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
    color.r = 1;
  }
  return color;
}