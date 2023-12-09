#include <Wire.h>
#include <Adafruit_GFX.h> // Biblioteca para itens graficos (fontes, figuras)
#include <Adafruit_SSD1306.h> // Biblioteca da tela OLED

Adafruit_SSD1306 oled(128, 64, &Wire, -1); // Configura a tela OLED

float valorpH, VcalpH4, VcalpH7;

float Ler(int pinoBotao) {  // Rotina para fazer a leitura e cálculos
  long acumula = 0;
  while (!digitalRead(pinoBotao)) {
    delay(10);
  }
  for (int i = 0; i < 100; i++) {
    int leitura = analogRead(A0);
    delay(10);
    acumula = acumula + leitura;
  }
  return ((acumula / 100.0) * (5.0 / 1024.0)) - 2.5;
}

void setup() {
  pinMode(8, INPUT_PULLUP);
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Atencao ao endereco 0x3C
  oled.setTextColor(WHITE);               // pode ser diferente
  oled.setTextSize(1); // Tamanho da letra
  oled.clearDisplay(); // Limpa a tela
  oled.setCursor(0, 0); // Comeca a escrever nesta posicao
  oled.println("Calibracao pH 4"); // A calibração é feita no setup
  oled.setCursor(0, 16);
  oled.println("Mergulhe o eletrodo");
  oled.println("na solucao tampao");
  oled.println("de pH 4 e");
  oled.println("aperte o botao");
  oled.display(); // Mostra tudo na tela
  VcalpH4 = Ler(8);
  oled.clearDisplay();
  oled.setCursor(0, 20);
  oled.println("Tampao pH 4 lido");
  oled.display();
  delay(3000);
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println("Calibracao pH 7");
  oled.setCursor(0, 16);
  oled.println("Mergulhe o eletrodo");
  oled.println("na solucao tampao");
  oled.println("de pH 7 e");
  oled.println("aperte o botao");
  oled.display();
  VcalpH7 = Ler(8);
  oled.clearDisplay();
  oled.setCursor(0, 20);
  oled.println("Tampao pH 7 lido");
  oled.display();
  delay(3000);
}

void loop() {
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println("Medida de pH");
  oled.setCursor(0, 16);
  oled.println("Mergulhe o eletrodo");
  oled.println("na solucao para");
  oled.println("medir o pH e");
  oled.println("aperte o botao");
  oled.display();
  float medepH = Ler(8);
  valorpH = (((medepH - VcalpH7) * 3.0) / (VcalpH7 - VcalpH4)) + 7.0;
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println("   pH da solucao");
  oled.setCursor(20, 20);
  oled.setTextSize(2);
  oled.println(valorpH, 2);
  oled.display();
  oled.setTextSize(1);
  delay (10000);
}
