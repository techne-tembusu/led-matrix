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

void disp(char m[10][20], int row, int col){
  for (int i=0; i<row; i++){
    for (int j=0; j<col; j++){
      Serial.print(m[i][j]);
      Serial.print(' ');
    }
    Serial.print("\n");
  }
  Serial.print("\n");
}

void move_down(){ //every GAME_TIME the thing will move down
  pass; 
}

void move_left(){
  pass;
}

void move_right(){
  pass;
}

void rotate(){
  pass; //haha
}

void check_full_line(){
  pass;
}

void shift_down(){ //shift all tiles down after clearing line
  pass;
}

void clear_line(){
  pass;
}

int lower_x_coord(){
  pass;
}

int lower_y_coord(){
  pass;
}

void check_collision(){
  pass;
}

void insert_piece(){ //temporarily have piece just magically appear in its entirely
  //hardcoded for the 7 pieces; no staggered entry (leave for later, if got time)
  pass;
}

void change_color(){ //after piece has fallen, color to be changed to white
  pass;
}


void loop() {
  // put your main code here, to run repeatedly:
  char matrix[10][20]= {{'-','-','-','-','-','-','-','-','-','-'},
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
  while (count <= 20){
    //disp(matrix, 10, 20);  
    Serial.print(gen_piece());
    Serial.print("\n");
    count++;         
  }
}
