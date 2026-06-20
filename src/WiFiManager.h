#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>
#include <WiFiS3.h>
#include <EEPROM.h>
#include <WiFiUdp.h>

class WiFiManager
{
public:
    enum SystemStatus
    {
        STATUS_IDLE,
        STATUS_AP_MODE,
        STATUS_CONNECTING,
        STATUS_CONNECTED,
        STATUS_RECONNECTING
    };

    typedef void (*WiFiManagerCallback)();

    WiFiManager();
    ~WiFiManager();

    bool autoConnect(const char *apName = "HiTECH_AP", const char *apPassword = nullptr);
    void setPort(uint16_t port);
    void setCustomHTML(const char *html);
    void setKeepServerAlive(bool keepAlive);
    void process();
    void resetSettings();
    String getConnectionStatusJSON();
    SystemStatus getStatus();

    void addParameter(const char *id, const char *label, const char *defaultValue);
    String getParameter(const char *id);

    void setAPCallback(WiFiManagerCallback callback);
    void setSaveCallback(WiFiManagerCallback callback);
    void setConnectCallback(WiFiManagerCallback callback);

private:
    uint16_t _serverPort;
    WiFiServer *_server;
    const char *_customHTML;
    bool _keepServerAlive;
    SystemStatus _currentStatus;

    char _apName[33];
    char _apPassword[65];

    uint8_t _reconnectAttempts;
    uint8_t _reconnectStep;
    unsigned long _lastReconnectTime;

    WiFiUDP _dnsServer;
    WiFiUDP _mDnsServer;

    WiFiClient _client;
    bool _clientActive;
    unsigned long _clientTimeout;
    char _currentLine[256];
    uint16_t _currentLineLen;
    char _requestMethod[8];
    char _requestPath[64];
    char _requestBody[512];
    uint16_t _requestBodyLen;
    bool _isBody;
    int _contentLength;

    bool _pendingReset;
    unsigned long _resetTime;

    struct WiFiProfile
    {
        char ssid[33];
        char password[65];
    };

    struct CustomParamValue
    {
        char id[32];
        char value[65];
    };

    struct EEPROMData
    {
        char magic[4];
        WiFiProfile profiles[3];
        bool useStaticIP;
        uint32_t staticIP;
        uint32_t staticGW;
        uint32_t staticSN;
        uint32_t staticDNS;
        CustomParamValue params[5];
    };

    struct CustomParamDef
    {
        char id[32];
        char label[64];
        char defaultValue[65];
    };

    CustomParamDef _params[5];
    uint8_t _numParams;

    WiFiManagerCallback _apCallback;
    WiFiManagerCallback _saveCallback;
    WiFiManagerCallback _connectCallback;

    void startAP();
    void handleClient();
    void processDNS();
    void processMDNS();
    void resetClientState();
    void processHttpRequest();
    void sendResponse(WiFiClient &client, int code, const String &contentType, const char *content);
    void sendResponse(WiFiClient &client, int code, const String &contentType, const String &content);
    String scanNetworksJSON();
    String getParamsJSON();
    void loadCredentials(EEPROMData &data);
    void saveCredentials(const String &ssid, const String &password, EEPROMData &newData);
    void obfuscateData(uint8_t *data, size_t len);
    String getEncryptionTypeString(int type);
    String extractParam(const char *body, const char *param);
    String getSystemInfoJSON();
    int getFreeMemory();
    String getDeviceUID();
};

#endif