#include <Arduino.h>
#include "Ticker.h"

global int GAME_SPEED = 1000;
global bool movement = false;

global int curX;
global int curY;
global int curPiece;
global int Matrix[21][10];

global char pieces[28][4][4] = [
                                [['-','-','-','-'],
                                 ['-','y','y','-'],
                                 ['-','y','y','-'],
                                 ['-','-','-','-']],

                                [['-','-','-','-'],
                                 ['-','x','x','-'],
                                 ['-','x','x','-'],
                                 ['-','-','-','-']],

                                [['-','-','-','-'],
                                 ['-','x','x','-'],
                                 ['-','x','x','-'],
                                 ['-','-','-','-']],

                                [['-','-','-','-'],
                                 ['-','x','x','-'],
                                 ['-','x','x','-'],
                                 ['-','-','-','-']],

                                [['-','-','x','-'],
                                 ['-','-','x','-'],
                                 ['-','-','x','-'],
                                 ['-','-','x','-']],

                                [['-','-','-','-'],
                                 ['x','x','x','x'],
                                 ['-','-','-','-'],
                                 ['-','-','-','-']],

                                [['-','-','x','-'],
                                 ['-','-','x','-'],
                                 ['-','-','x','-'],
                                 ['-','-','x','-']],

                                [['-','-','-','-'],
                                 ['x','x','x','x'],
                                 ['-','-','-','-'],
                                 ['-','-','-','-']]
                                 //to be continued...
                                                   ]




void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Ticker tickerObject(movementToggle, GAME_SPEED);
}

/*
Implementation:

- Store the initial matrix
- Have a separate 2D array for the falling piece
- Display function combines the both of them
- Keep track of location of falling piece (CurrentX, Current Y)
  - Update the initial location of falling piece
  - check_full_lines
    - if true, clear lines, push everything down, reupdate matrix, add to score
    - else, proceed to insertion of next piece
- rotate_collision_check & rotate needs to be hardcoded for each possible orientation
- insert_piece needs to be recoded
*/


void move_down(){ //moves piece down
  return;
}

void move_left(){
  return;
}

void move_right{
  return;
}

void rotate(){
  if (!rotate_check_collision()){
    curPiece = (curPiece%4==3) ? curPiece-3 : curPiece+1;
  }
}

void check_full_line(){
  return;
}

void shift_down(){ //shifts everything down after clearing lines
  return;
}

bool check_collision(){ //checks collision at the bottom
  char piece[4][4] = pieces[curPiece];
  for (int i = 0; i<4; i++){
    for (int j = 0; j<4; j++){
      if (piece[i][j]!='-'){
        if (curY + i == 20){ //hits the floor
          return true;
        }
        else if (piece[i+1][j]!='-' && Matrix[curY+i+1][curX]!='-'){ //hits already fallen pieces
          return true;
        }
      }
    }
  }
  return false;
}

bool rotate_check_collision(){
  int tocheck[4][4];
  tocheck = (curPiece%4==3) ? pieces[curPiece-3] : pieces[curPiece+1];
  for (int i = 0; i<4; i++){
    for (int j = 0; j<4; j++){
      if (tocheck[i][j]!='-'){
        if ((curX + j > 9) || (curY + i > 20)){
          return true;
        }
        if (Matrix[curY+i][curX+j]!='-'){
          return true;
        }
      }
    }
  }
  return false;
}


void movementToggle(bool movement){
  movement = true;
}

void loop() {

}
