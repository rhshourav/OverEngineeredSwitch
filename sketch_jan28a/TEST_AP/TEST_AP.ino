#include <WiFiManager.h>
 
void setup() {
 
    Serial.begin(115200);
     
    WiFiManager manager;    
     
    bool success = manager.autoConnect("ESP32_AP","password");
 
    if(!success) {
        Serial.println("Failed to connect");
    } 
    else {
        Serial.println("Connected");
    }
}
 
void loop(){}