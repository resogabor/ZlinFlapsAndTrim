#include <Arduino.h>
#include <Joystick.h>

byte encoder0PinA = 2;
byte encoder0PinB = 3;



uint8_t encoder0Pos, encoder0LastPos = 0;
uint8_t encoder0PinALast = LOW;

uint8_t n0 = LOW;
uint16_t z;
Joystick_ joy(0x21, 0x04, 4, 0, false, false, true, false, false, false, false, false, false, false, false);
void setup() {
  joy.begin();
  joy.setZAxisRange(0, 1023);

  pinMode (encoder0PinA,INPUT_PULLUP);
  pinMode (encoder0PinB, INPUT_PULLUP);

}

void loop() {

z = analogRead(A3);
joy.setZAxis(z);

n0 = !digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n0 == HIGH)) 
  {
    if (!digitalRead(encoder0PinB) == LOW) 
    {
      encoder0Pos--;
    } 
    else 
    {
      encoder0Pos++;
    }
   }
  encoder0PinALast = n0;   
 // Serial.println(encoder0Pos); 

  if (encoder0Pos != encoder0LastPos){
    int16_t val_diff = encoder0Pos - encoder0LastPos;
    if (abs(val_diff) > 100){
      encoder0LastPos = encoder0Pos;
    }
    if (encoder0Pos < encoder0LastPos){
      joy.setButton(0, 1);
      delay(20);
      joy.setButton(0, 0);
    }else{
      joy.setButton(1, 1);
      delay(20);
      joy.setButton(1, 0);
    }
    encoder0LastPos = encoder0Pos;
  }  
}

