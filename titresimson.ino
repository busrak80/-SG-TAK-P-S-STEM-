const int titresimPin = 4;  // Titresim sensoru sinyal pinini belirtin
const int titresimEsigi = 500;  // Belirli bir titresim esigini belirtin

void setup() {
  Serial.begin(9600);
  pinMode(titresimPin, INPUT);
}

void loop() {
  // Titresim sensorunden okuma yapin
  int titresimDegeri = analogRead(titresimPin);

  // Okunan degeri seri monitore yazdirin
  Serial.print("Titresim Degeri: ");
  Serial.println(titresimDegeri);
  delay(1000);

  // Belirli bir esik degeri asildiginda uyarı verin
  if (titresimDegeri > titresimEsigi) {
    Serial.println("Titresim esigi asildi!");

    // Burada başka bir uyarı veya işlem ekleyebilirsiniz.

    // Kısa bir bekleme süresi ekleyebilirsiniz, aynı titreşimin sürekli olarak rapor edilmesini önlemek için
    delay(1000);
  }

  // İsteğe bağlı olarak biraz bekleme ekleyebilirsiniz
  delay(100);
}
