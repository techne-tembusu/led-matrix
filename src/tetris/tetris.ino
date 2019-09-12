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
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_D1_PIN_ORDER
#include "FastLED.h"

#include "globals.h"

#define DATA_PIN D6
const uint NUM_LEDS = 512;
const uint BOARD_WIDTH = 16;
const uint BOARD_HEIGHT = 32;

const size_t STICK_H = 10;
const size_t STICK_W = 5;

CRGB leds[NUM_LEDS];

uint cur_row = 15;
uint cur_col = 0;
bool stickman_changed = true;
bool isGamePaused = true;

byte stickman[STICK_H][STICK_W] = {
  {0, 1, 1, 1, 0},
  {0, 1, 0, 1, 0},
  {0, 1, 1, 1, 0},
  {0, 0, 1, 0, 0},
  {1, 1, 1, 1, 1},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 0, 1, 0},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1}
};

void setup() {
    // server.ino
    mountFs();
    startWifi();
    startWebServer();
    startWebsocketServer();

    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
    display_stickman();
}

void loop() {
    server.handleClient();
    webSocket.loop();

    if (stickman_changed && !isGamePaused) {
      display_stickman();
      stickman_changed = false;
    }
    delay(10);
}

void update_col(int move) {
  // -1 for left, +1 for right
  if ((cur_col + move <= BOARD_WIDTH  - STICK_W) &&
     (cur_col + move >= 0)) {
    cur_col += move;
    stickman_changed = true;
  }
}

void update_row(int move) {
  // -1 for up, +1 for down
  if ((cur_row + move <= BOARD_HEIGHT  - STICK_H) &&
     (cur_row + move >= 0)) {
    cur_row += move;
    stickman_changed = true;
  }
}

void display_stickman() {
    FastLED.clear();
    for (int row=0; row<STICK_H; row++) {
      for (int col=0; col<STICK_W; col++) {
        byte pixel = stickman[row][col];
        if (pixel == 1) {
          leds[rcToIndex(cur_row + row, cur_col + col)] =  CRGB(50, 50, 50);
        } else {
          leds[rcToIndex(cur_row + row, cur_col + col)] =  CRGB(0, 0, 0);
        }
      }
    }
    FastLED.show();
}

uint rcToIndex(uint row, uint col) {
    // Converts 0-indexed row and col co-ords into a single index position
    // for the snake layout of the board. Assumes data in is bottom right corner
    if (col & 0x01) {  // col is odd
        return (BOARD_WIDTH - 1 - col)*BOARD_HEIGHT + BOARD_HEIGHT - 1 - row;
    } else {  // col is even
        return (BOARD_WIDTH - 1 - col)*BOARD_HEIGHT + row;
    }
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
        stickman_changed = true;
        webSocket.sendTXT(num, "start");
    } else if (strcmp(msg, "newgame") == 0) {
        // TODO
        // newgame();
        isGamePaused = false;
        stickman_changed = true;
        webSocket.sendTXT(num, "start");
    }
    // Control input
    else if (strcmp(msg, "up") == 0) {
        update_row(-1);
    } else if (strcmp(msg, "down") == 0) {
        update_row(1);
    } else if (strcmp(msg, "left") == 0) {
        update_col(-1);
    } else if (strcmp(msg, "right") == 0) {
        update_col(1);
    } else if (strcmp(msg, "clock") == 0) {
//        net_rotate++;
    } else if (strcmp(msg, "anti") == 0) {
//        net_rotate--;
    } else {
      Serial.printf("[Ws] Unknown message: %s\n", msg);
    }
}
