```markdown
# 🎲 Hybrid Smart Monopoly Board Game

> **Menghubungkan interaksi fisik papan Monopoli tradisional dengan kecanggihan sistem digital real-time.** > ESP32 bertindak sebagai *Single Source of Truth* (Otoritas Utama), sementara browser pada perangkat pemain murni berfungsi sebagai antarmuka klien (*client interface*).

Proyek *Cyber-Physical System (CPS)* ini dirancang untuk:
`🎓 Skripsi/Tugas Akhir` • `📄 Publikasi Jurnal Sains` • `🤖 Riset CPS` • `🌐 IoT` • `⚙️ Embedded Systems`

---

## 🏗️ Arsitektur Sistem

**Prinsip Desain Utama:** Logika bisnis dan *runtime state* sepenuhnya berada di dalam ESP32. Browser tidak pernah memiliki data game, melainkan hanya mengirim *request* dan merender antarmuka (UI).

```text
[ Fisik ]                      [ Pusat Kontrol ]                     [ Digital / UI ]

Kartu NFC  ──────┐                                              ┌──> Layar OLED (Info)
                 │                                              │
                 ▼             ┌─────────────────┐              ├──> Buzzer & LED
 Modul PN532 ────┼─── SPI ───> │      ESP32      │              │
                               │  (Main Server)  │ ── REST API ─┼──> Player Dashboard (Browser)
 Monopoly JSON ──┼── SPIFFS ─> │                 │              │
                 │             └─────────────────┘ ─ WebSocket ─┼──> Bank Dashboard (Browser)
                 │                                              │
                 └──────────────────────────────────────────────┘

```

---

## 🛠️ Tech Stack

| Kategori | Teknologi yang Digunakan |
| --- | --- |
| **Embedded** | ESP32 DevKit V1, C++, Arduino Framework, PlatformIO (VS Code) |
| **Frontend** | HTML5, CSS3, Vanilla JavaScript, SPA Router |
| **Komunikasi** | REST API, WebSocket, SPI, I2C |

---

## 🔌 Pemetaan Pin Perangkat Keras (Hardware Wiring)

Seluruh komponen terhubung langsung ke ESP32 sebagai *Main Controller*.

| Modul | Komponen / Pin | Pin ESP32 | Protokol / Catatan |
| --- | --- | --- | --- |
| **PN532 (NFC)** | SCK, MOSI, MISO, SS/SDA | 18, 23, 19, 14 | SPI |
| **OLED SSD1306** | SDA, SCL | 21, 22 | I2C |
| **Buzzer (Pasif)** | Kutub Positif (+) | 26 | - |
| **LED Status** | Anoda | 25 | Gunakan Resistor 220Ω |
| *(Semua Modul)* | VCC / GND | 3.3V / GND | Jalur daya utama |

---

## ⚙️ Inovasi Arsitektur Perangkat Lunak

Untuk menjaga skalabilitas proyek, kode dipisahkan ke dalam beberapa *layer*:

1. **Transaction Engine:** Logika bisnis dipisahkan secara total dari *runtime session*. Mesin transaksi menggunakan *State Machine* (`IDLE ➔ WAIT_SENDER ➔ PROCESSING ➔ SUCCESS/FAIL`).
2. **Repository Pattern:** Aturan game (harga, sewa, rumah) bersifat statis dan diload satu kali dari `monopoly_rules.json` di memori SPIFFS, terpisah dari data kepemilikan yang bersifat dinamis.
3. **Property Ownership Engine:** Data kepemilikan properti dan uang disimpan di dalam RAM ESP32 dan disinkronkan ke semua browser secara instan via WebSocket.
4. **NFC Authentication:** Kepemilikan sesi (*Bank* atau *Player 1-6*) dan validasi setiap transaksi uang/aset wajib menggunakan ketukan kartu NFC fisik.

---

## 🚀 Status Pengembangan & Roadmap

### ✅ Fase 1: Backend & Infrastruktur Dasar (Selesai)

* [x] **Konektivitas:** Auto WiFi Manager & Web Server (SPIFFS).
* [x] **Komunikasi:** REST API & Real-time WebSocket *Broadcasting*.
* [x] **Autentikasi:** Sistem Sesi Perangkat, Verifikasi NFC, dan Kontrol Akses Berbasis *Role* (Bank/Player).
* [x] **UI Dinamis:** *Single Page Application* (SPA) dengan *Router* & Dasbor otomatis menyesuaikan *Role*.

### ✅ Fase 2: Core Gameplay Foundation (Selesai)

* [x] **Mesin Transaksi:** *State machine*, *Generic Money Service*, dan sistem Timeout/Cancel.
* [x] **Transfer Uang:** Mendukung Player ➔ Player, Player ➔ Bank, Bank ➔ Player.
* [x] **Monopoly Repository:** Parser JSON sentral untuk aturan aset properti.
* [x] **Property Engine Dasar:** Struktur data *runtime* kepemilikan properti.

### 🚧 Fase 3: Property Trading & Sinkronisasi UI (Sedang Dikerjakan - *Current Checkpoint*)

* [ ] Mengambil daftar properti dari `monopoly_rules.json` langsung ke UI via WebSocket.
* [ ] Alur pembelian properti (Tombol *Buy* ➔ Verifikasi NFC ➔ *Broadcast* Perubahan).
* [ ] Sinkronisasi *real-time* antara Dasbor Pemain dan Daftar Properti.

### ⏳ Fase 4: Mekanik Lanjutan & Smart Board (Mendatang)

* **Gameplay:** Sistem Sewa Lengkap, Jual Properti, Pajak, Lelang, Penjara, Kartu Kesempatan & Dana Umum.
* **Smart Board:** Notifikasi UI via Layar OLED, *Feedback* Suara (Buzzer) & Cahaya (LED).
* **Lanjutan:** Sistem *Save/Load Game*, Log Transaksi, Sinkronisasi Cloud.

---

**Dikembangkan oleh:** Pulung Bagas Setiawan | Universitas Sains dan Teknologi Komputer (USTK)

```

```