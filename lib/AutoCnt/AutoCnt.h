#ifndef AutoCnt_h
#define AutoCnt_h
#define _DNS_PORT 53
#define _IP_ADDR "10.10.1.1"

#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>


class AutoCnt {
    public:
        AutoCnt();
        AutoCnt(String ssid);
        ~AutoCnt();
        void loop(void);
    private:
        IPAddress _apIP;
        DNSServer _dnss;
        WiFiServer _server;

        //String responseHTML = "<!DOCTYPE html><html><head><title>CaptivePortal</title></head><body><h1>Hello World!</h1><p>This is a captive portal example. All requests will be redirected here.</p></body></html>";

};
#endif
