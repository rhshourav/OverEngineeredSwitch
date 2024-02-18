#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "On";
const char* password = "123456789";
const int relayPins[] = {14, 27, 26, 25, 4}; // Replace with the actual pins connected to the relays
const int numRelays = 5;
const int lightPin = 13; // Replace with the actual pin connected to the light
int lightState;
WebServer server(80);

const char* html = R"=====(
<!DOCTYPE html>
<html>
<head>
  <style>
    /* Your provided CSS styles */
    body {
      background-color: #222;
      color: #fff;
      font-family: Arial, sans-serif;
      text-align: center;
    }

    h2 {
      color: #00f7ff;
    }

    .button-container {
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      margin-top: 20px;
    }

    .button {
      width: 80px;
      height: 80px;
      border-radius: 50%;
      color: #fff;
      margin: 10px;
      display: flex;
      flex-direction: column;
      justify-content: center;
      align-items: center;
      text-align: center;
      transition: background-color 0.3s;
    }

    .button:hover {
      opacity: 0.8;
    }

    .button.active {
      background-color: #0f0; /* Change to green when active */
    }

    /* New styles for each button */
    #relay1 {
      background-color: #FF6F61; /* Coral color */
    }

    #relay2 {
      background-color: #5DADE2; /* Sky blue color */
    }

    #relay3 {
      background-color: #2E86C1; /* Dark cerulean color */
    }

    #relay4 {
      background-color: #48C9B0; /* Medium turquoise color */
    }

    #relay5 {
      background-color: #F4D03F; /* Sahara color */
    }
  </style>
</head>
<body>

<h2>Relay Control</h2>

<div class="button-container">
  <div class="button" id="relay1" onclick="toggleRelay(1)">
    <div>Relay 1</div>
    <div id="relay1-state">Off</div>
  </div>
  <div class="button" id="relay2" onclick="toggleRelay(2)">
    <div>Relay 2</div>
    <div id="relay2-state">Off</div>
  </div>
  <div class="button" id="relay3" onclick="toggleRelay(3)">
    <div>Relay 3</div>
    <div id="relay3-state">Off</div>
  </div>
  <div class="button" id="relay4" onclick="toggleRelay(4)">
    <div>Relay 4</div>
    <div id="relay4-state">Off</div>
  </div>
  <div class="button" id="relay5" onclick="toggleRelay(5)">
    <div>Light</div>
    <div id="relay5-state">Off</div>
  </div>
</div>

<script>
function toggleRelay(relayNum) {
  var state = document.getElementById("relay" + relayNum + "-state").innerHTML;
  var newState = state === "Off" ? "On" : "Off";
  document.getElementById("relay" + relayNum + "-state").innerHTML = newState;
  // Send a GET request to the ESP32 to control the relay
  fetch("/control?relay=" + relayNum + "&state=" + newState);
}

</script>

</body>
</html>
)=====";

void handleRoot() {
  server.send(200, "text/html", html);
}

void handleControl() {
  if (server.args() > 0) {
    for (uint8_t i = 0; i < server.args(); i++) {
      if (server.argName(i) == "relay") {
        // Handle the relay control based on the "state" parameter
        int relayNum = server.arg("relay").toInt();
        String state = server.arg("state");
        if (state == "On") {
          // Turn on the relay
          digitalWrite(relayPins[relayNum - 1], HIGH);
          Serial.print("Relay ");
          Serial.print(relayNum);
          Serial.println(" turned on");
        } else if (state == "Off") {
          // Turn off the relay
          digitalWrite(relayPins[relayNum - 1], LOW);
          Serial.print("Relay ");
          Serial.print(relayNum);
          Serial.println(" turned off");
        }
      } 
      
    }
  }
  server.send(200, "text/plain", "OK");
}

void handleLightControl() {
  if (server.arg("state") == "on") {
    // Turn on the light relay
    lightState = true;
    // Update the Blynk app with the new light state
    //Blynk.virtualWrite(V5, lightState);
  } else if (server.arg("state") == "off") {
    // Turn off the light relay
    lightState = false;
    Serial.print("Ldafsdjfklsjdf");
    // Update the Blynk app with the new light state
    //Blynk.virtualWrite(V5, lightState);
  }
  server.send(200, "text/plain", "OK");
}
void setup() {
  Serial.begin(115200);
  for (int i = 0; i < numRelays; i++) {
    pinMode(relayPins[i], OUTPUT);
  }
  pinMode(lightPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  server.on("/", HTTP_GET, handleRoot);
  server.on("/control", HTTP_GET, handleControl);
  server.on("/light", handleLightControl);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}