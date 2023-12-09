#include <Wire.h> // Bibliotecas para o I2C
#include <Adafruit_GFX.h> // Biblioteca para itens graficos (fontes, figuras)
#include <Adafruit_SSD1306.h> // Biblioteca da tela OLED
#include <Adafruit_NeoPixel.h> // Biblioteca do LED RGB
#define I2C_ADDRESS 0x3C // Endereco I2C da tela
Adafruit_NeoPixel ledRGB(1, 3, NEO_GRB + NEO_KHZ800); // Configura o LED
Adafruit_SSD1306 oled(128, 64, &Wire, -1); // Configura a tela OLED
int indice = 1; // Variáveis usadas
int leitura;
long acumula;
long media;

void setup() {
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Atencao ao endereco 0x3C
  oled.setTextColor(WHITE);               // pode ser diferente
  oled.setTextSize(1);
  pinMode(4, INPUT_PULLUP);
  oled.clearDisplay();
  ledRGB.begin();
}

void loop() {
  if (!digitalRead(4)) // Se o botao for apertado...
  {
    oled.clearDisplay();  // Apaga a tela
    delay(100);
    indice = indice + 1;    // Incrementa o indice de cores
    if (indice > 6) {
      indice = 1;
    }
  }
  oled.setCursor(10, 0);
  oled.print("Cor selecionada:");
  switch (indice)  // Mostra a cor selecionada
  {
    case 1:
      oled.setCursor(0, 20);
      oled.print("Violeta 380nm");
      oled.display();
      ledRGB.setPixelColor(1, ledRGB.Color(97, 0, 97));
      break;
    case 2:
      oled.setCursor(0, 20);
      oled.print("Azul 440nm");
      oled.display();
      ledRGB.setPixelColor(1, ledRGB.Color(255, 0, 0));
      break;
    case 3:
      oled.setCursor(0, 20);
      oled.print("Verde 500nm");
      oled.display();
      ledRGB.setPixelColor(1, ledRGB.Color(0, 255, 0));
      break;
    case 4:
      oled.setCursor(0, 20);
      oled.print("Amarelo 580nm");
      oled.display();
      ledRGB.setPixelColor(1, ledRGB.Color(0, 255, 255));
      break;
    case 5:
      oled.setCursor(0, 20);
      oled.print("Laranja 600nm");
      oled.display();
      ledRGB.setPixelColor(1, ledRGB.Color(0, 127, 255));
      break;
    case 6:
      oled.setCursor(0, 20);
      oled.print("Vermelho 700nm");
      oled.display();
      ledRGB.setPixelColor(1, ledRGB.Color(0, 0, 255));
      break;
  }
  acumula = 0;
  media = 0;
  delay(1000);
  for (int b = 0; b < 100; b++) {  // Faz 100 leituras...
    leitura = analogRead(A0);
    acumula = acumula + leitura;
    delay(1);
  }
  media = (int)(acumula / 100); // ... e calcula a media delas
  oled.clearDisplay();  // Mostra o resultado na tela
  oled.setCursor(0, 0);
  oled.print("  Leitura:  ");
  oled.setCursor(0, 20);
  oled.setTextSize(2);
  oled.print(media);
  oled.setTextSize(1);
  oled.setCursor(0, 45);
  oled.print("Anote. Apaga em 10s!");
  oled.display();
  delay(10000);
  oled.clearDisplay();
}
