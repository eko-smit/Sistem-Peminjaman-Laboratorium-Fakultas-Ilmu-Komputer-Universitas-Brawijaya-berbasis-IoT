#include <Arduino.h>
#include <WiFi.h>
#include <ESP32QRCodeReader.h>
#include <FirebaseESP32.h>
#include "time.h"

#define FLASH 4
#define DOOR 12
#define BUZZER 2

#define WIFI_SSID "Nyol2"
#define WIFI_PASSWORD "dadingsukma"
#defineFIREBASE_HOST "peminjaman-lab-7b07f-default-rtdb.Firebaseio.com"
#defineFIREBASE_AUTH "B7tjw0qRvnJc12jBaH5ehqZP856oQ9j3nxDIUQoH"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

ESP32QRCodeReader reader(CAMERA_MODEL_AI_THINKER);
struct QRCodeData qrCodeData;

const char *ntpServer = "id.pool.ntp.org";
const long gmtOffset_sec = 25200;
const int daylightOffset_sec = 0;

int jam;
int hari;
int bulan;
int tahun;

String KCV =” Laboratorium%20Komputasi%20Cerdas%20dan%20Visualisasi";
String GAME = "Laboratorium%20Game";
String JARKOM = "Laboratorium%20Jaringan%20Komputer";
String RPL = "Laboratorium%20Rekayasa%20Perangkat%20Lunak";
String SI = "Laboratorium%20Sistem%20Informasi";
String MOBILE = "Laboratorium%20Mobile%20Apps";
String ROBOTIK = "Laboratorium%20Sistem%20Komputer%20dan%20Robotika%20";

String Time()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
  }
  String path;
  path = String(timeinfo.tm_mday) + "-" + String(timeinfo.tm_mon + 1) + "-" + String(timeinfo.tm_year + 1900) + "%20Jam%20" + String(timeinfo.tm_hour);
  return path;
}
String getData(String path)
{
  if (Firebase.getString(fbdo, path))
  {
    Serial.print("Sukses mengambil data");
    return fbdo.stringData();
  }
  else
  {
    Serial.print("Gagal mengambil data");
    return fbdo.errorReason();
  }
}

String CodeQR;
String Penc;
String a = "\\";
String b = "\"";

void setup()
{
  Serial.begin(115200);
  pinMode(FLASH, OUTPUT);
  pinMode(DOOR, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(FLASH, LOW);
  digitalWrite(DOOR, HIGH);
  digitalWrite(BUZZER, LOW);
  //Mengaktifkan WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Menyambung ke WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("-");
    delay(300);
  }
  Serial.println();
  Serial.print("Tersambung dengan IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  //Mengaktifkan QR Reader
  reader.setup();
  reader.begin();
  Serial.println("Memulai Scan QR");
}

void loop()
{
  CodeQR = "Tidak Terbaca";

  Penc = Time() + "/encryption";
  /*String path bagian “GAME” diganti dengan lab yang akan dikasih alat ini*/
  String path = "Aplikasi_Peminjaman_Lab/" + GAME + "/" + Penc;
  if (reader.receiveQrCode(&qrCodeData, 100))
  {
    Serial.print("QRCode terdeteksi");
    if (qrCodeData.valid)
    {
      Serial.print("Payload: ");
      Serial.println((const char *)qrCodeData.payload);
      Serial.println();
      CodeQR = (char *)qrCodeData.payload;
      digitalWrite(FLASH, HIGH);
      digitalWrite(BUZZER, HIGH);
      delay(200);
      digitalWrite(FLASH, LOW);
      delay(1000);
      digitalWrite(BUZZER, LOW);
    }
    else
    {
      Serial.print("Invalid");
      Serial.println();
    }
  }
  if (CodeQR != "Tidak Terbaca")
  {
    Serial.print(Time());
    Serial.println();

    Serial.print("Login ke Firebase");
    Firebase.reconnectWiFi(true);
    Firebase.begin(&config, &auth);
    Serial.print("Sukses");
    Serial.println();

    String tes = getData(path);

    Serial.print(tes);
    Serial.println();
    String data = a + b + CodeQR + a + b;
    Serial.print(data);
    Serial.println();
    if (data == tes)
    {
      Serial.print("benar");
    
      digitalWrite(DOOR, LOW);
      delay(10000);
      digitalWrite(DOOR, HIGH);
    }
    else
    {
      Serial.print("salah");
      digitalWrite(LED_RED, HIGH);
    }
    delay(2000);
  }
}