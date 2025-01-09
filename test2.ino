#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>

// Wi-Fi Configuration
const char* ssid = "ssid";          // Replace with your Wi-Fi SSID
const char* password = "password";        // Replace with your Wi-Fi Password

// Server URL
const char* serverUrl = "https://cmpdir.in/random_number_api.php";  // HTTPS API endpoint

WiFiClientSecure wifiClientSecure;  // Create secure WiFi client object

void connectWiFi() {
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void fetchRandomNumber() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    wifiClientSecure.setInsecure();  // Disable certificate validation (insecure)

    http.begin(wifiClientSecure, serverUrl);  // Use HTTPS
    int httpCode = http.GET();  // Send GET request

    if (httpCode > 0) {
      Serial.printf("HTTP Response code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();

        // Extract "random_number" from JSON response
        int startIdx = payload.indexOf("\"random_number\":") + 16;
        int endIdx = payload.indexOf(",", startIdx);
        String randomNumber = payload.substring(startIdx, endIdx);

        Serial.println("Random Number: " + randomNumber);
      }
    } else {
      Serial.printf("HTTP Request failed: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();  // Close connection
  } else {
    Serial.println("Wi-Fi is not connected. Reconnecting...");
    connectWiFi();
  }
}

void setup() {
  Serial.begin(115200);  // Start Serial communication at baud rate 115200
  connectWiFi();
}

void loop() {
  fetchRandomNumber();
  delay(10000);  // Wait for 10 seconds before the next request
}
