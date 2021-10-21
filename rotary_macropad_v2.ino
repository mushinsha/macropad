//////////////////////////////////////////////

#include <SimpleRotary.h>
#include "HID-Project.h"

//////////////////////////////////////////////

// Pin A, Pin B, Button Pin
SimpleRotary rotary(2,3,A0);

#define KEY_PIN1 16
#define KEY_PIN2 8
#define KEY_PIN3 7
#define KEY_PIN4 15
#define KEY_PIN5 6

//////////////////////////////////////////////

void setup() {
  Keyboard.begin();
  Consumer.begin();
  Serial.begin(9600);

  pinMode(6,  INPUT_PULLUP);
  pinMode(7,  INPUT_PULLUP);
  pinMode(8,  INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(A0, INPUT_PULLUP);
}

void loop() 
{
  
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
      
  if(digitalRead(15)==LOW)// F21
      {
      Keyboard.write(KEY_F21);
      delay(50);
      }
  
  if(digitalRead(16)==LOW)// F24
      {
      Keyboard.write(KEY_F24);
      delay(50);
      }
  
  if(digitalRead(A0)==LOW)// TOGGLE MUTE
      {
      Consumer.write(MEDIA_VOL_MUTE);
      delay(200);
      }
}
