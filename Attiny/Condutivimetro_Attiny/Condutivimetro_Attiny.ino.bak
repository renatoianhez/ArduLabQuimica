#include <TinyWireM.h>
#include <Tiny4kOLED.h>
#include <Adafruit_NeoPixel.h>
#include <avr/io.h>
#define PIN 1 // Pino de controle do LED
#define NUMPIXELS 1 // So tem um mesmo

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int index = 1;
int leitura = 1;
long acumula;
float conta = 0.0;
int media;

void setup() {
  oled.begin(); // Inicia OLED
  oled.setFont(FONT6X8); // Seleciona a fonte
  oled.clear(); // Limpa a memoria do OLED
  oled.on(); // Liga o OLED
  pixels.begin(); // Inicia o LED
  // Define botoes
  pinMode(4, INPUT);
  pinMode(A3, INPUT);
}

void loop() {
  if (digitalRead(4))
  {
    oled.clear();
    delay(100);
    index = index + 1;
    if (index > 6) {
      index = 1;
    }
  }
  oled.setCursor(0, 0);
  switch (index)
  {
    case 1:
      oled.print(F("Violeta 380nm"));
      pixels.setPixelColor(0, pixels.Color(97, 0, 97));
      Mede();
      break;
    case 2:
      oled.print(F("Azul 440nm"));
      pixels.setPixelColor(0, pixels.Color(0, 0, 255));
      Mede();
      break;
    case 3:
      oled.print(F("Verde 500nm"));
      pixels.setPixelColor(0, pixels.Color(0, 255, 0));
      Mede();
      break;
    case 4:
      oled.print(F("Amarelo 580nm"));
      pixels.setPixelColor(0, pixels.Color(255, 255, 0));
      Mede();
      break;
    case 5:
      oled.print(F("Laranja 600nm"));
      pixels.setPixelColor(0, pixels.Color(255, 127, 0));
      Mede();
      break;
    case 6:
      oled.print(F("Vermelho 700nm"));
      pixels.setPixelColor(0, pixels.Color(255, 0, 0));
      Mede();
      break;
  }
}

void Mede()
{
  pixels.show();
  acumula = 0;
  media = 0;
  for (int b = 0; b < 100; b++) {
    leitura = analogRead(A3);
    acumula = acumula + leitura;
    delay(1);
  }
  conta = acumula / 8;
  media = abs(conta);
  oled.setCursor(0, 1);
  oled.print(F("Leitura:"));
  oled.setCursor(0, 2);
  oled.setFont(FONT8X16);
  oled.println(F("      "));
  oled.print(media);
  delay(1000);
  oled.setFont(FONT6X8);
}
