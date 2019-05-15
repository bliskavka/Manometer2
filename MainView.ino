void mainViewOnClick() {
  data.setDifference();
}

void mainViewOnHold() {
  lcd.clear();
  activeView = SETTINGSVIEW;
}

void mainView() {
  if (data.updateData()) lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Pdm: ");
  lcd.print(data.dmPr, 1);
  lcd.setCursor(11, 0);
  lcd.print("mmH2O");

  lcd.setCursor(0, 1);
  lcd.print("Pst: ");
  lcd.print(data.stPr, 1);
  lcd.setCursor(11, 1);
  lcd.print("mmHg");

  lcd.setCursor(0, 2);
  lcd.print("Tmp: ");
  lcd.print(data.tempStr);
  lcd.setCursor(11, 2);
  lcd.print("\1C");


  lcd.setCursor(0, 3);
  lcd.print("Spd: ");
  lcd.print(data.v);
  lcd.setCursor(11, 3);
  //lcd.print("m/s-");  
  lcd.print("(" + data.pipeShortenNames[data.pipeSelected] + ")");

}
