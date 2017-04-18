#ifndef TIMER_RELE
#define TIMER_RELE

#include "Arduino.h"

#define DEBUG

class TimerRele{
  public:
  TimerRele(byte pinIn, byte pinReset, byte pinOut){
    _pinIn = pinIn;
    _pinReset = pinReset;
    _pinOut = pinOut;
    
    pinMode(_pinOut, OUTPUT);
    pinMode(pinReset, INPUT);
  
    turnOff();
  }

  void check(){
    bool reseted = digitalRead(_pinReset);
    
    if(reseted ==  HIGH){
      if(!_on)
        reset();
      else
        turnOff();  

      while(digitalRead(_pinReset)) {
        #ifdef DEBUG
        Serial.println("esperando soltar el boton");
        #endif
        delay(10);
      }
    }
    
    if(_on){
      unsigned long duration = map(analogRead(_pinIn), 0, 1023, 0, 21600);
      unsigned long elapsed = millis() / 1000;

      #ifdef DEBUG
      Serial.print(elapsed);Serial.print(" / ");Serial.println(_startAt + duration);
      #endif
      
      if(_startAt + duration  < elapsed){
        turnOff();
      }
    }
  }

  void reset(){
    Serial.println("reset");
        
    turnOn();
    _startAt = millis() / 1000;
    
    unsigned long duration = map(analogRead(_pinIn), 0, 1023, 0, 21600);
    Serial.print("Start at: ");Serial.print(_startAt);Serial.println(" s");
    Serial.print("Duration: ");Serial.print(duration);Serial.println(" s");
  }

  void turnOff(){
    Serial.println("turn off");
    digitalWrite(_pinOut, HIGH);
    _on = false;
  }

  void turnOn(){
    Serial.println("turn on");
    digitalWrite(_pinOut, LOW);
    _on = true;
  }

  private:
    byte _pinIn = 0;
    byte _pinOut = 0;
    byte _pinReset = 0;
    unsigned long _startAt = 0;
    
    bool _on;
};

#endif
