#include <ESP8266WiFi.h>  // Bibliothek für die WiFi Funktionen
#include <PubSubClient.h> // Bilbiothek für MQTT Funktionen
#include <WiFiUdp.h>

#define ledBlue D5
#define ledRed D6
#define ledGreen D7


// WiFi
const char* ssid = "EVP-LF7";
const char* wifi_password = "APevpLF7";

// MQTT
const char* mqtt_server = "ssf.local";
const char* mqtt_topic = "rgb"; 
const char* mqtt_username = "ssf";
const char* mqtt_password = "a123123@";
const char* clientID = "";


// Initialisiere Wifi und MQTT
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 ist der Port für den Broker


void setupWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Stellt Verbindung mit dem Netzwerk her
  WiFi.begin(ssid, wifi_password);

  // Warten bis die Verbindung aufgebaut ist
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Ausgabe der IP Adresse des ESP
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void readRGB(String rgbString){

  rgbString.replace("rgb", "");
  rgbString.replace("(", "");
  rgbString.replace(")", "");
  rgbString.trim();
  
  int comma1 = rgbString.indexOf(",");
  int comma2 = rgbString.lastIndexOf(",");

  int R = rgbString.substring(0, comma1).toInt();
  int G = rgbString.substring(comma1 + 1, comma2).toInt();
  int B = rgbString.substring(comma2 + 1).toInt();
  
  if(R < 0 ) R = 0;
  if(G < 0 ) G = 0;
  if(B < 0) B = 0;

  analogWrite(ledRed,   R > 250 ? 250 : R);
  analogWrite(ledGreen, G > 250 ? 250 : G);
  analogWrite(ledBlue,  B > 250 ? 250 : B);
}

void callback(String topic, byte* message, unsigned int length) {
  Serial.println(topic);
  String msg;
  for (int i=0; i<length; i++) {
    // Serial.print((char)message[i]);
    msg += (char)message[i];
  }
  Serial.println();
  readRGB(msg);
}

void setupMQTT() {
  // Verbindung mit MQTT Broker (Mosquitto)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }

  // callback Funktion wird aufgerufen, sobald ein abonniertes Topic eine Nachricht vom Broker erhält.
  client.setCallback(callback);
  client.subscribe(mqtt_topic);
}

void setup() {
  Serial.begin(115200);
  setupWiFi();
  setupMQTT();
}

void loop() {
  if (!client.connected()) setupMQTT();
  client.loop();
}