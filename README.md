# Monitoring Debit Air dengan ESP32 dan Terhubung ke Firebase
### Sistem ini menggunakan mikrokontroler ESP32 __bukan ESP8266__
Semua library yang diperlukan sudah ada di repository ini, untuk firebase nya menggunakan email MBC, jadi silahkan menghubungi Asisten Lab MBC untuk mendapatkan aksesnya, atau edit di codingan arduino nya.
### Schematic rangkaian:
| ESP32 | Water Flow Sensor |
|-------|-------------------|
|3v3    |Kabel Merah        |
|GND    |Kabel Hitam        |
|D15    |Kabel Kuning       |
- [x] Monitoring debit air (L/min)
- [x] Kirim data ke firebase
