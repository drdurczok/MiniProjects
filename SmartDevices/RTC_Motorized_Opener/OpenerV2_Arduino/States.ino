enum CPUState {Asleep, Awake};
bool CPUState = Awake;

enum MotorState {Closed, Open};
bool motor_state = Closed;

uint8_t buttonPressMin;

void main_init(){
  motor_startup();
  LCD_setup();
  RTC_setup();
  button_setup();
  gui_startup();
  
  buttonPressMin = RTC_getMin();
}

void main_loop(){
  if (!CPUState) {
    sleep_init();
    while(!CPUState){
      sleep();
    }
  }
  else{
    awake_init();
    while(is_active()){
      awake();
    }
  }
}

//______________________________________________________
//
//                    Sleep Mode
//______________________________________________________

void sleep_init(){
  LCD_clear();
  LCD_BacklightOff();
}

void sleep(){
  // Check if opening and closing time is met
  if(motorOpen_hour == RTC_getHourInt()){
    if(motorOpen_min == RTC_getMin()){
      motor_action_open();
      delay(70000);
    }
  }
  else if(motorClose_hour == RTC_getHourInt()){
    if( motorClose_min == RTC_getMin()){
      motor_action_close();
      delay(70000);
    }
  }

  button_scan();
  //If any button is pressed enter awake state
  if(isPressed(1) || isPressed(2) || isPressed(3)){
    //Get current minute which is used for screen timeout
    buttonPressMin = RTC_getMin();
    CPUState = Awake;
  }

  delay(1000);
}

//______________________________________________________
//
//                    Awake Mode
//______________________________________________________
void awake_init(){
  menu_reset();
  LCD_BacklightOn();
}

void awake(){
  button_scan();
  menu_select();
}


//______________________________________________________
//
//                    Helper Methods
//______________________________________________________
bool is_active(){
  //Check time since last button press
  if(abs(RTC_getMin() - buttonPressMin) > 1){
    CPUState = Asleep;
    return false;
  }
  return true;
}
