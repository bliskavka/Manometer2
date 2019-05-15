#include <GyverEncoder.h>
#include <Thread.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "OneButton.h"
#include "GyverEncoder.h"
#include "Data.h"

#define REFRESH_TIME 800

#define DEBUG_ENABLED true
#define DISPLAY_REFRESH false
#define ROUNDING_ENABLED true

#define RIGHT 1
#define LEFT 2

#define MAINVIEW 1
#define WINDSPEEDVIEW 2
#define SETTINGSVIEW 3
int activeView; //mainScreen, lcdSettingsScreen, bluetoothSettingsScreen

LiquidCrystal_I2C lcd(0x3f, 20, 4); // 0x3f for large, 0x3f for small disp
Encoder enc1(3, 4, 5);

Thread adcThread = Thread();
OneButton button1(3, true);
float dpValue = 0.0;
int i;

uint8_t symbols[3][8] = {{12, 18, 18, 12, 0, 0, 0, 0 }, // degree
                         {14, 31, 17, 17, 17, 17, 17, 31 }, // battery 4.76
                         {0, 4, 2, 31, 2, 4, 0, 0}}; // arrow

Data data;

//************************setup**********************
void setup()
{
  Serial.begin(9600);
  enc1.setType(TYPE2);
  data.setupData();

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  lcd.init();
  lcd.createChar(1, symbols[0]); // degree
  lcd.createChar(2, symbols[2]); // arrow

  activeView = MAINVIEW;

  adcThread.onRun(selectDisplayOutput);   //creating new thread
  adcThread.setInterval(REFRESH_TIME);  //loop interval
}

//***********************loop*********************
void loop()
{
  enc1.tick();
  if (enc1.isRight()) onTurn(RIGHT);
  if (enc1.isLeft()) onTurn(LEFT);
  if (enc1.isRelease()) onClick();
  if (enc1.isHolded()) onHold();
  if (enc1.isRightH()) onHoldTurn(RIGHT);
  if (enc1.isLeftH()) onHoldTurn(LEFT);

  if (adcThread.shouldRun())adcThread.run(); // starting the thread
}

void selectDisplayOutput() {
  if (activeView == MAINVIEW) {
    adcThread.setInterval(800);
    mainView();
  }
  if (activeView == SETTINGSVIEW) {
    settingsView();
  }
}
