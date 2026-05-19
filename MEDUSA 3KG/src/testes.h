//** Testes básicos do Robô **

#include <Arduino.h>
#include "sensores.h"
#include "motor.h"

#ifndef TESTES_H
#define TESTES_H

// Função para Piscar o Led da Placa
void piscar_led()
{
  digitalWrite(LED, HIGH);
  delay(300);
  digitalWrite(LED, LOW);
  delay(300);
}

// Função para Leitura dos Sensores de Linha
void leitura_linha()
{
  // float val1 = map(linha_dir, 0, 4095, 0, 1); // 1 preto 0 branco
  // float val2 = map(linha_esq, 0, 4095, 0, 1); // 1 preto 0 branco

  leituraSensoresLinha();

  /*while ((linha_dir > 1800) && (linha_esq > 1800))
  {
    mover_motor('d', 'f', 100);
    mover_motor('e', 'f', 100);
  }*/

  if ((linha_dir < 1800) && (linha_esq < 1800))
  {
    parar();
    delay(50);
    tras();
    delay(100);
    girar_180();
    delay(50);
  }
  else if (linha_dir < 1800)
  {
    parar();
    delay(50);
    tras();
    delay(100);
    girar_180();
    delay(50);
  }
  else if (linha_esq < 1800)
  {
    parar();
    delay(50);
    tras();
    delay(100);
    girar_180();
    delay(50);
  }
}

#endif
