#include <SDS011.h>

#include <UTFT.h>
#include <URTouch.h>

float p10,p25;
int error;
SDS011 sds;

extern uint8_t BigFont[];
UTFT myGLCD(ITDB24E_V2_8,13,12,17,16);
URTouch myTouch(15,10,14,9,8);
  
void setup() {
  sds.begin(18,19);

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_HI);

  myGLCD.InitLCD();
  myGLCD.setFont(BigFont);

  myGLCD.clrScr();

  myGLCD.setColor(0, 55, 55);
  myGLCD.fillRoundRect(10, 125, 310, 230); //(Point1X,Point1Y,Point2X,Point2Y)
  myGLCD.setBackColor(0, 55, 55);

  myGLCD.setColor(255, 255, 255);
  myGLCD.print("PM 2.5",300,225,180); //(text, X, Y,)
  myGLCD.print("PM 10" ,300,170,180);

  delay(1000);
  //Serial.begin(9600);
}

void loop() {
  show_pm();
  //print_pm();
  delay(5000);
}

void show_pm(){  
  myGLCD.setColor(0, 55, 55);
  myGLCD.fillRoundRect(10, 125, 210, 210); //(Point1X,Point1Y,Point2X,Point2Y)
  myGLCD.setBackColor(0, 55, 55);
    
  error = sds.read(&p25,&p10);
  if (! error) {
    myGLCD.setColor(255, 255, 255);
    myGLCD.print(String(p25),150,205,180);
    myGLCD.print(String(p10) ,150,150,180);
  }
}


//______________________________________________-
void print_pm(){
  error = sds.read(&p25,&p10);
  if (! error) {
    Serial.println("____________________");
    Serial.println("P2.5: "+String(p25));
    Serial.println("P10:  "+String(p10));
  }
}
