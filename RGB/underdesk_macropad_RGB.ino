////////////////////////////////////////////// INCLUDED LIBRARIES

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
#define NUM_LEDS 6
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

//void loop() 
//{
//  //delay(250);
//  uint8_t thisSpeed = 10;
//    uint8_t deltaHue= 5;
//    uint8_t thisHue = beat8(thisSpeed,255); 
//    fill_rainbow(leds, NUM_LEDS, thisHue, deltaHue);            
//    FastLED.show();
//}

void loop() {
  for(int j = 0; j < 256; j++) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = Scroll((i * 256 / NUM_LEDS + j) % 256);      
    } 

    FastLED.show();
    delay(1);  
  
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
//      leds[6] = CRGB::Green;
//      FastLED.show();
      delay(50);
      }
      
  if(digitalRead(7)==LOW)// F22
      {
      Keyboard.write(KEY_F22);
//      leds[6] = CRGB::Blue;
//      FastLED.show();
      delay(50);
      }
  
  if(digitalRead(8)==LOW)// F23
      {
      Keyboard.write(KEY_F23);
//      leds[6] = CRGB::Black;
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
}

// WS2812B LED Strip switches Red and Green
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
