//Sketch do condutivimetro que imprime os resultados no Monitor Serial
float voltagem = 0.0; // Variaveis necessarias
long acumula;
long media;

void setup(void) {
  Serial.begin(115200);
  pinMode(2, OUTPUT); // O pino digital 2 sera utilizado
}

void loop(void) {
  acumula = 0;  // Zera o acumulador
  for (int contador = 0; contador < 100; contador++) // Faz 100 leituras
  {
    digitalWrite(2, HIGH); // Liga a tensao entre os eletrodos
    delay(10);    // Espera um tempo para a polarizacao
    int leitura = analogRead(A0); // Lê o pino analogico 0
    digitalWrite(2, LOW); // Desliga a tensao
    delay(10);    // Espera um tempo para a despolarizacao
    acumula = acumula + leitura; // Vai somando as leituras  
  }
  media = round(acumula / 100); // Tira a media
  voltagem = (media * 5 / 1024.0); // Converte o valor lido para voltagem
  Serial.print("Leitura = "); // Mostra o resultado
  Serial.print(media, 5);
  Serial.println(" Volts");
  delay(10000);  // Espera 10 segundos pra comecar tudo de novo
}
