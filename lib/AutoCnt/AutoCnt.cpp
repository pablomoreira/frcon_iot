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
    this->_server = new WebServer(80);

    this->_dnss->start(_DNS_PORT, "*", *(this->_apIP));
    this->_server->on("/", [this](){
        this->_handleRoot();
    });

    this->_server->onNotFound([this](){
        //this->_handleNotFound();
        this->_handleRoot();
    });
    this->_server->on("/ScanWiFi",__Scan);


    this->_server->begin();

}

void AutoCnt::_handleRoot(){
      String message = "<!DOCTYPE html>";
      message += "<html lang=\"es\">";
      message += "<head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"> <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\"> <title>Título del documento HTML</title> </head>";
      message += "<body> <p>AutoCnt</p>";
      message += "<p> <a href=\"ScanWiFi\"><button>Scan</button></a>";
      message += "</body> </html>";
      this->_server->send(200, "text/html", message);

      Serial.printf("%s\n", this->_server->uri().c_str());
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
void AutoCnt::loop(){
    while (1) {
      this->_dnss->processNextRequest();
      this->_server->handleClient();

      delay(5);

    }
}

void __Scan(){
  if (WiFi.getMode() == WIFI_OFF) WiFi.mode(WIFI_AP_STA);
  int n = WiFi.scanNetworks();

  for (int i = 0; i < n; i++){
    Serial.printf("%d %s %d %x\n",i,WiFi.SSID(i).c_str(),WiFi.RSSI(i),WiFi.encryptionType(i));
  }
  Serial.printf("---\n");
}
