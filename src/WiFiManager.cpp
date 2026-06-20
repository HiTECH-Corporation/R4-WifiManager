#include "WiFiManager.h"
#include "CaptivePortal.h"
#include "bsp_api.h"

extern "C" char *sbrk(int incr);

WiFiManager::WiFiManager()
{
    _serverPort = 80;
    _server = nullptr;
    _customHTML = captive_portal_html;
    _keepServerAlive = true;
    _currentStatus = STATUS_IDLE;
    _reconnectAttempts = 0;
    _lastReconnectTime = 0;
    _numParams = 0;
    _apCallback = nullptr;
    _saveCallback = nullptr;
    _connectCallback = nullptr;
    memset(_apName, 0, sizeof(_apName));
    memset(_apPassword, 0, sizeof(_apPassword));
    _clientActive = false;
    resetClientState();
}

WiFiManager::~WiFiManager()
{
    if (_server != nullptr)
        delete _server;
}

void WiFiManager::resetClientState()
{
    if (_clientActive && _client) {
        _client.stop();
    }
    _clientActive = false;
    _currentLineLen = 0;
    memset(_requestMethod, 0, sizeof(_requestMethod));
    memset(_requestPath, 0, sizeof(_requestPath));
    memset(_requestBody, 0, sizeof(_requestBody));
    _requestBodyLen = 0;
    _isBody = false;
    _contentLength = 0;
}

void WiFiManager::setPort(uint16_t port)
{
    _serverPort = port;
}

void WiFiManager::setCustomHTML(const char *html)
{
    _customHTML = html;
}

void WiFiManager::setKeepServerAlive(bool keepAlive)
{
    _keepServerAlive = keepAlive;
}

void WiFiManager::setAPCallback(WiFiManagerCallback callback)
{
    _apCallback = callback;
}

void WiFiManager::setSaveCallback(WiFiManagerCallback callback)
{
    _saveCallback = callback;
}

void WiFiManager::setConnectCallback(WiFiManagerCallback callback)
{
    _connectCallback = callback;
}

WiFiManager::SystemStatus WiFiManager::getStatus()
{
    return _currentStatus;
}

void WiFiManager::addParameter(const char *id, const char *label, const char *defaultValue)
{
    if (_numParams < 5)
    {
        strncpy(_params[_numParams].id, id, 31);
        strncpy(_params[_numParams].label, label, 63);
        strncpy(_params[_numParams].defaultValue, defaultValue, 64);
        _numParams++;
    }
}

String WiFiManager::getParameter(const char *id)
{
    EEPROMData data;
    loadCredentials(data);
    if (strncmp(data.magic, "HTC2", 4) == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            if (strcmp(data.params[i].id, id) == 0)
            {
                return String(data.params[i].value);
            }
        }
    }
    for (int i = 0; i < _numParams; i++)
    {
        if (strcmp(_params[i].id, id) == 0)
        {
            return String(_params[i].defaultValue);
        }
    }
    return "";
}

void WiFiManager::obfuscateData(uint8_t *data, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        data[i] ^= 0xA5;
    }
}

void WiFiManager::loadCredentials(EEPROMData &data)
{
    EEPROM.get(0, data);
    obfuscateData((uint8_t *)&data, sizeof(EEPROMData));
}

void WiFiManager::saveCredentials(const String &ssid, const String &password, EEPROMData &newData)
{
    EEPROMData existingData;
    loadCredentials(existingData);

    if (strncmp(existingData.magic, "HTC2", 4) == 0)
    {
        bool found = false;
        for (int i = 0; i < 3; i++)
        {
            if (String(existingData.profiles[i].ssid) == ssid)
            {
                memset(&newData.profiles, 0, sizeof(newData.profiles));
                strncpy(newData.profiles[0].ssid, ssid.c_str(), 32);
                strncpy(newData.profiles[0].password, password.c_str(), 64);
                int idx = 1;
                for (int j = 0; j < 3; j++)
                {
                    if (i != j && idx < 3)
                    {
                        memcpy(&newData.profiles[idx], &existingData.profiles[j], sizeof(WiFiProfile));
                        idx++;
                    }
                }
                found = true;
                break;
            }
        }
        if (!found)
        {
            memset(&newData.profiles, 0, sizeof(newData.profiles));
            strncpy(newData.profiles[0].ssid, ssid.c_str(), 32);
            strncpy(newData.profiles[0].password, password.c_str(), 64);
            memcpy(&newData.profiles[1], &existingData.profiles[0], sizeof(WiFiProfile));
            memcpy(&newData.profiles[2], &existingData.profiles[1], sizeof(WiFiProfile));
        }
    }
    else
    {
        memset(&newData.profiles, 0, sizeof(newData.profiles));
        strncpy(newData.profiles[0].ssid, ssid.c_str(), 32);
        strncpy(newData.profiles[0].password, password.c_str(), 64);
    }

    strncpy(newData.magic, "HTC2", 4);
    obfuscateData((uint8_t *)&newData, sizeof(EEPROMData));
    EEPROM.put(0, newData);
}

void WiFiManager::resetSettings()
{
    EEPROMData creds;
    memset(&creds, 0, sizeof(EEPROMData));
    obfuscateData((uint8_t *)&creds, sizeof(EEPROMData));
    EEPROM.put(0, creds);
}

bool WiFiManager::autoConnect(const char *apName, const char *apPassword)
{
    if (apName != nullptr)
        strncpy(_apName, apName, 32);
    if (apPassword != nullptr)
        strncpy(_apPassword, apPassword, 64);

    EEPROMData data;
    loadCredentials(data);

    if (strncmp(data.magic, "HTC2", 4) == 0)
    {
        if (data.useStaticIP)
        {
            IPAddress ip(data.staticIP);
            IPAddress gw(data.staticGW);
            IPAddress sn(data.staticSN);
            IPAddress dns(data.staticDNS);
            WiFi.config(ip, dns, gw, sn);
        }

        bool connected = false;
        for (int i = 0; i < 3; i++)
        {
            if (strlen(data.profiles[i].ssid) > 0)
            {
                _currentStatus = STATUS_CONNECTING;
                WiFi.begin(data.profiles[i].ssid, data.profiles[i].password);
                delay(500);

                unsigned long startAttemptTime = millis();
                while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 15000)
                {
                    delay(500);
                }

                if (WiFi.status() == WL_CONNECTED)
                {
                    connected = true;
                    break;
                }
            }
        }

        if (connected)
        {
            _currentStatus = STATUS_CONNECTED;

            unsigned long ipWaitTime = millis();
            while (WiFi.localIP().toString() == "0.0.0.0" && millis() - ipWaitTime < 5000)
            {
                delay(100);
            }

            if (_keepServerAlive)
            {
                if (_server != nullptr)
                    delete _server;
                _server = new WiFiServer(_serverPort);
                _server->begin();
            }
            else
            {
                if (_server != nullptr)
                {
                    delete _server;
                    _server = nullptr;
                }
            }

            if (_connectCallback)
                _connectCallback();
            return true;
        }
    }

    startAP();
    return false;
}

void WiFiManager::startAP()
{
    _currentStatus = STATUS_AP_MODE;
    if (_apCallback)
        _apCallback();

    if (strlen(_apPassword) >= 8)
    {
        WiFi.beginAP(_apName, _apPassword);
    }
    else
    {
        WiFi.beginAP(_apName);
    }

    if (_server != nullptr)
        delete _server;
    _server = new WiFiServer(_serverPort);
    _server->begin();
    
    _dnsServer.begin(53);
    _mDnsServer.begin(5353);
}

void WiFiManager::processDNS()
{
    int packetSize = _dnsServer.parsePacket();
    if (packetSize > 0 && packetSize <= 512)
    {
        uint8_t buf[512];
        _dnsServer.read(buf, packetSize);
        if (packetSize < 12) return;
        
        buf[2] |= 0x80;
        buf[3] |= 0x80;
        buf[6] = 0; buf[7] = 1;
        
        _dnsServer.beginPacket(_dnsServer.remoteIP(), _dnsServer.remotePort());
        _dnsServer.write(buf, packetSize);
        
        uint8_t ans[16] = {
            0xC0, 0x0C,
            0x00, 0x01,
            0x00, 0x01,
            0x00, 0x00, 0x00, 0x3C,
            0x00, 0x04,
            192, 168, 4, 1
        };
        IPAddress apIP = WiFi.localIP();
        if (!apIP || apIP[0] == 0) {
            apIP = IPAddress(192, 168, 4, 1);
        }
        ans[12] = apIP[0]; ans[13] = apIP[1]; ans[14] = apIP[2]; ans[15] = apIP[3];
        _dnsServer.write(ans, 16);
        _dnsServer.endPacket();
    }
}

void WiFiManager::processMDNS()
{
    int packetSize = _mDnsServer.parsePacket();
    if (packetSize > 0 && packetSize <= 512)
    {
        uint8_t buf[512];
        _mDnsServer.read(buf, packetSize);
        
        const uint8_t searchStr[] = {0x04, 'r', '4', 'w', 'm', 0x05, 'l', 'o', 'c', 'a', 'l', 0x00};
        bool found = false;
        for (int i = 12; i < packetSize - (int)sizeof(searchStr); i++)
        {
            if (memcmp(buf + i, searchStr, sizeof(searchStr)) == 0)
            {
                found = true;
                break;
            }
        }
        
        if (found)
        {
            uint8_t ans[256];
            memset(ans, 0, sizeof(ans));
            ans[0] = buf[0]; ans[1] = buf[1];
            ans[2] = 0x84; ans[3] = 0x00;
            ans[4] = 0; ans[5] = 0;
            ans[6] = 0; ans[7] = 1;
            ans[8] = 0; ans[9] = 0;
            ans[10] = 0; ans[11] = 0;
            
            int idx = 12;
            memcpy(ans + idx, searchStr, sizeof(searchStr));
            idx += sizeof(searchStr);
            
            ans[idx++] = 0x00; ans[idx++] = 0x01;
            ans[idx++] = 0x80; ans[idx++] = 0x01;
            ans[idx++] = 0x00; ans[idx++] = 0x00; ans[idx++] = 0x00; ans[idx++] = 0x78;
            ans[idx++] = 0x00; ans[idx++] = 0x04;
            
            IPAddress apIP = WiFi.localIP();
            if (!apIP || apIP[0] == 0) {
                apIP = IPAddress(192, 168, 4, 1);
            }
            ans[idx++] = apIP[0]; ans[idx++] = apIP[1]; ans[idx++] = apIP[2]; ans[idx++] = apIP[3];
            
            IPAddress mDNSIP(224, 0, 0, 251);
            _mDnsServer.beginPacket(mDNSIP, 5353);
            _mDnsServer.write(ans, idx);
            _mDnsServer.endPacket();
            
            _mDnsServer.beginPacket(_mDnsServer.remoteIP(), _mDnsServer.remotePort());
            _mDnsServer.write(ans, idx);
            _mDnsServer.endPacket();
        }
    }
}

void WiFiManager::process()
{
    if (_currentStatus == STATUS_AP_MODE)
    {
        processDNS();
        processMDNS();
    }
    else if (_currentStatus == STATUS_CONNECTED)
    {
        if (WiFi.status() != WL_CONNECTED)
        {
            _currentStatus = STATUS_RECONNECTING;
            _reconnectAttempts = 0;
            _lastReconnectTime = millis();

            EEPROMData data;
            loadCredentials(data);
            WiFi.begin(data.profiles[0].ssid, data.profiles[0].password);
        }
    }
    else if (_currentStatus == STATUS_RECONNECTING)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            _currentStatus = STATUS_CONNECTED;

            if (_keepServerAlive)
            {
                if (_server == nullptr)
                {
                    _server = new WiFiServer(_serverPort);
                    _server->begin();
                }
            }
            else
            {
                if (_server != nullptr)
                {
                    delete _server;
                    _server = nullptr;
                }
            }
        }
        else if (millis() - _lastReconnectTime > 5000)
        {
            _reconnectAttempts++;
            _lastReconnectTime = millis();

            if (_reconnectAttempts >= 3)
            {
                startAP();
            }
            else
            {
                EEPROMData data;
                loadCredentials(data);
                WiFi.begin(data.profiles[0].ssid, data.profiles[0].password);
            }
        }
    }

    if (_server != nullptr)
    {
        if (!_clientActive)
        {
            WiFiClient newClient = _server->available();
            if (newClient)
            {
                _client = newClient;
                _clientActive = true;
                _clientTimeout = millis();
            }
        }
        
        if (_clientActive)
        {
            handleClient();
        }
    }
}

void WiFiManager::handleClient()
{
    if (!_client.connected())
    {
        resetClientState();
        return;
    }
    if (millis() - _clientTimeout > 2000)
    {
        resetClientState();
        return;
    }

    while (_client.available() > 0)
    {
        _clientTimeout = millis();
        char c = _client.read();

        if (!_isBody)
        {
            if (c == '\n')
            {
                if (_currentLineLen == 0)
                {
                    _isBody = true;
                }
                else
                {
                    _currentLine[_currentLineLen] = '\0';
                    if (strlen(_requestMethod) == 0)
                    {
                        sscanf(_currentLine, "%7s %63s", _requestMethod, _requestPath);
                    }
                    else if (strncmp(_currentLine, "Content-Length: ", 16) == 0 || strncmp(_currentLine, "content-length: ", 16) == 0)
                    {
                        _contentLength = atoi(_currentLine + 16);
                    }
                    _currentLineLen = 0;
                }
            }
            else if (c != '\r')
            {
                if (_currentLineLen < 255)
                {
                    _currentLine[_currentLineLen++] = c;
                }
            }
        }
        else
        {
            if (_requestBodyLen < 511 && _requestBodyLen < _contentLength)
            {
                _requestBody[_requestBodyLen++] = c;
            }
            if (_requestBodyLen >= _contentLength)
            {
                _requestBody[_requestBodyLen] = '\0';
                processHttpRequest();
                resetClientState();
                return;
            }
        }
    }
    
    if (_isBody && _contentLength == 0)
    {
        processHttpRequest();
        resetClientState();
    }
}

String WiFiManager::extractParam(const char *body, const char *param)
{
    String bodyStr = String(body);
    String searchKey = String(param) + "=";
    int start = bodyStr.indexOf(searchKey);
    if (start == -1)
        return "";
    start += searchKey.length();
    int end = bodyStr.indexOf("&", start);
    if (end == -1)
        end = bodyStr.length();

    String value = bodyStr.substring(start, end);
    value.replace("+", " ");

    String decoded = "";
    decoded.reserve(value.length());
    for (int i = 0; i < value.length(); i++)
    {
        if (value[i] == '%' && i + 2 < value.length())
        {
            int hexVal = strtol(value.substring(i + 1, i + 3).c_str(), NULL, 16);
            decoded += (char)hexVal;
            i += 2;
        }
        else
        {
            decoded += value[i];
        }
    }
    return decoded;
}

void WiFiManager::processHttpRequest()
{
    String reqPath = String(_requestPath);
    String reqMethod = String(_requestMethod);

    if (reqPath.startsWith("/api/"))
    {
        if (reqMethod == "GET" && reqPath == "/api/scan")
        {
            sendResponse(_client, 200, "application/json", scanNetworksJSON());
        }
        else if (reqMethod == "GET" && reqPath == "/api/status")
        {
            sendResponse(_client, 200, "application/json", getConnectionStatusJSON());
        }
        else if (reqMethod == "GET" && reqPath == "/api/info")
        {
            sendResponse(_client, 200, "application/json", getSystemInfoJSON());
        }
        else if (reqMethod == "GET" && reqPath == "/api/params")
        {
            sendResponse(_client, 200, "application/json", getParamsJSON());
        }
        else if (reqMethod == "POST" && reqPath == "/api/connect")
        {
            String ssid = extractParam(_requestBody, "ssid");
            String pass = extractParam(_requestBody, "password");
            String useStaticStr = extractParam(_requestBody, "useStatic");

            if (ssid.length() > 0)
            {
                EEPROMData newData;
                memset(&newData, 0, sizeof(EEPROMData));

                newData.useStaticIP = (useStaticStr == "true" || useStaticStr == "1");
                if (newData.useStaticIP)
                {
                    IPAddress ip, gw, sn, dns;
                    ip.fromString(extractParam(_requestBody, "ip"));
                    gw.fromString(extractParam(_requestBody, "gw"));
                    sn.fromString(extractParam(_requestBody, "sn"));
                    dns.fromString(extractParam(_requestBody, "dns"));
                    newData.staticIP = (uint32_t)ip;
                    newData.staticGW = (uint32_t)gw;
                    newData.staticSN = (uint32_t)sn;
                    newData.staticDNS = (uint32_t)dns;
                }

                for (int i = 0; i < _numParams; i++)
                {
                    String pVal = extractParam(_requestBody, _params[i].id);
                    strncpy(newData.params[i].id, _params[i].id, 31);
                    strncpy(newData.params[i].value, pVal.c_str(), 64);
                }

                if (_saveCallback)
                    _saveCallback();
                saveCredentials(ssid, pass, newData);

                sendResponse(_client, 200, "application/json", "{\"status\":\"success\",\"message\":\"Credentials saved. Device will now reboot.\"}");
                _client.stop();
                delay(1000);
                NVIC_SystemReset();
            }
            else
            {
                sendResponse(_client, 400, "application/json", "{\"status\":\"error\",\"message\":\"Missing SSID.\"}");
            }
        }
        else if (reqMethod == "POST" && reqPath == "/api/reset")
        {
            resetSettings();
            sendResponse(_client, 200, "application/json", "{\"status\":\"success\",\"message\":\"Settings cleared.\"}");
            _client.stop();
            delay(1000);
            NVIC_SystemReset();
        }
        else
        {
            sendResponse(_client, 404, "text/plain", "Endpoint Not Found");
        }
    }
    else if (reqPath == "/" || reqPath == "/index.html")
    {
        sendResponse(_client, 200, "text/html", _customHTML);
    }
    else
    {
        IPAddress apIP = WiFi.localIP();
        if (!apIP || apIP[0] == 0) apIP = IPAddress(192, 168, 4, 1);
        String redirectUrl = "http://" + apIP.toString() + "/";
        
        _client.print("HTTP/1.1 302 Found\r\n");
        _client.print("Location: " + redirectUrl + "\r\n");
        _client.print("Connection: close\r\n\r\n");
    }
}

String WiFiManager::scanNetworksJSON()
{
    int numNetworks = WiFi.scanNetworks();
    if (numNetworks == 0)
        return "[]";

    String json;
    json.reserve(512 + numNetworks * 64);
    json = "[";
    for (int i = 0; i < numNetworks; i++)
    {
        json += "{";
        json += "\"ssid\":\"" + String(WiFi.SSID(i)) + "\",";
        json += "\"rssi\":" + String(WiFi.RSSI(i)) + ",";
        json += "\"encryption\":\"" + getEncryptionTypeString(WiFi.encryptionType(i)) + "\"";
        json += "}";
        if (i < numNetworks - 1)
            json += ",";
    }
    json += "]";
    return json;
}

String WiFiManager::getParamsJSON()
{
    String json;
    json.reserve(512);
    json = "[";
    EEPROMData data;
    loadCredentials(data);
    for (int i = 0; i < _numParams; i++)
    {
        String val = String(_params[i].defaultValue);
        if (strncmp(data.magic, "HTC2", 4) == 0)
        {
            for (int j = 0; j < 5; j++)
            {
                if (strcmp(data.params[j].id, _params[i].id) == 0)
                {
                    if (strlen(data.params[j].value) > 0)
                    {
                        val = String(data.params[j].value);
                    }
                    break;
                }
            }
        }
        json += "{\"id\":\"" + String(_params[i].id) + "\",\"label\":\"" + String(_params[i].label) + "\",\"value\":\"" + val + "\"}";
        if (i < _numParams - 1)
            json += ",";
    }
    json += "]";
    return json;
}

int WiFiManager::getFreeMemory()
{
    char top;
    return &top - reinterpret_cast<char *>(sbrk(0));
}

String WiFiManager::getDeviceUID()
{
    bsp_unique_id_t const *p_uid = R_BSP_UniqueIdGet();
    const uint32_t *uid_ptr = (const uint32_t *)p_uid;
    char buf[35];
    sprintf(buf, "%08lX%08lX%08lX%08lX",
            (unsigned long)uid_ptr[0],
            (unsigned long)uid_ptr[1],
            (unsigned long)uid_ptr[2],
            (unsigned long)uid_ptr[3]);
    return String(buf);
}

String WiFiManager::getSystemInfoJSON()
{
    int freeRamBytes = getFreeMemory();
    String ramStr = String(freeRamBytes / 1024.0, 1) + " KB Free / 32.0 KB Total";
    String cpuStr = "Renesas RA4M1 @ " + String(SystemCoreClock / 1000000) + "MHz";
    String boardStr = "Arduino UNO R4 WiFi (UID: " + getDeviceUID().substring(0, 8) + ")";

    String json;
    json.reserve(256);
    json = "{";
    json += "\"board\":\"" + boardStr + "\",";
    json += "\"cpu\":\"" + cpuStr + "\",";
    json += "\"ram\":\"" + ramStr + "\",";
    json += "\"wifi_fw\":\"" + String(WiFi.firmwareVersion()) + "\"";
    json += "}";
    return json;
}

String WiFiManager::getEncryptionTypeString(int type)
{
    switch (type)
    {
    case ENC_TYPE_NONE: return "Open";
    case ENC_TYPE_WEP: return "WEP";
    case ENC_TYPE_WPA: return "WPA";
    case ENC_TYPE_WPA2: return "WPA2";
    case ENC_TYPE_WPA3: return "WPA3";
    case ENC_TYPE_AUTO: return "Auto";
    default: return "Unknown";
    }
}

String WiFiManager::getConnectionStatusJSON()
{
    String statusStr = "UNKNOWN";
    switch (_currentStatus)
    {
    case STATUS_IDLE: statusStr = "IDLE"; break;
    case STATUS_AP_MODE: statusStr = "AP_MODE"; break;
    case STATUS_CONNECTING: statusStr = "CONNECTING"; break;
    case STATUS_CONNECTED: statusStr = "CONNECTED"; break;
    case STATUS_RECONNECTING: statusStr = "RECONNECTING"; break;
    }

    String json;
    json.reserve(128);
    json = "{";
    json += "\"status\":\"" + statusStr + "\"";
    if (_currentStatus == STATUS_CONNECTED)
    {
        json += ",\"ip\":\"" + WiFi.localIP().toString() + "\"";
        json += ",\"ssid\":\"" + String(WiFi.SSID()) + "\"";
    }
    json += "}";
    return json;
}

void WiFiManager::sendResponse(WiFiClient &client, int code, const String &contentType, const String &content)
{
    sendResponse(client, code, contentType, content.c_str());
}

void WiFiManager::sendResponse(WiFiClient &client, int code, const String &contentType, const char *content)
{
    size_t len = strlen(content);
    client.print("HTTP/1.1 " + String(code) + " OK\r\n");
    client.print("Content-Type: " + contentType + "\r\n");
    client.print("Connection: close\r\n");
    client.print("Content-Length: " + String(len) + "\r\n");
    client.print("Access-Control-Allow-Origin: *\r\n");
    client.print("\r\n");

    size_t chunkSize = 1024;
    for (size_t i = 0; i < len; i += chunkSize)
    {
        size_t currentChunk = (len - i) > chunkSize ? chunkSize : (len - i);
        client.write((const uint8_t *)(content + i), currentChunk);
    }
}