#include <Arduino.h>

int t_previo = 0, t_delay = 500;
int led = 2;
bool estLed=LOW;

void setup() {
  pinMode (led, OUTPUT);
}

void loop() {
  
  int t_actual = millis();

  if(t_actual - t_previo >= t_delay){
      digitalWrite(led, estLed);
      estLed=!estLed;
    
    t_previo = t_actual;
  }
  }
  