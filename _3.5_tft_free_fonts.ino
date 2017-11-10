#include <TFT_HX8357.h>
#include "Free_Fonts.h"
#include <PID_v1.h>

TFT_HX8357 tft = TFT_HX8357();

//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Define the aggressive and conservative Tuning Parameters
double aggKp=4, aggKi=0.2, aggKd=1;
double consKp=1, consKi=0.05, consKd=0.25;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint, consKp, consKi, consKd, DIRECT);


void setup() {
 
tft.init();
tft.setRotation(1);
tft.fillScreen(HX8357_BLACK);
printUI();
Input = analogRead(0);
Setpoint = 100;
myPID.SetMode(AUTOMATIC);
}

void loop(){
  
Input = analogRead(0);
  
  double gap = abs(Setpoint-Input); //distance away from setpoint
  if(gap<10)
  {  //we're close to setpoint, use conservative tuning parameters
    myPID.SetTunings(consKp, consKi, consKd);
  }
  else
  {
     //we're far from setpoint, use aggressive tuning parameters
     myPID.SetTunings(aggKp, aggKi, aggKd);
  }
  
  myPID.Compute();
  analogWrite(3,Output);

tft.setCursor(20,230);
tft.setTextFont(6);
tft.setTextColor(TFT_GREEN,TFT_BLACK);
tft.println(Input);

tft.setCursor(20,145);
tft.setTextFont(6);
tft.setTextColor(TFT_GREEN,TFT_BLACK);
tft.println(Setpoint);

delay(1000);
}

void printUI()
{
  
tft.drawRoundRect(5,5,470,71,5,TFT_WHITE);
tft.drawRoundRect(6,6,470,71,5,TFT_WHITE);
//tft.fillRect(5,5,470,71,TFT_WHITE);
//tft.fillRect(6,6,470,71,TFT_WHITE);

tft.drawRoundRect(5,90,220,225,5,TFT_GREEN);
tft.drawRoundRect(6,91,220,225,5,TFT_GREEN);

tft.drawRoundRect(250,90,220,225,5,TFT_WHITE);
tft.drawRoundRect(251,91,220,225,5,TFT_WHITE);
  
tft.fillRect(26,80,180,40,TFT_GREEN);
tft.fillRect(270,80,180,40,TFT_WHITE);


tft.setCursor(45,112);
tft.setTextColor(TFT_RED);
tft.setFreeFont(FSB18);
tft.print("ACTUAL");

tft.setCursor(30,280);
tft.setTextColor(TFT_GREEN);
tft.setTextFont(1);
tft.print("TEMPERATURE");

tft.setCursor(30,198);
tft.setTextColor(TFT_GREEN);
tft.setTextFont(1);
tft.print("DUTY CYCLE");

tft.setCursor(285,112);
tft.setTextColor(TFT_RED);
tft.setFreeFont(FSB18);
tft.print("SETTING");


tft.setCursor(190,175);
tft.setTextColor(TFT_GREEN);
tft.setFreeFont(FSB12);
tft.print("%");

tft.setCursor(430,175);
tft.setTextColor(TFT_WHITE);
tft.setFreeFont(FSB12);
tft.print("%");

tft.setCursor(190,260);
tft.setTextColor(TFT_GREEN);
tft.setFreeFont(FSB12);
tft.print("C");

tft.setCursor(180,250);
tft.setTextColor(TFT_GREEN);
tft.setFreeFont(FSB9);
tft.print("o");

tft.setCursor(435,260);
tft.setTextColor(TFT_WHITE);
tft.setFreeFont(FSB12);
tft.print("C");

tft.setCursor(425,250);
tft.setTextColor(TFT_WHITE);
tft.setFreeFont(FSB9);
tft.print("o");

tft.setCursor(65,50);
tft.setTextColor(TFT_GREEN);
tft.setFreeFont(FSB18);
tft.print("MAIN CONTROLLER");

}


