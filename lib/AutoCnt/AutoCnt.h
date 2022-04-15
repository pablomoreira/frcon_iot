#ifndef AutoCnt_h
#define AutoCnt_h
#include <portal.h>


#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>
#include <Server.h>


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
        Server* _server;
        String _ssid;





        //String responseHTML = "<!DOCTYPE html><html><head><title>CaptivePortal</title></head><body><h1>Hello World!</h1><p>This is a captive portal example. All requests will be redirected here.</p></body></html>";

};
#endif
