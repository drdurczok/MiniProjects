#include "Button_Grid.h"

int row[4] = {6, 7, 8, 9};
int col[4] = {A3, A2, A1, A0};
int thresh = 500;

bool state[4][4] = {0,0,0,0,
                    0,0,0,0,
                    0,0,0,0,
                    0,0,0,0};

void button_grid_init(){
  pinMode(col[0], INPUT_PULLUP);
  pinMode(col[1], INPUT_PULLUP);
  pinMode(col[2], INPUT_PULLUP);
  pinMode(col[3], INPUT_PULLUP);
  pinMode(row[0], OUTPUT);
  pinMode(row[1], OUTPUT);
  pinMode(row[2], OUTPUT);
  pinMode(row[3], OUTPUT);

  digitalWrite(row[0], HIGH);
  digitalWrite(row[1], HIGH);
  digitalWrite(row[2], HIGH);
  digitalWrite(row[3], HIGH);

  delay(100);

  led_init();

  Serial.write("Button Grid Initialized");
}

void set_to_on(int col, int row){
  if (state[col][row] == false){
    led_light(col, row);

    state[col][row] = true;
  }
}

void set_to_off(int col, int row){
  if (state[col][row] == true){
    led_reset(col, row);

    state[col][row] = false;
  }
}

void scanRow(int i){
  digitalWrite(row[i], LOW);
  delay(10);
  int col0_value = analogRead(col[0]);
  int col1_value = analogRead(col[1]);
  int col2_value = analogRead(col[2]);
  int col3_value = analogRead(col[3]);
  digitalWrite(row[i], HIGH);

  
  if (col0_value < thresh){ set_to_on(i, 0); }
  else                    { set_to_off(i, 0); }

  if (col1_value < thresh){ set_to_on(i, 1); }
  else                    { set_to_off(i, 1); }

  if (col2_value < thresh){ set_to_on(i, 2); }
  else                    { set_to_off(i, 2); }

  if (col3_value < thresh){ set_to_on(i, 3); }
  else                    { set_to_off(i, 3); }

}

void isPressed(){
  scanRow(0);
  scanRow(1);
  scanRow(2);
  scanRow(3);
}
