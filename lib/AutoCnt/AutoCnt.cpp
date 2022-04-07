#include "Arduino.h"
#include "AutoCnt.h"


AutoCnt::AutoCnt() {

}

AutoCnt::AutoCnt(String ssid) {


  //this->_dnss = new DNSServer();
  //this->_server = new WiFiServer(80);

  //this->_dnss->start(_DNS_PORT, "*", this->_apIP);
  //this->_server->begin();
  this->_apIP = new IPAddress(10,11,11,1);
}

AutoCnt::~AutoCnt(void) {


}

void AutoCnt::begin(){

    WiFi.mode(WIFI_OFF); //agrega a empezar con el wifi apagado, evitar estrellarse
    WiFi.mode(WIFI_AP);
    WiFi.softAP("wwwww");
    WiFi.softAPConfig(*(this->_apIP),*(this->_apIP), IPAddress(255, 255, 255, 0));


}
void AutoCnt::loop(){

    while(1){

    }
}
