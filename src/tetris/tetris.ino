/* Download the library at https://github.com/Links2004/arduinoWebSockets
 * Install with Sketch > Include Library > Add .ZIP Library...
 *
 * - Download the tool from
 *   https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.3.0/ESP8266FS-0.3.0.zip.
 *   In your Arduino sketchbook directory, create tools directory if it doesn't exist yet
 * - Unpack the tool into tools directory (the path will look like
 *   <user_dir>/Documents/tools/ESP8266FS/tool/esp8266fs.jar) // or inside arduino, tools
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
 * Or if it says : SPIFFS Not defined for ... Just choose a setting with SPIFFS under Tools>Flash Size
 * Even if your computer says that the files are smaller than the selected SPIFFS size, you can still get
 * this error: this has to do with block sizes, and metadata like file and folder names that take up space
 * as well.
 * If you change the SPIFFS size, you have to reupload your sketch, because when you change the SPIFFS size,
 * the memory location will be different. The program has to know the updated SPIFFS address offset to be able
 * to read the files.
**/
#include "globals.h"
#include <Ticker.h>

#define BOARD_HEIGHT 32
#define BOARD_WIDTH 16

bool isGamePaused = false;

int net_right = 0;
int net_rotate = 0;
int curX;
int curY;
int curPiece;
// MOVEMENT FUNCTIONS

void move_down(){ //moves piece down
  curY++;
}

void move_left(){
  if (!check_overlap_left()){
    curX--;
  }
}

void move_right(){
  if (!check_overlap_right()){
    curX++;
  }
}

void rotate_c(){
  if (!rotate_check_collision(0)){
    curPiece = (curPiece%4==3) ? curPiece-3 : curPiece+1;
  }
}

void rotate_ac(){
  if (!rotate_check_collision(1)){
    curPiece = (curPiece%4==0) ? curPiece+3 : curPiece-1;
  }
}

// COLLISION CHECK FUNCTIONS

bool check_overlap_left(){
  for (int i = 0; i<4; i++){
    for (int j = 0; j<4; j++){
      if (pieces[curPiece][i][j]!='-'){
        if (curX + j - 1 < 0){ // crashes with left side
          return true;
        }
        if (Matrix[curY+i][curX+j-1]!='-'){
          return true;
        }
      }
    }
  }
  return false;
}

bool check_overlap_right(){
  for (int i = 0; i<4; i++){
    for (int j = 0; j<4; j++){
      if (pieces[curPiece][i][j]!='-'){
        if (curX + j + 1 > 9){ // crashes with right side
          return true;
        }
        if (Matrix[curY+i][curX+j+1]!='-'){
          return true;
        }
      }
    }
  }
  return false;
}

bool rotate_check_collision(int anti){
  int tocheck;
  tocheck = (anti == 0) ? ((curPiece%4==3) ? curPiece-3 : curPiece+1) : ((curPiece%4==0) ? curPiece+3 : curPiece-1);
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

// GAME FUNCTIONS

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

void update_score_disp(){ //Updates Score matrix
  /*
   index of #1: 2<=i<=6, 1<=j<=3
   index of #2: 2<=i<=6, 5<=j<=7
   index of #3: 2<=i<=6, 9<=j<=11
   */
   int digit1 = score/100;
   int digit2 = (score-(score/100)*100)/10;
   int digit3 = score-((score/10)*10);
   for (int i = 2; i<7; i++){
    for (int j = 1; j<3; j++){
      Score[i][j] = numbers[digit1][i-2][j-1]; 
    }
   }
   for (int i = 2; i<7; i++){
    for (int j = 5; j<8; j++){
      Score[i][j] = numbers[digit2][i-2][j-1]; 
    }
   }
   for (int i = 2; i<7; i++){
    for (int j = 9; j<12; j++){
      Score[i][j] = numbers[digit3][i-2][j-1]; 
    }
   }
}

void check_full_line(){
  // FIND FULL LINES
  int full[21]; //array to store full rows
  int numfull = 0; //index to stop at
  bool is_full = true;
  for (int i = 20; i>=0; i--){ //finds full rows
    for (int j = 0; j<10; j++){
      if (Matrix[i][j] == '-'){
        is_full = false;
      }
    }
    if (is_full){
      full[numfull] = i;
      numfull++;
    }
    is_full = true;
  }
  // CLEAR FULL LINES
  for (int k = 0; k<numfull; k++){
    for (int m = 0; m<10; m++){
      Matrix[full[k]][m] = '-';
    }
  }
  // ADDS TO SCORE
  score += numfull;
  
  // SHIFTS EVERYTHING DOWN AFTER CLEARING
  if (numfull==0){
    return; // no full lines; nothing to shift down
  }
  int remain[21] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
  for (int i = 0; i<numfull; i++){
    remain[full[i]] = -1;
  }
  for (int i = 20; i>=0; i--){
    int idx = i;
    if (remain[i]!=-1){
      while (remain[idx+1]==-1){
        int temp = remain[idx];
        remain[idx+1] = temp;
        remain[idx] = -1;
        idx++;
        if (idx==20){
          break;
        }
      }
    }
  }
  for (int i = 20; i>=0; i--){
    if (remain[i]!=i && remain[i]!=-1){
      for (int j = 0; j<10; j++){
        Matrix[i][j] = Matrix[remain[i]][j];
      }
    }
    else if (remain[i]==-1){
      for (int j = 0; j<10; j++){
        Matrix[i][j] = '-';
      }
    }
  }
}

void generate_piece(){
  nextPiece = (random(0,7))*4;
}

void insert_piece(){
  curPiece = (nextPiece == -1) ? (random(0,7))*4 : nextPiece; // -1 -> first piece of the game
  generate_piece(); //generates the next piece so that it can be displayed
  curX = 3;
  curY = 0;
}

// TICKER FUNCTION

void tick(){
  nexttick = true;
  //Serial.print("tick");
  //Serial.print("\n");
}

// THE REST

void setup() {
    Serial.begin(115200);

    // server.ino
    mountFs();
    startWifi();
    startWebServer();
    startWebsocketServer();

    Ticker gameTicker;
    gameTicker.attach(1, tick);
}

void loop() {
    server.handleClient();
    
    webSocket.loop();

    if (net_right>0){
      while (net_right!=0){
        move_right();
        net_right--;
      }
    }

    if (net_right<0){
      while (net_right!=0){
        move_left();
        net_right++;
      }
    }

    if (net_rotate>0){
      while (net_rotate!=0){
        rotate_c();
        net_rotate--;
      }
    }

    if (net_rotate<0){
      while (net_rotate!=0){
        rotate_ac();
        net_rotate++;
      }
    }

    if (nexttick) {
        Serial.println("Game tick");
        nexttick = false;
    }
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
        webSocket.sendTXT(num, "start");
    } else if (strcmp(msg, "newgame") == 0) {
        
        serveControls(); // NEW
        isGamePaused = false;
        webSocket.sendTXT(num, "start");
    }
    // Control input
    else if (strcmp(msg, "slam") == 0) {
        // TODO
    } else if (strcmp(msg, "left") == 0) {
        Serial.printf("left");
        net_right--;
    } else if (strcmp(msg, "right") == 0) {
        net_right++;
    } else if (strcmp(msg, "down") == 0) {
        // TODO
    } else if (strcmp(msg, "clock") == 0) {
        net_rotate++;
    } else if (strcmp(msg, "anti") == 0) {
        net_rotate--;
    } else {
      Serial.printf("[Ws] Unknown message: %s\n", msg);
    }
}
