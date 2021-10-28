
#include "HID-Project.h"
#include <FastLED.h>

///////////////////////////////////
#define NUM_LEDS 10
#define DATA_PIN 10
#define BRIGHTNESS 32
CRGB leds[NUM_LEDS];

int R = 255;
int G = 30;
int B = 198;

///////////////////////////////////
int debounce = 200;
bool toggle = 0;
bool toggle1 = 0;
///////////////////////////////////

char ctrlKey    = KEY_LEFT_CTRL;
char downArrow  = KEY_DOWN_ARROW;
char upArrow    = KEY_UP_ARROW;
char leftArrow  = KEY_LEFT_ARROW;
char rightArrow = KEY_RIGHT_ARROW;
char caps = KEY_CAPS_LOCK;

char F13 = KEY_F13;
char F14 = KEY_F14;
char F15 = KEY_F15;
char F16 = KEY_F16;
char F17 = KEY_F17;
char F18 = KEY_F18;
char F19 = KEY_F19;
char F20 = KEY_F20;
char F21 = KEY_F21;
char F22 = KEY_F22;
char F23 = KEY_F23;
char F24 = KEY_F24;
///////////////////////////////////

void setup() {
  Keyboard.begin();
  Consumer.begin();
///////////LED STUFF////////////////////////////////////////
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  pinMode(DATA_PIN, OUTPUT);

  for (int i = 0; i <= NUM_LEDS; i++)
  {
    leds[i] = CRGB(R, G, B);
  }//end for
  FastLED.show();
  
////////////////////////////////////////////////////////////
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9 , INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
////////////////////////////////////////////////////////////
  
}//end setup/////////////////////////////////////////////////

void loop() 
{
////////////////////////////////////////////////////////////
  if(digitalRead(2)==LOW)//vol up
    {
      Consumer.write(MEDIA_VOL_UP);
      Consumer.write(MEDIA_VOL_UP);
      Consumer.write(MEDIA_VOL_UP);
      delay(debounce*2);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(3)==LOW)//vol dn
    {
      Consumer.write(MEDIA_VOL_DOWN);
      Consumer.write(MEDIA_VOL_DOWN);
      Consumer.write(MEDIA_VOL_DOWN);
      delay(debounce*2);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(4)==LOW)//left arrow
    {
      Keyboard.write(KEY_LEFT_ARROW);
      delay(debounce);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(5)==LOW && toggle1 ==0)//ctrl spam
    {
      Serial.print("5"); Serial.println();
      delay(debounce);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(6)==LOW)// F20
    {
      Keyboard.write(KEY_F20);
      delay(debounce);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(7)==LOW)// F22
    {
      Keyboard.write(KEY_F22);
      delay(debounce);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(8)==LOW)//toggle headset
    {
      Keyboard.write(KEY_F23);
      delay(debounce);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(9)==LOW)//up arrow
    {
      Keyboard.write(KEY_UP_ARROW);
      delay(debounce);
    }
////////////////////////////////////////////////////////////
///PIN 10 USED FOR DATA OUT TO RGB LEDS/////////////////////
////////////////////////////////////////////////////////////
  if(digitalRead(14)==LOW)// caps lock
    {
      Keyboard.write(KEY_CAPS_LOCK);
      delay(debounce);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(15)==LOW)// F21
    {
      Keyboard.write(KEY_F21);
      delay(debounce);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(16)==LOW)//toggle speakers
    {
      Keyboard.write(KEY_F24);
      delay(debounce);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(A0)==LOW)//toggle volume mute
    {
      Consumer.write(MEDIA_VOL_MUTE);
      delay(debounce*2);
    }
////////////////////////////////////////////////////////////
  if(digitalRead(A2)==LOW)//idk yet "green pulse"
    {
      Serial.print("A2"); Serial.println();
      delay(debounce);
    }
}
//end loop/////////////////////////////////////////////////

void CtrlSpam()
{
  while(toggle1 ==1)  
  { 
    delay(150); 
    Keyboard.write(KEY_LEFT_CTRL);
    if(digitalRead(5)==LOW)
    {
      toggle1 = 0;
      delay(debounce);
    }
  }
}
