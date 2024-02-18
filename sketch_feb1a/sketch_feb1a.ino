const int ir_in = 33 ;
const int led = 2;

void setup() {
  Serial.begin(115200);
  pinMode(ir_in, INPUT);
  pinMode(led, OUTPUT);
  Serial.print("initing Program:!");
  // put your setup code here, to run once:

}

void loop() {
  Serial.println(digitalRead(ir_in));
  if (digitalRead(ir_in)){
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW);
  }
  // put your main code here, to run repeatedly:

}
