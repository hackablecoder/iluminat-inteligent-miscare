
#include <WiFi.h>
#include <PubSubClient.h>

const int SENZOR_PIR = 27;
const int LED_ILUMINAT = 18;
int stareAnterioaraMiscare = LOW;

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

const char* MQTT_SERVER = "test.mosquitto.org";
const int MQTT_PORT = 1883;

WiFiClient espClient;
PubSubClient mqtt(espClient);

void conectareWiFi() {
  Serial.print("Conectare la Wi-Fi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectat!");
  Serial.print("Adresa IP: ");
  Serial.println(WiFi.localIP());
}

void conectareMQTT() {
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);

  Serial.print("Conectare la brokerul MQTT...");

  while (!mqtt.connected()) {
    String clientId = "ESP32-Iluminat-";
    clientId += String((uint32_t)ESP.getEfuseMac(), HEX);

    if (mqtt.connect(clientId.c_str())) {
      Serial.println("conectat!");
    } else {
      Serial.print("Eroare MQTT, cod: ");
      Serial.print(mqtt.state());
      Serial.println(". Reincerc in 2 secunde.");
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(SENZOR_PIR, INPUT);
  pinMode(LED_ILUMINAT, OUTPUT);
  digitalWrite(LED_ILUMINAT, LOW);

  Serial.println("Iluminat inteligent pornit.");

  conectareWiFi();
  conectareMQTT();
}

void loop() {
  if (!mqtt.connected()) {
    conectareMQTT();
  }

  mqtt.loop();

  int miscare = digitalRead(SENZOR_PIR);

  if (miscare == HIGH) {
    digitalWrite(LED_ILUMINAT, HIGH);

    if (stareAnterioaraMiscare == LOW) {
      Serial.println("Miscare detectata - lumina aprinsa");
      mqtt.publish(
        "ps1a/duku/iluminat",
        "MISCARE_DETECTATA"
      );
    }
  } else {
    digitalWrite(LED_ILUMINAT, LOW);
  }

  stareAnterioaraMiscare = miscare;

  delay(50);
}
