#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <Arduino.h>

//Driver TB6612FNG
const uint8_t STBY = 3;
const uint8_t AI1 = 2;
const uint8_t AI2 = 4;
const uint8_t PWMA = 5;
const uint8_t BI1 = 8;
const uint8_t BI2 = 7;
const uint8_t PWMB = 6;
//Para la definición de pines se utiliza uint8_t por cuestiones de optimización, pues ocupa solo 1 byte


//Variables
const int velocidadMid = 180;
const int velocidadMax = 230;
const int velocidadSuave = 150;

//Declaración de funciones
void giroDerecha();
void giroIzquierda();
void ejeDerecha();
void ejeIzquierda();
void busqueda();
void avance();
void retroceso();
void detener();

#endif
