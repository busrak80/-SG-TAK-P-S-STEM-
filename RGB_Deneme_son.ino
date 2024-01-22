int redPin = 4;
int greenPin = 12;
int bluePin = 13;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Kırmızı rengi aç
  analogWrite(redPin, 255);
  delay(1000);

  // Yeşil rengi aç
  analogWrite(greenPin, 255);
  delay(1000);

  // Mavi rengi aç
  analogWrite(bluePin, 255);
  delay(1000);

  // Tüm renkleri kapat
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
  delay(1000);
}
