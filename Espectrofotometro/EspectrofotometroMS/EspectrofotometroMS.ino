//Este sketch realiza a leitura do espectrofotometro e 
//imprime os resultados no Monitor Serial
float voltagem = 0.0; // Variaveis necessarias
long acumula;
float media;

void setup(void) {
  Serial.begin(9600);
  pinMode(2, OUTPUT); // O pino digital 2 sera utilizado pra ligar o LED
}

void loop(void) {
  acumula = 0;  // Zera o acumulador
  digitalWrite(2, HIGH); // Liga o LED
  for (int contador = 0; contador < 100; contador++) // Faz 100 leituras
  {

    int leitura = analogRead(A0); // Lê o pino analogico 0
    acumula = acumula + leitura; // Vai somando as leituras  
    delay(10);    // Espera um tempo entre uma leitura e outra
  }
  digitalWrite(2, LOW); // Desliga o LED
  media = acumula/100; Calcula a media das 100 leituras
  Serial.print("Leitura: ");  // Escreve o resultado
  Serial.println(media, 2);   // com duas casa decimais
  delay(2000);  // Aguarda 2s para a proxima leitura
}
