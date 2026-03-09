#include <WiFi.h>
#include <PubSubClient.h>
#include <Smart_Fridge_inferencing.h>
#include <eloquent_esp32cam.h>
#include <eloquent_esp32cam/edgeimpulse/fomo.h>

// Replace these with your network credentials and MQTT broker address
const char* ssid = "Infinix HOT 20i";
const char* password = "olfa1234";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);

using eloq::camera;
using eloq::ei::fomo;

void setup_wifi() {
    delay(10);
    Serial.begin(115200);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.print(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    while (!client.connected()) {
        Serial.println("Attempting MQTT connection...");
        if (client.connect("ESPClient")) {
            Serial.println("Connected");
        } else {
            Serial.print("Failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void setup() {
    delay(3000);
    Serial.begin(115200);
    Serial.println("_EDGE IMPULSE FOMO (NO-PSRAM)_");
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    
    camera.pinout.aithinker();
    camera.brownout.disable();
    camera.resolution.yolo();
    camera.pixformat.rgb565();

    while (!camera.begin().isOk())
        Serial.println(camera.exception.toString());

    Serial.println("Camera OK");
    Serial.println("Put object in front of camera");
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    if (!camera.capture().isOk()) {
        Serial.println(camera.exception.toString());
        return;
    }

    if (!fomo.run().isOk()) {
        Serial.println(fomo.exception.toString());
        return;
    }

    char payload[256];
    int len = snprintf(payload, sizeof(payload),
        "{\"object_count\": %d, \"time_ms\": %d}",
        fomo.count(), fomo.benchmark.millis());
    client.publish("esp32/cam", payload);

    if (!fomo.foundAnyObject()) 
        return;

    len = snprintf(payload, sizeof(payload),
        "{\"label\": \"%s\", \"x\": %d, \"y\": %d, \"width\": %d, \"height\": %d, \"proba\": %.2f}",
        fomo.first.label, fomo.first.x, fomo.first.y, fomo.first.width, fomo.first.height, fomo.first.proba);
    client.publish("esp32/cam/object", payload);

    if (fomo.count() > 1) {
        fomo.forEach([](int i, bbox_t bbox) {
           char object_payload[256];
            int len = snprintf(object_payload, sizeof(object_payload),
                "{\"index\": %d, \"label\": \"%s\", \"x\": %d, \"y\": %d, \"width\": %d, \"height\": %d, \"proba\": %.2f}",
                i + 1, bbox.label, bbox.x, bbox.y, bbox.width, bbox.height, bbox.proba);
            client.publish("esp32/cam/objects", object_payload);
        });
    }
}
