
#include <TM1637Display.h>

// PIN SENSOR HC-SR04
#define TRIG 9
#define ECHO 10

// PIN DISPLAY TM1637
#define CLK 3
#define DIO 4

TM1637Display display(CLK, DIO);

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  display.setBrightness(7);
  display.clear();

  Serial.begin(9600);
}

void loop() {

  // Mengirim pulsa ultrasonik
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  // Mengukur waktu pantulan
  long durasi = pulseIn(ECHO, HIGH, 30000UL);

  // Jika tidak ada pantulan
  if (durasi == 0) {
    display.clear();
    Serial.println("Tidak ada pantulan");
  }
  else {
    // Menghitung jarak dalam cm
    float jarak = durasi * 0.0343 / 2.0;

    // Membulatkan hasil ke bilangan bulat
    int jarakCm = (int)(jarak + 0.5);

    // Membatasi angka tampilan
    if (jarakCm > 9999) jarakCm = 9999;

    // Menampilkan jarak pada TM1637
    display.showNumberDec(jarakCm, false);

    // Menampilkan juga di Serial Monitor
    Serial.print("Jarak: ");
    Serial.print(jarak);
    Serial.println(" cm");
  }

  delay(200);
}
