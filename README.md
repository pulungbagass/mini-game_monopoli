# 🎲 Hybrid Smart Monopoly Board Game using ESP32

## Overview

Hybrid Smart Monopoly Board Game is a cyber-physical board game system based on ESP32 that combines a physical Monopoly board with a web-based control interface. The system utilizes NFC cards, WebSocket communication, and a browser dashboard to provide real-time multiplayer interaction while maintaining the traditional board game experience.

This project is intended for:

- Final Year Project / Skripsi
- Journal Publication
- Cyber-Physical System Research
- Embedded System Learning
- IoT and Real-Time Web Application Development

The architecture is designed so that the ESP32 acts as the main authority (server), while smartphones or laptops function as clients through a browser.

---

# Main Objectives

- Create a digital Monopoly control system without eliminating the physical board.
- Integrate embedded systems and web technologies.
- Build a real-time multiplayer game using ESP32.
- Demonstrate Cyber-Physical System implementation.

---

# Technology Stack

## Embedded Side

- ESP32 DevKit V1
- C++
- Arduino Framework
- PlatformIO

## Frontend Side

- HTML
- CSS
- JavaScript
- WebSocket API

## Communication

- REST API
- WebSocket
- SPI
- I2C

---

# Development Environment

## IDE

### Visual Studio Code

Extensions:

- PlatformIO IDE
- ESP32 Arduino Framework

---

# Hardware Components

| Component            | Function                          |
| -------------------- | --------------------------------- |
| ESP32 DevKit V1      | Main Controller                   |
| PN532 NFC Module     | Authentication & Ownership System |
| SSD1306 OLED Display | System Information                |
| Passive Buzzer       | Sound Indicator                   |
| 5mm LED              | Status Indicator                  |
| Resistor 220Ω        | LED Protection                    |
| Smartphone / Browser | User Interface                    |
| WiFi Network         | Communication Medium              |

---

# Pin Mapping

## PN532 NFC (SPI)

| PN532  | ESP32   |
| ------ | ------- |
| VCC    | 3.3V    |
| GND    | GND     |
| SCK    | GPIO 18 |
| MOSI   | GPIO 23 |
| MISO   | GPIO 19 |
| SS/SDA | GPIO 14 |

---

## OLED SSD1306 (I2C)

| OLED | ESP32   |
| ---- | ------- |
| VCC  | 3.3V    |
| GND  | GND     |
| SDA  | GPIO 21 |
| SCL  | GPIO 22 |

---

## Passive Buzzer

| Buzzer | ESP32   |
| ------ | ------- |
| +      | GPIO 26 |
| -      | GND     |

---

## LED Indicator

| LED         | ESP32                       |
| ----------- | --------------------------- |
| Anode (+)   | GPIO 25                     |
| Cathode (-) | GND (through 220Ω resistor) |

---

# System Architecture

```
          Smartphone
               │
               │
        Browser Dashboard
               │
         WebSocket / REST
               │
         ┌─────────────┐
         │    ESP32    │
         │ Main Server │
         └─────────────┘
          │     │     │
          │     │     │
        PN532 OLED Buzzer
          │
      NFC Cards
```

---

# Project Structure

```
src
│
├── controllers/
├── data/
├── display/
├── nfc/
├── web/
├── websocket/
│     ├── handlers/
│     ├── ws_manager.cpp
│     └── ws_manager.h
│
└── main.cpp


data
│
├── players.json
├── ownership_data
├── session_data
├── game_state
└── nfc_roles


data/
│
├── html
├── css
└── js
      ├── components
      ├── pages
      ├── websocket
      └── state.js
```

---

# Current Features (Checkpoint 1)

## WiFi Manager

- Auto configuration portal
- Dynamic WiFi setup

---

## Web Server

- SPIFFS based file system
- HTML/CSS/JavaScript serving

---

## WebSocket Communication

- Real-time communication
- Multi-client support
- Device registration

---

## Session Management

Each browser receives a unique:

```
DEV-xxxxxxxx
```

Stored using LocalStorage.

---

## Ownership System

Role ownership is stored inside ESP32 memory.

Supported roles:

- BANK
- PLAYER1
- PLAYER2
- PLAYER3
- PLAYER4
- PLAYER5
- PLAYER6

One device can own only one role.

---

## NFC Authentication

Role claiming process:

```
Select Role
     ↓
Request Access
     ↓
Need Claim
     ↓
Tap NFC Card
     ↓
Validate Card
     ↓
Claim Success
     ↓
Ownership Stored
```

---

## Access Control

Supported states:

### access_granted

Owner is valid.

### access_denied

Role belongs to another device.

### need_claim

Role has not been claimed yet.

---

## Game State Broadcast

ESP32 periodically broadcasts:

- Player money
- Property count
- Role information

Using WebSocket.

---

## Dynamic Routing System

Pages:

- Home Page
- ATM Page
- Auction Page
- Logs Page
- Settings Page
- Private Role Page

---

## Dynamic Private Page

Special UI based on role.

### BANK

Administrative panel.

### PLAYER

Player dashboard.

---

# Features In Development

## Transfer System

Money transfer between players.

---

## Property Ownership System

List of owned properties.

---

## Auction System

Property bidding mechanism.

---

## Transaction Logs

History of game activities.

---

## Event Cards

- Chance
- Community Chest

---

## Turn Management

Current player tracking.

---

## Jail System

Special state handling.

---

## Dice Integration

Physical or digital dice synchronization.

---

## Sound Effects

Using passive buzzer.

---

## LED Indicators

Visual status notifications.

---

## OLED Information Screen

Display:

- IP Address
- Connected Clients
- Current Turn
- Game Status

---

## Session Recovery

Reconnect browser without losing ownership.

---

## Save and Load Game

Persistent storage.

---

## Admin Mode

BANK privileges.

---

## Real-Time Synchronization

Instant updates for all connected devices.

---

# Planned Features (Future)

- TFT Display Integration
- Touch Interface
- LVGL GUI
- Web App PWA
- QR Code Pairing
- ESP-NOW Support
- AI Banker Assistant
- Online Multiplayer
- Database Integration
- Cloud Synchronization

---

# Current Development Status

## Phase 1

### Backend Foundation

- [x] WiFi Manager
- [x] Web Server
- [x] SPIFFS
- [x] WebSocket
- [x] Session System
- [x] Ownership System
- [x] NFC Authentication
- [x] Routing System
- [x] Dynamic Page

---

## Phase 2

### Gameplay Layer

- [ ] Transfer System
- [ ] Property System
- [ ] Auction System
- [ ] Transaction Logs
- [ ] Turn System

---

## Phase 3

### Advanced Features

- [ ] OLED Enhancement
- [ ] Sound System
- [ ] Save Game
- [ ] Admin System
- [ ] Session Recovery

---

## Phase 4

### Smart Board

- [ ] TFT Display
- [ ] Touchscreen
- [ ] LVGL Interface
- [ ] PWA Support
- [ ] Cloud Integration

---

# Author

**Pulung Bagas Setiawan**

Universitas Sains dan Teknologi Komputer

---

# Notes For Future Development

ESP32 acts as the single source of truth.

Browser clients only display information and send requests.

Player data, ownership, and authority remain inside ESP32 RAM.

Frontend should remain modular:

```
state.js
socket.js
socket_access.js
socket_game_state.js
socket_ui.js
router.js

components/
pages/
```

Avoid monolithic files and maintain a modular architecture for easier scaling and maintenance.
