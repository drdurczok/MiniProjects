const int buttons = 15;     // (A2) the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int prev_buttonState = 0;

void button_setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttons, INPUT);
  Serial.begin(115200);
  Serial.println("INIT");
}

uint8_t isPressed() {
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  int val = analogRead(buttons);

  if     (val > -5 && val < 5) { buttonState = 2;  }    // Top button
  else if(val >=5 && val < 12) { buttonState = 1;  }    // Middle button
  else if(val >=12 && val < 22){ buttonState = 3;  }    // Bottom button
  else{ return 0; }



  if (prev_buttonState == buttonState){
    Serial.println("__________");
    Serial.println("Current  Button: " + String(buttonState));
    Serial.println("Previous Button: " + String(prev_buttonState));
    Serial.println("__________");
    return 0;
  }
  else {
    prev_buttonState = buttonState;
    buttonState = 0;
    Serial.println("Current  Button: " + String(buttonState));
    Serial.println("Previous Button: " + String(prev_buttonState));
    return prev_buttonState;
  }
}
