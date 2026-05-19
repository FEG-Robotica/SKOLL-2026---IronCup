//** Movimentação dos Motores **

#include <Arduino.h>
#include "sensores.h"

#ifndef MOTOR_H
#define MOTOR_H

const double corrd = 1;
const double corre = 1;

// Função para Movimentação do Robô
void mover_motor(char lado, char direcao, int velocidade)
{
  // Motor Esquerdo
  if (lado == 'e')
  {
    // Ir para Frente
    if (direcao == 'f')
    {
      analogWrite(PWMC, velocidade * corre);
      analogWrite(PWMD, LOW);
    }
    // Ir para Trás
    if (direcao == 't')
    {
      analogWrite(PWMC, LOW);
      analogWrite(PWMD, velocidade * corre);
    }
  }

  // Motor Direito
  if (lado == 'd')
  {
    // Ir para Frente
    if (direcao == 'f')
    {
      analogWrite(PWMA, velocidade * corre);
      analogWrite(PWMB, LOW);
    }
    // Ir para Trás
    if (direcao == 't')
    {
      analogWrite(PWMA, LOW);
      analogWrite(PWMB, velocidade * corre);
    }
  }
}

// Função Ir para Frente
void frente()
{
  mover_motor('e', 'f', 500);
  mover_motor('d', 'f', 500);
}

// Função Ir para Trás
void tras()
{
  mover_motor('e', 't', 800);
  mover_motor('d', 't', 800);
}

// Função Ir para Direita
void direita()
{
  mover_motor('e', 'f', 80);
  mover_motor('d', 'f', 100);
}

// Função Ir para Esquerda
void esquerda()
{
  mover_motor('e', 'f', 100);
  mover_motor('d', 'f', 80);
}

// Função Parar
void parar()
{
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(PWMC, LOW);
  digitalWrite(PWMD, LOW);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  analogWrite(PWMC, 0);
  analogWrite(PWMD, 0);
}

// Função Girar Eixo
void girar_eixo()
{
  mover_motor('e', 'f', 100);
  mover_motor('d', 't', 100);
}

// Função Girar Círculo
void girar_circulo()
{
  mover_motor('e', 'f', 100);
  mover_motor('d', 'f', 50);
}

// Função Girar 180
void girar_180()
{
  mover_motor('e', 'f', 100);
  mover_motor('d', 't', 100);
  delay(200);
  parar();
}

#endif