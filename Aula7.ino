
/************************************************************/
/* Aula 07 - Painel de Senhas com display LCD 16x2 I2C      */
/************************************************************/

/* Carrega as bibliotecas necessárias                       */
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

/* Configura o endereço do LCD para 0x27 com 16 colunas e 2 linhas */
/* Se não funcionar com 0x27, tente 0x3F.                         */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Definições das portas utilizadas                         */
#define botao_DOWN 6
#define botao_UP 7
#define buzzer 8

/* Variável que armazenará a senha                          */
int senha = -1;

void setup() {
  /* Inicializa o LCD I2C                                   */
  lcd.init();
  /* Liga a luz de fundo do LCD                             */
  lcd.backlight();

  /* Configura os pinos dos botões como entrada PULLUP      */
  pinMode(botao_UP, INPUT_PULLUP);
  pinMode(botao_DOWN, INPUT_PULLUP);
  
  /* Configura o pino do buzzer como saída                  */
  pinMode(buzzer, OUTPUT);

  /* Inicia com a senha zero                                */
  chamar(+1);
}

void loop() {
  /* Se pressionar o botão UP                               */
  if (digitalRead(botao_UP) == LOW) {
    chamar(+1);
    delay(300); // Debounce simples para evitar múltiplas contagens
  }
  
  /* Se pressionar o botão DOWN                             */
  if (senha > 0 && digitalRead(botao_DOWN) == LOW) {
    chamar(-1);
    delay(300); // Debounce simples
  }
}

/* Função responsável por imprimir a senha no display       */
void chamar(int botao) {
  // Efeito sonoro
  tone(buzzer, 236, 250);
  delay(250);
  tone(buzzer, 2093, 400);
  delay(400);

  senha = senha + botao;
  
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("Painel de Senhas");
  
  lcd.setCursor(0, 1); 
  lcd.print("Senha: ");
  lcd.print(senha); // Mais eficiente que concatenar String
}
