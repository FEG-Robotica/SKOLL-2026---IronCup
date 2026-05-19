//** Definição dos Pinos **

#ifndef SENSORES_H
#define SENSORES_H

// Sensores de Linha
#define SENSOR_LINHA_FRONTAL_ESQ 14 // SL2
#define SENSOR_LINHA_FRONTAL_DIR 12 // SL3

// Sensores de Distancia
#define SENSOR_DIST_FRONTAL_ESQ 32 // SD5 invertido(1 nao vendo 0 vendo) OK
#define SENSOR_DIST_FRONTAL_DIR 36 // SD1 invertido(1 nao vendo 0 vendo) OK
#define SENSOR_DIST_ESQ 34         // SD3 invertido(1 nao vendo 0 vendo) OK
#define SENSOR_DIST_DIR 33         // SD6 invertido(1 nao vendo 0 vendo) OK
#define SENSOR_DIST_CENTRAL 26     // SD8 invertido(1 nao vendo 0 vendo) OK

// Modulo Start
#define START 15

// Led
#define LED 2

// Pwm
#define PWMA 23 // PWMA
#define PWMB 22 // PWMB
#define PWMC 21 // PWMC
#define PWMD 19 // PWMD

// Bluetooth
#define SERVICE_UUID "a83d4416-9199-4601-849b-9faa03a34979"
#define CHARACTERISTIC_UUID "7a53760e-950e-4141-895c-fe9e394cf274"

// Variaveis Tipo Inteiro e Iguais á Zero
int linha_dir = 0;
int linha_esq = 0;
int distancia_front_esq = 0;
int distancia_front_dir = 0;
int distancia_esq = 0;
int distancia_dir = 0;
int distancia_cent = 0;
int velmotor = 0;
int parametro = 0;

// Chamada de funções
void leituraSensoresLinha();
void leituraSensoresDistancia();

#endif
