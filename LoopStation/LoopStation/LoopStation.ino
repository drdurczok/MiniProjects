int row1 = 6;
int row2 = 7;
int row3 = 8;
int row4 = 9;
int col1 = A3;
int col2 = A2;
int col3 = A1;
int col4 = A0;

int thresh = 500;

void setup() {
  Serial.begin(9600);
  
  pinMode(col1, INPUT_PULLUP);
  pinMode(col2, INPUT_PULLUP);
  pinMode(col3, INPUT_PULLUP);
  pinMode(col4, INPUT_PULLUP);
  pinMode(row1, OUTPUT);
  pinMode(row2, OUTPUT);
  pinMode(row3, OUTPUT);
  pinMode(row4, OUTPUT);

  digitalWrite(row1, HIGH);
  digitalWrite(row2, HIGH);
  digitalWrite(row3, HIGH);
  digitalWrite(row4, HIGH);

  delay(100);

  Serial.write("Initialized");
}

int scanRow(int pin){
  digitalWrite(pin, LOW);
  delay(10);
  int col1_value = analogRead(col1);
  int col2_value = analogRead(col2);
  int col3_value = analogRead(col3);
  int col4_value = analogRead(col4);
  digitalWrite(pin, HIGH);

  int button = 0;
  if (col1_value < thresh){
    button = 1;
  }
  if (col2_value < thresh){
    button = 2;
  }
  if (col3_value < thresh){
    button = 3;
  }
  if (col4_value < thresh){
    button = 4;
  }

  return button;
}

int pressed;
void loop() {
  pressed = scanRow(row1);
  if(pressed > 0){
    Serial.print("Pressed 1x");
    Serial.println(pressed);
  }
  pressed = scanRow(row2);
  if(pressed > 0){
    Serial.print("Pressed 2x");
    Serial.println(pressed);
  }
  pressed = scanRow(row3);
  if(pressed > 0){
    Serial.print("Pressed 3x");
    Serial.println(pressed);
  }
  pressed = scanRow(row4);
  if(pressed > 0){
    Serial.print("Pressed 4x");
    Serial.println(pressed);
  }
}
