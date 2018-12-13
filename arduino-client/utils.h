#include "ESP8266WiFi.h"
#include "ESP8266HTTPClient.h"

#include "lib/json.h"
#include "config.h"

StaticJsonBuffer<JSON_BUFFER_SIZE>  jsonBuffer;

// Connects to our reportback WiFi network
void connectToWiFi() {
    wifi_promiscuous_enable(0);

    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(WIFI_SSID);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.print(WiFi.localIP());
    Serial.println();
}


JsonArray& getJob() {
    HTTPClient http;
    http.begin(PATH);

    if (http.GET() != 200) {
        JsonArray& err = jsonBuffer.createArray();
        Serial.println("Error getting web task");
        return err;
    }
 
    String payload = http.getString();
    http.end();

    JsonArray& response = jsonBuffer.parseArray(payload);
    Serial.print("Got job with ");
    Serial.print(response.size());
    Serial.println(" tasks");

    return response;
}

void processTasks(JsonArray& tasks) {
    bool isBold     = false;
    bool isInversed = false;

    // Go through and do as the tasks say...
    for (int i = 0; i < tasks.size(); i++) {
        String command = tasks.get<String>(i);

        if (command == "println") {
            printer.println(tasks.get<String>(i++));
        } 
        
        else if (command == "bold") {
            if (isBold) {
                printer.boldOff();
            } else {
                printer.boldOn();
            }
            isBold = !isBold;
        } 
        
        else {
            Serial.print("Unrecognised command: ");
            Serial.print(command);
            Serial.println("!");
        }

    }
}

void processJob() {
    JsonArray& tasks = getJob();
    processTasks(tasks);
}