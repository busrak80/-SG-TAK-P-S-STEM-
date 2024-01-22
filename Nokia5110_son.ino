#include <U8g2lib.h>
#include <Wire.h>

U8G2_PCD8544_84X48_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 3, /* data=*/ 4, /* cs=*/ 5, /* dc=*/ 6, /* reset=*/ 7);

void setup() {
  Serial.begin(9600);

  // Ekranı başlat
  u8g2.begin();
}

void loop() {
  // Ekran temizle
  u8g2.clearBuffer();

  // Yazıyı ekrana yazdır
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 10, "ISG Takip Sistemi");

  // Ekranı güncelle
  u8g2.sendBuffer();

  // Yazıyı Serial Monitor'a yazdır
  Serial.println("ISG Takip Sistemi");

  // Bir süre bekleyin
  delay(2000);
}
