int count = 0;
void loop() {
  /*
  insert game logic here
  */
  char mv;
  if (Serial.available()>0){
    mv = Serial.read();
  }
  switch(mv){
    case 'l':
      move_left();
      disp();
      break;
    case 'r':
      move_right();
      disp();
      break;
  }
  if (nexttick){
    if (count<3){
      if (!check_collision()){
        move_down();
        disp();
        nexttick=false;
      }
      else{
        count++;
        update_Matrix();
        if (count<3){
          insert_piece();
        }
        else{
          Serial.end();
        }
      }
    }
  }
}
