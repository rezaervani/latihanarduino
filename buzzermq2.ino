// Definisi Pin
const int MQ2_PIN    = A0;  // Pin analog pembacaan MQ-2
const int BUZZER_PIN = 8;   // Pin sinyal buzzer

// Ambang batas deteksi asap (0 - 1023)
// Sesuaikan nilai ini sesuai hasil pembacaan udara normal di ruangan Anda
int threshold = 350;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.println("=================================");
  Serial.println("Sistem Deteksi Asap Siap!");
  Serial.println("=================================");
}

void loop() {
  // Membaca nilai kepekatan dari pin analog MQ-2
  int sensorValue = analogRead(MQ2_PIN);

  // Debugging melalui Serial Monitor
  Serial.print("Kadar Asap: ");
  Serial.print(sensorValue);
  Serial.print(" | Status: ");

  if (sensorValue > threshold) {
    Serial.println("BAHAYA! Asap Terdeteksi!");
    
    // Pola bunyi alarm dua nada bergantian
    tone(BUZZER_PIN, 1500); // Frekuensi 1.5 kHz
    delay(150);
    noTone(BUZZER_PIN);
    delay(80);

    tone(BUZZER_PIN, 2000); // Frekuensi 2.0 kHz
    delay(150);
    noTone(BUZZER_PIN);
    delay(80);
  } else {
    Serial.println("Aman / Normal");
    noTone(BUZZER_PIN); // Pastikan buzzer mati saat kondisi normal
    delay(300);         // Interval pembacaan
  }
}
