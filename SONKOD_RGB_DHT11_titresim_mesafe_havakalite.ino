#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <DHT.h>

const int AOUTpin = A0;    // Analog çıkış pini (Hava kalitesi sensörü)
const int DOUTpin = 3;    // Dijital çıkış pini (Hava kalitesi sensörü)
int ppm;                    // Ölçülen ppm değeri (Hava kalitesi sensörü)
int esikDurumu;             // Eşik değeri durumu (aşıldı/aşılmadı - Hava kalitesi sensörü)

#define SCLK_PIN   11
#define DIN_PIN    10
#define DC_PIN     9
#define CS_PIN     8
#define RST_PIN    7

#define DHTPIN 2
#define DHTTYPE DHT11

#define VIBRATION_SENSOR_PIN A1
#define TRIGGER_PIN 5
#define ECHO_PIN 6

int redPin = 4;    // Kırmızı pin
int greenPin = 12;  // Yeşil pin
int bluePin = 13;   // Mavi pin

DHT dht(DHTPIN, DHTTYPE);
Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK_PIN, DIN_PIN, DC_PIN, CS_PIN, RST_PIN);

const float TEMPERATURE_THRESHOLD = 25.0;  // Sıcaklık eşik değeri
const float HUMIDITY_THRESHOLD = 50.0;    // Nem eşik değeri
const int VIBRATION_THRESHOLD = 500;      // Titreşim eşik değeri
const float DISTANCE_THRESHOLD = 10.0;    // Mesafe eşik değeri
const int POLLUTION_THRESHOLD = 200;      // Kirlilik eşik değeri

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
  pinMode(DOUTpin, INPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

}

void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

float getDistance() {
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration / 2.0) * 0.0343;
  return distance;
}



void displayAndWait(String text, int waitTime) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(text);
  display.display();
  Serial.println(text);  // Serial monitöre yaz
  setColor(0, 0, 0);
  delay(waitTime);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  int vibrationValue = analogRead(VIBRATION_SENSOR_PIN);
  float distance = getDistance();

  ppm = analogRead(AOUTpin);

  if (temperature > TEMPERATURE_THRESHOLD) {
    String warning = "Sicaklik esik degeri asildi! (" + String(TEMPERATURE_THRESHOLD) + ")";
    displayAndWait(warning, 3000);
   // Kırmızı rengi göster
    setColor(255, 0, 0);
    delay(1000);
  } else {
    displayAndWait("Sicaklik: " + String(temperature) + " C", 5000);
  }

  if (humidity > HUMIDITY_THRESHOLD) {
    String warning = "Nem esik degeri asildi! (" + String(HUMIDITY_THRESHOLD) + ")";
    displayAndWait(warning, 3000);
    // Yeşil rengi göster
    setColor(0, 255, 0);
    delay(1000);
  } else {
    displayAndWait("Nem: " + String(humidity) + "%", 5000);
  }

  if (vibrationValue > VIBRATION_THRESHOLD) {
    String warning = "Titreşim esik degeri asildi! (" + String(VIBRATION_THRESHOLD) + ")";
    displayAndWait(warning, 3000);
    // Mavi rengi göster
    setColor(0, 0, 255);
    delay(1000);

  } else {
    displayAndWait("Titresim: " + String(vibrationValue), 5000);
  }

  if (distance < DISTANCE_THRESHOLD) {
    String warning = "Mesafe esik degeri asildi! (" + String(DISTANCE_THRESHOLD) + ")";
    displayAndWait(warning, 3000);
    // Sarı rengi göster (kırmızı ve yeşil karışımı)
    setColor(255, 255, 0);
    delay(1000);
  } else {
    displayAndWait("Mesafe: " + String(distance) + " cm", 5000);
  }

  if (ppm > POLLUTION_THRESHOLD) {
    String warning = "Hava kirliligi esik degeri asildi! (" + String(POLLUTION_THRESHOLD) + ")";
    displayAndWait(warning, 3000);
    // Mor rengi göster (kırmızı ve mavi karışımı)
    setColor(255, 0, 255);
    delay(1000);

  } else {
    displayAndWait("Hava Kirliligi: " + String(ppm), 5000);
  }

  setColor(0, 0, 0);
  delay(1000);
}
