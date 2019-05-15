#define PIPE 1
#define BACKLIGHT 2
#define DMPUNITS 3
#define STPUNITS 4
#define TMPUNITS 5
#define CLOSE 6

bool backlightEnabled = false;
int rawSelected = 1;

void settingsOnClick() {
  if (rawSelected == PIPE && data.pipeSelected <= 6) data.pipeSelected++;
  if (data.pipeSelected >= 7) data.pipeSelected = 0;

  if (rawSelected == BACKLIGHT & backlightEnabled) {
    backlightEnabled = false;
    lcd.noBacklight();
  }
  else if (rawSelected == BACKLIGHT & !backlightEnabled) {
    backlightEnabled = true;
    lcd.backlight();
  }
}

void settingsOnHold() {
  lcd.clear();
  activeView = MAINVIEW;
}

void settingsOnTurn(int dir) {
  if (dir == RIGHT && rawSelected < 2) rawSelected++;
  if (dir == LEFT && rawSelected > 1) rawSelected--;
  lcd.clear();
  settingsView();
}

void settingsOnHoldTurn(int dir) {
}

void settingsView() {

  if (rawSelected <= 3) {
    lcd.setCursor(0, rawSelected);
    lcd.print("\2");

    lcd.setCursor(0, 0);
    lcd.print("(hold to exit)");

    lcd.setCursor(1, 1);
    lcd.print("Pipe: ");
    lcd.print(data.pipeName[data.pipeSelected]);

    lcd.setCursor(1, 2);
    lcd.print("Backlight: ");
    if (backlightEnabled) lcd.print("ON ");
    else lcd.print("OFF");

//    lcd.setCursor(1, 3);
//    lcd.print("DMP units: ");
//
//    lcd.setCursor(1, 4);
//    lcd.print("STP units: ");
  }

//  if (rawSelected > 3 && rawSelected <= 7) {
//    lcd.setCursor(0, rawSelected - 4);
//    lcd.print("\2");
//
//    lcd.setCursor(1, 0);
//    lcd.print("TMP units: ");
//
//    lcd.setCursor(1, 1);
//    lcd.print("Close");
//  }
}
