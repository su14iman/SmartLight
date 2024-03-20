# SmartLight
Das Ziel dieses Projekts ist es, eine RGB-Lampe zu entwickeln, die über ein Smartphone gesteuert werden kann. Die Steuerung erfolgt über einen ColorPicker in Node-Red, der mit einem MQTT-Knoten verbunden ist. Die übermittelten Daten haben das Format "rgb(255, 255, 255)", wobei die Reihenfolge der Farben Rot, Grün und Blau ist. 
Der ESP8266 soll diese Daten empfangen, die Farbwerte extrahieren und die RGB-LED entsprechend einstellen.

## Hardware / Aufbau
Die Hardware besteht aus einem ESP8266-Mikrocontroller, einer RGB-LED, Resistor 1k Ω, Test-Board und Kabel. 
Die RGB-LED wird mit den Pins D5, D6 und D7 des ESP8266 verbunden, die jeweils die Farben Blau, Rot und Grün steuern. 
Der ESP8266 wird über WLAN mit dem Netzwerk verbunden und kommuniziert über MQTT mit dem Raspberry Broker.

### Hardware komponenten:
    * WeMos D1 R2 WiFi ESP8266
    * Test-Board
    * RGB LED
    * Resistor 1k Ω
    * Kabel
    * Raspberry pi 400
    * Access Point -> Wlan

### Beispielbild:
![WeMos_D1_R2_WiFi_ESP8266](assets/images/WeMos_D1_R2_WiFi_ESP8266.jpeg)


## Projektdurchführung
1. Die Bibliotheken importieren
![bibliotheken](/assets/codes/0.png)
2. Die pins definieren
![pins](/assets/codes/1.png)
3. Die wichtige Variablen definieren
![variablen](/assets/codes/2.png)
4. Einrichtung der WLAN-Verbindung des ESP8266 mit dem Netzwerk.
![setupWifi](/assets/codes/4.png)
5. Verbindung des ESP8266 mit dem MQTT-Broker und Abonnement des Topics "rgb".
![setupMQTT](/assets/codes/7.png)
6. Implementierung einer Callback-Funktion, die aufgerufen wird, wenn eine Nachricht über MQTT empfangen wird.
![setupCallback](/assets/codes/6.png)
7. Extraktion der RGB-Farbwerte aus der empfangenen Nachricht und Anpassung der Helligkeit und Einstellung der RGB-LED entsprechend den extrahierten Farbwerten.
![readRGB](/assets/codes/5.png)
8. Die Funktionen in Setup/Loop-Funktion aufrufen
![SetupLoop-FN-aufrufen](/assets/codes/8.png)
9. Node-Red einrichten
![noderedFlow](/assets/images/nodered-flow.png)
9. Die Topic in Node-Red einrichten
![noderedSettings](/assets/images/nodered-settings.png)


## Qualitätssicherung/Tests
Die Qualitätssicherung umfasst die Überprüfung der ordnungsgemäßen Funktion der RGB-Lampe. Hierbei werden verschiedene Farben über den ColorPicker in Node-Red ausgewählt und die Reaktion der RGB-LED überprüft. Es werden auch Grenzfälle getestet, um sicherzustellen, dass das System robust und zuverlässig ist.
![readRGB](/assets/images/nodered-ui.png)


Oder Farben können mithilfe von Mosquito simuliert werden:
```bash
mosquitto_pub -h XX.XX.XX.XX -u XxX -P XxX -p 1883 -t rgb -m "15" -q 1
```

## Hinweise zur realen Umsetzung
Bei der realen Umsetzung sollten folgende Punkte beachtet werden:

- Die richtige Verkabelung der RGB-LED mit dem ESP8266.
- Die korrekte Konfiguration der WLAN-Verbindung und des MQTT-Brokers.
- Die Sicherstellung, dass der ESP8266 eine stabile Verbindung zum WLAN und zum MQTT-Broker aufrechterhält.