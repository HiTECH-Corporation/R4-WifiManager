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
}

WiFiManager::~WiFiManager()
{
    if (_server != nullptr)
        delete _server;
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
        _params[_numParams].id = String(id);
        _params[_numParams].label = String(label);
        _params[_numParams].defaultValue = String(defaultValue);
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
            if (String(data.params[i].id) == String(id))
            {
                return String(data.params[i].value);
            }
        }
    }
    for (int i = 0; i < _numParams; i++)
    {
        if (_params[i].id == String(id))
        {
            return _params[i].defaultValue;
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
    {
        _apName = String(apName);
    }
    if (apPassword != nullptr)
    {
        _apPassword = String(apPassword);
    }
    else
    {
        _apPassword = "";
    }

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

    if (_apPassword.length() >= 8)
    {
        WiFi.beginAP(_apName.c_str(), _apPassword.c_str());
    }
    else
    {
        WiFi.beginAP(_apName.c_str());
    }

    if (_server != nullptr)
        delete _server;
    _server = new WiFiServer(_serverPort);
    _server->begin();
}

void WiFiManager::process()
{
    if (_currentStatus == STATUS_CONNECTED)
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
        WiFiClient client = _server->available();
        if (client)
        {
            handleClient(client);
        }
    }
}

void WiFiManager::handleClient(WiFiClient &client)
{
    String currentLine = "";
    String requestMethod = "";
    String requestPath = "";
    String requestBody = "";
    bool isBody = false;
    int contentLength = 0;

    unsigned long timeout = millis();
    while (client.connected() && millis() - timeout < 2000)
    {
        if (client.available())
        {
            char c = client.read();

            if (!isBody)
            {
                if (c == '\n')
                {
                    if (currentLine.length() == 0)
                    {
                        isBody = true;
                    }
                    else
                    {
                        if (requestMethod == "")
                        {
                            int space1 = currentLine.indexOf(' ');
                            int space2 = currentLine.indexOf(' ', space1 + 1);
                            if (space1 != -1 && space2 != -1)
                            {
                                requestMethod = currentLine.substring(0, space1);
                                requestPath = currentLine.substring(space1 + 1, space2);
                            }
                        }
                        else if (currentLine.startsWith("Content-Length: "))
                        {
                            contentLength = currentLine.substring(16).toInt();
                        }
                        currentLine = "";
                    }
                }
                else if (c != '\r')
                {
                    currentLine += c;
                }
            }
            else
            {
                requestBody += c;
                if (requestBody.length() >= contentLength)
                {
                    break;
                }
            }
        }
    }

    if (requestPath.startsWith("/api/"))
    {
        if (requestMethod == "GET" && requestPath == "/api/scan")
        {
            sendResponse(client, 200, "application/json", scanNetworksJSON());
        }
        else if (requestMethod == "GET" && requestPath == "/api/status")
        {
            sendResponse(client, 200, "application/json", getConnectionStatusJSON());
        }
        else if (requestMethod == "GET" && requestPath == "/api/info")
        {
            sendResponse(client, 200, "application/json", getSystemInfoJSON());
        }
        else if (requestMethod == "GET" && requestPath == "/api/params")
        {
            sendResponse(client, 200, "application/json", getParamsJSON());
        }
        else if (requestMethod == "POST" && requestPath == "/api/connect")
        {
            String ssid = extractParam(requestBody, "ssid");
            String pass = extractParam(requestBody, "password");
            String useStaticStr = extractParam(requestBody, "useStatic");

            if (ssid.length() > 0)
            {
                EEPROMData newData;
                memset(&newData, 0, sizeof(EEPROMData));

                newData.useStaticIP = (useStaticStr == "true" || useStaticStr == "1");
                if (newData.useStaticIP)
                {
                    IPAddress ip, gw, sn, dns;
                    ip.fromString(extractParam(requestBody, "ip"));
                    gw.fromString(extractParam(requestBody, "gw"));
                    sn.fromString(extractParam(requestBody, "sn"));
                    dns.fromString(extractParam(requestBody, "dns"));
                    newData.staticIP = (uint32_t)ip;
                    newData.staticGW = (uint32_t)gw;
                    newData.staticSN = (uint32_t)sn;
                    newData.staticDNS = (uint32_t)dns;
                }

                for (int i = 0; i < _numParams; i++)
                {
                    String pVal = extractParam(requestBody, _params[i].id);
                    strncpy(newData.params[i].id, _params[i].id.c_str(), 31);
                    strncpy(newData.params[i].value, pVal.c_str(), 64);
                }

                if (_saveCallback)
                    _saveCallback();
                saveCredentials(ssid, pass, newData);

                sendResponse(client, 200, "application/json", "{\"status\":\"success\",\"message\":\"Credentials saved. Device will now reboot.\"}");
                client.stop();
                delay(1000);
                NVIC_SystemReset();
            }
            else
            {
                sendResponse(client, 400, "application/json", "{\"status\":\"error\",\"message\":\"Missing SSID.\"}");
            }
        }
        else if (requestMethod == "POST" && requestPath == "/api/reset")
        {
            resetSettings();
            sendResponse(client, 200, "application/json", "{\"status\":\"success\",\"message\":\"Settings cleared.\"}");
            client.stop();
            delay(1000);
            NVIC_SystemReset();
        }
        else
        {
            sendResponse(client, 404, "text/plain", "Endpoint Not Found");
        }
    }
    else
    {
        sendResponse(client, 200, "text/html", _customHTML);
    }

    client.stop();
}

String WiFiManager::extractParam(const String &body, const String &param)
{
    String searchKey = param + "=";
    int start = body.indexOf(searchKey);
    if (start == -1)
        return "";
    start += searchKey.length();
    int end = body.indexOf("&", start);
    if (end == -1)
        end = body.length();

    String value = body.substring(start, end);
    value.replace("+", " ");

    String decoded = "";
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

String WiFiManager::scanNetworksJSON()
{
    int numNetworks = WiFi.scanNetworks();
    if (numNetworks == 0)
        return "[]";

    String json = "[";
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
    String json = "[";
    EEPROMData data;
    loadCredentials(data);
    for (int i = 0; i < _numParams; i++)
    {
        String val = _params[i].defaultValue;
        if (strncmp(data.magic, "HTC2", 4) == 0)
        {
            for (int j = 0; j < 5; j++)
            {
                if (String(data.params[j].id) == _params[i].id)
                {
                    if (strlen(data.params[j].value) > 0)
                    {
                        val = String(data.params[j].value);
                    }
                    break;
                }
            }
        }
        json += "{\"id\":\"" + _params[i].id + "\",\"label\":\"" + _params[i].label + "\",\"value\":\"" + val + "\"}";
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

    String json = "{";
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
    case ENC_TYPE_NONE:
        return "Open";
    case ENC_TYPE_WEP:
        return "WEP";
    case ENC_TYPE_WPA:
        return "WPA";
    case ENC_TYPE_WPA2:
        return "WPA2";
    case ENC_TYPE_WPA3:
        return "WPA3";
    case ENC_TYPE_AUTO:
        return "Auto";
    default:
        return "Unknown";
    }
}

String WiFiManager::getConnectionStatusJSON()
{
    String statusStr = "UNKNOWN";
    switch (_currentStatus)
    {
    case STATUS_IDLE:
        statusStr = "IDLE";
        break;
    case STATUS_AP_MODE:
        statusStr = "AP_MODE";
        break;
    case STATUS_CONNECTING:
        statusStr = "CONNECTING";
        break;
    case STATUS_CONNECTED:
        statusStr = "CONNECTED";
        break;
    case STATUS_RECONNECTING:
        statusStr = "RECONNECTING";
        break;
    }

    String json = "{";
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