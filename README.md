# 🔐 Hemlarmssystem – IoT-baserad lösning med realtidsövervakning

Ett komplett IoT-baserat hemlarmssystem som använder MQTT, Flask, ultraljudssensor och webbaserad övervakning. Systemet upptäcker rörelse, larmar, och skickar realtidsdata till en webapp via MQTT och REST API.

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
