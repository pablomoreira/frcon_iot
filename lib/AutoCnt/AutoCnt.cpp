#include "Arduino.h"
#include "AutoCnt.h"


AutoCnt::AutoCnt() {

}

AutoCnt::AutoCnt(String ssid) {

  WiFi.mode(WIFI_OFF); //agrega a empezar con el wifi apagado, evitar estrellarse
  WiFi.mode(WIFI_AP);
  //this->_dnss = new DNSServer();
  //this->_server = new WiFiServer(80);
  this->_apIP.fromString("10.10.10.1");

  WiFi.softAP("xxx");
  WiFi.softAPConfig(this->_apIP, this->_apIP, IPAddress(255, 255, 255, 0));

  //this->_dnss->start(_DNS_PORT, "*", this->_apIP);
  //this->_server->begin();

}

AutoCnt::~AutoCnt(void) {


}

void AutoCnt::loop(){
    while(1){

    }
}
