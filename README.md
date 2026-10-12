# 🌡️ ESP32 Telegram Temperature Monitor

Proyek Internet of Things (IoT) berbasis ESP32 untuk memonitor suhu dan kelembapan ruangan menggunakan sensor DHT11. Sistem ini terintegrasi dengan Bot Telegram untuk memberikan laporan kondisi ruangan secara berkala dan mengirimkan peringatan (alert) secara *real-time* apabila suhu melebihi batas yang ditentukan.

## ✨ Fitur Utama
*   **Real-time Monitoring:** Membaca suhu dan kelembapan setiap 1 detik.
*   **Telegram Alert System:** Mengirimkan notifikasi darurat secara otomatis jika suhu melebihi batas (contoh: >= 35°C).
*   **Periodic Reporting:** Mengirimkan pembaruan (update) status ruangan ke Telegram secara berkala.
*   **LED Indicator:** Lampu LED menyala sebagai peringatan visual saat suhu ruangan terpantau panas.
*   **Non-blocking Code:** Menggunakan fungsi `millis()` sehingga tidak ada *delay* yang menghambat eksekusi program.

## 🛠️ Perangkat Keras (Hardware)
1.  Board ESP32 (atau NodeMCU ESP32)
2.  Sensor Suhu & Kelembapan DHT11
3.  LED (1 buah)
4.  Kabel Jumper secukupnya

### Konfigurasi Pin (Wiring)
| Komponen | Pin ESP32 | Keterangan |
| :--- | :---: | :--- |
| **DHT11 Data** | `GPIO 15` | Pin data sensor suhu |
| **LED** | `GPIO 0` | Indikator suhu panas |

## 📚 Kebutuhan Library (Software)
Pastikan Anda telah menginstal *library* berikut di Arduino IDE Anda:
1.  **DHT sensor library** oleh Adafruit
2.  **UniversalTelegramBot** oleh Brian Lough (Disarankan versi 1.3.0)
3.  **ArduinoJson** oleh Benoit Blanchon (Dependensi untuk UniversalTelegramBot)

## 🚀 Cara Penggunaan
1. Kloning repositori ini atau *download* kode `main.ino`.
2. Buka aplikasi Telegram, cari **BotFather**, dan buat bot baru untuk mendapatkan **BOT TOKEN**.
3. Dapatkan **CHAT ID** Telegram Anda (Bisa menggunakan bot IDBot).
4. Buka kode melalui Arduino IDE, lalu **WAJIB** ubah pengaturan berikut dengan data Anda:

```cpp
// ====== WIFI ======
#define WIFI_SSID     "NAMA_WIFI_ANDA"
#define WIFI_PASSWORD "PASSWORD_WIFI_ANDA"

// ====== TELEGRAM ======
#define BOT_TOKEN "TOKEN_BOT_DARI_BOTFATHER"
#define CHAT_ID   "CHAT_ID_ANDA"
```

5. *Upload* program ke board ESP32 Anda.
6. Buka *Serial Monitor* (Baudrate 115200) untuk melihat status koneksi.
7. Bot Telegram Anda akan mengirimkan pesan saat sistem sudah aktif!

## ⚙️ Penyesuaian (Customization)
Anda dapat menyesuaikan beberapa parameter di dalam kode sesuai kebutuhan:
*   `BATAS_SUHU`: Ubah nilai `35` menjadi batas derajat celcius yang Anda inginkan untuk *trigger* peringatan.
*   `telegramInterval`: Waktu *update* berkala ke Telegram (Default 5000 ms / 5 detik. Sangat disarankan mengubahnya ke `60000` / 1 menit untuk menghindari *rate-limit* dari API Telegram).

## 📄 Lisensi
[MIT License](LICENSE)