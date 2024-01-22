#include <DHT.h>
#include <Adafruit_PCD8544.h>

#define DHT_PIN 8
#define VIBRATION_SENSOR_PIN A1

#define SCLK_PIN 7
#define DIN_PIN 6
#define DC_PIN 5
#define CS_PIN 4
#define RST_PIN 3

DHT dht(DHT_PIN, DHT11);

Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK_PIN, DIN_PIN, DC_PIN, CS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);

  dht.begin();
  display.begin();
  
  display.setContrast(60); // Ekran kontrastını ayarlayabilirsiniz
  display.clearDisplay();
}

void loop() {
  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  int vibrationValue = analogRead(VIBRATION_SENSOR_PIN);

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("DHT okuma hatasi");
    return;
  }

  Serial.print("Sicaklik: ");
  Serial.println(temperature);
  Serial.print("Nem: ");
  Serial.println(humidity);
  Serial.print("Titresim: ");
  Serial.println(vibrationValue);

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(BLACK);

  display.setCursor(0,0);
  display.print("Sicaklik: ");
  display.print(temperature);
  display.print("C");

  display.setCursor(0,10);
  display.print("Nem: ");
  display.print(humidity);
  display.print("%");

  display.setCursor(0,20);
  display.print("Titresim: ");
  display.print(vibrationValue);

  display.display();

  // Yazıları kaydırarak ekranın sığma sorununu çöz
  for (int i = 0; i < 84; i++) {
    display.scroll(-1, 0);
    delay(50);
    display.display();
  }
}
