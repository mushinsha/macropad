////////////////////////////////////////////// 
//INCLUDED LIBRARIES

#include "HID-Project.h"
#include <FastLED.h>

////////////////////////////////////////////// 
//     Key Pinout (Keycap side up)
//            9 6 5 2
//            8 7 4 3
//         LED Strip Pin 10
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
#define NUM_LEDS 2
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

void loop() 
{
  delay(1);
  uint8_t thisSpeed = 50;
    uint8_t deltaHue= 10;
    uint8_t thisHue = beat8(thisSpeed,255); 
    fill_rainbow(leds, NUM_LEDS, thisHue, deltaHue);            
    FastLED.show();

////////////////////////////////////////////// 
//TOP ROW KEYSTROKE LOOP

  if(digitalRead(9)==LOW)// F13
      {
      Keyboard.write(KEY_F13);
      delay(50);
      }

  if(digitalRead(6)==LOW)// F16
      {
      Keyboard.write(KEY_F16);
      delay(75);
      }

  if(digitalRead(5)==LOW)// F17
      {
      Keyboard.write(KEY_F17);
      delay(50);
      }

  if(digitalRead(2)==LOW)// F20
      {
      Keyboard.write(KEY_F20);
      delay(50);
      }

////////////////////////////////////////////// 
//BOTTOM ROW KEYSTROKE LOOP

  if(digitalRead(8)==LOW)// F14
      {
      Keyboard.write(KEY_F14);
      delay(50);
      }
      
  if(digitalRead(7)==LOW)// F15
      {
      Keyboard.write(KEY_F15);
      delay(50);
      }
  
  if(digitalRead(4)==LOW)// F18
      {
      Keyboard.write(KEY_F18);
      delay(100);
      }

  if(digitalRead(3)==LOW)// F19
      {
      Keyboard.write(KEY_F19);
      delay(50);
      }      

}
