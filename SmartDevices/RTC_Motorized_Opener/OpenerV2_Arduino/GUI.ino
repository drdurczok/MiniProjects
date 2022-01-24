#define MENU_MAX 5;
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
  LCD_print_top("Booting...");
  delay(1000);
  
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

void menu_reset(){
  menu_id = 0;
  menu_id_prev = 1;
}

void menu_select(){
  menu();
  //Iterate through menu
  if(isPressed(1)){
    menu_id = (menu_id + 1) % MENU_MAX;
    Serial.println("Going to menu: " + String(menu_id));
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
    //case 5: menu_calibration( "     Manual", 16); break;
  }
  menu_id_prev = menu_id;
}
