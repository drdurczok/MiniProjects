
#include <stdio.h>
#include <hFramework.h>
#include <math.h>
#include <Lego_Ultrasonic.h>
#include "Lego_Touch.h"

#define iMeas 190
#define tick 5
#define maxSens 225         //Maximum distance of target
#define goldilock 5         //Range of distance of target
#define minLen 5            //Minimum number of measurements to count as target

void calibrationMode();
void autoMode();
void manualControl();
void setLever();
void setAbs();
void proximityScan();
void systemScan();
void targetingAndFire();
void calibrate();
void calibrationPhase();
void fire(int);
void confirmPress();
void rotateAngle(int);
int setPower(int);

using namespace hSensors;

Lego_Ultrasonic sens(hSens1);
Lego_Touch sensor(hSens2);

int dist[iMeas];
int box[4]={0,0,0,0};

void hMain(void){
    printf("\r\n\n------Lady Fist Fire is getting ready, please hold------\r\n\n");
    calibrate();
    setAbs();
    printf("\r\nWe are ready to get going, what mode would you like to enter?");

    for (;;){
        if (hBtn1.isPressed() == true){
            sys.delay(500);
            if (hBtn2.isPressed() == true) {calibrationMode();}
            else {manualControl();}
        }
        if (hBtn2.isPressed() == true)  {autoMode();}
    }
}

void setLever(){
    hMot2.setPower(-200);
    hMot3.setPower(-200);
    sys.delay(180);
    hMot2.setPower(0);
    hMot3.setPower(0);
}

void proximityScan(){
    printf("\r\n\n*****Starting Scan*****\r\n\n");
    for (int i=0; i<iMeas; i++){
        hMot6.rotRel(tick,600);
        sys.delay(100);
        dist[i] = sens.readDist();
        printf("%d  |   ", dist[i]);
    }
    printf("\r\n\n*****Scan Finished*****\r\n\n");
}

//Calculate potential boxes and parameters
void systemScan(){
    printf("\r\n\n*****Starting Calculations*****\r\n\n");
    int n = 1;                   //Iterator
    int k = 0;                   //Iterator
    for (int j=0; j<iMeas; j++){
        if((dist[j] < maxSens)&&(abs(dist[j] - dist[j+1]) < goldilock)){
            k=1;
            printf("Found Potential Box");

            while(abs(dist[j+k] - dist[j+k+1]) < goldilock){k++;}
            printf("\r\nLength(k) = %d, j = %d\r\n",k,j);

            if(k>minLen){
                box[n]= (k/2)+j;
                n++;
            }
            j += k;
        }

    }
    printf("\r\n\n*****Calculations finished*****\r\n\n");
}

int setPower(int dist){
    int pow = 0;

    if (dist<=10){pow = 450;}
    else if (dist<=20){pow = 480;}
    else if (dist<=30){pow = 485;}
    else if (dist<=40){pow = 520;}
    else if (dist<=50){pow = 530;}
    else if (dist<=60){pow = 550;}
    else if (dist<=70){pow = 580;}
    else if (dist<=80){pow = 590;}
    else if (dist<=90){pow = 620;}
    else if (dist<=100){pow = 625;}
    else if (dist<=110){pow = 665;}
    else if (dist<=120){pow = 695;}
    else if (dist<=130){pow = 710;}
    else if (dist<=140){pow = 730;}
    else if (dist<=150){pow = 760;}
    else if (dist<=180){pow = 825;}
    else if (dist<=200){pow = 900;}
    else if (dist<=210){pow = 930;}
    else if (dist<=250){pow = 1000;}

    return pow;
}

void rotateAngle(int ang){
    hMot6.rotRel(ang*5.65,400);
}

void confirmPress(){
    int wait = 0;
    printf("Press the button to continue");
    while(wait == 0){
        LED1.toggle();
        sys.delay(100);
        if (sensor.isPressed() == true) {wait = 1;}
        if (hBtn1.isPressed() == true) {rotateAngle(10);}
        if (hBtn2.isPressed() == true) {rotateAngle(-10);}
    }
}

void targetingAndFire(){
    setAbs();
    int pow = 0;
    //Shoot to targets
    for (int n=1;n<4;n++){
        if (box[n] != 0){
            printf("Rotation ticks %d\r\n",(tick*(box[n]-box[n-1])));
            hMot6.rotRel((tick*(box[n]-box[n-1])),500);
            setLever();
            printf("<<<ARMED>>>");
            pow = setPower(dist[box[n]]);
            printf("Box[%d]  = %d steps | distance %d\r\n",n,box[n],dist[box[n]]);
            confirmPress();
            sys.delay(500);
            fire(pow);
        }
        else n++;
    }
    setAbs();
}

void calibrate(){
    for (int i = 0; i<5; i++){
        sys.delay(60);
        printf("%d | ",sens.readDist());
    }
    for(int i = 0; i < iMeas; i++){
        dist[i]=0;
    }
    for(int i = 0; i < 4; i++){
        box[i]=0;
    }
}

void setAbs(){
    sys.delay(100);
    while (sensor.isPressed() == false){
        hMot6.rotRel(1,500);
    }
    hMot6.rotRel(-950,400);
    sys.delay(100);
}

void fire(int power){
    printf("\r\n<<<FIRE>>> power = %d\r\n\r\n",power);
    sys.delay(500);
    hMot2.setPower(power);
    hMot3.setPower(power);
    sys.delay(100);
    hMot2.setPower(0);
    hMot3.setPower(0);
    sys.delay(200);
}
void calibrationPhase(){
    int Wait = 0;
    float pow = 0;

    rotateAngle(90);

    while(Wait == 0){
        sys.delay(1000);
        if (hBtn1.isPressed() == true)  {
            Wait = 1;
        }
        sens.readDist();

        printf("\r\n<<<SCAN>>> ");
        confirmPress();
        dist[0] = sens.readDist();
        printf("  ---> Distance %d",dist[0]);
        setLever();
        sys.delay(2000);

        pow = setPower(dist[0]);

        printf("\r\n<<<ARMED>>>");
        confirmPress();
        fire(pow);
    }
    Wait = 0;
}

void calibrationMode(){
    printf("\r\n\n*****Entered Calibration Mode*****\r\n\n");
    calibrationPhase();
    setAbs();
    calibrate();
    printf("\r\n\n*****Exciting Calibration Mode*****\r\n\n");
}

void autoMode(){
    printf("\r\n\n*****Entered Automated Control*****\r\n\n");
    proximityScan();
    systemScan();
    targetingAndFire();
    hMot2.setPower(0);
    hMot3.setPower(0);
    calibrate();
    printf("\r\n\n*****Exciting Automated Control*****\r\n\n");
}

void manualControl(){
    printf("\r\n\n*****Entered Manual Control*****\r\n\n");
    int selfAng = 0;
    int selfPow = 0;
    int selfDist = 0;
    int wait = 0;
    getchar();

    while (wait == 0){
        printf("\r\nPlease enter angle of shot: ");
        scanf("%d",&selfAng);
        getchar();
        printf("\r\nYou entered: %d" ,selfAng);
        if(selfAng <= 0) {printf("\r\nEnter a valid number\r\n");}
        else {wait = 1;}
    }
    wait = 0;
    while (wait == 0){
        printf("\r\nPlease enter distance of shot: ");
        scanf("%d",&selfDist);
        getchar();
        printf("\r\nYou entered: %d",selfDist);
        if(selfDist <= 0) {printf("\r\nEnter a valid number\r\n");}
        else {wait = 1;}
    }
    wait = 0;
    rotateAngle(selfAng);
    printf("\r\nAngle set | ");
    setLever();
    printf("Lever set | ");
    selfPow = setPower(selfDist);
    printf("Power calculated | ");
    printf("<<<ARMED>>>");
    confirmPress();
    printf("Button pressed | ");
    fire(selfPow);
    printf("fire\r\n");

    setAbs();
    calibrate();

    printf("\r\n\n*****Exciting Manual Control*****\r\n\n");
}