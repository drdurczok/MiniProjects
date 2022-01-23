void menu_calibration(String menuText, uint8_t addr){
  if(menu_id != menu_id_prev || updateText){
    LCD_clear();
    LCD_print_top(menuText);

    String timestring = "CLOSE       OPEN";
            
    LCD_print_bottom(timestring);

    updateText = 0;
  }

  if(isPressed(2)){
    LCD_print_bottom("         OPENING");
    motor_open();
   
    motor_stop();
    LCD_print_bottom(date);

    motorState = 3;
    writeEEPROM(state_addr, motorState);

    updateText = 1;
  }
  else if(isPressed(3)){
    LCD_print_bottom("CLOSING         ");
    motor_close();

    motor_stop();
    LCD_print_bottom(date);

    motorState = 3;
    writeEEPROM(state_addr, motorState);

    updateText = 1;
  }
}
