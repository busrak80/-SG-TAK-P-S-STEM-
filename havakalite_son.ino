const int mqPin = A0;  // MQ-135 sensörünün analog pinini belirtin
const int ppmThreshold = 200;  // Belirli bir PPM eşiğini belirtin

void setup() {
  Serial.begin(9600);
}

void loop() {
  // MQ-135 sensöründen analog değeri okuyun
  int mqValue = analogRead(mqPin);

  // Analog değeri PPM cinsine dönüştürün (Bu değeri datasheet'e göre ayarlamalısınız)
  float ppmValue = map(mqValue, 0, 1023, 0, 1000);  

  // Hava kalite değerini seri monitöre yazdırın
  Serial.print("Hava Kalite Değeri: ");
  Serial.print(ppmValue);
  Serial.println(" ppm");

  // Belirli bir PPM eşiği aşıldığında uyarı verin
  if (ppmValue > ppmThreshold) {
    Serial.println("Uyarı: Hava kalitesi düşük!");

    // Burada başka bir uyarı veya işlem ekleyebilirsiniz.

    // Kısa bir bekleme süresi ekleyebilirsiniz, aynı uyarının sürekli olarak rapor edilmesini önlemek için
    delay(1000);
  }

  // İsteğe bağlı olarak biraz bekleme ekleyebilirsiniz
  delay(1000);
}
