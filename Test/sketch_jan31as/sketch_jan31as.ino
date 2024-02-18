#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "On";
const char* password = "123456789";

WebServer server(80);
int relayPin1 = 2; // Pin for relay 1
int relayPin2 = 16; // Pin for relay 2
int relayPin3 = 17; // Pin for relay 3
int relayPin4 = 18; // Pin for relay 4
int relayPin5 = 20; // Pin for relay 5
int pushButtonPin = 19; // Pin for the push button
int relayStatus1 = LOW; // Initial status of relay 1
int relayStatus2 = LOW; // Initial status of relay 2
int relayStatus3 = LOW; // Initial status of relay 3
int relayStatus4 = LOW; // Initial status of relay 4
int relayStatus5 = LOW; // Initial status of relay 5

void setup() {
  Serial.begin(115200);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  pinMode(relayPin4, OUTPUT);
  pinMode(relayPin5, OUTPUT);
  pinMode(pushButtonPin, INPUT_PULLUP);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, [](){
    String html = "<!DOCTYPE html><html><head><title>Relay Control</title><style>.button{width:100px;height:100px;border-radius:50%;background-color:#ccc;display:flex;align-items:center;justify-content:center;font-size:20px;}</style></head><body><h1>Relay Control</h1>";
    html += "<button class=\"button\" id=\"relayButton1\">Off</button>";
    html += "<button class=\"button\" id=\"relayButton2\">Off</button>";
    html += "<button class=\"button\" id=\"relayButton3\">Off</button>";
    html += "<button class=\"button\" id=\"relayButton4\">Off</button>";
    html += "<button class=\"button\" id=\"relayButton5\">Off</button>";
    html += "<script>";
    html += "function updateButtonStatus1(status){document.getElementById(\"relayButton1\").innerText=status;}";
    html += "function updateButtonStatus2(status){document.getElementById(\"relayButton2\").innerText=status;}";
    html += "function updateButtonStatus3(status){document.getElementById(\"relayButton3\").innerText=status;}";
    html += "function updateButtonStatus4(status){document.getElementById(\"relayButton4\").innerText=status;}";
    html += "function updateButtonStatus5(status){document.getElementById(\"relayButton5\").innerText=status;}";
    html += "function fetchRelayStatus(){fetch('/status1').then(response=>response.text()).then(status=>updateButtonStatus1(status));fetch('/status2').then(response=>response.text()).then(status=>updateButtonStatus2(status));fetch('/status3').then(response=>response.text()).then(status=>updateButtonStatus3(status));fetch('/status4').then(response=>response.text()).then(status=>updateButtonStatus4(status));fetch('/status5').then(response=>response.text()).then(status=>updateButtonStatus5(status));}";
    html += "document.getElementById(\"relayButton1\").addEventListener(\"click\",function(){fetch('/toggle1').then(fetchRelayStatus);});";
    html += "document.getElementById(\"relayButton2\").addEventListener(\"click\",function(){fetch('/toggle2').then(fetchRelayStatus);});";
    html += "document.getElementById(\"relayButton3\").addEventListener(\"click\",function(){fetch('/toggle3').then(fetchRelayStatus);});";
    html += "document.getElementById(\"relayButton4\").addEventListener(\"click\",function(){fetch('/toggle4').then(fetchRelayStatus);});";
    html += "document.getElementById(\"relayButton5\").addEventListener(\"click\",function(){fetch('/toggle5').then(fetchRelayStatus);});";
    html += "setInterval(fetchRelayStatus,1000);</script></body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/status1", HTTP_GET, [](){
    server.send(200, "text/plain", relayStatus1 == HIGH ? "On" : "Off");
  });
  server.on("/status2", HTTP_GET, [](){
    server.send(200, "text/plain", relayStatus2 == HIGH ? "On" : "Off");
  });
  server.on("/status3", HTTP_GET, [](){
    server.send(200, "text/plain", relayStatus3 == HIGH ? "On" : "Off");
  });
  server.on("/status4", HTTP_GET, [](){
    server.send(200, "text/plain", relayStatus4 == HIGH ? "On" : "Off");
  });
  server.on("/status5", HTTP_GET, [](){
    server.send(200, "text/plain", relayStatus5 == HIGH ? "On" : "Off");
  });

  server.on("/toggle2", HTTP_GET, [](){
    if (relayStatus2 == HIGH) {
      digitalWrite(relayPin2, LOW);
      relayStatus2 = LOW;
    } else {
      digitalWrite(relayPin2, HIGH);
      relayStatus2 = HIGH;
    }
    server.send(200, "text/plain", relayStatus2 == HIGH ? "On" : "Off");
  });
  server.on("/toggle2", HTTP_GET, [](){
    if (relayStatus2 == HIGH) {
      digitalWrite(relayPin2, LOW);
      relayStatus2 = LOW;
    } else {
      digitalWrite(relayPin2, HIGH);
      relayStatus2 = HIGH;
    }
    server.send(200, "text/plain", relayStatus2 == HIGH ? "On" : "Off");
  });
  server.on("/toggle3", HTTP_GET, [](){
    if (relayStatus3 == HIGH) {
      digitalWrite(relayPin3, LOW);
      relayStatus3 = LOW;
    } else {
      digitalWrite(relayPin3, HIGH);
      relayStatus3 = HIGH;
    }
    server.send(200, "text/plain", relayStatus3 == HIGH ? "On" : "Off");
  });
  server.on("/toggle4", HTTP_GET, [](){
    if (relayStatus4 == HIGH) {
      digitalWrite(relayPin4, LOW);
      relayStatus4 = LOW;
    } else {
      digitalWrite(relayPin4, HIGH);
      relayStatus4 = HIGH;
    }
    server.send(200, "text/plain", relayStatus4 == HIGH ? "On" : "Off");
  });
  server.on("/toggle5", HTTP_GET, [](){
    if (relayStatus5 == HIGH) {
      digitalWrite(relayPin5, LOW);
      relayStatus5 = LOW;
    } else {
      digitalWrite(relayPin5, HIGH);
      relayStatus5 = HIGH;
    }
    server.send(200, "text/plain", relayStatus5 == HIGH ? "On" : "Off");
  });

  server.begin();
}

void loop() {
  server.handleClient();
  if (digitalRead(pushButtonPin) == HIGH) {
    digitalWrite(relayPin1, !relayStatus1);
    relayStatus1 = !relayStatus1;
    digitalWrite(relayPin2, !relayStatus2);
    relayStatus2 = !relayStatus2;
    digitalWrite(relayPin3, !relayStatus3);
    relayStatus3 = !relayStatus3;
    digitalWrite(relayPin4, !relayStatus4);
    relayStatus4 = !relayStatus4;
    digitalWrite(relayPin5, !relayStatus5);
    relayStatus5 = !relayStatus5;
    delay(200); // Debouncing delay
  }
}