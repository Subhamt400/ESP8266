# ESP8266 HTTPS Random Number Fetcher

This project demonstrates how to use an **ESP8266** microcontroller to perform a secure HTTPS GET request to a remote API. It connects to Wi-Fi, queries a PHP endpoint, and parses a JSON response to extract and display a random number on the Serial Monitor.

## 📋 Features

  * **Wi-Fi Connectivity:** Automatically connects to a specified Wi-Fi network.
  * **HTTPS Support:** Uses `WiFiClientSecure` to handle SSL/TLS connections.
  * **SSL Bypass:** Demonstrates the use of `.setInsecure()` for simple HTTPS requests without managing specific fingerprints/certificates (useful for beginners and testing).
  * **Manual JSON Parsing:** Extracts data from the response string without requiring heavy external libraries like ArduinoJson.

## 🛠️ Hardware Requirements

  * **ESP8266 Board:** (e.g., NodeMCU, Wemos D1 Mini, or Generic ESP-01).
  * **Micro USB Cable:** For programming and power.

## 💻 Software Prerequisites

  * **Arduino IDE:** (Version 1.8.x or 2.x recommended).
  * **ESP8266 Board Package:** Must be installed in the Arduino IDE Board Manager.

## ⚙️ Configuration

Before uploading the code, you must update the credentials in the sketch to match your network.

1.  Open the `.ino` file.
2.  Locate the following lines:
    ```cpp
    const char* ssid = "ssid";          // Replace with your Wi-Fi SSID
    const char* password = "password";  // Replace with your Wi-Fi Password
    ```
3.  Replace `"ssid"` and `"password"` with your actual Wi-Fi network details.

## 🚀 How to Run

1.  Connect your ESP8266 board to your computer.
2.  Open the project in the Arduino IDE.
3.  Select your specific board from **Tools \> Board \> ESP8266 Boards**.
4.  Select the correct COM port.
5.  Click **Upload**.
6.  Once uploaded, open the **Serial Monitor** (Ctrl+Shift+M).
7.  Set the baud rate to **115200**.

## 📊 Sample Output

Upon successful connection, the Serial Monitor will display:

```text
Connecting to Wi-Fi: MyHomeNetwork
.......
Connected to Wi-Fi!
IP Address: 192.168.1.105

HTTP Response code: 200
Random Number: 42
```

*(The loop repeats every 10 seconds)*

## ⚠️ Important Note on Security

This code uses the following command:

```cpp
wifiClientSecure.setInsecure();
```

This instructs the ESP8266 to **ignore** the validity of the SSL certificate.

  * **Pros:** Much easier to set up; no need to hardcode SHA1 fingerprints or load root CA certificates.
  * **Cons:** Vulnerable to Man-in-the-Middle (MitM) attacks.
  * **Usage:** Acceptable for hobby projects or non-sensitive data. **Do not use this method for passing passwords, banking info, or sensitive credentials in a production environment.**

## 🧩 Code Overview

  * **`connectWiFi()`**: Handles the initial connection to the network and waits until an IP is assigned.
  * **`fetchRandomNumber()`**:
    1.  Initializes an HTTPS connection to `https://cmpdir.in/random_number_api.php`.
    2.  Checks for a valid HTTP 200 (OK) response.
    3.  Parses the raw string response to find the value associated with the JSON key `"random_number"`.
    4.  Prints the result to Serial.

## 📜 License

This project is open-source and available for modification and distribution.
