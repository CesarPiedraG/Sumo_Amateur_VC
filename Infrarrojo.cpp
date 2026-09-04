#include "Infrarrojo.h"

int detectarFrontDer(){
  return analogRead(infraFrontDer);
}

int detectarFrontIzq(){
  return analogRead(infraFrontIzq);
}
int detectarTras(){
  return analogRead(infraTras);
}

