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

  uint8_t button_press_top = isPressed(2);
  uint8_t button_press_bottom = isPressed(3);

  if(button_press_top || button_press_bottom){
    int16_t temp_min = motor_min;
    int16_t temp_hour = motor_hour;
    if(button_press_top){
      temp_min += 15;
    }
    else if(button_press_bottom){
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
