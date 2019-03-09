#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "WebSocketsServer.h"

// Global variables
extern const char* ssid = "tembusu_stickman";
extern const char* password = "";
extern const uint8_t wsPort = 81;
extern IPAddress apIP(192, 168, 4, 1);
extern ESP8266WebServer server(80);
extern WebSocketsServer webSocket = WebSocketsServer(wsPort);
