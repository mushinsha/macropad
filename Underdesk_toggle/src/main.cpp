//      Code written by Hunter Nelson 
//          github.com/mushinsha
//    This is a constant work in progress
//        Last Updated - 12/09/2021

////////////////////////////////////////////// INCLUDED LIBRARIES

#include <Arduino.h>
#include <SimpleRotary.h>
#include <HID-Project.h>
#include <FastLED.h>

////////////////////////////////////////////// PINOUT
//
//          Key Pin layout
//     Rotary, 16, 8, 7, 15, 6
//         LED Strip Pin 10
//        Toggle Switches 4, 5
//
//////////////////////////////////////////////  KEY PINS

// Pin A (CCW), Pin B (CW), Button Pin
SimpleRotary rotary(2,3,A0);

#define KEY_PIN1        16
#define KEY_PIN2        8
#define KEY_PIN3        7
#define KEY_PIN4        15
#define KEY_PIN5        6
#define ROTARY_BUTTON   A0
#define TOGGLE_SWITCH1  4
#define TOGGLE_SWITCH2  5

//////////////////////////////////////////////  LED SECTION

// How many leds in your strip?
#define NUM_LEDS 23
#define COLOR_ORDER GRB
#define LED_TYPE WS2812
#define FRAMES_PER_SECOND 120
#define UPDATES_PER_SECOND 100

//Data pin to WS2812 LED strip
#define DATA_PIN 10

// Define the array of leds
CRGB leds[NUM_LEDS];

// WS2812B LED Rainbow Wave

CRGB Scroll(int pos) 
{
  CRGB color (0,0,0);
  if(pos < 85) 
    {
      color.g = 0;
      color.r = ((float)pos / 85.0f) * 255.0f;
      color.b = 255 - color.r;
    } 
  else if(pos < 170) 
    {
      color.g = ((float)(pos - 85) / 85.0f) * 255.0f;
      color.r = 255 - color.g;
      color.b = 0;
    } 
  else if(pos < 256) 
    {
      color.b = ((float)(pos - 170) / 85.0f) * 255.0f;
      color.g = 255 - color.b;
      color.r = 0;
    }
  return color;
}

void ScrollTest();

////////////////////////////////////////////// MAIN SETUP

void setup()
{
  Keyboard.begin();
  Consumer.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  Serial.begin(9600);

//pin 2 is used for rotary CW
//pin 3 is used for rotary CCW

  pinMode(4,  INPUT_PULLUP); //pin 4 is used for toggle switch one
  pinMode(5,  INPUT_PULLUP); //pin 5 is used for toggle switch two
  pinMode(6,  INPUT_PULLUP); //pin 6 is used for key 5
  pinMode(7,  INPUT_PULLUP); //pin 7 is used for key 3
  pinMode(8,  INPUT_PULLUP); //pin 8 is used for key 2
  pinMode(15, INPUT_PULLUP); //pin 15 is used for key 4
  pinMode(16, INPUT_PULLUP); //pin 16 is used for key 1
  pinMode(A0, INPUT_PULLUP); //pin A0 is used for rotary button
  delay(1000);
} // void setup end



//////////////////////////////////////////// MAIN CODE

void loop() 
{
 

////////////////////////////////////////////// ROTARY INPUTS

  byte f;

  // 0 = not turning, 1 = CW, 2 = CCW
  // IF DIRECTION IS REVERSED, SWAP THE '1' AND '2' VALUES BELOW

  f = rotary.rotate();

  if(digitalRead(TOGGLE_SWITCH1)==LOW)// Function switch for VOLUME CONTROL
      {

    if( f == 2 )
        {
        Consumer.write(MEDIA_VOLUME_UP); // MEDIA VOLUME UP
          delay(50);
        }

    if( f == 1 )
        {
        Consumer.write(MEDIA_VOLUME_DOWN); // MEDIA VOLUME DOWN
          delay(50);
        }     
          
    if(digitalRead(ROTARY_BUTTON)==LOW)

        {
        Consumer.write(MEDIA_VOL_MUTE); // TOGGLE MUTE
          delay(200);
          
        }
      }
      
  if(digitalRead(TOGGLE_SWITCH2)==LOW)// Function switch for MEDIA CONTROL
    {

    if( f == 2 )
      {
      Consumer.write(MEDIA_NEXT); // MEDIA NEXT TRACK
        delay(50);
      }

    if( f == 1 )
      {
      Consumer.write(MEDIA_PREVIOUS); // MEDIA PREVIOUS TRACK
        delay(50);
      }     
        
    if(digitalRead(ROTARY_BUTTON)==LOW)
      {
      Consumer.write(MEDIA_PLAY_PAUSE); // MEDIA PLAY/PAUSE
        delay(200);
        
      }        
    }

  ////////////////////////////////////////////// BUTTON KEY INPUTS

  if(digitalRead(TOGGLE_SWITCH1)==LOW)// Function switch to F13-F17
    {

    if(digitalRead(KEY_PIN1)==LOW)
      {
      Keyboard.write(KEY_F20); // Function Key F20
        delay(50);
      }
    
    if(digitalRead(KEY_PIN2)==LOW)
      {
      Keyboard.write(KEY_F21); // Function Key F21
        delay(50);
      }
    
    if(digitalRead(KEY_PIN3)==LOW)
      {
      Keyboard.write(KEY_F22); // Function Key F22 
        delay(50);
      }

    if(digitalRead(KEY_PIN4)==LOW)
      {
      Keyboard.write(KEY_F23); // Function Key F23 (AudioSwitcher to Headset keybind)
        delay(50);
      }
      
    if(digitalRead(KEY_PIN5)==LOW)
      {
      Keyboard.write(KEY_F24); // Function Key F24 (AudioSwitcher to Speakers keybind)
        delay(50);
      }
    }

  if(digitalRead(TOGGLE_SWITCH2)==LOW)// Function switch to F13-F17
    {

    if(digitalRead(KEY_PIN1)==LOW)
      {
      Keyboard.write(KEY_F13); // Function Key F13
        delay(50);
      }
      
    if(digitalRead(KEY_PIN1)==LOW)
      {
      Keyboard.write(KEY_F14); // Function Key F14
        delay(50);
      }

    if(digitalRead(KEY_PIN1)==LOW)
      {
      Keyboard.write(KEY_F15); // Function Key F15
        delay(50);
      }

    if(digitalRead(KEY_PIN1)==LOW)
      {
      Keyboard.write(KEY_F16); // Function Key F16
        delay(50);
      }

    while(digitalRead(KEY_PIN5)==LOW)
      {
      Keyboard.write(KEY_SCROLL_LOCK); // Push To Talk (Discord)
      }
    }
    
   // Rainbow LED Scroll
  } // void loop end

void ScrollTest()
{
  for(int j = 0; j < 256; j++) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = Scroll((i * 256 / NUM_LEDS + j) % 256);      
    }

    FastLED.show();
    delay(5);
  }
}