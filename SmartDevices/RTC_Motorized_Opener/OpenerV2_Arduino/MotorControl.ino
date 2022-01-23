#define en 3
#define dir 2

//_____________________________________________
void motor_action_open(){
  if(motorState != 1){
    LCD_print_bottom("OPENING         "); 
    motor_open_sec(motorOpenLen);
    motorState = 1;
    writeEEPROM(state_addr, motorState);
  }
}

void motor_action_close(){
  if(motorState != 0){
    LCD_print_bottom("CLOSING         "); 
    motor_close_sec(motorCloseLen);
    motorState = 0;
    writeEEPROM(state_addr, motorState);
  }
}

//_____________________________________________
void motor_startup(){
  pinMode(en, OUTPUT);
  motor_stop();

  pinMode(dir, OUTPUT);  
}

void motor_stop(){
  analogWrite(en, 0);
}

void motor_start(){
  analogWrite(en, 255);
}

void motor_open(){
  motor_stop();
  delay(100);
  analogWrite(dir, 0);
  delay(100);
  motor_start();
}

void motor_close(){
  motor_stop();
  delay(100);
  analogWrite(dir, 255);
  delay(100);
  motor_start();
}

void motor_open_sec(int motorTime){
  motor_open();
  delay(motorTime*100);
  motor_stop();
}

void motor_close_sec(int motorTime){
  motor_close();
  delay(motorTime*100);
  motor_stop();
}
