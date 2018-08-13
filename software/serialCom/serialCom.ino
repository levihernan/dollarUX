#include <SevSeg.h>

SevSeg sevseg; //Initiate a seven segment controller object

int incomingByte = 0;   // for incoming serial data
String incomingString;
float readFloat = 0;
int readInt= 0;

void setup() 
{
    
  
    Serial.begin(9600);     // communication with the host computer
    //while (!Serial)   { ; }
    // Start the software serial for communication with the ESP8266
    //ESPserial.begin(9600);  
 
    Serial.println("");
    Serial.println("Start your engines.");

    byte numDigits = 4;

    byte digitPins[] = {2, 3, 4, 5};
    
    byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
    
    sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
    
    sevseg.setBrightness(10);
}
 
void loop() 
{
    leerDolar();
    sevseg.refreshDisplay(); // Must run repeatedly
    
}

void leerDolar(){

  // listen for communication from the ESP8266 and then write it to the serial monitor
    //if ( ESPserial.available() )   {  
    if ( Serial.available() )   {  
        readFloat = Serial.parseFloat();
        Serial.print("Read float: ");
        Serial.println(readFloat);
        readInt = readFloat * 100;
        Serial.println(readInt);
        if (readInt > 10) {
          sevseg.setNumber(readInt, 2);
          sevseg.refreshDisplay(); // Must run repeatedly
        }
        
        delay(3000);
      }
 
    // listen for user input and send it to the ESP8266
    //if ( Serial.available() )       {  ESPserial.write( Serial.read() );  }
    
}

