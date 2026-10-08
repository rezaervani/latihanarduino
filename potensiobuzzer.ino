const int potensiometer = A0;
const int tombol = 2;
const int buzzer = 9;

void setup() {
  pinMode(tombol, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  int nilaiPot = analogRead(potensiometer);

  // Ubah nilai 0-1023 menjadi 0-255
  int intensitas = map(nilaiPot, 0, 1023, 0, 255);

  // Tombol ditekan
  if (digitalRead(tombol) == LOW) {

    analogWrite(buzzer, 0);

  } else {

    analogWrite(buzzer, intensitas);

  }

  Serial.print("Potensiometer = ");
  Serial.print(nilaiPot);

  Serial.print(" | PWM Buzzer = ");
  Serial.println(intensitas);

  delay(50);
}
