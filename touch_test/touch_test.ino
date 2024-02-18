int touchCount;
bool initCount = false ;
int touchLoopCount = 0;
const int touchCountDelay = 100 ;
const int maxCount = 5;
#define touchPin 13


void setup(){
  Serial.begin(115200);
  delay(2000);
  Serial.println("Initing Program");
}

void loop(){
  if (touchRead(touchPin) <= 50){
    initCount = true;
    touchCount = 0;
  }
  while (initCount == true && touchLoopCount <= 100){
    int16_t x1, y1;
    uint16_t w, h;
    
    if (touchRead(touchPin) <= 40 ){
      touchCount++;
      Serial.println(touchCount);
      delay(touchCountDelay);
      touchLoopCount = 0;
      
    }
    resetDisplay();
    display.setTextSize(2);
    display.println("Selected :");
    display.getTextBounds(touchCount, 0, 0, &x1, &y1, &w, &h);
    display.setCursor((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - w) /2 );
    display.setTextSize(3);
    display.println(touchCount);
    display.display();
    
    delay(10);
    touchLoopCount++;
  }
  if (touchCount >= maxCount){
    touchCount = 0;
    touchLoopCount = 0;
    initCount = false;
  }else if (touchCount == 1){
    touchCount = 0;
    touchLoopCount = 0;
    initCount = false;
     if (relayStatus1 == LOW) {
        Serial.print("Relay 1 = ON");
        Blynk.virtualWrite(V1, 1);
        relayStatus1 = HIGH;
       resetDisplay();
       clearDisplay();
        display.setTextSize(2);
        display.println("Relay 1:");
        display.setTextSize(3);
        display.setCursor(35,23);
        display.println("ON");
        display.display();
        delay(500);
      } else {
        Serial.print("Relay 1 = OFF");
        Blynk.virtualWrite(V1, 0);
        relayStatus1 = LOW;
        resetDisplay();
        clearDisplay();
        display.setTextSize(2);
        display.println("Relay 1:");
        display.setTextSize(3);
        display.setCursor(35,23);
        display.println("OFF");
        display.display();
        delay(500);
      }
    }else if (touchCount == 2){
      touchCount = 0;
    touchLoopCount = 0;
    initCount = false;
     if (relayStatus3 == LOW) {
        Serial.print("Relay 2 = ON");
        Blynk.virtualWrite(V2, 1);
        relayStatus2 = HIGH;
       resetDisplay();
       clearDisplay();
        display.setTextSize(2);
        display.println("Relay 2:");
        display.setTextSize(3);
        display.setCursor(35,23);
        display.println("ON");
        display.display();
        delay(500);
      } else {
        Serial.print("Relay 2 = OFF");
        Blynk.virtualWrite(V2, 0);
        relayStatus2 = LOW;
        resetDisplay();
        clearDisplay();
        display.setTextSize(2);
        display.println("Relay 2:");
        display.setTextSize(3);
        display.setCursor(35,23);
        display.println("OFF");
        display.display();
        delay(500);
      }
    }else if (touchCount == 3){
      touchCount = 0;
    touchLoopCount = 0;
    initCount = false;
     if (relayStatus3 == LOW) {
        Serial.print("Relay 3 = ON");
        Blynk.virtualWrite(V3, 1);
        relayStatus3 = HIGH;
       resetDisplay();
       clearDisplay();
        display.setTextSize(2);
        display.println("Relay 3:");
        display.setTextSize(3);
        display.setCursor(35,23);
        display.println("ON");
        display.display();
        delay(500);
      } else {
        Serial.print("Relay 3 = OFF");
        Blynk.virtualWrite(V3, 0);
        relayStatus3 = LOW;
        resetDisplay();
        clearDisplay();
        display.setTextSize(2);
        display.println("Relay 3:");
        display.setTextSize(3);
        display.setCursor(35,23);
        display.println("OFF");
        display.display();
        delay(500);
      }
    }else if (touchCount == 4){
      touchCount = 0;
    touchLoopCount = 0;
    initCount = false;
     if (relayStatus4 == LOW) {
        Serial.print("Relay 4 = ON");
        Blynk.virtualWrite(V4, 1);
        relayStatus4 = HIGH;
       resetDisplay();
       clearDisplay();
        display.setTextSize(2);
        display.println("Relay 4:");
        display.setTextSize(3);
        display.setCursor(35,23);
        display.println("ON");
        display.display();
        delay(500);
      } else {
        Serial.print("Relay 4 = OFF");
        Blynk.virtualWrite(V4, 0);
        relayStatus4 = LOW;
        resetDisplay();
        clearDisplay();
        display.setTextSize(2);
        display.println("Relay 4:");
        display.setTextSize(3);
        display.setCursor(35,23);
        display.println("OFF");
        display.display();
        delay(500);
      }
    }else if (touchCount == 5) {
      touchCount = 0;
    touchLoopCount = 0;
    initCount = false;
    if (relayStatus5 == HIGH) {
      relayStatus5 = LOW;
      Blynk.virtualWrite(V5, 0);
      resetDisplay();
      clearDisplay();
      display.setTextSize(2);
      display.println("Light :");
      display.setTextSize(3);
      display.setCursor(35,23);
      display.println("OFF");
      display.display();
      delay(2000);
    } else {
      relayStatus5 = HIGH;
      Blynk.virtualWrite(V5, 1);
      resetDisplay();
      clearDisplay();
      display.setTextSize(2);
      display.println("Light :");
      display.setTextSize(3);
      display.setCursor(35,23);
      display.println("ON");
      display.display();
      delay(2000);
    }
    }

}



