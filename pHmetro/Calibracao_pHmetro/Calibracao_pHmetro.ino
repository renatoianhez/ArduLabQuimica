int valor_pH;
float Voltagem;

void setup() 
{ 
  Serial.begin(9600);
} 
 
void loop() 
{ 
  valor_pH = analogRead(A0);  // recebe o valor do modulo
  Voltagem = valor_pH * (5.0 / 1023.0); // passa para volts
  Serial.println(Voltagem); // imprime do Monitor Serial
  delay(500); 
}
