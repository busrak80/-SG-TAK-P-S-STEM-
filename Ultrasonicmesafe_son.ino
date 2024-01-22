#define trigPin 5  // Ultrasonik sensörün trig pinini belirtin
#define echoPin 6  // Ultrasonik sensörün echo pinini belirtin
#define esikMesafe 50  // Belirli bir eşik mesafeyi belirtin (örneğin, 50 cm)

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Ultrasonik sensörden mesafe okuma
  long sure, mesafe;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  sure = pulseIn(echoPin, HIGH);
  mesafe = sure * 0.034 / 2;

  // Mesafeyi seri monitöre yazdırma
  Serial.print("Mesafe: ");
  Serial.print(mesafe);
  Serial.println(" cm");

  // Belirli bir eşik mesafeyi aştığında uyarı verme
  if (mesafe < esikMesafe) {
    Serial.println("Uyarı: Tehlikeli alana girdiniz yaklaşmayın !");

    // Burada başka bir uyarı veya işlem ekleyebilirsiniz.

    // Kısa bir bekleme süresi ekleyebilirsiniz, aynı uyarının sürekli olarak rapor edilmesini önlemek için
    delay(1000);
  }

  // İsteğe bağlı olarak biraz bekleme ekleyebilirsiniz
  delay(1000);
}
