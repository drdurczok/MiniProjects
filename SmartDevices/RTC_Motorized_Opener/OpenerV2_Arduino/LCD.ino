/*
 * LCD Pinout
 * 1(GND), 2(VCC), 3(4.7K Potentiometer), 4(12 - RS), 5(GND), 6(11 - EN), 
 * 7(NULL), 8(NULL), 9(NULL), 10(NULL), 
 * 11(5), 12(4), 13(3), 14(2), 15(VCC), 16(GND)
 */

#include <LiquidCrystal.h>

const int LCD_BACKLIGHT = 14;

// initialize the library with the numbers of the interface pins
const int rs = 4, en = 9, d4 = 8, d5 = 7, d6 = 6, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void LCD_setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(LCD_BACKLIGHT, OUTPUT);
  digitalWrite(LCD_BACKLIGHT, HIGH);
}

void LCD_clear(){
  lcd.clear();
}

void LCD_print_top(String text) {
  lcd.setCursor(0,0); // start on third position of the second line of the display
  lcd.print (text + "                ");
}

void LCD_print_bottom(String text) {
  lcd.setCursor(0,1); // start on third position of the second line of the display
  lcd.print (text + "                ");
}

void LCD_BacklightOn() {
  digitalWrite(LCD_BACKLIGHT, HIGH);
}

void LCD_BacklightOff() {
  digitalWrite(LCD_BACKLIGHT, LOW);
}

void LCD_print(String text) {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  //Print a message to second line of LCD
  lcd.print(text);
}
