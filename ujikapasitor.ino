#include <TM1637Display.h>

const int kapasitor = A0;
const int pengisi = 8;

const int CLK = 2;
const int DIO = 3;

TM1637Display display(CLK, DIO);

void setup() {

  pinMode(pengisi, OUTPUT);

  Serial.begin(9600);

  display.setBrightness(7);
  display.clear();
}

void loop() {

  // CHARGING
  digitalWrite(pengisi, HIGH);

  Serial.println("CHARGING");

  for (int i = 0; i < 900; i++) {

    int nilaiADC = analogRead(kapasitor);

    float tegangan = nilaiADC * 5.0 / 1023.0;

    int persen = map(nilaiADC, 0, 1023, 0, 100);

    display.showNumberDec(persen);

    Serial.print("ADC = ");
    Serial.print(nilaiADC);

    Serial.print(" | Tegangan = ");
    Serial.print(tegangan);

    Serial.print(" V | Muatan = ");
    Serial.print(persen);

    Serial.println(" %");

    delay(100);
  }

  // DISCHARGING
  digitalWrite(pengisi, LOW);

  Serial.println();
  Serial.println("DISCHARGING");

  for (int i = 0; i < 900; i++) {

    int nilaiADC = analogRead(kapasitor);

    float tegangan = nilaiADC * 5.0 / 1023.0;

    int persen = map(nilaiADC, 0, 1023, 0, 100);

    display.showNumberDec(persen);

    Serial.print("ADC = ");
    Serial.print(nilaiADC);

    Serial.print(" | Tegangan = ");
    Serial.print(tegangan);

    Serial.print(" V | Muatan = ");
    Serial.print(persen);

    Serial.println(" %");

    delay(100);
  }

  Serial.println();
}
