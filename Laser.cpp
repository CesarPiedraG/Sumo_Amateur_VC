#include "Laser.h"

VL53L0X sensorDer;
VL53L0X sensorIzq;

void inicializarLasers(){
  pinMode(XSHUTA, OUTPUT);
  pinMode(XSHUTB, OUTPUT);
  
  Wire.begin();//Inicializa comunicacion I2C

  // Reset de sensores láser
  digitalWrite(XSHUTA, LOW);
  digitalWrite(XSHUTB, LOW);
  delay(10);

  // Configuracion sensor Derecho 
  digitalWrite(XSHUTA, HIGH);
  delay(10);
  sensorDer.init();
  sensorDer.setTimeout(500);
  sensorDer.setAddress(direccionDer);

  // Configuracion sensor Izquierdo
  digitalWrite(XSHUTB, HIGH);
  delay(10);
  sensorIzq.init();
  sensorIzq.setTimeout(500);
  sensorIzq.setAddress(direccionIzq);

  sensorIzq.startContinuous();
  sensorDer.startContinuous();

}

int distDer(){
  int lecturaDer = sensorDer.readRangeContinuousMillimeters();
  if (sensorDer.timeoutOccurred() || lecturaDer > 2000) {
    return 9999;
  }
  return lecturaDer;
}

int distIzq(){
  int lecturaIzq = sensorIzq.readRangeContinuousMillimeters();
  if (sensorIzq.timeoutOccurred() || lecturaIzq > 2000) { //2000 ajustable a prubeas
    return 9999;
  }
  return lecturaIzq;
}

bool rivalDetectado(int dist){
  if(dist < distanciaAtaque){
    return true;
  }else{
    return false;
  }
}



