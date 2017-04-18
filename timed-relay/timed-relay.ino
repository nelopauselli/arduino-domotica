#include "TimerRele.cpp"

TimerRele rele1(A0, 2, 4);
TimerRele rele2(A0, 8, 6);

void setup() {
  Serial.begin(9600);
  Serial.println("Started");
}

void loop() {
  rele1.check();
  rele2.check();
  
  delay(100);
}
