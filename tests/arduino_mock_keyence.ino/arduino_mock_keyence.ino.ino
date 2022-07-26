/*
 * Author: Manash Kumar Mandal
 * Example For receiving data from SerialPort
 */

#define BAUD 9600
#define DELAY_TIME 100
#define led 13



String receivedString;

void setup() {
  Serial.begin(BAUD);
  pinMode(led, OUTPUT);
}

void loop() {
  if (Serial.available() > 0){
    receivedString = Serial.readStringUntil('\n');
  }

  if (receivedString.equals("R0"))
  {
    digitalWrite(led, HIGH);
    Serial.print("R0");
    delay(100);
  }
  else if (receivedString.equals("OFF")) digitalWrite(led, LOW);
}
