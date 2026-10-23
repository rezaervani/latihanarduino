#include <Arduino.h>
#include <TM1637Display.h>

// ==========================================
// PENGATURAN PIN DISPLAY TM1637
// ==========================================
#define PIN_CLK 4        // Jalur CLK bersama (paralel ke 3 display)

#define DIO_VGATE  5     // Display 1: Tegangan Gate (V)
#define DIO_VDRAIN 6     // Display 2: Tegangan Drain (V)
#define DIO_ARUS   7     // Display 3: Arus Beban (mA)

TM1637Display dispGate(PIN_CLK, DIO_VGATE);
TM1637Display dispDrain(PIN_CLK, DIO_VDRAIN);
TM1637Display dispArus(PIN_CLK, DIO_ARUS);

// ==========================================
// PENGATURAN PIN SENSOR & KENDALI
// ==========================================
const int pinPotensio    = A3; // Masukan tuas kendali dari siswa
const int pinSensorGate  = A0; // Probe pembaca tegangan kaki Gate (VG)
const int pinSensorDrain = A1; // Probe pembaca tegangan kaki Drain (VD)
const int pinSensorShunt = A2; // Probe pembaca drop tegangan di resistor Shunt

const int pinGatePWM     = 9;  // Output sinyal kendali PWM ke kaki Gate MOSFET

// Barisan 4 LED Indikator Beban Bertingkat
const int pinLEDMerah    = 10; // Level 1
const int pinLEDKuning   = 11; // Level 2
const int pinLEDBiru     = 12; // Level 3
const int pinLEDHijau    = 13; // Level 4

// ==========================================
// NILAI RESISTOR SHUNT
// Ganti ke 1.0 jika memakai resistor 1 Ohm
// Ganti ke 10.0 jika memakai resistor 10 Ohm
// ==========================================
const float R_SHUNT = 10.0; 

void setup() {
  Serial.begin(115200);

  // Atur kecerahan ketiga display (rentang 0x00 hingga 0x0f)
  dispGate.setBrightness(0x0a);
  dispDrain.setBrightness(0x0a);
  dispArus.setBrightness(0x0a);

  // Bersihkan tampilan display
  dispGate.clear();
  dispDrain.clear();
  dispArus.clear();

  // Konfigurasi pin output
  pinMode(pinGatePWM, OUTPUT);
  pinMode(pinLEDMerah, OUTPUT);
  pinMode(pinLEDKuning, OUTPUT);
  pinMode(pinLEDBiru, OUTPUT);
  pinMode(pinLEDHijau, OUTPUT);
}

void loop() {
  // 1. Baca posisi potensiometer (0 - 1023)
  int nilaiPot = analogRead(pinPotensio);

  // 2. Petakan ke nilai PWM 8-bit (0 - 255) lalu kirim ke Gate MOSFET via pin D9
  int nilaiPWM = map(nilaiPot, 0, 1023, 0, 255);
  analogWrite(pinGatePWM, nilaiPWM);

  // 3. Baca nilai parameter fisik tegangan pada rangkaian (ADC 0 - 1023 -> 0 - 5.0V)
  float vGate   = (analogRead(pinSensorGate) * 5.0) / 1023.0;
  float vDrain  = (analogRead(pinSensorDrain) * 5.0) / 1023.0;
  float vShunt  = (analogRead(pinSensorShunt) * 5.0) / 1023.0;

  // Hitung arus beban berdasarkan Hukum Ohm: I = V_shunt / R_shunt (dikonversi ke mA)
  float arus_mA = (vShunt / R_SHUNT) * 1000.0;

  // 4. Logika penyalaan LED bertingkat berdasarkan bukaan tegangan Gate
  if (vGate < 0.8) {
    // Level 0: OFF / Cut-off (Semua LED padam)
    digitalWrite(pinLEDMerah, LOW);
    digitalWrite(pinLEDKuning, LOW);
    digitalWrite(pinLEDBiru, LOW);
    digitalWrite(pinLEDHijau, LOW);
  } 
  else if (vGate >= 0.8 && vGate < 2.0) {
    // Level 1: Ambang awal (LED Merah aktif)
    digitalWrite(pinLEDMerah, HIGH);
    digitalWrite(pinLEDKuning, LOW);
    digitalWrite(pinLEDBiru, LOW);
    digitalWrite(pinLEDHijau, LOW);
  } 
  else if (vGate >= 2.0 && vGate < 3.2) {
    // Level 2: Daya Sedang (LED Merah + Kuning aktif)
    digitalWrite(pinLEDMerah, HIGH);
    digitalWrite(pinLEDKuning, HIGH);
    digitalWrite(pinLEDBiru, LOW);
    digitalWrite(pinLEDHijau, LOW);
  } 
  else if (vGate >= 3.2 && vGate < 4.2) {
    // Level 3: Daya Tinggi (LED Merah + Kuning + Biru aktif)
    digitalWrite(pinLEDMerah, HIGH);
    digitalWrite(pinLEDKuning, HIGH);
    digitalWrite(pinLEDBiru, HIGH);
    digitalWrite(pinLEDHijau, LOW);
  } 
  else {
    // Level 4: Saturasi Penuh (Keempat LED Merah, Kuning, Biru, Hijau menyala semua)
    digitalWrite(pinLEDMerah, HIGH);
    digitalWrite(pinLEDKuning, HIGH);
    digitalWrite(pinLEDBiru, HIGH);
    digitalWrite(pinLEDHijau, HIGH);
  }

  // 5. Format dan tampilkan data ke 3 modul TM1637
  // Format voltase ditampilkan dalam 2 angka desimal tanpa titik (contoh: 3.45V -> angka 345)
  int dispValGate  = (int)(vGate * 100);
  int dispValDrain = (int)(vDrain * 100);
  int dispValArus  = (int)arus_mA;

  dispGate.showNumberDec(dispValGate, false);
  dispDrain.showNumberDec(dispValDrain, false);
  dispArus.showNumberDec(dispValArus, false);

  // Jeda pembacaan agar tampilan stabil dan responsif terhadap putaran tangan
  delay(50);
}
