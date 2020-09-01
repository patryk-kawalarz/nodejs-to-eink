#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <GxEPD.h>
#define ROTATION 3
#include <GxGDEW0583T7/GxGDEW0583T7.cpp>
#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

GxIO_Class io(SPI, 5, 0, 15);
GxEPD_Class display(io, 15, 12);

#define X_RES 448
#define Y_RES 600
String url = "http://192.168.0.42:3000/test";

void setup() {
  SPI.setFrequency(8000000L);
  WiFi.begin("YOUR_SSID", "your_WIFI_password");
}

void loop() {
  if((WiFi.status() == WL_CONNECTED)) {
    HTTPClient http;
    http.begin(url);
    int httpCode = http.GET();

    if(httpCode == 200) {
      display.init(9600);
      display.setRotation(ROTATION);
      display.fillScreen(GxEPD_WHITE);

      int curs = 0;
      int col = 0;
      uint8_t buff[128] = { 0 };
      char charBuff[128];
      String text = "";
      bool endOfFile = false;

      WiFiClient * stream = http.getStreamPtr();
      while(http.connected() && (!endOfFile)) {
        size_t size = stream->available();

        if(size) {
          int c = stream->readBytes(buff, ((size > sizeof(buff)) ? sizeof(buff) : size));
          text = (char*)buff;
          text.toCharArray(charBuff, sizeof(buff) + 2);

          for(int i = 0; i < c; i++) {
            if(charBuff[i] == '1') {
              col = floor(curs / X_RES);
              display.drawPixel(curs - (col * X_RES), col, GxEPD_BLACK);
            }

            if(charBuff[i] == '2') {
              endOfFile = true;
            }

            curs += 1;
          }
        }
      }

      http.end();
      display.update();
    }


    WiFi.disconnect(true);
    delay(10000000);
  }
}
