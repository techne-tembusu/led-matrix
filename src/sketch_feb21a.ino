int count = 1;
char pieces[] = {'O','I','S','Z','L','J','T'};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

char gen_piece(){ //generates random piece
  return pieces[random(7)];
}

void disp(char m[21][10], int row, int col){
  for (int i=0; i<row; i++){ //ignore first row
    for (int j=0; j<col; j++){
      Serial.print(m[i][j]);
      Serial.print(' ');
    }
    Serial.print("\n");
  }
  Serial.print("\n");
}

void move_down(){ //every GAME_TIME the thing will move down
  return; 
}

void move_left(){
  return;
}

void move_right(){
  return;
}

void rotate(){
  return; //haha
}

void check_full_line(){
  return;
}

void shift_down(){ //shift all tiles down after clearing line
  return;
}

void clear_line(){
  return;
}

bool check_collision(char m[21][10], char color){
  for (int i = 20; i>=0; i--){ //iteration from bottom-up to make check more efficient
    for (int j = 0; j<10; j++){
      if (m[i][j] == color){
        if (i == 20){ //collides with bottom
          return true;
        }
        else if(m[i+1][j] == 'w'){
          return true; // collides with already dropped pieces
        }
      }
    }
  }
  return false; //collided with nothing
}

void insert_piece(char c, char m[21][10]){ //temporarily have piece just magically appear in its entirely
  if(c == 'O'){
    char m1[4][4]={ {'-','X','X','-'},
                    {'-','X','X','-'},
                    {'-','-','-','-'},
                    {'-','-','-','-'} };
    for(int r = 0; r<4; r++){ //using the padding
      for(int c = 3; c<7; c++){
        if(m[r][c] == '-'){ // if not m[r][c] == '-', should return error (not handled yet)
          m[r][c] = m1[r][c-3];
        }
        }
      }
      
        } else if(c == 'I'){
          char m1[4][4]={ {'-','-','-','-'},
                          {'X','X','X','X'},
                          {'-','-','-','-'},
                          {'-','-','-','-'} }; //appears on the second row so that it can be seen
     for(int r = 0; r<4; r++){ 
      for(int c = 3; c<7; c++){
        if(m[r][c] == '-'){
          m[r][c] = m1[r][c-3];
        }
        }
      }
      } else if(c=='S'){
    char m1[4][4]={ {'-','-','X','X'},
                    {'-','X','X','-'},
                    {'-','-','-','-'},
                    {'-','-','-','-'} };
    for(int r = 0; r<4; r++){ //using the padding
      for(int c = 3; c<7; c++){
        if(m[r][c] == '-'){ // if not m[r][c] == '-', should return error (not handled yet)
          m[r][c] = m1[r][c-3];
        }
        }
    }        
      } else if(c=='Z'){
    char m1[4][4]={ {'-','X','X','-'},
                    {'-','-','X','X'},
                    {'-','-','-','-'},
                    {'-','-','-','-'} };
    for(int r = 0; r<4; r++){ //using the padding
      for(int c = 3; c<7; c++){
        if(m[r][c] == '-'){ // if not m[r][c] == '-', should return error (not handled yet)
          m[r][c] = m1[r][c-3];
        }
        }
    }             
      } else if(c=='L'){
    char m1[4][4]={ {'-','-','-','X'},
                    {'-','X','X','X'},
                    {'-','-','-','-'},
                    {'-','-','-','-'} };
    for(int r = 0; r<4; r++){ //using the padding
      for(int c = 3; c<7; c++){
        if(m[r][c] == '-'){ // if not m[r][c] == '-', should return error (not handled yet)
          m[r][c] = m1[r][c-3];
        }
        }
    }        
      } else if(c=='J'){
    char m1[4][4]={ {'-','X','-','-'},
                    {'-','X','X','X'},
                    {'-','-','-','-'},
                    {'-','-','-','-'} };
    for(int r = 0; r<4; r++){ //using the padding
      for(int c = 3; c<7; c++){
        if(m[r][c] == '-'){ // if not m[r][c] == '-', should return error (not handled yet)
          m[r][c] = m1[r][c-3];
        }
        }
    }        
      } else if(c=='T'){
    char m1[4][4]={ {'-','-','X','-'},
                    {'-','X','X','X'},
                    {'-','-','-','-'},
                    {'-','-','-','-'} };
    for(int r = 0; r<4; r++){ //using the padding
      for(int c = 3; c<7; c++){
        if(m[r][c] == '-'){ // if not m[r][c] == '-', should return error (not handled yet)
          m[r][c] = m1[r][c-3];
        }
        }
    }                
      }
  }

  //hardcoded for the 7 pieces; no staggered entry (leave for later, if got time)
//  pass;
// insert into index 4 (pos 5)


//void change_color(char m[20][10], char color){ //after piece has fallen, color to be changed to white
//  int bottom = -1;
//  for (int i = 19; i=>0; i--){
//    if (i<bottom-4){ //early termination; pieces are at most 4 tiles in height
//      break;
//    }
//    for (int j = 0; j<10; j++){
//      if (m[i][j] == color){
//         m[i][j] = 'w';
//        if (bottom == -1){
//          bottom = i;
//        }
//      }
//    }
//  }
//}


void loop() {
  // put your main code here, to run repeatedly: // changed to 21 for padding top layer
  char matrix[21][10]= {
                      {'-','-','-','-','-','-','-','-','-','P'}, //P = padding layer
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
                      {'-','-','-','-','-','-','-','-','-','-'}};
  while (count <= 1){
    disp(matrix, 21, 10);  
//    Serial.print(gen_piece());
    Serial.print("\n");
    insert_piece('O', matrix);
    disp(matrix, 21, 10);
    count++;         
  }
}
