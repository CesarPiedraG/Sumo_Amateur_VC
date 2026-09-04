#ifndef INFRARROJO_H
#define INFRARROJO_H

#include <Arduino.h>

//Sensor QRE1113
const uint8_t infraFrontDer = A0;
const uint8_t infraFrontIzq = A1;
const uint8_t infraTras = A2;

const int umbralLineaBlanca = 100;

int detectarFrontDer();
int detectarFrontIzq();
int detectarTras();

#endif
