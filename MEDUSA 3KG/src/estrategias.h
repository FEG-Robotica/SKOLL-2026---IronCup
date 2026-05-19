//** Estratégias do Robô **

#include <Arduino.h>
#include "motor.h"
#include "sensores.h"
#include "testes.h"

#ifndef ESTRATEGIAS_H
#define ESTRATEGIAS_H

// Estratégia do Missil
void missil()
{
  mover_motor('d', 'f', 1023);
  mover_motor('e', 'f', 1023);
}

// Estratégia de Buscar Inimigo
void busca()
{
  // 0 = vendo inimigo
  // 1 = vendo nada
  leituraSensoresDistancia();
  leitura_linha();

  if (((distancia_front_esq == 0) && (distancia_cent == 0) && (distancia_front_dir == 0)))
  {
    missil();
    delay(50);
  }
  else if (((distancia_front_esq == 0) && (distancia_cent == 0)))
  {
    mover_motor('d', 'f', 90);
    mover_motor('e', 'f', 75);
    delay(50);
  }
  else if (((distancia_front_dir == 0) && (distancia_cent == 0)))
  {
    mover_motor('d', 'f', 75);
    mover_motor('e', 'f', 90);
    delay(50);
  }
  else if ((distancia_esq == 0))
  {
    direita();
    delay(100);
  }
  else if ((distancia_dir == 0))
  {
    esquerda();
    delay(100);
  }
  else
  {
    girar_eixo();
  }
}

// Estratégia do Arco
void arco()
{

  unsigned long timerMilis = 0.0;
  unsigned long intervalo = 2500; // 2,5s

  // 0 = vendo inimigo
  // 1 = vendo nada
  leituraSensoresDistancia();
  leitura_linha();

  timerMilis = millis(); // atualiza tempo

  // Aguarda 500ms antes de iniciar movimento
  if (millis() - timerMilis < 500)
  {
    return;
  }

  // ----- LÓGICA DE OBSTÁCULOS -----
  if ((distancia_dir == 1) && (distancia_front_esq == 1) && (distancia_cent == 1) && (distancia_front_dir == 1) && (distancia_esq == 1))
  {
    // Nenhum obstáculo -> anda pra frente
    mover_motor('d', 'f', 75);
    mover_motor('e', 'f', 90);
  }
  else if (distancia_esq == 0)
  {
    mover_motor('e', 't', 60);
    mover_motor('d', 'f', 60);
  }
  else if (distancia_cent == 0)
  {
    mover_motor('e', 'f', 100);
    mover_motor('d', 'f', 100);
  }
  else if (distancia_front_dir == 0)
  {
    mover_motor('e', 'f', 60);
    mover_motor('d', 't', 60);
  }
  else if (distancia_front_esq == 0)
  {
    mover_motor('e', 't', 60);
    mover_motor('d', 'f', 60);
  }
  else
  {
    // fallback padrão: segue em frente
    mover_motor('d', 'f', 75);
    mover_motor('e', 'f', 90);
  }

  // ----- LÓGICA DE LINHA -----
  leitura_linha();

  // ----- RESET DO TIMER -----
  if (millis() - timerMilis > intervalo)
  {
    timerMilis = millis();
  }
}

// Estratégia da Estrela
void estrela()
{
  // 0 = vendo inimigo
  // 1 = vendo nada
  leituraSensoresDistancia();
  leitura_linha();

  while ((distancia_esq == 1) && (distancia_front_esq == 1) && (distancia_cent == 1) && (distancia_front_dir == 1) && (distancia_dir == 1))
  {
    mover_motor('d', 'f', 90);
    mover_motor('e', 'f', 90);
    delay(50);
  }

  if (((distancia_front_esq == 0) && (distancia_cent == 0) && (distancia_front_dir == 0)))
  {
    missil();
    delay(50);
  }
  else if (((distancia_front_esq == 0) && (distancia_cent == 0)))
  {
    mover_motor('d', 'f', 90);
    mover_motor('e', 'f', 75);
    delay(50);
  }

  else if (((distancia_front_dir == 0) && (distancia_cent == 0)))
  {
    mover_motor('d', 'f', 75);
    mover_motor('e', 'f', 90);
    delay(50);
  }
  else if ((distancia_esq == 0))
  {
    direita();
    delay(50);
  }
  else if ((distancia_dir == 0))
  {
    esquerda();
    delay(50);
  }
}

// Estratégia do Toquinho
void toquinho()
{
  // 0 = vendo inimigo
  // 1 = vendo nada
  leituraSensoresDistancia();
  leitura_linha();

  if (((distancia_front_esq == 0) && (distancia_cent == 0) && (distancia_front_dir == 0)))
  {
    missil();
    delay(50);
  }
  else if (((distancia_front_esq == 0) && (distancia_cent == 0)))
  {
    mover_motor('d', 'f', 90);
    mover_motor('e', 'f', 75);
    delay(50);
  }
  else if (((distancia_front_dir == 0) && (distancia_cent == 0)))
  {
    mover_motor('d', 'f', 75);
    mover_motor('e', 'f', 90);
    delay(50);
  }
  else if ((distancia_esq == 0))
  {
    direita();
    delay(50);
  }
  else if ((distancia_dir == 0))
  {
    esquerda();
    delay(50);
  }
  else
  {
    mover_motor('d', 'f', 90);
    mover_motor('e', 'f', 90);
    delay(100);
    parar();
    delay(100);
  }
}

#endif