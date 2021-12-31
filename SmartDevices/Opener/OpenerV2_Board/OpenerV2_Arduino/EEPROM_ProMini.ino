#include <EEPROM.h>

/** the current address in the EEPROM (i.e. which byte we're going to write to next) **/
int addr = 0;


void writeEEPROM(uint8_t addr, uint8_t val){
  /***
    Write the value to the appropriate byte of the EEPROM.
    these values will remain there when the board is
    turned off.
  ***/

  EEPROM.write(addr, val);
}

uint8_t readEEPROM(uint8_t addr){
  return EEPROM.read(addr);
}
