#include <ESP8266WiFi.h>                   // Include the Wi-Fi library
#define LED D2  // LED at GPIO4 D2

const char *ssid = "Kyoz ESP";             // The name of the Wi-Fi network that will be created
const char *password = "nopassword";       // The password required to connect to it, leave blank for an open network
unsigned char led_status = 0;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  WiFi.softAP(ssid, password);             // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started...");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer

  server.begin();
  Serial.println("HTTP Server started...");
}

void loop() {
  const int connected_devices = WiFi.softAPgetStationNum();
  WiFiClient client = server.available();  // Listen for incomming clients

  if (!connected_devices || !client) {
    return;
  }

  // Connected
  Serial.println("Connected...");
  delay(1000);
}
