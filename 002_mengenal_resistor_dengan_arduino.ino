// 2. Mengenal Cara Kerja Resistor dengan Arduino
// Pin 13 diset HIGH terus-menerus sebagai sumber tegangan 5 V.
// Resistor 220 Ohm bekerja membatasi arus yang masuk ke LED eksternal.

const int pinSumber = 13; // Pin digital yang digunakan sebagai sumber 5 V

void setup() {
  // Inisialisasi pin sebagai OUTPUT
  pinMode(pinSumber, OUTPUT);
  
  // Mengeluarkan tegangan konstan 5 V
  digitalWrite(pinSumber, HIGH);
}

void loop() {
  // Tidak ada proses berulang karena tujuan percobaan
  // adalah mengamati fungsi resistor membatasi arus secara kontinu.
}
