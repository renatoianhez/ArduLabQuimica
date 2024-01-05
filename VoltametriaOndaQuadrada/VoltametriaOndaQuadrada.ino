#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads;
Adafruit_MCP4725 dac;
int Vi = 2000; // Tensao inicial (alterar se necessario)
int Vf = 3500; // Tensao final (alterar se necessario)
int Ampli = 30; // Amplitude do pulso (alterar se necessario)
long Vr; // Tensao resultante
int Vb; // Tensao-base
long Vma; // Tensao do pulso direto
long Vme; // Tensao do pulso reverso
long Volt1; // Tensao lida ao fim do pulso direto
long Volt2; // Tensao lida ao fim do pulso reverso
long CorrRes; // Corrente resultante
long Corr1; // Corrente lida ao fim do pulso direto
long Corr2; // Corrente lida ao fim do pulso reverso

void setup(void) {
  Serial.begin(115200);
  dac.begin(0x62);
  ads.begin(0x4A);
  Wire.setClock(400000);
}

void loop(void) {
  for (Vb = Vi; Vb < Vf; Vb = Vb + 1)
  {
    Vma = Vb + Ampli;
    dac.setVoltage(Vma, false);
    delayMicroseconds (500); // Tempo do pulso direto (alterar se necessario)
    Volt1 = ads.readADC_SingleEnded(0);
    Corr1 = ads.readADC_SingleEnded(1);
    Vme = Vb - 30;
    dac.setVoltage(Vme, false);
    delayMicroseconds (500); // Tempo do pulso inverso (alterar se necessario)
    Volt2 = ads.readADC_SingleEnded(0);
    Corr2 = ads.readADC_SingleEnded(1);
    CorrRes = Corr1 - Corr2;
    Vr = (Volt1 + Volt2) / 2;
    Serial.println("Tensao     Corrente");
    Serial.print(Vr);
    Serial.print("\t");
    Serial.println(CorrRes);
  }
  Serial.println("****FIM****");
  delay(5000);
}
