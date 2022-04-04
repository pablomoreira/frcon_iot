#include <WiFi.h>
#include <Arduino.h>
#include <TaskScheduler.h>
#include <Preferences.h>

Scheduler ts;

void wifiScanCallback();

Task wifiScan(8 * TASK_SECOND, TASK_FOREVER, &wifiScanCallback, &ts, true);

void setup() {
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_OFF);
  delay(10);

}

void loop() {
  ts.execute();
}

//70702145

void wifiScanCallback() {
  if (WiFi.getMode() == WIFI_OFF) WiFi.mode(WIFI_STA);
  int n = WiFi.scanNetworks();

  for (int i = 0; i < n; i++){
    Serial.printf("%d %s %d %x\n",i,WiFi.SSID(i).c_str(),WiFi.RSSI(i),WiFi.encryptionType(i));


  }
  Serial.printf("---\n");
}
