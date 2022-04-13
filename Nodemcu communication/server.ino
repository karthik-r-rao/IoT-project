#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>

const char* ssid = "shashank";
const char* password = "shashank";

WiFiServer server(80);

void setup() {
  delay(200);
  Serial.begin(115200);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println();
  Serial.println(myIP);
  server.begin();
  Serial.println("server started");
  
}

void loop() {
  WiFiClient client = server.available();
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(30);
  String request = client.readStringUntil('\r');
  Serial.println(request);

}
