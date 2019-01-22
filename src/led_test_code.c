#define FASTLED_ESP8266_D1_PIN_ORDER
#include <FastLED.h>
#define NUM 150
#define DATA_PIN D6

CRGB leds[NUM];
int n=0;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM);
}

void loop() {
  leds[n] = CRGB(127,127,127);
  leds[(n-1)%NUM] = CRGB(0,0,0);
  FastLED.show();
  n = (n+1) % NUM;
  delay(200);
}
