#include "Arduino.h"
#include "AutoCnt.h"

void __Scan();

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
    WiFi.mode(WIFI_AP_STA);

    WiFi.softAP(this->_ssid.c_str());
    WiFi.softAPConfig(*(this->_apIP),*(this->_apIP), IPAddress(255, 255, 255, 0));
    this->_dnss = new DNSServer();
    this->_server = new Server(80);

    this->_dnss->start(_DNS_PORT, "*", *(this->_apIP));


    this->_server->begin();

}

void AutoCnt::run() {
    this->_dns->processNextRequest();
    WiFiClient client = this->_server->available();   // escuchar para los clientes entrantes

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
              client.print(this->_responseHTML);
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

// void AutoCnt::_handleNotFound() {
//   String message = "File Not Found\n\n";
//   message += "URI: ";
//   message += this->_server->uri();
//   message += "\nMethod: ";
//   message += (this->_server->method() == HTTP_GET) ? "GET" : "POST";
//   message += "\nArguments: ";
//   message += this->_server->args();
//   message += "\n";
//   for (uint8_t i = 0; i < this->_server->args(); i++) {
//     message += " " + this->_server->argName(i) + ": " + this->_server->arg(i) + "\n";
//   }
//   this->_server->send(404, "text/plain", message);
// }
//


void __Scan(){
  if (WiFi.getMode() == WIFI_OFF) WiFi.mode(WIFI_AP_STA);
  int n = WiFi.scanNetworks();

  for (int i = 0; i < n; i++){
    Serial.printf("%d %s %d %x\n",i,WiFi.SSID(i).c_str(),WiFi.RSSI(i),WiFi.encryptionType(i));
  }
  Serial.printf("---\n");
}
