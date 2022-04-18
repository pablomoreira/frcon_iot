#include <WiFi.h>
#include <Arduino.h>
#include <TaskScheduler.h>
#include <Preferences.h>
#include "AutoCnt.h"


Scheduler ts;
void autoConnectCallback();
void wifiScanCallback();
AutoCnt autocnt;


Task wifiScan(8 * TASK_SECOND, TASK_FOREVER, &wifiScanCallback, &ts, true);
Task autoConnect(8 * TASK_SECOND, TASK_FOREVER, &wifiScanCallback, &ts, true);

void setup() {
  Serial.begin(115200);
  delay(10);
  autocnt.begin();
}

void loop() {
 delay(5);
 autocnt.run();
}

//70702145

void wifiScanCallback() {

}
