#include "FS.h"


uint8_t numConnections = 0;


void mountFs() {
    if (!SPIFFS.begin()) {
        Serial.println("SPIFFS mount failed.");
    } else {
        Serial.println("SPIFFS mount succesful.");
    }
}

void startWifi() {
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid, password);
    Serial.printf("Created network %s, password: %s\n", ssid, password);
    Serial.printf("ESP IP address: %s\n", WiFi.softAPIP().toString().c_str());
}

void startWebServer() {
    server.on("/", serveIndex);
    server.on("/controls.html", serveControls);
    server.on("/hammer.min.js", serveHammerJs);
    server.begin();
}

void startWebsocketServer() {
    Serial.printf("Starting websocket server at ws://%s:%u/\n", WiFi.softAPIP().toString().c_str(), wsPort);
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
}

void serveIndex() {
    if (numConnections == 0) {
        //debug code to test successful connectiion
        //server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Tembusu Tetris</title><body>You are connected!.</body>");

        File file = SPIFFS.open("/index.html", "r");

        server.streamFile(file, "text/html");        
        file.close();
    }
    else {
        server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Tembusu Tetris</title><body>Someone is already playing tetris. Refresh the page after they're done.</body>");
    }

}

void serveControls() {
    if (numConnections == 1) { // only when got player then can see
        File file = SPIFFS.open("/controls.html", "r");
        server.streamFile(file, "text/html");
        file.close();
    }
    else {
        serveIndex();//server.send(200, "text/html", "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>Tembusu Tetris</title><body>Someone is already playing tetris. Refresh the page after they're done.</body>");
    }
}

void serveHammerJs() {
    File file = SPIFFS.open("/hammer.min.js", "r");
    server.streamFile(file, "application/javascript");
    file.close();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
    case WStype_CONNECTED:
        Serial.printf("[Ws] Connected to url: %s\n", payload);
        numConnections += 1;
        break;
    case WStype_DISCONNECTED:
        Serial.println("[Ws] Disconnected!");
        numConnections -= 1;
        break;
    case WStype_TEXT:
        Serial.printf("[Ws] Received text: %s\n", payload);
        handleWebsocketMessage(num, (const char*) payload); // defined in main.ino
        break;
    case WStype_BIN:
        Serial.printf("[Ws] Received binary, length: %u\n", length);
        hexdump(payload, length);
        break;
    }
}
