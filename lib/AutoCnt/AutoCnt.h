#ifndef AutoCnt_h
#define AutoCnt_h
#define DNS_PORT 53

#include <Arduino.h>
#include <DNSServer.h>
#include <WiFi.h>


class AutoCnt {
    public:
        AutoCnt(void);
        AutoCnt(String ssid);
        ~AutoCnt(void);
        void loop(void);
    private:

        bool _run;
        //String responseHTML = "<!DOCTYPE html><html><head><title>CaptivePortal</title></head><body><h1>Hello World!</h1><p>This is a captive portal example. All requests will be redirected here.</p></body></html>";

};
#endif
