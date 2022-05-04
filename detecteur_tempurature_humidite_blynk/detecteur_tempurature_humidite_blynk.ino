                                      #define BLYNK_TEMPLATE_ID "TMPLnzYNqfZs"
#define BLYNK_DEVICE_NAME "smarthome"
#define BLYNK_AUTH_TOKEN "jW9GBkCEEQCwJJPsElbZ741pSsoZa3xx"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "DESKTOP-EKQAQL7 9227";
char pass[] = "malek0000";

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();

  float t = dht.readTemperature();
  Serial.println("temp= ");
  Serial.println(t);
  Serial.println("hum= ");
  Serial.println(h);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth,ssid,pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);// L seconde in blynk
}

void loop() {
  Blynk.run();
  timer.run();
}
