# 🎲 Hybrid Smart Monopoly Board Game using ESP32

> A Cyber-Physical Monopoly Board Game powered by ESP32, NFC, WebSocket, and a real-time browser interface.

---

# Overview

Hybrid Smart Monopoly Board Game is a Cyber-Physical System (CPS) that combines a traditional physical Monopoly board with a real-time web application powered by an ESP32.

Unlike fully digital board games, the physical gameplay remains intact while every game transaction, ownership, authentication, and synchronization is managed digitally.

ESP32 acts as the **single source of truth**, while every browser functions only as a client interface.

This project is designed for:

- 🎓 Final Year Project (Skripsi)
- 📄 Scientific Journal Publication
- 🤖 Cyber-Physical System Research
- 🌐 Internet of Things (IoT)
- ⚙ Embedded System Learning
- 💻 Real-Time Web Application Development

---

# Main Objectives

- Build a hybrid Monopoly game that preserves physical interaction.
- Integrate Embedded Systems with modern Web Technology.
- Demonstrate Cyber-Physical System implementation.
- Build a modular and scalable embedded software architecture.
- Create a real-time multiplayer board game using ESP32.

---

# Technology Stack

## Embedded

- ESP32 DevKit V1
- C++
- Arduino Framework
- PlatformIO

## Frontend

- HTML5
- CSS3
- Vanilla JavaScript

## Communication

- REST API
- WebSocket
- SPI
- I2C

---

# Development Environment

## IDE

Visual Studio Code

Extensions

- PlatformIO IDE
- C/C++
- Arduino Framework for ESP32

---

# Hardware Components

| Component | Function |
|------------|----------|
| ESP32 DevKit V1 | Main Controller |
| PN532 NFC Module | Authentication & Ownership |
| SSD1306 OLED | Information Display |
| Passive Buzzer | Sound Notification |
| 5mm LED | Status Indicator |
| 220Ω Resistor | LED Protection |
| Smartphone / Laptop | Browser Dashboard |
| WiFi Router | Communication Medium |

---

# Hardware Pin Mapping

## PN532 (SPI)

| PN532 | ESP32 |
|--------|--------|
| VCC | 3.3V |
| GND | GND |
| SCK | GPIO18 |
| MOSI | GPIO23 |
| MISO | GPIO19 |
| SS/SDA | GPIO14 |

---

## OLED SSD1306 (I2C)

| OLED | ESP32 |
|------|--------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO21 |
| SCL | GPIO22 |

---

## Passive Buzzer

| Buzzer | ESP32 |
|----------|--------|
| + | GPIO26 |
| - | GND |

---

## LED Indicator

| LED | ESP32 |
|------|--------|
| Anode | GPIO25 |
| Cathode | GND via 220Ω |

---

# System Architecture

```text
                  Smartphone / Laptop
                          │
                          │
                   Browser Dashboard
                          │
                  REST API / WebSocket
                          │
                  ┌─────────────────┐
                  │      ESP32      │
                  │  Main Authority │
                  └─────────────────┘
                     │      │      │
                     │      │      │
                  PN532   OLED   Buzzer
                     │
                 NFC Player Cards
```

---

# Software Architecture

```
ESP32
│
├── Controllers
├── Services
├── Data
├── NFC
├── WebSocket
├── Web
├── Display
└── main.cpp

Frontend
│
├── components/
├── pages/
│   ├── Public Pages
│   └── Private Pages
│
├── js/
│   ├── ws/
│   ├── router/
│   ├── state
│   └── controllers
│
└── assets/
```

The project follows a layered architecture:

```
UI
 ↓
Controller
 ↓
Service
 ↓
Session
 ↓
Game Data
```

Business logic is separated from runtime state.

---

# Current Development Status

## ✅ Phase 1 — Backend Foundation (Completed)

---

## WiFi Manager

- Auto WiFi Configuration Portal
- Dynamic WiFi Setup
- Automatic Reconnection

---

## Web Server

- SPIFFS File System
- HTML Serving
- CSS Serving
- JavaScript Serving
- Static Assets

---

## REST API

- Player Data
- Game State
- Ownership API

---

## WebSocket System

- Real-time Communication
- Multi-client Support
- Automatic Broadcasting
- Event-driven Architecture

---

## Device Session System

Every browser receives a permanent Device ID.

Example

```
DEV-xxxxxxxx
```

Stored using LocalStorage.

The same browser keeps its identity after reconnecting.

---

## Ownership System

Implemented ownership management inside ESP32 RAM.

Supported Roles

- BANK
- PLAYER1
- PLAYER2
- PLAYER3
- PLAYER4
- PLAYER5
- PLAYER6

Rules

- One browser owns one role
- One role belongs to one browser
- Ownership stored entirely inside ESP32

---

## NFC Authentication

Implemented NFC ownership claiming.

Workflow

```
Choose Role

↓

Request Access

↓

Need Claim

↓

Tap NFC Card

↓

Validate UID

↓

Ownership Stored

↓

Access Granted
```

---

## Access Control

Implemented

- access_granted
- access_denied
- need_claim

---

## Game State Broadcast

Real-time broadcasting

Current broadcasted data

- Money
- Houses
- Hotels
- Properties
- Player Role

---

## Dynamic Router

Implemented SPA Router

Pages

- Home
- Player Dashboard
- Bank Dashboard
- Transfer
- ATM
- Auction
- Logs
- Settings

---

## Dynamic Dashboard

Automatic dashboard switching

Player

↓

Player Dashboard

Bank

↓

Bank Dashboard

---

# ✅ Phase 2 — Gameplay Foundation (Current Checkpoint)

---

## Transaction Session Engine

Completely redesigned.

Old

```
senderVerified
receiverVerified
```

New

```
sourceRole
targetRole

sourceVerified
targetVerified

sourceDevice
targetDevice

startTime

state

active
```

Transaction now behaves like a reusable transaction engine instead of a transfer-only implementation.

---

## Transaction State Machine

Implemented

```
IDLE

↓

WAIT_SENDER

↓

WAIT_RECEIVER

↓

PROCESSING

↓

SUCCESS / FAILED / TIMEOUT

↓

IDLE
```

---

## Generic Money Service

Implemented

```
addMoney()

deductMoney()

transferMoney()

playerExists()

getPlayerMoney()
```

Supports future gameplay modules.

---

## Money Transfer System

Fully implemented.

Supported

- ✅ Player → Player
- ✅ Player → Bank
- ✅ Bank → Player

Automatic rollback if transaction fails.

---


## Monopoly Repository

Implemented centralized Monopoly repository using JSON.

```
SPIFFS

↓

monopoly_rules.json

↓

Repository Loader

↓

Repository Service
```

Every Monopoly asset (property, railroad, utility, tax, chance, etc.) is loaded only once during boot.

The repository acts as a read-only database for every gameplay module.

Implemented:

- Asset Lookup
- Purchase Price
- Rent Data
- House Cost
- Hotel Cost
- Mortgage Value
- Release Cost
- Color Group
- Asset Category

---

## NFC Transaction Verification

Implemented

```
Tap Sender

↓

Verify Sender

↓

Tap Receiver

↓

Verify Receiver

↓

Execute Transaction

↓

Broadcast Result
```

BANK automatically skips NFC verification because it has no NFC card.

---

## Transaction Timeout

Implemented

Automatic timeout after

```
30 seconds
```

Session automatically clears.

---

## Transaction Cancel

Implemented

Browser

↓

Cancel Button

↓

ESP32

↓

Cancel Session

↓

Broadcast Cancellation

---

## Transaction Broadcast Events

Implemented

```
transaction_wait_sender

transaction_wait_receiver

transaction_processing

transaction_success

transaction_failed

transaction_timeout

transaction_cancelled

transaction_busy
```

---

## Transfer UI

Implemented

- Dynamic Sender
- Dynamic Receiver
- Amount Validation
- Balance Validation
- Auto Reset
- Status Card
- Cancel Button
- Browser Debug Logging

---

## Browser Debugging

Detailed logs

```
Current Role

Game State

Active Player

Receiver List

Transaction Request

WebSocket Messages

Transfer Reset
```

---

# Architecture Improvements

During development several architectural improvements were introduced.

## Transaction Engine

Business logic completely separated from runtime session.

```
TransactionService

↓

TransactionSession

↓

TransactionExecutor
```

---

## Repository Pattern

Gameplay configuration is completely separated from runtime state.

```
monopoly_rules.json

↓

Repository

↓

Services

↓

Transaction Engine
```

Static game rules never change during gameplay, while runtime ownership is stored separately.

---

## Runtime Session

Temporary runtime information stored only inside Session.

Examples

- Current transaction
- Current sender
- Current receiver
- Timeout timer
- Verification status


---

## Property Ownership Engine

Implemented dedicated ownership storage independent from Monopoly repository.

Architecture

```
Monopoly Repository
(Read Only)

↓

Property Ownership Data
(Runtime)

↓

Property Services
```

Each property stores:

- Owner
- Owned Status
- Mortgage Status
- House Count
- Hotel Status

Property ownership is stored only inside ESP32 runtime.

---


## Property Service

Implemented generic property service.

Supported operations

```
getOwnership()

setOwner()

clearOwner()

ownsProperty()

getOwner()

playerPropertyCount()

playerHouseCount()

playerHotelCount()
```

Business logic is separated from runtime ownership data.

---

## Generic Property Transaction Session

Property actions now use the same transaction engine architecture as money transfer.

Architecture

```
Web

↓

WebSocket

↓

Transaction Session

↓

Transaction Executor

↓

Property Transaction Service
```

The Property Transaction Executor dispatches gameplay actions without embedding business logic.

This makes future gameplay features modular and reusable.

---

## Business Logic

All permanent logic moved into Services.

Examples

```
Money

Ownership

Transactions

Players
```

---

## Modular WebSocket

Separated into

```
ws_access

ws_game_state

ws_transaction

ws_transaction_start

ws_transaction_cancel

ws_transaction_broadcast

socket_ui.js

socket_game_state.js

socket_access.js
```

---

# Features Currently Under Development

- Property Trading
- Complete Rent Rules
- Tax System
- Auction System
- Jail System
- Chance Card
- Community Chest
- Turn Management

---

# Future Roadmap

## Gameplay

- Property Engine
- Rent Engine
- Mortgage
- Trading
- Bankruptcy
- Jail
- Auction
- Turn Manager

---

## Embedded

- OLED Dashboard
- Sound Effects
- LED Notification
- Physical Dice Integration

---

## Smart Board

- TFT Display
- Touchscreen
- LVGL GUI
- PWA
- ESP-NOW
- QR Pairing

---

## Cloud

- Database
- Save Game
- Load Game
- Online Multiplayer
- Cloud Synchronization

---

# Current Progress

## Backend Foundation

- [x] WiFi Manager
- [x] Web Server
- [x] SPIFFS
- [x] REST API
- [x] WebSocket
- [x] Device Session
- [x] Ownership System
- [x] NFC Authentication
- [x] Access Control
- [x] Game State Broadcast
- [x] Dynamic Router
- [x] Dynamic Dashboard

---

## Gameplay Foundation

- [x] Transaction Session
- [x] Money Service
- [x] Money Transfer
- [x] Player → Player
- [x] Player → Bank
- [x] Bank → Player
- [x] Transaction Timeout
- [x] Transaction Cancel
- [x] Transaction Broadcast
- [x] Runtime Session
- [x] Generic Transaction Engine

---

## Gameplay Systems

## Gameplay Systems

- [x] Monopoly Repository
- [x] Property Ownership
- [x] Property Purchase
- [x] Property Runtime Data
- [x] Property Transaction Session
- [x] Property Executor
- [ ] Property Selling
- [ ] Complete Rent Rules
- [ ] Tax System
- [ ] Auction
- [ ] Chance Card
- [ ] Community Chest
- [ ] Jail
- [ ] Turn Manager
- [ ] Transaction Log

---

## Smart Board

- [ ] OLED UI
- [ ] Buzzer Feedback
- [ ] LED Feedback
- [ ] Dice Synchronization

---

## Advanced

- [ ] Save / Load Game
- [ ] Session Recovery
- [ ] Admin Mode
- [ ] Cloud Sync
- [ ] Online Multiplayer

---

# Author

**Pulung Bagas Setiawan**

Universitas Sains dan Teknologi Komputer (USTK)

---

# Design Principles

- ESP32 is the Single Source of Truth.
- Browser never owns game data.
- Browser only sends requests and renders UI.
- Business logic stays inside ESP32.
- Runtime state is stored inside Session.
- Frontend remains modular and scalable.

---

# Repository Status

**Current Checkpoint**

✅ Selesai
Backend Foundation
WebSocket Framework
Session Engine
Ownership System
Money Transaction Engine
Generic Transaction Engine
Monopoly Repository
Property Ownership Engine
Property Runtime Data
Property Transaction Framework
SPA Frontend Foundation
🚧 Sedang dikerjakan
Property UI
Property WebSocket Flow
Buy Property Flow
Rent Flow
⏳ Berikutnya
Property List Page (mengambil data langsung dari monopoly_rules.json yang sudah di-load di repository).
WebSocket request_property_list agar browser menerima seluruh data properti dari ESP32.
Render daftar properti di halaman PROPERTY LIST.
Tombol Buy yang mengirim PROPERTY_BUY.
NFC verification untuk pembelian.
Broadcast perubahan kepemilikan ke semua browser.
Sinkronisasi tampilan Player Dashboard dan Property List secara real-time.