const int buttons = 15;     // (A2) the number of the pushbutton pin

// variables will change:
uint8_t button_buffer = 0;         // variable for reading the pushbutton status
double timestamp = 0;


void button_setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttons, INPUT);
  Serial.begin(115200);
  Serial.println("INIT");
}

void button_scan() {
  uint8_t button_temp = button_check();

  // If a button was pressed and it is not an already handled press, handle the press
  if (button_temp && button_temp != button_buffer){
    double timestamp_temp = millis();

    if ((timestamp_temp - timestamp) > 300){
      button_buffer = button_temp;
      timestamp = timestamp_temp;      
    }
  }
}

bool isPressed(uint8_t ask) {
  if (button_buffer == ask) {
    button_buffer = 0;
    return true;
  }
  return false;
}

uint8_t button_check() {
  uint8_t val = analogRead(buttons);

  if     (val > -5 && val < 5) { return 2;  }    // Top button
  else if(val >=5 && val < 16) { return 1;  }    // Middle button
  else if(val >=16 && val < 22){ return 3;  }    // Bottom button
  else{ return 0; }
}
