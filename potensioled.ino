const int potensiometer = A0;
const int led = 9;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Membaca posisi potensiometer
  int nilaiPot = analogRead(potensiometer);

  // Mengubah rentang 0-1023 menjadi 0-255
  int terang = map(nilaiPot, 0, 1023, 0, 255);

  // Mengatur kecerahan LED
  analogWrite(led, terang);

  // Menampilkan nilai di Serial Monitor
  Serial.print("Potensiometer: ");
  Serial.print(nilaiPot);

  Serial.print(" | Kecerahan LED: ");
  Serial.println(terang);

  delay(50);
}
