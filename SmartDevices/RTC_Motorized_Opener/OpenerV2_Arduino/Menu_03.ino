
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

  uint8_t button_press_top = isPressed(2);
  uint8_t button_press_bottom = isPressed(3);
  
  if(button_press_top || button_press_bottom){
    int16_t temp_len = motor_len;
    
    if(button_press_top){
      temp_len += 1;
    }
    else if(button_press_bottom){
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
