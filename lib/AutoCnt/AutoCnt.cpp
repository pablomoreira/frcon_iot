#include "Arduino.h"
#include "AutoCnt.h"

AutoCnt::AutoCnt() {

  this->_apIP = new IPAddress(APIP);
  this->_ssid = "Default ESP32 " +   WiFi.macAddress();
}

AutoCnt::AutoCnt(String ssid) {

  this->_apIP = new IPAddress(APIP);
  this->_ssid = ssid;
  //this->_dnss = new DNSServer();
  //this->_server = new WiFiServer(80);

  //this->_dnss->start(_DNS_PORT, "*", this->_apIP);
  //this->_server->begin();

}

AutoCnt::~AutoCnt(void) {


}

void AutoCnt::begin(){

     void (*handleRoot)(void) = this->_handleRoot;

    WiFi.mode(WIFI_OFF); //agrega a empezar con el wifi apagado, evitar estrellarse
    WiFi.mode(WIFI_AP);

    WiFi.softAP(this->_ssid.c_str());
    WiFi.softAPConfig(*(this->_apIP),*(this->_apIP), IPAddress(255, 255, 255, 0));
    this->_dnss = new DNSServer();
    this->_server = new WebServer(80);

    this->_dnss->start(_DNS_PORT, "*", *(this->_apIP));
    this->_server->on("/", handleRoot);
    this->_server->begin();

}

void AutoCnt::_handleRoot(){
  Serial.printf("%d\n", 3 );
}
