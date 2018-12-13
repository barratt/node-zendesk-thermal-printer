#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include "./config.h"	 // Config options

#include "./printer.h"	 // Main printer code
#include "./utils.h"	 // Useful functions for use throughout the program.

void setup() {
    Serial.begin(SERIAL_BAUD);
	Serial.println();
	Serial.println();
	Serial.println("ESP-WiFi based thermal printer");
	Serial.printf("SDK version: %s \n", system_get_sdk_version());
	Serial.println();
	Serial.println();
    
    mySerial.begin(PRINTER_BAUD);  // Initialize SoftwareSerial (Some printers use 9600 baud)
    printer.begin();        // Init printer (same regardless of serial type)

    connectToWiFi();
    printTestPage();
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Unable to connect to WiFi!");
    }

    processJob();
    delay(1000); // Give the printer time to breathe.
}
