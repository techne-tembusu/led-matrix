#define FASTLED_ESP8266_D1_PIN_ORDER
#include <FastLED.h>
#define NUM 150
#define DATA_PIN D6


#define BOARD_HEIGHT 32
#define BOARD_WIDTH 16


CRGB leds[NUM];
int n=0;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM);
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



void loop() {

// lights up the selected LEDs 
  for (int r = 15; r<21; r++){ 
    for (int c = 12;c <16 ; c++){
      leds[rcToIndex(r,c)] = CRGB(80,0,0);
         n = (n+1) % NUM;
   }
 }
 FastLED.show();

}

