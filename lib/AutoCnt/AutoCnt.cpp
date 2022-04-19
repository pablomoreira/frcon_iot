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
    this->_server = new WiFiServer(80);

    this->_dnss->start(_DNS_PORT, "*", *(this->_apIP));


    this->_server->begin();

}

void AutoCnt::run() {
  this->_dnss->processNextRequest();
  WiFiClient client = this->_server->available();   // escuchar para los clientes entrantes

  if (client) {
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '\n') {

          if (currentLine.length() == 0) {
            Serial.printf("%s",currentLine.c_str());
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            this->_responseHTML = _HEAD;
            this->_responseHTML += _PRE_LIST;
            this->_Scan();////////
            this->_responseHTML += _POST_LIST;
            this->_responseHTML += _END;
            client.printf("\n%s",this->_responseHTML.c_str());
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


void AutoCnt::_Scan(){
  if (WiFi.getMode() == WIFI_OFF) WiFi.mode(WIFI_AP_STA);
  String _str_tmp;
  int n = WiFi.scanNetworks();

  for (int i = 0; i < n; i++){
    Serial.printf("%d %s %d %x\n",i,WiFi.SSID(i).c_str(),WiFi.RSSI(i),WiFi.encryptionType(i));
    _str_tmp = (String(i) + " " + WiFi.SSID(i) + " " + WiFi.RSSI(i) + " " + WiFi.encryptionType(i));
    _str_tmp = "<li>" + _str_tmp + "</li>";
    this->_responseHTML += _str_tmp;
  }
  Serial.printf("---\n");
}
