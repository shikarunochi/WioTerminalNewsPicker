#include<SPI.h>
#include <Seeed_FS.h>
#include <SD/Seeed_SD.h>

#include <LGFX_TFT_eSPI.hpp>
static TFT_eSPI tft;

void setup() {
    tft.begin();
    Serial.begin(115200);
    while(!Serial); // Wait for Serial to be ready
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK); //Black background

    while(!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)){
        Serial.println("SD card error!\n");
        while(1);
  }
  delay(1000);

  tft.drawJpgFile(SD, "niseharuna.jpg");

  tft.loadFont("genshin-regular-24pt.vlw");
  tft.setTextColor(TFT_BLACK);

}
void loop(){
      String inputText = "";
      if (Serial.available() > 0) {
          //tft.fillScreen(TFT_BLACK); //Black background
          //tft.setCursor(0,0);
          String newsString = Serial.readStringUntil(';');

          int textEnd = newsString.indexOf(":");
          String newsContent = newsString.substring(0,textEnd);
          int rowCountEnd = newsString.indexOf(":", textEnd + 1);
          String comment = newsString.substring(textEnd + 1, rowCountEnd);
          String rowCountString = newsString.substring(rowCountEnd + 1);
          int rowCount = rowCountString.toInt();

          int yOffset = 0;
          if(rowCount >= 3){
            yOffset = -15;
          }
          Serial.println(newsString);
          tft.fillRect(10,40,180,115,TFT_WHITE);
          tft.setCursor(0,55 + yOffset);
          tft.println(newsContent);
          tft.fillRect(10,190,145,30,TFT_WHITE);
          tft.setCursor(10,188);
          tft.println(comment);
      }
}
