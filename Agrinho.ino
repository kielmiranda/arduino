/* Programa: Acionar motor com push button
 * Projeto: Recicla Ostra
 * Relé: JQC-3FF-S-Z (5VDC)
 */

int pino_botao = 3;      // Push button no pino 3
int pino_rele = 2;       // Relé no pino 2
int pino_led_verde = 4;  // LED verde (pronto)
int pino_led_vermelho = 5; // LED vermelho (moendo)

boolean estado_rele = LOW;      // LOW = relé desligado, motor parado
int ultimo_estado_botao = HIGH; // INPUT_PULLUP: HIGH quando não apertado

void setup() {
  pinMode(pino_botao, INPUT_PULLUP);  // Usa resistor interno do Arduino
  pinMode(pino_rele, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);
  pinMode(pino_led_vermelho, OUTPUT);
  
  // Estado inicial: motor desligado, LED verde aceso
  digitalWrite(pino_rele, LOW);
  digitalWrite(pino_led_verde, HIGH);
  digitalWrite(pino_led_vermelho, LOW);
}

void loop() {
  int estado_botao = digitalRead(pino_botao);
  
  // Detecta quando o botão foi pressionado (mudou de HIGH para LOW)
  if (estado_botao == LOW && ultimo_estado_botao == HIGH) {
    
    // Inverte o estado do relé
    estado_rele = !estado_rele;
    digitalWrite(pino_rele, estado_rele);
    
    // Atualiza os LEDs
    if (estado_rele == HIGH) {
      digitalWrite(pino_led_verde, LOW);
      digitalWrite(pino_led_vermelho, HIGH);  // Moendo
    } else {
      digitalWrite(pino_led_verde, HIGH);     // Pronto
      digitalWrite(pino_led_vermelho, LOW);
    }
    
    delay(200);  // Debounce do botão
  }
  
  ultimo_estado_botao = estado_botao;
}