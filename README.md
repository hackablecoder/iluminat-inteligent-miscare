
# Iluminat inteligent activat prin miscare

## 1. Descriere
Proiect realizat pentru disciplina Sisteme cu microcontrolere si IoT industriale.
Sistemul detecteaza miscarea cu ajutorul unui senzor PIR conectat la un ESP32.
La detectarea miscarii, LED-ul se aprinde, iar microcontrolerul publica un mesaj
prin protocolul MQTT. Node-RED receptioneaza mesajele si le salveaza intr-o
baza de date SQLite.

## 2. Arhitectura
- **ESP32:** citeste senzorul PIR si controleaza LED-ul.
- **Wi-Fi:** asigura conectivitatea sistemului.
- **Broker MQTT:** transmite mesajele intre ESP32 si Node-RED.
- **Node-RED:** receptioneaza si proceseaza evenimentele.
- **SQLite:** stocheaza istoricul evenimentelor de miscare.

## 3. Tehnologii
- ESP32 si Arduino framework
- Wokwi pentru simulare
- MQTT si brokerul public test.mosquitto.org
- Node-RED
- SQLite

## 4. Topic MQTT
`ps1a/duku/iluminat`

Mesaj publicat la detectarea miscarii:
`MISCARE_DETECTATA`

## 5. Structura proiectului
- `esp32/sketch.ino` - codul microcontrolerului
- `node-red/flows.json` - fluxul exportat din Node-RED
- `iluminat.db` - baza de date SQLite

## 6. Rulare
1. Deschideti proiectul ESP32 in Wokwi.
2. Porniti simularea si verificati conexiunea Wi-Fi si MQTT.
3. Porniti Node-RED in mediul Ubuntu.
4. Deschideti editorul Node-RED la `http://localhost:1880`.
5. Importati `node-red/flows.json` daca fluxul nu este deja incarcat.
6. Activati injectarea evenimentelor de test pentru a consulta istoricul SQLite.

## 7. Observatii
Brokerul MQTT utilizat este public. Pentru utilizare in productie,
se recomanda un broker securizat, autentificare si comunicatie criptata.
