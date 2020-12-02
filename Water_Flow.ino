#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>
#include <time.h>

#define FIREBASE_HOST "smart-mosque-32bd7.firebaseio.com"
#define FIREBASE_AUTH "dArXCI74b8wFlAsZagm9h06TOAp9zrdBzu8Tl5NG"
#define WIFI_SSID "Smart Mosque"
#define WIFI_PASSWORD "13245768"

const int pin_waterflow     = 15;
byte sensorInterrupt        = 0;
float calibrationFactor     = 6.9; //sesuaikan saja, bisa 7.5
volatile byte pulseCount    = 0;
float debit                 = 0.0;
float volume                = 0.0;
unsigned long oldTime       = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();

  //Menghubungkan ke WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  //Authentikasi ke Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  attachInterrupt(pin_waterflow, pulseCounter, CHANGE);
  oldTime = millis();
}

void loop() {
  if (millis()-oldTime > 1000) {
    debit   = pulseCount/(2*calibrationFactor);
    volume  += debit;

    //Mengirim ke Firebase
    Firebase.setString("Air/debit", String(debit));
    Firebase.setString("Air/volume", String(volume));

    //Menampilkan ke serial monitor
    Serial.print("debit: ");
    Serial.println(debit);
    Serial.print("volume: ");
    Serial.println(volume);
    oldTime = millis();
    pulseCount = 0;
  }
//  debit      = ((1000.0/(millis()-oldTime))*pulseCount)/calibrationFactor;
//  mL_flow  = (debit/60)*1000;//mL/Sec

  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
}

void pulseCounter() {
  pulseCount++;
}
