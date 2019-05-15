#include <Adafruit_ADS1015.h>

#define FILTER_ACCURACY 10 // 1 - to disable
#define PRECISION_COEF 0.54
#define MAXTEMP 600

Adafruit_ADS1115 ads(0x48);

class Data {
  private:
    float difference = 0.0;
    float diffValue = 0.0;
    
  public:
    float dmPr = 0.0;
    float stPr = 0.0;
    float temp = 0.0;
    String tempStr = "0.0";
    float v = 0.0;   
    String pipeShortenNames[7] = {"PT0.5", "TH293", "TH411", "TH279", "TH234", "TH2.5", "TH10 "};
    String pipeName[7]  = {"PITO-0.5  ", "TH-1.0:293", "TH-1.0:411", "TH-1.5:279", "TH-1.5:234", "TH-2.5:234", "TH-1.2:10 "};
    float pipeVal[7]  = {0.579,          0.58,         0.585,        0.573,        0.591,        0.582,        0.708};
 
    int pipeSelected = 0;

    void setupData() {
      ads.begin();
    }

    void setDifference() {
      difference = diffValue;
    }

    bool updateData() {
      unsigned long adc0 = 0, adc1 = 0, adc2 = 0;
      float volt0, volt1, volt2, vcc;

      String prevData = String(dmPr) + String(stPr) + String(temp) + String(v);
      
      for (unsigned int i = 0; i < FILTER_ACCURACY; i++)
      {
        adc0 += ads.readADC_SingleEnded(0);
        adc1 += ads.readADC_SingleEnded(1);
        adc2 += ads.readADC_SingleEnded(2);
      }
      volt1 = (adc1 / FILTER_ACCURACY * 0.1865) / 1000;
      volt0 = (adc0 / FILTER_ACCURACY * 0.1865) / 1000;
      volt2 = (adc2 / FILTER_ACCURACY * 0.1865) / 1000;
      vcc = (ads.readADC_SingleEnded(3) * 0.1875) / 1000;

      diffValue = (volt0 / vcc - 0.5) / 0.057 * 101.97;  // dinamic
      dmPr = diffValue - difference;
      dmPr = int(dmPr * 10) / 10.0 ;

      stPr = (volt2 / vcc + 0.095) / 0.009 + PRECISION_COEF; // static
      stPr = int(stPr * 100) / 100.0 * 7.5;

      temp = (volt1 - 1.25) / 0.005 + 1;
      tempStr = String(temp);
      if (temp > MAXTEMP) tempStr = "n/a"; //check if TC is connected 

      v = sqrt (abs(2 * 9.8 * dmPr * pipeVal[pipeSelected] * (273 - temp) / (0.359 * 1.29 * stPr)));
    
      String newData = String(dmPr) + String(stPr) + String(temp) + String(v);

      if (newData.length() < prevData.length())
      return true;
      return false;
    }
};
