#include <DHT.h>

int redPin = 10;    // Kırmızı pin
int greenPin = 11;  // Yeşil pin
int bluePin = 12;   // Mavi pin

int sensorPin = 8;  // DHT11 sensörü pin

DHT dht(sensorPin, DHT11);

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Sıcaklık: ");
  Serial.println(temperature);

  Serial.print("Nem: ");
  Serial.println(humidity);

  if (!isnan(temperature) && !isnan(humidity)) {
    if (temperature > 25) {  // Sıcaklık eşik değeri
      setColor(255, 0, 255); // Mor
    } else if (humidity > 60) {  // Nem eşik değeri
      setColor(0, 255, 255);     // Turkuaz
    } else {
      setColor(255, 255, 255);  // Beyaz
    }
  }

  delay(1000);  // 1 saniye bekleyin, sensör değerlerini sık sık okumamak için
}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);     // Kırmızı rengi ayarla
  analogWrite(greenPin, green); // Yeşil rengi ayarla
  analogWrite(bluePin, blue);   // Mavi rengi ayarla
}
