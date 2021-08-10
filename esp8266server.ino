#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <Adafruit_GFX.h>     // Core graphics library
#include <Adafruit_ST7789.h>  // Hardware-specific library for ST7789
// ST7789 TFT module connections
#define TFT_RST   D8     // TFT RST pin is connected to NodeMCU pin D8 (GPIO15)
#define TFT_DC    D4     // TFT DC  pin is connected to NodeMCU pin D4 (GPIO2)
#define TFT_CS    -1     // TFT CS  pin is directly connected to GND
// initialize ST7789 TFT library with hardware SPI module
// SCK (CLK) ---> NodeMCU pin D5 (GPIO14)
// MOSI(DIN) ---> NodeMCU pin D7 (GPIO13)
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

const char *ssid = "ESP8266";
const char *password = "00000000";

WiFiUDP Udp;
unsigned int localUdpPort = 2333;  // local port to listen on
char incomingPacket[8000];// buffer for incoming packets



void receive_handler(char* data){
  if(*data<15){ // pic
    receive_pic(*data,data+2);
  }

  
}

void receive_pic(int n, char* data){
  Serial.println("receiveed!");
  Serial.println(n);
  tft.drawRGBBitmap(0, n*16, (uint16_t*)data,240,16);
}


void setup(void){
  Serial.begin(9600);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  Udp.begin(localUdpPort);
  tft.init(240, 240, SPI_MODE2);    // init ST7789 display 240x240 pixel
  tft.fillScreen(ST77XX_BLACK);
  tft.setRotation(2);
}

void loop(void){
  int packetSize = Udp.parsePacket();
  if (packetSize){
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 8000);
    Serial.println(incomingPacket[0]);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    receive_handler(incomingPacket);
    }
}
