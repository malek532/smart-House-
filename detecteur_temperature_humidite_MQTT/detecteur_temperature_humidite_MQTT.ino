 #include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

#define DHTPIN 2  
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
//WiFi
const char *ssid = "DESKTOP-NOL29JG 2717 iso";
const char *password = "youcandoit"; 

//MQTT Broker
//const char *mqtt_broker = "141.94.175.18" 
const char *mqtt_broker = "robotn-cloud-server.robotika.systems";
const char *mqtt_username = "*****";
const char *mqtt_password = "******";
const int mqtt_port = 1883;

//#define topic_1 "Hello everyone" 
WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) 
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) 
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
void setup() {
  //Set software serial baud to 115200
  Serial.begin(115200);
  Serial.println("DHTxx test!");
  dht.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    delay(2000);
    float h = dht.readHumidity(); //read humidity
    float t = dht.readTemperature(); 
    float f = dht.readTemperature(true);
    if (isnan(h) || isnan(t) || isnan(f)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }
    float hif = dht.computeHeatIndex(f, h);
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("% Tempurature: ");
    Serial.print(t);
    Serial.print("°C: ");
    Serial.print(f);
    Serial.print("°F Heat index: ");
    Serial.print(hic);
    Serial.print("°C ");
    Serial.print(hif);
    Serial.println("°F");
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());

    Serial.println("Connected to the public mqtt broke");

    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Broker is connected");
      client.subscribe("humidity_topic");//read topic haifa //subscribe call callback
      client.subscribe("tempurature_topic");//read topic achraf //subscribe call callback
      client.publish("achraftemp", String(t).c_str(),true);// send topic tempurature
      client.publish("achrafhum", String(h).c_str(),true);// send topic humidité
      
      



      Serial.println("topic published successfully");

    }
    else {
      Serial.print("failed with state");
      Serial.print(client.state());
      delay(2000);
    }
  };
}

void loop() {
  client.loop();//go to void setup

}
