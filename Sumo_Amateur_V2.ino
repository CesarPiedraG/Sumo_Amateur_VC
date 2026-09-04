#include "Movimiento.h"
#include "Laser.h"
#include "Infrarrojo.h"

//Estados de maniobra
enum EstadoLRT { ATAQUE,
                 RETROCO,
                 AVANCE,
                 BUSQUEDA };
EstadoLRT estadoActual = ATAQUE;

unsigned long tiempoInicio = 0;


void setup() {
  //Pines puente H
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AI1, OUTPUT);
  pinMode(AI2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BI1, OUTPUT);
  pinMode(BI2, OUTPUT);

  //Pines sensores infrarrojo
  pinMode(infraTras, INPUT);
  pinMode(infraFrontIzq, INPUT);
  pinMode(infraFrontDer, INPUT);

  inicializarLasers();

  delay(5000);  //5 segundos
  digitalWrite(STBY, HIGH);

  retrocesoDer();
  delay(300);
}

void loop() {

  bool rivalDer = rivalDetectado(distDer());
  bool rivalIzq = rivalDetectado(distIzq());
  bool rival = rivalDer && rivalIzq;

  int lecturaFrontDer = detectarFrontDer();
  int lecturaFrontIzq = detectarFrontIzq();
  int lecturaTrasera = detectarTras();

  if (lecturaFrontDer < umbralLineaBlanca && lecturaFrontIzq < umbralLineaBlanca) {
    estadoActual = RETROCO;
  } else if (lecturaTrasera < umbralLineaBlanca) {
    estadoActual = AVANCE;
  } else if (lecturaFrontIzq < umbralLineaBlanca) {
    retrocesoDer();
    estadoActual = RETROCO;
  } else if (lecturaFrontDer < umbralLineaBlanca) {
    retrocesoIzq();
    estadoActual = RETROCO;
  } else {
    estadoActual = ATAQUE;
  }

  switch (estadoActual) {
    case RETROCO:
      retroceso();
      delay(2000);
      break;
    case AVANCE:
      avance();
      delay(2000);
      break;
    case ATAQUE:
      if (rival) {
        avance();
        delay(1000);
      } else if (rivalIzq) {
        ejeIzquierda();
        delay(1000);
        detener();
      } else if (rivalDer) {
        ejeDerecha();
        delay(1000);
        detener();
      } else {
        estadoActual = BUSQUEDA;
      }
      break;
    case BUSQUEDA:
      ejeDerecha();
      delay(1000);
      if (rival || rivalDer || rivalIzq) {
        estadoActual = ATAQUE;
      }
      ejeIzquierda();
      delay(1200);
      break;
  }
}
