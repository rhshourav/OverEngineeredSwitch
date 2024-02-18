#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "On";
const char* password = "123456789";
int test;

WebServer server(80);
int relayPin = 2; // Pin for the relay
int pushButtonPin = 19; // Pin for the push button

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  pinMode(pushButtonPin, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, [](){
    server.send(200, "text/html", "<!DOCTYPE html><html><head><title>Relay Control</title><style>.button{width:100px;height:100px;border-radius:50%;background-color:#ccc;display:flex;align-items:center;justify-content:center;font-size:20px;}</style></head><body><h1>Relay Control</h1><button class=\"button\" id=\"relayButton\">Off</button><script>function updateButtonStatus(status){document.getElementById(\"relayButton\").innerText=status;}function fetchRelayStatus(){fetch('/status').then(response=>response.text()).then(status=>updateButtonStatus(status));}document.getElementById(\"relayButton\").addEventListener(\"click\",function(){fetch('/toggle').then(fetchRelayStatus);});setInterval(fetchRelayStatus,1000);</script></body></html>");
  });

  server.on("/status", HTTP_GET, [](){
    server.send(200, "text/plain", test == HIGH ? "On" : "Off");
  });

  server.on("/toggle", HTTP_GET, [](){
    if (digitalRead(relayPin) == HIGH) {
      digitalWrite(relayPin, LOW);
      test = LOW;
    } else {
      digitalWrite(relayPin, HIGH);
      test = HIGH;
    }
    server.send(200, "text/plain", test == HIGH ? "On" : "Off");
  });

  server.begin();
}

void loop() {
  server.handleClient();
  if (digitalRead(pushButtonPin) == HIGH) {
    if (test == HIGH) {
      digitalWrite(relayPin, LOW);
      test = LOW;
    } else {
      digitalWrite(relayPin, HIGH);
      test = HIGH;
    }
    delay(200); // Debouncing delay
  }
}