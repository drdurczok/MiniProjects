#define MENU_MAX 6;
uint8_t menu_id = 0;
uint8_t menu_id_prev = 1;
String date, date_prev;

uint8_t motorOpen_hour = 6;
uint8_t motorOpen_min = 30;
uint8_t motorClose_hour = 20;
uint8_t motorClose_min = 30;
bool    motorOpen = 1;
bool    motorClose = 1;
uint8_t motorOpenLen = 50;
uint8_t motorCloseLen = 50;
uint8_t motorState = 0;   //0 - closed, 1 - open, 2 - undefined
bool updateText = 0;
uint8_t state_addr = 16;

void gui_startup(){
  motorOpen_hour = EEPROM.read(0);
  motorOpen_min = EEPROM.read(1);
  motorOpen = EEPROM.read(2);
  motorClose_hour = EEPROM.read(4);
  motorClose_min = EEPROM.read(5);
  motorClose = EEPROM.read(6);
  motorOpenLen = EEPROM.read(8);
  motorCloseLen = EEPROM.read(12);
  motorState = EEPROM.read(state_addr);
}

void motor_action_open(){
  if(motorState != 1){
    motor_open_sec(motorOpenLen);
    motorState = 1;
    writeEEPROM(state_addr, motorState);
  }
}

void motor_action_close(){
  if(motorState != 0){
    motor_close_sec(motorCloseLen);
    motorState = 0;
    writeEEPROM(state_addr, motorState);
  }
}

void menu_reset(){
  menu_id = 0;
  menu_id_prev = 1;
}

void menu_select(){
   menu();
  //Iterate through menu
  if(isPressed() == 1){
    menu_id = (menu_id + 1) % MENU_MAX;
    while(isPressed());
  }     
}

void menu(){
  //Menu interface
  switch(menu_id){
    case 0: menu_01(); break;
    case 1: menu_toggleTime(motorOpen_min, motorOpen_hour, motorOpen, "Set Opening Time", 0); break;
    case 2: menu_toggleTime(motorClose_min, motorClose_hour, motorClose, "Set Closing Time", 4); break;
    case 3: menu_toggleLen(motorOpenLen, "Set Opening Len", 8); break;
    case 4: menu_toggleLen(motorCloseLen, "Set Closing Len", 12); break;
    case 5: menu_calibration( "     Manual", 16); break;
  }
  menu_id_prev = menu_id;
}

void menu_01(){
  if(menu_id != menu_id_prev){
    LCD_clear();
    LCD_print_top(RTC_getDate());
  }
  
  date = RTC_getTime();
  if (date_prev.compareTo(date)){
      LCD_print_bottom(date);
      date_prev = date;
  }
  
  if(isPressed()==2)     { motor_action_open(); }
  else if(isPressed()==3){ motor_action_close();}
}

void menu_toggleTime(uint8_t& motor_min, uint8_t& motor_hour, bool& motorState, String menuText, uint8_t addr){
  if(menu_id != menu_id_prev || updateText){
    LCD_clear();
    LCD_print_top(menuText);

    if(motorState){
      char timestring[16];
  
      snprintf_P(timestring, 
              countof(timestring),
              PSTR("          %02u:%02u"),
              motor_hour,
              motor_min );
              
      LCD_print_bottom(timestring);
    }
    else{
      LCD_print_bottom("           --:--");
    }
    updateText = 0;
  }

  if(isPressed()){
    delay(10);
    int16_t temp_min = motor_min;
    int16_t temp_hour = motor_hour;
    if(isPressed()==2){
      temp_min += 15;
    }
    else if(isPressed()==3){
      temp_min -=15;
    }
    if (temp_min >= 60){
      temp_min = 0;
      temp_hour += 1;
      if(temp_hour > 23){
        temp_hour = 0;
      }
    }
    else if (temp_min < 0){
      temp_min = 45;
      temp_hour -= 1;
      if(temp_hour < 0){
        temp_hour = 23;
      }
    }
    motor_min = temp_min % 60;
    motor_hour = temp_hour;
    updateText = 1;

    if(motor_hour == 0 && motor_min == 0){
      motorState = 0;
    }
    else{
      motorState = 1;
    }
    
    writeEEPROM(addr, motor_hour);
    writeEEPROM(addr + 1, motor_min);
    writeEEPROM(addr + 2, motorState);
    //Write number of EEPROM write cycles per byte
    writeEEPROM(addr + 3, readEEPROM(addr + 3) + 1);
  }
}


void menu_toggleLen(uint8_t& motor_len, String menuText, uint8_t addr){
  if(menu_id != menu_id_prev || updateText){
    LCD_clear();
    LCD_print_top(menuText);

    String s1 = String(motor_len/10);
    String s2 = String(motor_len%10);
    String timestring = "            " + s1 + "." + s2;
            
    LCD_print_bottom(timestring);

    updateText = 0;
  }

  if(isPressed()){
    delay(10);
    int16_t temp_len = motor_len;
    
    if(isPressed()==2){
      temp_len += 1;
    }
    else if(isPressed()==3){
      temp_len -= 1;
    }
    if (temp_len >= 400){
      temp_len = 400;
    }
    else if (temp_len < 0){
      temp_len = 0;
    }

    motor_len = temp_len;
    updateText = 1;
    
    writeEEPROM(addr, motor_len);
    //Write number of EEPROM write cycles per byte
    writeEEPROM(addr + 3, readEEPROM(addr + 3) + 1);
  }
}

void menu_calibration(String menuText, uint8_t addr){
  if(menu_id != menu_id_prev || updateText){
    LCD_clear();
    LCD_print_top(menuText);

    String timestring = "CLOSE       OPEN";
            
    LCD_print_bottom(timestring);

    updateText = 0;
  }

  if(isPressed()==2){
    while(isPressed()== 2){
      LCD_print_bottom("         OPENING");
      motor_open();
    }
    motor_stop();
    LCD_print_bottom(date);

    motorState = 3;
    writeEEPROM(state_addr, motorState);

    updateText = 1;
  }
  else if(isPressed()==3){
     while(isPressed()==3){
      LCD_print_bottom("CLOSING         ");
      motor_close();
     }
    motor_stop();
    LCD_print_bottom(date);

    motorState = 3;
    writeEEPROM(state_addr, motorState);

    updateText = 1;
  }
}
