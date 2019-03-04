/* Screensaver code where the message 'TEMBUSU TETRIS'
 * scrolls in row by row from the left, stays for a while 
 * and scrolls out row by row into the right
*/
#define FASTLED_ESP8266_D1_PIN_ORDER
#include "FastLED.h"
#define NUM 512
#define DATA_PIN D6
#define BOARD_HEIGHT 32
#define BOARD_WIDTH 16

CRGB leds[NUM];
int n=0;
int UPDATE_DELAY = 400;
int UPDATE_DELAY_LONG = 3000;

unsigned int rcToIndex(unsigned int row, unsigned int col) {
    // Converts 0-indexed row and col co-ords into a single index position
    // for the snake layout of the board. Assumes data in is bottom right corner
    if (col & 0x01) {  // col is odd
        return (BOARD_WIDTH - 1 - col)*BOARD_HEIGHT + BOARD_HEIGHT - 1 - row;
    } else {  // col is even
        return (BOARD_WIDTH - 1 - col)*BOARD_HEIGHT + row;
    }
}

//Original matrix
char Matrix_orig[BOARD_HEIGHT][BOARD_WIDTH];

/* 4 rows of messages:
 *  TEM
 *  BUSU
 *  TET
 *  RIS
*/

char message1[5][16] = {{'-','g','g','g','-','g','g','g','-','g','-','-','-','g','-','-'},
                        {'-','-','g','-','-','g','-','-','-','g','g','-','g','g','-','-'},
                        {'-','-','g','-','-','g','g','g','-','g','-','g','-','g','-','-'},
                        {'-','-','g','-','-','g','-','-','-','g','-','-','-','g','-','-'},
                        {'-','-','g','-','-','g','g','g','-','g','-','-','-','g','-','-'}};

char message2[5][16] = {{'g','g','-','-','g','-','g','-','g','g','g','-','g','-','g','-'},
                        {'g','-','g','-','g','-','g','-','g','-','-','-','g','-','g','-'},
                        {'g','g','-','-','g','-','g','-','g','g','g','-','g','-','g','-'},
                        {'g','-','g','-','g','-','g','-','-','-','g','-','g','-','g','-'},
                        {'g','g','-','-','g','g','g','-','g','g','g','-','g','g','g','-'}};

char message3[5][16] = {{'-','-','r','r','r','-','o','o','o','-','b','b','b','-','-','-'},
                        {'-','-','-','r','-','-','o','-','-','-','-','b','-','-','-','-'},
                        {'-','-','-','r','-','-','o','o','o','-','-','b','-','-','-','-'},
                        {'-','-','-','r','-','-','o','-','-','-','-','b','-','-','-','-'},
                        {'-','-','-','r','-','-','o','o','o','-','-','b','-','-','-','-'}};

char message4[5][16] = {{'-','-','g','g','-','-','p','p','p','-','y','y','y','-','-','-'},
                        {'-','-','g','-','g','-','-','p','-','-','y','-','-','-','-','-'},
                        {'-','-','g','g','-','-','-','p','-','-','y','y','y','-','-','-'},
                        {'-','-','g','-','g','-','-','p','-','-','-','-','y','-','-','-'},
                        {'-','-','g','-','g','-','p','p','p','-','y','y','y','-','-','-'}};

/* row_i and column_i takes the initial position of the 
 * top left square of the message
*/
void scroll_in(int row_i, int column_i, char msg[5][16]) {
  
  while (column_i <= 0) {
    //clear 5 rows
    for(int i = row_i; i < row_i + 5; i++) {
      for(int j = 0; j < BOARD_WIDTH; j++) {
        Matrix_orig[i][j] = '-';
      }
    }
    
    //set message location
    for(int j = column_i; j < column_i + BOARD_WIDTH; j++) {
      //Display LEDs when they appear on the board
      if (j >= 0 && j < BOARD_WIDTH) {
        for(int i = row_i; i < row_i + 5; i++) {
          Matrix_orig[i][j] = msg[i][j];
        }
      }
    }
    
    //display new rows
    fill_matrix();
    
    delay(UPDATE_DELAY);
    //shift message to the right
    column_i += 1;
  }
  
  //return when message fully disappears
  return;
}

/* row_f and column_f takes the final desired position of the 
 * top left square of the message
*/
void scroll_out(int row_f, int column_f, char msg[5][16]) {
  
  int new_column_pos = 1;
  
  while (new_column_pos <= column_f) {
    
    //clear 5 rows
    for(int i = row_f; i < row_f + 5; i++) {
      for(int j = 0; j < BOARD_WIDTH; j++) {
        Matrix_orig[i][j] = '-';
      }
    }
    
    //set message location
    for(int j = new_column_pos; j < column_f + BOARD_WIDTH; j++) {
      //Display LEDs when they appear on the board
      if (j >= 0 && j < BOARD_WIDTH) {
        for(int i = row_f; i < row_f + 5; i++) {
          Matrix_orig[i][j] = msg[i][j];
        }
      }
    }
    
    //display new rows
    fill_matrix();
    
    delay(UPDATE_DELAY);
    //shift message to the right
    new_column_pos += 1;
  }

  //return when message fully disappears
  return;
}

void fill_matrix() {
  //colour every pixel on the board 
  for(int i = 0; i < BOARD_HEIGHT; i++) {
    for(int j = 0; j < BOARD_WIDTH; j++) {
      switch(Matrix_orig[i][j]) {
      case 'r':
        leds[rcToIndex(i, i)] = CRGB(128,0,0);
        break;
      case 'g':
        leds[rcToIndex(i, i)] = CRGB(0,128,0);
        break;
      case 'b':
        leds[rcToIndex(i, i)] = CRGB(0,0,128);
        break;
      case 'o':
        leds[rcToIndex(i, i)] = CRGB(175,95,0);
        break;
      case 'p':
        leds[rcToIndex(i, i)] = CRGB(128,0,128);
        break;
      case 'y':
        leds[rcToIndex(i, i)] = CRGB(128,128,0);
        break;
      default:
        leds[rcToIndex(i, i)] = CRGB(0,0,0);
        break;
      }
    }
  }
  FastLED.show();
  return;
}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM);
  Serial.begin(9600);
  for (int i = 0; i < BOARD_HEIGHT; i++) {
    for (int j = 0; j < BOARD_WIDTH; j++) {
      Matrix_orig[i][j] = '-';
    }
  }
  delay(1000);
}

void loop() {
  scroll_in(5,-14,message1);
  scroll_in(11,-15,message2);
  scroll_in(19,-13,message3);
  scroll_in(25,-13,message4);
  delay(UPDATE_DELAY_LONG);
  scroll_out(5,15,message1);
  scroll_out(11,16,message2);
  scroll_out(19,14,message3);
  scroll_out(25,14,message4);
  delay(UPDATE_DELAY_LONG);
}
