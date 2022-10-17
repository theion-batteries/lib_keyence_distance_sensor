/*
 * Author: Manash Kumar Mandal
 * Example For receiving data from SerialPort
 */

#define BAUD 115200
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

  if (receivedString.equals("x"))
  {
    digitalWrite(led, HIGH);
    delay(100);
  }
  if (receivedString.equals("xx"))
  {
    digitalWrite(led, LOW);
  }
   if (receivedString.equals("xxx"))
  {
    digitalWrite(led, HIGH);
  }
}
