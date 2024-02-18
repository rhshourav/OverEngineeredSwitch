#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YourSSID";
const char* password = "YourPassword";

WebServer server(80);
int relayPins[] = {2, 3, 4, 5, 6}; // Pins for the 5 relays
int pushButtonPins[] = {19, 18, 17, 16, 15}; // Pins for the 5 push buttons
int relayStatus[] = {LOW, LOW, LOW, LOW, LOW}; // Initial status of the relays

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 5; i++) {
    pinMode(relayPins[i], OUTPUT);
    pinMode(pushButtonPins[i], INPUT_PULLUP);
  }

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, [](){
    // Create HTML with buttons to control each relay
    String html = "<!DOCTYPE html><html><head><title>Relay Control</title><style>.button{width:100px;height:100px;border-radius:50%;background-color:#ccc;display:flex;align-items:center;justify-content:center;font-size:20px;}</style></head><body><h1>Relay Control</h1>";
    for (int i = 0; i < 5; i++) {
      html += "<button class=\"button\" id=\"relayButton" + String(i) + "\">Off</button>";
    }
    html += "<script>";
    // Add JavaScript to control each relay
    for (int i = 0; i < 5; i++) {
      html += "document.getElementById(\"relayButton" + String(i) + "\").addEventListener(\"click\",function(){fetch('/toggle?relay=" + String(i) + "').then(fetchRelayStatus);});";
    }
    html += "function updateButtonStatus(status, buttonId){document.getElementById(buttonId).innerText=status;}function fetchRelayStatus(){";
    for (int i = 0; i < 5; i++) {
      html += "fetch('/status?relay=" + String(i) + "').then(response=>response.text()).then(status=>updateButtonStatus(status, 'relayButton" + String(i) + "'));";
    }
    html += "}setInterval(fetchRelayStatus,1000);</script></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/status", HTTP_GET, [](){
    int relay = server.arg("relay").toInt();
    server.send(200, "text/plain", relayStatus[relay] == HIGH ? "On" : "Off");
  });

  server.on("/toggle", HTTP_GET, [](){
    int relay = server.arg("relay").toInt();
    if (digitalRead(relayPins[relay]) == HIGH) {
      digitalWrite(relayPins[relay], LOW);
      relayStatus[relay] = LOW;
    } else {
      digitalWrite(relayPins[relay], HIGH);
      relayStatus[relay] = HIGH;
    }
    server.send(200, "text/plain", relayStatus[relay] == HIGH ? "On" : "Off");
  });

  server.begin();
}

void loop() {
  server.handleClient();
  for (int i = 0; i < 5; i++) {
    if (digitalRead(pushButtonPins[i]) == HIGH) {
      if (relayStatus[i] == HIGH) {
        digitalWrite(relayPins[i], LOW);
        relayStatus[i] = LOW;
      } else {
        digitalWrite(relayPins[i], HIGH);
        relayStatus[i] = HIGH;
      }
      delay(200); // Debouncing delay
    }
  }
}