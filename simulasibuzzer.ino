// Definisi pin buzzer
const int BUZZER_PIN = 8;

// Frekuensi nada (dalam Hertz) pada Oktaf 4
#define NOTE_C4  262  // Do
#define NOTE_D4  294  // Re
#define NOTE_E4  330  // Mi
#define NOTE_F4  349  // Fa
#define NOTE_G4  392  // Sol
#define NOTE_A4  440  // La
#define NOTE_B4  494  // Si
#define NOTE_C5  523  // Do (Tinggi)

// Array tangga nada naik dan turun
int melody[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, 
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_G4, NOTE_F4, 
  NOTE_E4, NOTE_D4, NOTE_C4
};

// Durasi tiap nada dalam milidetik (misal: 350 ms per ketukan)
const int noteDuration = 350;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  int totalNotes = sizeof(melody) / sizeof(melody[0]);

  for (int i = 0; i < totalNotes; i++) {
    // Fungsi tone(pin, frekuensi, durasi)
    tone(BUZZER_PIN, melody[i], noteDuration);

    // Beri jeda sedikit lebih lama dari durasi nada agar antar-nada terpisah jelas
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // Hentikan suara sebelum nada berikutnya
    noTone(BUZZER_PIN);
  }

  // Jeda 2 detik sebelum mengulang kembali dari awal
  delay(2000);
}
