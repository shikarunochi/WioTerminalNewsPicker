#include<SPI.h>
#include "Seeed_FS.h"
#include "SD/Seeed_SD.h"
#include <TFT_eSPI.h>
#include "RawImage.h"  //Including image processing library
TFT_eSPI tft;

void setup() {
    tft.begin();
    Serial.begin(115200);
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK); //Black background

    while(!SD.begin(SDCARD_SS_PIN, SDCARD_SPI)){
        Serial.println("SD card error!\n");
        while(1);
  }
  delay(1000);

  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  drawImage<uint8_t>("niseharuna8.bmp", 0, 0); 
  tft.loadFont("genshin-regular-24pt",SD);
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

          tft.fillRect(10,40,180,115,TFT_WHITE);
          tft.setCursor(0,60 + yOffset);
          tft.println(newsContent);
          tft.fillRect(10,190,145,30,TFT_WHITE);
          tft.setCursor(10,195);
          tft.println(comment);
      }
}
