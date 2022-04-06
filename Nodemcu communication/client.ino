#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include "DHT.h"        

#define DHTTYPE DHT11 
#define dht_dpin 0

DHT dht(dht_dpin, DHTTYPE); 

const char* host = "192.168.4.1";
const char* ssid = "shashank";
const char* password = "shashank";

void setup() {
  dht.begin();
  Serial.begin(115200);
  delay(10);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  

}

void loop() {
  
  WiFiClient client;
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  Serial.printf("\n Connecting to %s ... ", host);
  
  if (client.connect(host, 80))
  {
    Serial.println("Connected");

    Serial.println(" Sending a request");
    //client.print(String("GET /") + String( " "HTTP/1.1\r\n");
    client.print(String("GET /") + String( "humidity:") + ""String( " "HTTP/1.1\r\n");
  }
  delay(3000);

}
