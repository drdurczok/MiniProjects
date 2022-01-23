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
  
  if(isPressed(2))     {
    motor_action_open(); }
  if(isPressed(3)){
    motor_action_close();}
}
