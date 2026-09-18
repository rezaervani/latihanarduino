5V ── Buzzer ── Collector BC547
 │
D9 ── 1 kΩ ── Base │
 │
 Emitter
 │
 GND
const int transistor = 9;

void setup() {
 pinMode(transistor, OUTPUT);
}

void loop() {
 tone(transistor, 1000);
 delay(2000);

 noTone(transistor);
 delay(1000);
}
