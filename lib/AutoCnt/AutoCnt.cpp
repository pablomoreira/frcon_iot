#include "Arduino.h"
#include "AutoCnt.h"
void handleRoot(AutoCnt* _t);


AutoCnt::AutoCnt() {

  this->_apIP = new IPAddress(APIP);
  this->_ssid = "Default ESP32 " +   WiFi.macAddress();
}

AutoCnt::AutoCnt(String ssid) {

  this->_apIP = new IPAddress(APIP);
  this->_ssid = ssid;

}

AutoCnt::~AutoCnt(void) {


}

void AutoCnt::begin(){

    //AutoCnt* _t = this;
    WiFi.mode(WIFI_OFF); //agrega a empezar con el wifi apagado, evitar estrellarse
    WiFi.mode(WIFI_AP);

    WiFi.softAP(this->_ssid.c_str());
    WiFi.softAPConfig(*(this->_apIP),*(this->_apIP), IPAddress(255, 255, 255, 0));
    this->_dnss = new DNSServer();
    this->_server = new WebServer(80);

    this->_dnss->start(_DNS_PORT, "*", *(this->_apIP));
    this->_server->on("/", [this](){
        this->_handleRoot();
    });
    this->_server->begin();

}

void AutoCnt::_handleRoot(){
      this->_server->send(200, "text/plain", "hello from esp32!");
}

void AutoCnt::loop(){
    while (1) {
        this->_server->handleClient();
    }
}
