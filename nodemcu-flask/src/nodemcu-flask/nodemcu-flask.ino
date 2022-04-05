#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

WiFiClient wifiClient;
int count = 0;
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin("moto-karthik", "krao6969"); // SSID and password
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.println("Connecting..");
 
  }
  Serial.println("Connected to WiFi Network");
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { // Check WiFi connection status
 
    HTTPClient http;  // Declare an object of class HTTPClient

    http.begin(wifiClient, "http://192.168.76.216:5000/count/push");
    http.addHeader("Content-Type", "text/plain");

    Serial.println("Count = " + String(count));
    int httpCode = http.POST(String(count));
    http.end();
  }
  count++;
  delay(2000);    
 
}
