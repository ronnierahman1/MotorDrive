/*
  L293D Motor Shield quick test (Motor 1)
  Tries common pin mappings used by popular L293D shields/clones.
  Uses full on/off (no PWM) to make multimeter readings obvious.
*/

struct Map { uint8_t en, in1, in2; const char* name; };

// Two common layouts:
// A) Adafruit Motor Shield v1 style (many clones): EN=11, IN1=10, IN2=9
// B) Some clones swap order: EN=10, IN1=9, IN2=8  (seen on some "MH Electronics" variants)
// If neither works, we’ll extend the list after you report results.
Map maps[] = {
  {11, 10, 9,  "Map A: EN11 IN110 IN29"},
  {10, 9,  8,  "Map B: EN10 IN19  IN28"}
};

void driveStop(const Map& m) {
  digitalWrite(m.en, LOW);
  digitalWrite(m.in1, LOW);
  digitalWrite(m.in2, LOW);
}

void driveForward(const Map& m) {
  digitalWrite(m.in1, HIGH);
  digitalWrite(m.in2, LOW);
  digitalWrite(m.en, HIGH);
}

void driveReverse(const Map& m) {
  digitalWrite(m.in1, LOW);
  digitalWrite(m.in2, HIGH);
  digitalWrite(m.en, HIGH);
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("L293D shield test starting...");
  for (auto &m : maps) {
    pinMode(m.en, OUTPUT);
    pinMode(m.in1, OUTPUT);
    pinMode(m.in2, OUTPUT);
    driveStop(m);
  }
}

void loop() {
  for (auto &m : maps) {
    Serial.println();
    Serial.println(m.name);

    Serial.println("STOP 2s");
    driveStop(m);
    delay(2000);

    Serial.println("FORWARD 3s (measure across M1 terminals)");
    driveForward(m);
    delay(3000);

    Serial.println("STOP 2s");
    driveStop(m);
    delay(2000);

    Serial.println("REVERSE 3s (measure across M1 terminals)");
    driveReverse(m);
    delay(3000);

    Serial.println("STOP 2s");
    driveStop(m);
    delay(2000);
  }
}
