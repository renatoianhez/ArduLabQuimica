#include <Wire.h> // Bibliotecas para o I2C
#include <Adafruit_GFX.h> // Biblioteca para itens graficos (fontes, figuras)
#include <Adafruit_SSD1306.h> // Biblioteca da tela OLED
#include <SPI.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1); // Configura a tela OLED

float valor = 0.0;
float constanteK = 0.0;
const float converte = 0.004888;

float Mede() {
  long acumula = 0;
  int leitura = 0;
  for (int b = 0; b < 100; b++) {
    digitalWrite(4, HIGH);
    delay(10);
    leitura = analogRead(A0);
    digitalWrite(4, LOW);
    acumula = acumula + leitura;
    delay(10);
  }
  float media = (float)acumula/100.0;
  return media*converte;
}

void setup() {
  Wire.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Endereco I2C 0x3C
  oled.setTextColor(WHITE);
  pinMode(3, INPUT_PULLUP);
  pinMode(2, OUTPUT);
  pinMode(A0, INPUT);
  oled.clearDisplay();
  digitalWrite(2, LOW);
  oled.setTextSize(1);
  oled.setCursor(0, 0);
  oled.println("Calibracao");
  oled.setCursor(0, 16);
  oled.println("Coloque o eletrodo na");
  oled.println("solucao a 1408uS/cm");
  oled.println("e aperte o botao.");
  oled.display();
  while (digitalRead(3) == LOW) {
    delay(10);
  }
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.print("Aguarde a leitura");
  oled.display();
  float Rx = Mede();
  float medidaK = (100.0*Rx)/(5.0-Rx);
  constanteK = 1408.0 / medidaK;
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.println("Padrao lido");
  oled.println("Constante K:");
  oled.setTextSize(2);
  oled.setCursor(0, 20);
  oled.print(constanteK);
  oled.display();
  delay(5000);
}

void loop() {
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(1);
  oled.print("Aguarde a leitura");
  oled.display();
  float Rsol = Mede();
  float medidaC = (100.0*Rsol)/(5.0-Rsol);
  valor = medidaC * constanteK;
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.print("Leitura:");
  oled.setCursor(0, 20);
  oled.setTextSize(2);
  oled.print(valor);
  oled.setTextSize(1);
  oled.println(" uS/cm");
  oled.display();
  delay(1000);
  oled.setCursor(0, 48);
  oled.print("Nova: aperte o botao");
  oled.display();
  while (digitalRead(3) == LOW) {
    delay(10);
  }
}
