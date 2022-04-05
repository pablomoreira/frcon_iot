#include "Arduino.h"
#include "AutoCnt.h"

AutoCnt::AutoCnt(void) {
  // constructor implementation here
}

AutoCnt::AutoCnt(String ssid) {

    this->_run = true;
}

AutoCnt::~AutoCnt(void) {
  // desctructor implementation here
}

void AutoCnt::loop(void){
    while(_run){
        delay(3000);
        Serial.printf("%s\n","*");
    }
}
