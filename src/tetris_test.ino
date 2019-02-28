#include <Arduino.h>
#include <Ticker.h>



int GAME_SPEED = 1000;
bool movement = false;

int curX; //current X-location of falling piece
int curY; //current X-location of falling piece
int curPiece; //id of current piece (pieces[curPiece] returns 4x4 piece array)
char Matrix[21][10] = {{'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'},
                      {'-','-','-','-','-','-','-','-','-','-'}}; //current Matrix

char pieces[28][4][4] = {
                                {{'-','-','-','-'}, // 0: O 1
                                 {'-','y','y','-'},
                                 {'-','y','y','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 1: O 2
                                 {'-','y','y','-'},
                                 {'-','y','y','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 2: O 3
                                 {'-','y','y','-'},
                                 {'-','y','y','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 3: O 4
                                 {'-','y','y','-'},
                                 {'-','y','y','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','b','-'}, // 4: I 1
                                 {'-','-','b','-'},
                                 {'-','-','b','-'},
                                 {'-','-','b','-'}},

                                {{'-','-','-','-'}, // 5:
                                 {'b','b','b','b'},
                                 {'-','-','-','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','b','-'}, // 6:
                                 {'-','-','b','-'},
                                 {'-','-','b','-'},
                                 {'-','-','b','-'}},

                                {{'-','-','-','-'}, // 7:
                                 {'b','b','b','b'},
                                 {'-','-','-','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 8: S 1
                                 {'-','-','r','r'},
                                 {'-','r','r','-'},
                                 {'-','-','-','-'}},

                                {{'-','r','-','-'}, // 9:
                                 {'-','r','r','-'},
                                 {'-','-','r','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 10:
                                 {'-','-','r','r'},
                                 {'-','r','r','-'},
                                 {'-','-','-','-'}},

                                {{'-','r','-','-'}, // 11:
                                 {'-','r','r','-'},
                                 {'-','-','r','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 12: Z 1
                                 {'g','g','-','-'},
                                 {'-','g','g','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','g','-'}, // 13:
                                 {'-','g','g','-'},
                                 {'-','g','-','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 14:
                                 {'g','g','-','-'},
                                 {'-','g','g','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','g','-'}, // 15:
                                 {'-','g','g','-'},
                                 {'-','g','-','-'},
                                 {'-','-','-','-'}},

                                {{'-','o','-','-'}, // 16: L 1
                                 {'-','o','-','-'},
                                 {'-','o','o','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 17:
                                 {'-','o','o','o'},
                                 {'-','o','-','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 18:
                                 {'-','o','o','-'},
                                 {'-','-','o','-'},
                                 {'-','-','o','-'}},

                                {{'-','-','-','-'}, // 19:
                                 {'-','-','o','-'},
                                 {'o','o','o','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','p','-'}, // 20: J 1
                                 {'-','-','p','-'},
                                 {'-','p','p','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 21:
                                 {'-','p','-','-'},
                                 {'-','p','p','p'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 22:
                                 {'-','p','p','-'},
                                 {'-','p','-','-'},
                                 {'-','p','-','-'}},

                                {{'-','-','-','-'}, // 23:
                                 {'p','p','p','-'},
                                 {'-','-','p','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','-','-'}, // 24: T 1
                                 {'-','v','v','v'},
                                 {'-','-','v','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','v','-'}, // 25:
                                 {'-','v','v','-'},
                                 {'-','-','v','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','v','-'}, // 26:
                                 {'-','v','v','v'},
                                 {'-','-','-','-'},
                                 {'-','-','-','-'}},

                                {{'-','-','v','-'}, // 27:
                                 {'-','-','v','v'},
                                 {'-','-','v','-'},
                                 {'-','-','-','-'}}
                                                   };


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
  curY++;
}

void move_left(){
  if (!check_overlap()){
    curX = (curX == 0) ? curX : curX-1;
  }
}

void move_right(){
  if (!check_overlap()){
    curX = (curX == 9) ? curX : curX+1;
  }
}

bool check_overlap(){
  //char piece[4][4] = pieces[curPiece];
  for (int i = 0; i<4; i++){
    for (int j = 0; j<4; j++){
      if (pieces[curPiece][i][j]!='-'){
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

void rotate(){
  if (!rotate_check_collision()){
    curPiece = (curPiece%4==3) ? curPiece-3 : curPiece+1;
  }
}

void update_Matrix(){ //updates Matrix after collision at bottom is detected
  //char piece[4][4] = pieces[curPiece];
  for (int i = 0; i<4; i++){
    for (int j = 0; j<4; j++){
      if (pieces[curPiece][i][j]!='-'){
        Matrix[curY+i][curX+j] = pieces[curPiece][i][j];
      }
    }
  }
}

void check_full_line(){
  // FIND FULL LINES
  int full[21]; //array to store full rows
  int numfull = 0; //index to stop at
  for (int i = 20; i>=0; i--){ //finds full rows
    for (int j = 0; j<10; j++){
      if (Matrix[i][j] = '-'){
        break;
      }
    }
    full[numfull] = i;
    numfull++;
  }
  // CLEAR FULL LINES
  for (int k = 0; k<numfull; k++){
    for (int m = 0; m<10; m++){
      Matrix[full[k]][m] = '-';
    }
  }
  // SHIFTS EVERYTHING DOWN AFTER CLEARING
  int remain[21] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
  for (int i = 0; i<numfull; i++){
    remain[full[i]] = -1;
  }
  for (int i = 20; i>=0; i--){
    int idx = i;
    while (idx < 21 || remain[idx+1]==-1){
      remain[idx+1]=remain[idx];
      remain[idx] = -1;
      idx++;
    }
  }
  /*E.g. for cleared rows 20, 19 and 16
  remain = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-1,17,18,-1,-1};
  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-1,17,-1,18,-1}
  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-1,17,-1,-1,18}
  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-1,-1,17,-1,18}
  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,-1,-1,-1,17,18}
  ...
  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,-1,-1,-1,15,17,18}
  ...
  {-1,-1,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,17,18}
  */
  for (int i = 20; i>=0; i--){
    if (remain[i]!=i){
      for (int j = 0; j<10; j++){
        Matrix[i][j] = Matrix[remain[i]][j];
      }
    }
  }
}


bool check_collision(){ //checks collision at the bottom
  //char piece[4][4] = pieces[curPiece];
  for (int i = 0; i<4; i++){
    for (int j = 0; j<4; j++){
      if (pieces[curPiece][i][j]!='-'){
        if (curY + i == 20){ //hits the floor
          return true;
        }
        else if ((i==3 || pieces[curPiece][i+1][j]=='-') && Matrix[curY+i+1][curX+j]!='-'){ //hits already fallen pieces
          return true;
        }
      }
    }
  }
  return false;
}

bool rotate_check_collision(){
  int tocheck;
  tocheck = (curPiece%4==3) ? curPiece-3 : curPiece+1;
  for (int i = 0; i<4; i++){
    for (int j = 0; j<4; j++){
      if (pieces[tocheck][i][j]!='-'){
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

void insert_piece(){
  curPiece = (random(0,7))*4;
  curX = 3;
  curY = 0;
}

void movementToggle(bool movement){
  movement = true;
}

void disp(){
  for (int i=0; i<21; i++){
    for (int j=0; j<10; j++){
      if (i>=curY && i<curY+4 && j>=curX && j<curX+4 && Matrix[i][j]=='-'){
        Serial.print(pieces[curPiece][i-curY][j-curX]);
      }
      else{
        Serial.print(Matrix[i][j]);
      }
      Serial.print(' ');
    }
    Serial.print("\n");
  }
  Serial.print("\n");
}

Ticker game_ticker;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  game_ticker.attach(1,tick);
  //FOR TESTING:
  curPiece = 5;
  curX = 3;
  curY = 0;
}

bool nexttick = true;

void tick(){
  nexttick = true;
  Serial.print("tick");
}

int count = 0;
void loop() {
  /*
  insert game logic here
  */
  while(nexttick && !check_collision() && count<3){
      move_down();
      disp();
      nexttick=false;
  }
  
  count++;
  update_Matrix();
  if (count<3){
    insert_piece();
  }
  else{
    Serial.end();
  }
}
