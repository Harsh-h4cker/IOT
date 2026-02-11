#include <Ticker.h>

Ticker ticker;

void led()
{
  int i = digitalRead(2);
  digitalWrite(2, !i);
}


void setup() {
  // put your setup code here, to run once:
pinMode(2, OUTPUT);
ticker.attach(1, led);
}

void loop() {
  // put your main code here, to run repeatedly:


}