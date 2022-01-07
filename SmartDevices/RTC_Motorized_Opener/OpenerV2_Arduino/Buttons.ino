const int buttons = 15;     // (A2) the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void button_setup() {
  // initialize the pushbutton pin as an input:
  pinMode(buttons, INPUT);
  Serial.begin(115200);
  Serial.println("INI");
}

uint8_t isPressed() {
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  int val = analogRead(buttons);
  Serial.println(val);
  if(val > -5 && val < 5){
    return 3;
  }
  else if(val >=5 && val < 12){
    return 1;
  }
  else if(val >=12 && val < 22){
    return 2;
  }
  else{
    return 0;
  }
}
