#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>

// ====== PIN ======
#define DHTPIN 15
#define DHTTYPE DHT11
#define LED_PIN 0

// ====== WIFI ======
#define WIFI_SSID     "NamaWIfi"
#define WIFI_PASSWORD "PW-Wifi"

// ====== TELEGRAM ======
#define BOT_TOKEN "TokenTelegram"
#define CHAT_ID   "ChatTelegram"

// ====== SUHU ======
#define BATAS_SUHU 35   // 35 derajat

// ====== OBJEK ======
DHT dht(DHTPIN, DHTTYPE);
WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

// ====== TIMER ======
unsigned long lastTelegram = 0;
const unsigned long telegramInterval = 5000; // 5 detik

unsigned long lastRead = 0;
const unsigned long interval = 1000; // 1 detik

bool alertSent = false;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  dht.begin();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  client.setInsecure(); // Telegram HTTPS

  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi connected!");
  Serial.println(WiFi.localIP());

  bot.sendMessage(CHAT_ID, "📡 Sistem Monitoring Suhu AKTIF", "");
}

void loop() {
  unsigned long now = millis();

  // ===== BACA SENSOR CEPAT =====
  if (now - lastRead >= interval) {
    lastRead = now;

    float suhu = dht.readTemperature();
    float hum  = dht.readHumidity();

    if (isnan(suhu) || isnan(hum)) return;

    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.print(" °C | Kelembapan: ");
    Serial.print(hum);
    Serial.println(" %");

    if (suhu >= BATAS_SUHU) {
      digitalWrite(LED_PIN, HIGH);

      if (!alertSent) {
        bot.sendMessage(
          CHAT_ID,
          "🔥 *PERINGATAN SUHU PANAS!*\n"
          "🌡 Suhu: " + String(suhu) + " °C\n"
          "💧 Kelembapan: " + String(hum) + " %",
          "Markdown"
        );
        alertSent = true;
      }

    } else {
      digitalWrite(LED_PIN, LOW);
      alertSent = false;
    }
  }

  // ===== UPDATE TELEGRAM BERKALA =====
  if (now - lastTelegram >= telegramInterval) {
    lastTelegram = now;

    float suhu = dht.readTemperature();
    float hum  = dht.readHumidity();

    if (isnan(suhu) || isnan(hum)) return;

    String status = (suhu >= BATAS_SUHU) ? "🔥 PANAS" : "🟢 NORMAL";

    bot.sendMessage(
      CHAT_ID,
      "📊 *Status Ruangan*\n"
      "🌡 Suhu: " + String(suhu) + " °C\n"
      "💧 Kelembapan: " + String(hum) + " %\n"
      "📌 Status: " + status,
      "Markdown"
    );
  }
}

