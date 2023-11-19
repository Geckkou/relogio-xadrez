#include <LiquidCrystal.h>              //Permite a comunicação com displays alfanuméricos de cristal líquido (LCDs).
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  //LCD(RS, E, D4, D5, D6, D7)



const int buzzer = 9;  //Variável para o buzzer
int b = 20;            //Variável para o tempo de delay dos botões (efeito boucing)
int cont = 0;          //Variável para o contador que muda de tela
int confirma = 0;      //Variável para a tecla confirma
int botaomin1 = 0;     //Variável para o botao de ajuste dos minutos
int botaoseg1 = 0;     //Variável para o botao de ajuste dos segundos
int botaobranco = 0;   //Variável para o botao de inicio do tempo do jogador 1
int botaoazul = 0;     //Variável para o botao de inicio do tempo di jogador 2

int tempoini = 0;   //Variável para o tempo de acréscimo
int segundos1 = 0;  //Variável para os segundos do jogador 1
int minutos1 = 0;   //Variável para os minutos do jogador 1
int segundos2 = 0;  //Variável para os segundos do jogador 2
int minutos2 = 0;   //Variável para os minutos do jogador 2

int botaoreset = 0;  //Variável para o botao de resetar
int x = 0;           //contador para setar se é a primeira vez do botão 1 (p/ contar acréscimo)
int y = 0;           //contador para setar se é a primeira vez do botão 2 (p/ contar acréscimo)

int botaorestart = 0;  //Variável para o botão restart

void setup() {

  //Inicialização do LCD
  lcd.begin(16, 2);  //LCD com 16 colunas e 2 linhas

  //Mensagem de inicio no Display
  lcd.setCursor(2, 0);   //seta o cursor
  lcd.print("Relogio");  //Mensagem de boas vindas com efeito scroll
  lcd.setCursor(2, 1);
  lcd.print("  Xadrez");
  delay(3000);
  //Leva para esquerda (Efeito de Scroll)
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft();
    delay(100);
  }

  lcd.clear();  //Limpa o LCD

  //Definição das entradas e saídas
  //INPUT_PULLUP não precisa usar resistor nos botões (Resistor interno de pullup do arduino)
  //Dessa forma elimina o efeito Bouncing
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, OUTPUT);
  pinMode(buzzer, OUTPUT);
}




void loop() {
  //Primeira rotina para o botão confirma
  confirma = digitalRead(A3);  //Leitura na entrada digital
  if (confirma == HIGH) {
    cont = cont + 1;  //Contador para contagem de telas
    delay(b);
  }



  //----------------------------- (0) - Primeira tela do menu - Ajuste de acréscimo
  while (cont == 0) {  //Enquanto o contador for = 0 ele vai ficar na primeira tela do menu

    botaobranco = digitalRead(6);  //Se apertar o botão branco vai para a tela de contagem
    if (botaobranco == LOW) {
      cont = 4;

      delay(b);
    }

    confirma = digitalRead(A3);  //Se apertar o botão confirma vai para a tela de ajuste do jogador
    if (confirma == HIGH) {
      cont = cont + 1;
      delay(b);
    }

    botaoreset = digitalRead(A4);  //Se apertar o botão reseta zera os valores [função void reseta()]
    if (botaoreset == HIGH) {
      reseta();
      delay(b);
    }

    lcd.clear();  //rotina da tela de ajuste de acréscimo
    lcd.setCursor(0, 0);
    lcd.print("Ajuste acrescimo");
    lcd.setCursor(0, 1);

    botaomin1 = digitalRead(A1);
    if (botaomin1 == HIGH) {
      tempoini = tempoini + 1;
      delay(b);
    }

    lcd.print("00:0");
    lcd.print(tempoini);
    delay(100);
  }


  //-------------------------------(1) Segunda tela: Jogador 1

  while (cont == 1) { //Enquanto o contador for = 1 ele vai ficar na tela do Jogador 1
    confirma = digitalRead(A3);  //Se apertar o botão confirma vai para a tela de ajuste do jogador 2

    if (confirma == HIGH) {
      cont = cont + 1;
      delay(b);
    }

    botaoreset = digitalRead(A4);  //Se apertar o botão reseta zera os valores [função void reseta()]
    if (botaoreset == HIGH) {
      reseta();
      delay(b);
    }

    lcd.clear();  //rotina da tela do jogador 1
    botaomin1 = digitalRead(A1);

    // Incremento dos minutos
    if (botaomin1 == HIGH) {
      minutos1 = minutos1 + 1;
      delay(b);
    }

    //Incremento dos segundos
    botaoseg1 = digitalRead(A2);
    if (botaoseg1 == HIGH) {
      segundos1 = segundos1 + 1;
      delay(b);
    }

    lcd.setCursor(0, 0);
    lcd.print("Jogador1:");
    lcd.setCursor(11, 0);
    if (minutos1 < 10) { lcd.print("0"); } //Se os minutos forem < 10 vai printar um 0 na frente (visual apenas 01:00)
    lcd.print(minutos1);
    lcd.print(":");
    if (segundos1 < 10) { lcd.print("0"); } //Se os segundos forem < 10 vai printar um 0 na frente (visual apenas 00:01)
    lcd.print(segundos1);
    delay(100);
  }

  //---------------------------------(2) - Terceira tela - Jogador 2

  while (cont == 2) {  //Enquanto o contador for = 2 ele vai ficar na tela do Jogador 2
    confirma = digitalRead(A3); //Se apertar o botão confirma vai para a tela de inicio do jogo
    if (confirma == HIGH) {
      cont = cont + 1;
      delay(b);
    }
    botaoreset = digitalRead(A4);  //Se apertar o botão reseta zera os valores [função void reseta()]
    if (botaoreset == HIGH) {
      reseta();
      delay(b);
    }
    lcd.clear();  //Rotina da tela jogador 2

    //Incremento dos minutos
    botaomin1 = digitalRead(A1);
    if (botaomin1 == HIGH) {
      minutos2 = minutos2 + 1;
      delay(b);
    }

    //Incremento dos segundos
    botaoseg1 = digitalRead(A2);
    if (botaoseg1 == HIGH) {
      segundos2 = segundos2 + 1;
      delay(b);
    }
    lcd.setCursor(0, 1);
    lcd.print("Jogador2:");
    lcd.setCursor(11, 1);
    if (minutos2 < 10) { lcd.print("0"); } //Se os minutos forem < 10 vai printar um 0 na frente (visual apenas 01:00)
    lcd.print(minutos2);
    lcd.print(":");
    if (segundos2 < 10) { lcd.print("0"); } //Se os segundos forem < 10 vai printar um 0 na frente (visual apenas 00:01)
    lcd.print(segundos2);
    delay(100);
  }
  //---------------------------------------(4) Quarta tela - Aparece tempo dos dois jogadores (tela de início do tempo)
  while (cont == 3) { //Enquanto o contador for = 3 ele vai ficar na tela de tempo dos dois jogadores

    confirma = digitalRead(A3);  //Se apertar o botão confirma vai para a tela de inicio do jogo
    if (confirma == HIGH) {
      cont = 0;
      delay(b);
    }

    botaoreset = digitalRead(A4);  //Se apertar o botão reseta zera os valores [função void reseta()]
    if (botaoreset == HIGH) {
      reseta();
      delay(b);
    }

    botaobranco = digitalRead(6);  //Se apertar o botão branco começa contar o tempo do jogador 1
    if (botaobranco == LOW) {
      cont = 4;
      delay(100);
    }

    botaoazul = digitalRead(7);  //Se apertar o botão azul começa contar o tempo do jogador 2
    if (botaoazul == LOW) {
      cont = 5;
      delay(100);
    }

    lcd.setCursor(0, 0);  //Rotina para apresentar o tempo do jogador 1
    lcd.print("Jogador1:");
    lcd.setCursor(11, 0);
    if (segundos1 > 60) { //Apresentação do tempo
      segundos1 = segundos1 - 60;
      minutos1 = minutos1 + 1;
    }
    if (minutos1 < 10) { lcd.print("0"); } //Se os minutos forem < 10 vai printar um 0 na frente (visual apenas 01:00)
    lcd.print(minutos1);
    lcd.print(":");
    if (segundos1 < 10) { lcd.print("0"); } //Se os segundos forem < 10 vai printar um 0 na frente (visual apenas 00:01)
    lcd.print(segundos1);


    lcd.setCursor(0, 1);  //Rotina para apresentar o tempo do jogador 2
    lcd.print("Jogador2:");
    lcd.setCursor(11, 1);
    if (segundos2 > 60) { //Apresentação do tempo
      segundos2 = segundos2 - 60;
      minutos2 = minutos2 + 1;
    }
    if (minutos2 < 10) { lcd.print("0"); } //Se os minutos forem < 10 vai printar um 0 na frente (visual apenas 01:00)
    lcd.print(minutos2);
    lcd.print(":");
    if (segundos2 < 10) { lcd.print("0"); } //Se os segundos forem < 10 vai printar um 0 na frente (visual apenas 00:01)
    lcd.print(segundos2);
    delay(100);
  }
  //-----------------------------------(5) Quinta tela - tempo 1 contando

  while (cont == 4) { //Enquanto o contador for = 4 ele vai ficar na tela de contagem de tempo


    botaobranco = digitalRead(6);  //Se apertar o botão branco para o tempo e 1 volta para a quarta tela
    if (botaobranco == LOW) {
      cont = 3;
      x++;
      if (x > 0) {  //Somente na segunda vez que o botão for acionado vai somar o acréscimo
        segundos1 = segundos1 + tempoini;
      }
      delay(20);
      tone(buzzer, 2581, 500);
      delay(50);
      //Desligando o buzzer.
      noTone(buzzer);
    }



    segundos1--;  //Rotina decrescendo o tempo 1


    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Jogador1: ");
    lcd.print("*");
    if (minutos1 < 10) { lcd.print("0"); } //Se os minutos forem < 10 vai printar um 0 na frente (visual apenas 01:00)
    lcd.print(minutos1);
    lcd.print(":");
    if (segundos1 < 10) { lcd.print("0"); } //Se os segundos forem < 10 vai printar um 0 na frente (visual apenas 00:01)
    lcd.print(segundos1);
    if (segundos1 == 0) { //Contagem decrescente do tempo
      segundos1 = 60;
      minutos1--;
    }

    if (segundos1 == -1) { //Mostra 59 segundos inves de 60
      segundos1 = 59;
      minutos1--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(minutos1);
      lcd.print(":59");
    }


    lcd.setCursor(0, 1);  //tempo 2 se apresenta parado até chegar avez do jogador 2
    lcd.print("Jogador2:  ");
    if (minutos2 < 10) { lcd.print("0"); } //Se os minutos forem < 10 vai printar um 0 na frente (visual apenas 01:00)
    lcd.print(minutos2);
    lcd.print(":");
    if (segundos2 < 10) { lcd.print("0"); } //Se os segundos forem < 10 vai printar um 0 na frente (visual apenas 00:01)
    lcd.print(segundos2);
    if (segundos2 == 0) { //Contagem decrescente do tempo
      segundos2 = 60;
      minutos2--;
    }

    if (segundos2 == -1) { //Mostra 59 segundos inves de 60
      segundos2 = 59;
      minutos2--;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(minutos2);
      lcd.print(":59");
    }

    if (minutos1 < 0) {
      fim1();
    }

    delay(1000);
  }

  //-------------------------------------(6) Sexta tela - tempo 2 contando


  while (cont == 5) { //Enquanto o contador for = 5 ele vai ficar na tela de contagem de tempo 2

    botaoreset = digitalRead(A4);  // Se apertar o botão reseta zera os valores [void reseta()]
    if (botaoreset == HIGH) {
      reseta();
      delay(b);
    }

    botaoazul = digitalRead(7);  //Se apertar o botão azul para o tempo e vai para a a quarta tela
    if (botaoazul == LOW) {
      cont = 3;
      y++;
      if (y > 0) {
        segundos2 = segundos2 + tempoini;  //Somente na segunda vez que o botão for acionado vai somar o acréscimo
      }
      delay(20);
      tone(buzzer, 2581, 500);
      delay(50);
      //Desligando o buzzer.
      noTone(buzzer);
    }



    segundos2--;  //Tempo 1 se apresenta parado

    lcd.setCursor(0, 0); //tempo 1 se apresenta parado até chegar avez do jogador 1
    lcd.print("Jogador1:  "); 
    if (minutos1 < 10) { lcd.print("0"); } //Se os minutos forem < 10 vai printar um 0 na frente (visual apenas 01:00)
    lcd.print(minutos1);
    lcd.print(":");
    if (segundos1 < 10) { lcd.print("0"); } //Se os segundos forem < 10 vai printar um 0 na frente (visual apenas 00:01)
    lcd.print(segundos1);
    if (segundos1 == 0) {
      segundos1 = 60;
      minutos1--;
    }

    if (segundos1 == -1) { //Mostra 59 segundos inves de 60
      segundos1 = 59;
      minutos1--;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(minutos1);
      lcd.print(":59");
    }

    lcd.setCursor(0, 1);  //Rotina decrescendo o tempo 2
    lcd.print("Jogador2: ");
    lcd.print("*");
    if (minutos2 < 10) { lcd.print("0"); } //Se os minutos forem < 10 vai printar um 0 na frente (visual apenas 01:00)
    lcd.print(minutos2);
    lcd.print(":");
    if (segundos2 < 10) { lcd.print("0"); } //Se os segundos forem < 10 vai printar um 0 na frente (visual apenas 00:01)
    lcd.print(segundos2);
    if (segundos2 == 0) { //Contagem decrescente do tempo
      segundos2 = 60;
      minutos2--;
    }

    if (segundos2 == -1) { //Mostra 59 segundos inves de 60
      segundos2 = 59;
      minutos2--;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(minutos2);
      lcd.print(":59");
    }
    if (minutos2 < 0) {
      fim2();
    }
    delay(1000);
  }
}

//Função para resetar todos os valores e volta para a quarta tela
void reseta() {  
  digitalWrite(8, LOW);
  minutos1 = 0;
  minutos2 = 0;
  segundos1 = 0;
  segundos2 = 0;
  tempoini = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Valores ");
  lcd.setCursor(0, 1);
  lcd.print("resetados");
  cont = 3;
  delay(2000);
}

//Rotina para fim do tempo jogador 1
void fim1() {  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jogador1");
  lcd.setCursor(0, 1);
  lcd.print("Perdeu!!");
  digitalWrite(8, HIGH);
  tone(buzzer, 2581, 500);
  delay(100);
  //Desligando o buzzer.
  noTone(buzzer);
  delay(100);
}

//Rotina para fim do tempo jogador 2
void fim2() {  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Jogador2");
  lcd.setCursor(0, 1);
  lcd.print("Perdeu!!");
  digitalWrite(8, HIGH);
  tone(buzzer, 2581);
  delay(100);
  //Desligando o buzzer.
  noTone(buzzer);
  delay(100);
}
