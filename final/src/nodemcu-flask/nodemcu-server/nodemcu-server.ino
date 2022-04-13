#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "shashank";
const char* password = "shashank";

WiFiServer server(80);

WiFiClient wifiClient;

void setup() {
  delay(200);
  Serial.begin(115200);
  WiFi.begin("moto-karthik", "krao6969"); // SSID and password
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
  Serial.println("Connected to WiFi Network");
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.println();
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  Serial.printf("Stations connected = %d\n", WiFi.softAPgetStationNum());
  delay(30);
  String request = client.readStringUntil('\r');
  Serial.println(request);

  if (WiFi.status() == WL_CONNECTED) { // Check WiFi connection status
 
    HTTPClient http;  // Declare an object of class HTTPClient

    http.begin(wifiClient, "http://192.168.76.216:5000/count/push");
    http.addHeader("Content-Type", "text/plain");
    int httpCode = http.POST(String(request));
    http.end();
  }
  delay(2000);    
}
