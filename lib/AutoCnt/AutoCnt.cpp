#include "Arduino.h"
#include "AutoCnt.h"


AutoCnt::AutoCnt() {
    this->_apIP.fromString(_IP_ADDR);
    WiFi.disconnect();   //agrega a empezar con el wifi apagado, evitar estrellarse
    WiFi.mode(WIFI_OFF); //agrega a empezar con el wifi apagado, evitar estrellarse
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(this->_apIP, this->_apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("DNSServer CaptivePortal example");
    this->_dnss.start(_DNS_PORT, "*", this->_apIP);
    this->_server.begin(80);
}

AutoCnt::AutoCnt(String ssid) {


}

AutoCnt::~AutoCnt(void) {


}

void AutoCnt::loop(){
while(1){
    this->_dnss.processNextRequest();
  WiFiClient client = this->_server.available();   // escuchar para los clientes entrantes

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            //client.print(responseHTML);
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    client.stop();
  }
}
}
