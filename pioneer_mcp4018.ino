#include "Wire.h"
#define pot_address 0x2F // MCP4018 address is 0x2F or 0101111 in binary

int incomingByte = 0; // for incoming serial data

void setup()
{
  Wire.begin();
  Serial.begin(9600); 
}


void potLoop()
// sends values of 0x00 to 0x7F to pot in order to change the resistance
// equates to 0~127
{
  
  {
    Wire.beginTransmission(pot_address);
    Wire.write(0x00); // 
    Wire.endTransmission();
    Serial.print(" sent - ");
    //Serial.println(rval, HEX);
    delay(2000);
  }
}


void loop()
{
  if (Serial.available() > 0) {
    // read the incoming byte:
   incomingByte = Serial.read();
    
  switch (incomingByte) {
  case 49:
    Serial.print("VOLUME +");
    Wire.beginTransmission(pot_address);
    Wire.write(0x6B); // 16k
    Wire.endTransmission();
    break;
  case 50:
    Serial.print("VOLUME -");
    Wire.beginTransmission(pot_address);
    Wire.write(0x61); // 24k 
    Wire.endTransmission();
    break;
  case 51:
    Serial.print("Source");
    Wire.beginTransmission(pot_address);
    Wire.write(0x7D); // 1.2k 
    Wire.endTransmission();
    break;
  case 52:
    Serial.print("Band");
    Wire.beginTransmission(pot_address);
    Wire.write(0x2F); // 62.75k 
    Wire.endTransmission();
    break;
  case 53: //5
    Serial.print("ATT");
    Wire.beginTransmission(pot_address);
    Wire.write(0x7B); // 3.5k 
    Wire.endTransmission();
    break;
  case 54: //6
    Serial.print("MODE"); //Display off
    Wire.beginTransmission(pot_address);
    Wire.write(0x78); // 5.75k 
    Wire.endTransmission();
    break;
   case 55: //7
    Serial.print("Next");
    Wire.beginTransmission(pot_address);
    Wire.write(0x75); // 8k 
    Wire.endTransmission();
    break;
  case 56: //8
    Serial.print("Previous"); //Display off
    Wire.beginTransmission(pot_address);
    Wire.write(0x71); // 11.25k 
    Wire.endTransmission();
    break;
  default:
    Serial.println("-");
    Wire.beginTransmission(pot_address);
    Wire.write(0x00); // 
    Wire.endTransmission();
    //Serial.print(" ");
    //Serial.println(incomingByte);
    // if nothing else matches, do the default
    break;
}
delay(200);
}
}
