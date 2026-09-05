#include "Movimiento.h"


void avance(){
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, HIGH);
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, HIGH);
  analogWrite(PWMA, velocidadMax);
  analogWrite(PWMB, velocidadMax);
}

void retroceso(){
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
  analogWrite(PWMA, velocidadMid);
  analogWrite(PWMB, velocidadMid);
}

void retrocesoDer(){
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
  analogWrite(PWMA, velocidadSuave);
  analogWrite(PWMB, velocidadMid);
}

void retrocesoIzq(){
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
  analogWrite(PWMA, velocidadMid);
  analogWrite(PWMB, velocidadSuave);
}


void ejeDerecha(){
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, LOW);
  digitalWrite(BI1, LOW);
  digitalWrite(BI2, HIGH);
  analogWrite(PWMA, velocidadSuave);
  analogWrite(PWMB, velocidadSuave);
}

void ejeIzquierda(){
  digitalWrite(AI1, LOW);
  digitalWrite(AI2, HIGH);
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, LOW);
  analogWrite(PWMA, velocidadSuave);
  analogWrite(PWMB, velocidadSuave);
}

void detener() {
  digitalWrite(AI1, HIGH);
  digitalWrite(AI2, HIGH);
  digitalWrite(BI1, HIGH);
  digitalWrite(BI2, HIGH);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
} 

