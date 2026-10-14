// 1. Menguji LED Bawaan Arduino
// Program ini menyalakan LED bawaan board Arduino selama 1 detik lalu mematikannya selama 1 detik.

void setup() {
  // Inisialisasi pin LED bawaan sebagai OUTPUT
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // Menyalakan LED
  delay(1000);                     // Menunggu 1 detik (1000 ms)
  digitalWrite(LED_BUILTIN, LOW);  // Mematikan LED
  delay(1000);                     // Menunggu 1 detik (1000 ms)
}
