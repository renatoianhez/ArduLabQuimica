#include <TinyWireM.h>
#include <Tiny4kOLED.h>
#include <avr/io.h>

float valor = 0.0;
float cK = 0.0;

float Mede() {
  long ac = 0;
  int lt = 0;
  for (int b = 0; b < 100; b++) {
    digitalWrite(4, HIGH);
    delay(10);
    int lt = analogRead(A3);
    digitalWrite(4, LOW);
    ac = ac + lt;
    delay(10);
  }
  return (float)ac*0.004888/100.0;
}

void setup() {
  oled.begin();
  oled.setFont(FONT6X8);
  oled.clear();
  oled.on();
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(1, INPUT_PULLUP);
  pinMode(A3, INPUT);
  oled.setCursor(0, 0);
  oled.println(F("Leitura do padrao"));
  oled.println(F("Coloque o eletrodo"));
  oled.println(F("na solucao padrao"));
  oled.println(F("e aperte o botao."));
  while (digitalRead(1) == LOW) {
    delay(10);
  }
  oled.clear();
  oled.setFont(FONT6X8);
  oled.print(F("Aguarde a leitura"));
  float Rx = Mede();
  float mK = (100.0*Rx)/(5.0-Rx);
  cK = 1408.0 / mK;
  oled.clear();
  oled.setCursor(0, 0);
  oled.println(F("Padrao lido"));
  oled.println(F("Constante K:"));
  oled.setFont(FONT8X16);
  oled.print(cK, 4);
  delay(5000);
}

void loop() {
  oled.clear();
  oled.setFont(FONT6X8);
  oled.print(F("Aguarde a leitura"));
  float Rsol = Mede();
  float mC = (100.0*Rsol)/(5.0-Rsol);
  valor = mC * cK;
  oled.clear();
  oled.setCursor(0, 0);
  oled.print(F("Leitura:"));
  oled.setCursor(0, 1);
  oled.setFont(FONT8X16);
  oled.print(valor);
  oled.setFont(FONT6X8);
  oled.println(F(" uS/cm"));
  delay(1000);
  oled.setCursor(0, 3);
  oled.print(F("Nova: aperte o botao"));
  while (digitalRead(1) == LOW) {
    delay(10);
  }
}
