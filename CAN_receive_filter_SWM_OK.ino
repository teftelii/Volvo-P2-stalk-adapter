// CAN Volvo SWM Receive filter 
// ok, 27.12.2022 tested

#include <mcp_can.h>
#include <SPI.h>

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];                        // Array to store serial string
char idString[128];  

#define CAN0_INT 2                              // Set INT to pin 2
MCP_CAN CAN0(10);                               // Set CS to pin 10


void setup()
{
  Serial.begin(115200);
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_125KBPS, MCP_16MHZ) == CAN_OK)
    Serial.println("Initialized Successfully!");
  else
    Serial.println("Error...");
  
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT);                            // Configuring pin for /INT input
  
  Serial.println("SWD sniffer");
}

void loop()
{
  if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)

    if((rxId & 0x1FFFFFFF) == 0x0131726C){
      sprintf(msgString, "ID: 0x%.8lX Data:", (rxId & 0x1FFFFFFF));
      Serial.print(msgString);
    
    for(byte i = 0; i<len; i++){
        sprintf(msgString, " 0x%.2X", rxBuf[i]);
        Serial.print(msgString);
        }
    Serial.println();
    }
        
    
  }

}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
