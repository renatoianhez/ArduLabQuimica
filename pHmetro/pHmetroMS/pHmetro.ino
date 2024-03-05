float valorpH, VcalpH4, VcalpH7;

float Ler(int pinoBotao) {  // Rotina para ler e calcular a média em volts
  long acumula = 0;
  while (!digitalRead(pinoBotao)) {  // O programa só continua se o botão for pressionado
    delay(10);
  }
  for (int i = 0; i < 100; i++) {  // Faz 100 leituras
    int leitura = analogRead(A0);
    delay(10);
    acumula = acumula + leitura;
  }
  return ((acumula / 100.0) * (5.0 / 1024.0)) - 2.5;  // Faz o calculo e retorna o valor final
}

void setup() {
  pinMode(8, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Mergulhe o eletrodo na solução tampão de pH 4 e aperte o botão");  // Calibracao no pH 4
  VcalpH4 = Ler(8);
  Serial.println("Calibração do pH 4 realizada");
  delay(2000);
  Serial.println("Mergulhe o eletrodo na solução tampão de pH 7 e aperte o botão"); // Calibracao no pH 7
  VcalpH7 = Ler(8);
  Serial.println("Calibração do pH 7 realizada");
  delay(2000);
}

void loop() {  // Mede o pH e apresenta o valor final
  Serial.println("Mergulhe o eletrodo na solução que se quer medir o pH e aperte o botão");
float medepH = Ler(8);
  valorpH = (((medepH - VcalpH7)*3.0)/(VcalpH7-VcalpH4))+7.0;
  Serial.print("O valor do pH é: ");
  Serial.println(valorpH, 2);
}
