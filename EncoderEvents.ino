void onTurn(int dir) {
  Serial.print("turn ");
  Serial.println(dir);

  if (activeView == MAINVIEW);
  if (activeView == SETTINGSVIEW) settingsOnTurn(dir);
}

void onDoubleClick() {
  Serial.println("doubleclick");
}

void onClick() {
  Serial.println("click");
  if (activeView == MAINVIEW) mainViewOnClick();
  if (activeView == SETTINGSVIEW) settingsOnClick();
  adcThread.run();
}

void onHold() {
  Serial.println("hold");
  if (activeView == MAINVIEW) {
    mainViewOnHold();
    return;
  }
  if (activeView == SETTINGSVIEW) {
    settingsOnHold();
    return;
  }
}

void onHoldTurn(int dir) {
  Serial.print("holdturn ");
  Serial.println(dir);
  if (activeView == SETTINGSVIEW) {
    settingsOnHoldTurn(dir);
    return;
  }
}
