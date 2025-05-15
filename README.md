# 🔐 Hemlarmssystem – IoT-baserad lösning med realtidsövervakning

Ett komplett IoT-baserat hemlarmssystem som använder MQTT, Flask, ultraljudssensor och webbaserad övervakning. Systemet upptäcker rörelse, larmar, och skickar realtidsdata till en webapp via MQTT och REST API.

---

## 🧾 Hårdvarukomponenter

- Raspberry Pi Pico W
- HC-SR04 (ultraljudssensor)
- 16x2 LCD-display (I2C)
- Buzzer
- LED
- 2 st tryckknappar
- Strömförsörjning
- Breadboard & kopplingskablar

## 🔧 Programvaruarkitektur

Projektet är uppdelat i flera moduler:

- `main.c`: Huvudlogik för larm, knappar, MQTT och avståndsmätning
- `lcd.[c/h]`: Hantering av LCD-display
- `wifi.[c/h]`: Anslutning till WiFi-nätverk
- `buzzer.[c/h]`: Summerstyrning
- `ultrasonic.[c/h]`: Avståndsmätning med HC-SR04
- `datetime.[c/h]`: Tidshantering
- `led.[c/h]`: LED-kontroll

## Funktioner i `main.c`

- **WiFi-anslutning**  
  Kopplar upp Pico W till ett WiFi-nätverk med angivet SSID och lösenord. Visar anslutningsstatus på en LCD-skärm.

- **MQTT-klient**  
  Initierar och ansluter till en MQTT-broker (t.ex. en Raspberry Pi Zero 2 W). Skickar avståndsvärden från ultraljudssensorn i realtid till backend.

- **Sensorhantering**  
  Läser av ultraljudssensorn som mäter avstånd till närliggande objekt för rörelsedetektering. Visar avstånd och aktuell tid på LCD-skärmen.

- **Larmlogik**  
  Använder två knappar:  
  - En knapp för att aktivera eller avaktivera larmet.  
  - En knapp för manuell överskrivning av larmet.  
  
  När larmet är aktiverat och sensorn detekterar rörelse inom 10 cm:  
  - Buzzern ljuder.  
  - En LED blinkar som visuell indikation.  
  - Avståndsvärdet skickas till MQTT-brokern.

- **Status och feedback**  
  Ger användaren visuell feedback på LCD-skärmen för WiFi-status, larmstatus och tid.

- **Kontinuerlig loop**  
  Programmet körs i en oändlig loop som uppdaterar sensorer, larmläge och skickar data kontinuerligt.

---



## 🧱 Tech Stack

| Lager             | Teknik                                       |
|-------------------|----------------------------------------------|
| ✅ Frontend       | **React** (Next.js)                           |
| ✅ Backend        | **Python (Flask)** – API, logik och SMS      |
| ✅ Mikrokontroller | **C/C++** – Raspberry Pi Pico W               |
| ✅ Fog-enhet      | **C** – Raspberry Pi Zero 2 W med MQTT Broker |
| ✅ Databas        | **SQLite**                                    |

---


## 🗺️ Systemöversikt

```mermaid
%%{init: { 'theme': 'base', 'themeVariables': { 'background': '#ffffff' }}}%%
graph TD
    classDef lilabox fill:#f9e3f9,stroke:#b565b6,stroke-width:2px;
    classDef pinkbox fill:#ffe0f0,stroke:#d63384,stroke-width:2px;
    classDef violetbox fill:#e0d7ff,stroke:#6f42c1,stroke-width:2px;

    subgraph "💡 Rörelsedetektor"
        A[Pico W<br/>C/C++]:::lilabox
        B[Sensorvärde<br/>Ultraljud]:::pinkbox
        A --> B
    end

    subgraph "📦 FOG-enhet"
        C[Pi Zero 2 W<br/>MQTT Broker]:::violetbox
        B -->|MQTT / WiFi| C
    end

    subgraph "🧠 Backend"
        D[Flask Server<br/>API & SMS]:::lilabox
        G[SMS-Tjänst]:::pinkbox
        D --> G
        C -->|HTTP POST / MQTT| D
    end

    subgraph "🗄️ Databas"
        E[(SQL Database)]:::violetbox
        D -->|Spara data| E
    end

    subgraph "🌍 Webapp"
        F[Next.js Frontend<br/>Dashboard]:::pinkbox
        F -->|GET /devices /logs| D
    end
```
---
## 📌 Projektets komponenter

| Komponent           | Beskrivning                                                                                     |
|---------------------|-------------------------------------------------------------------------------------------------|
| 💡 Rörelsedetektor  | Raspberry Pi Pico W som samlar in data från ultraljudssensor och skickar via MQTT. Firmware i C/C++. |
| 📦 Fog-enhet        | Raspberry Pi Zero 2 W som kör MQTT Broker och vidarebefordrar data till backend via HTTP/MQTT.  |
| 🧠 Backend          | Python Flask API som tar emot data, hanterar logik, sparar i SQLite och skickar SMS-larm.       |
| 🗄️ Databas         | SQLite lagrar sensorloggar och larmhistorik.                                                   |
| 🌍 Webapp           | React/Next.js-dashboard som visar realtidsdata och historik via REST API.                      |

---
