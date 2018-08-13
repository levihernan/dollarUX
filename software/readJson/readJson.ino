#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

// WiFi Parameters
//const char* ssid = "salta";
//const char* password = "atlas-8600";


typedef union {
  float floatingPoint;
  byte binary[4];
} binaryFloat;


void setup() {
  Serial.begin(115200);
  //WiFi.begin(ssid, password);
 
  //while (WiFi.status() != WL_CONNECTED) {
  //  delay(1000);
  //  //Serial.println("Connecting...");
  //}

  WiFiManager wifiManager;
  wifiManager.autoConnect("DollarWIFI");

}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    //Serial.println("CONECTED");
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://ws.geeklab.com.ar/dolar/get-dolar-json.php");
    int httpCode = http.GET();
    //Check the returning code                                                                  
    if (httpCode > 0) {
      // Parsing
      const size_t bufferSize = 512; //WTF?
      DynamicJsonBuffer jsonBuffer(bufferSize);
      JsonObject& root = jsonBuffer.parseObject(http.getString());
      // Parameters
      int id = root["id"]; // 1
      const char* libre = root["libre"]; // "LIBRE"
      String libreString = root["libre"]; // "LIBRE" en string
      int libreInt = libreString.toInt();
      binaryFloat libreFloat;
      libreFloat.floatingPoint = libreString.toFloat();
      
      const char* blue = root["blue"]; // "BLUE"
      // Output to serial monitor
      //Serial.print("Libre:");
      //Serial.println(libre);
      //Serial.print("Blue:");
      //Serial.println(blue);
      
      //Serial.println(libreFloat.floatingPoint);
      Serial.flush();
      Serial.println(libreFloat.floatingPoint);
      
      
      delay(500);

      
    }
    http.end();   //Close connection
  }
  // Delay
  delay(60000);
}
