/* Download the library at https://github.com/Links2004/arduinoWebSockets
 * Install with Sketch > Include Library > Add .ZIP Library...
 *
 * - Download the tool from
 *   https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.3.0/ESP8266FS-0.3.0.zip.
 *   In your Arduino sketchbook directory, create tools directory if it doesn't exist yet
 * - Unpack the tool into tools directory (the path will look like
 *   <user_dir>/Documents/tools/ESP8266FS/tool/esp8266fs.jar)
 * - Restart Arduino IDE
 * - Go to sketch directory (choose Sketch > Show Sketch Folder)
 * - Create a directory named data. Place any files you want in the file system there
 * - Make sure you have selected a board, port, and closed Serial Monitor
 * - Select Tools > ESP8266 Sketch Data Upload. This should start uploading the files into ESP8266 flash
 *   file system.
 * - When done, IDE status bar will display SPIFFS Image Uploaded message.
 * - Upload your sketch as per normal.
 *
 * You only need to Sketch Data Upload if you made changes to files in the `data` folder.
 * If you get an error saying `SPIFFS_write error(-10001): File system is full`, this means that your files
 * are too large to fit into the SPIFFS memory. Select a larger SPIFFS size under Tools > Flash Size, or delete
 * some files.
 * Even if your computer says that the files are smaller than the selected SPIFFS size, you can still get
 * this error: this has to do with block sizes, and metadata like file and folder names that take up space
 * as well.
 * If you change the SPIFFS size, you have to reupload your sketch, because when you change the SPIFFS size,
 * the memory location will be different. The program has to know the updated SPIFFS address offset to be able
 * to read the files.
**/
#include "globals.h"


bool isGamePaused = false;


void setup() {
    Serial.begin(115200);

    // server.ino
    mountFs();
    startWifi();
    startWebServer();
    startWebsocketServer();
}

void loop() {
    server.handleClient();
    webSocket.loop();
}


void handleWebsocketMessage(int num, const char* msg) {
    if (strcmp(msg, "paused?") == 0) {
        char buf[12];
        sprintf(buf, "paused=%d", isGamePaused);
        webSocket.sendTXT(num, buf);
    } else if (strcmp(msg, "pause") == 0) {
        isGamePaused = true;
        // Echo so frontend pauses game. Server is source of truth
        webSocket.sendTXT(num, "pause");
    } else if (strcmp(msg, "resume") == 0) {
        isGamePaused = false;
        webSocket.sendTXT(num, "start");
    } else if (strcmp(msg, "newgame") == 0) {
        // TODO
        // newgame();
        isGamePaused = false;
        webSocket.sendTXT(num, "start");
    }
    // Control input
    else if (strcmp(msg, "slam") == 0) {
        // TODO
    } else if (strcmp(msg, "left") == 0) {
        // TODO
    } else if (strcmp(msg, "right") == 0) {
        // TODO
    } else if (strcmp(msg, "down") == 0) {
        // TODO
    } else if (strcmp(msg, "clock") == 0) {
        // TODO
    } else if (strcmp(msg, "anti") == 0) {
        // TODO
    } else {
      Serial.printf("[Ws] Unknown message: %s\n", msg);
    }
}
