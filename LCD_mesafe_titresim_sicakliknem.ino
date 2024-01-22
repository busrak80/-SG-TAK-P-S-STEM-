#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h>

#define SCLK_PIN   7
#define DIN_PIN    6
#define DC_PIN     5
#define CS_PIN     4
#define RST_PIN    3

#define DHTPIN 8 //DHT11 sensörünün bağlı olduğu pin
#define DHTTYPE DHT11

#define VIBRATION_SENSOR_PIN A0  // Titreşim sensörünün bağlandığı pin
#define TRIGGER_PIN 9  // Ultrasonik sensörün tetik pin numarası
#define ECHO_PIN 10    // Ultrasonik sensörün echo pin numarası

DHT dht(DHTPIN, DHTTYPE);
Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK_PIN, DIN_PIN, DC_PIN, CS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  dht.begin();
  display.begin();
  display.setContrast(60);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

float getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration / 2.0) * 0.0343; // Hava ortamında ses hızı 343 m/s
  return distance;
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int vibrationValue = analogRead(VIBRATION_SENSOR_PIN);
  float distance = getDistance();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Sicaklik: ");
  display.print(temperature);
  display.println(" C");
  display.print("Nem: ");
  display.print(humidity);
  display.println("%");
  display.print("Titresim: ");
  display.println(vibrationValue);
  display.print("Mesafe: ");
  display.print(distance);
  display.println(" cm");

  display.display();
  delay(1000);
}
