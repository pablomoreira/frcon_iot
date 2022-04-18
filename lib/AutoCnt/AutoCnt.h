#ifndef AutoCnt_h
#define AutoCnt_h
#include <portal.h>
#include "html.h"


#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <WiFiServer.h>


class AutoCnt {
    public:
        AutoCnt();
        AutoCnt(String ssid);
        ~AutoCnt();
        void begin();
        void run();
    private:
        IPAddress* _apIP;
        DNSServer* _dnss;
        WiFiServer* _server;
        String _ssid;
        void _Scan();
        String _responseHTML;


};
#endif
