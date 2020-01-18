#define FASTLED_ESP8266_D1_PIN_ORDER
#include <FastLED.h>
#define NUM 150
#define DATA_PIN D6

/**
* LED test code!
*/

CRGB leds[NUM];
int n=0;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM);
}

void loop() {
  if(n < 512) {
    if (n % 3 == 0) {
      leds[n] = CRGB(63,0,0);
    }
    else if (n % 3 == 1) {
      leds[n] = CRGB(0,63,0);
    }
    else {
      leds[n] = CRGB(0,0,63);
    }
  }
  else {
    leds[(n)%NUM] = CRGB(0,0,0);
  }
  FastLED.show();
  n = (n+1) % (2 * NUM);
  delay(50);
}
