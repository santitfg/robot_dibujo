#include "AFMotor.h"

// ================= CONFIGURACION DE HARDWARE =================

const float DIAMETRO_RUEDA_CM = 6.5;
const float CIRCUNFERENCIA_CM = PI * DIAMETRO_RUEDA_CM;

uint8_t VELOCIDAD_PWM = 200;

AF_DCMotor motorIzq(3);  // M3
AF_DCMotor motorDer(4);  // M4


// ================= CONTROL DE MOTORES =================

void adelante(int velocidad) {
  motorIzq.setSpeed(velocidad);
  motorDer.setSpeed(velocidad);

  motorIzq.run(FORWARD);
  motorDer.run(FORWARD);
}

void atras(int velocidad) {
  motorIzq.setSpeed(velocidad);
  motorDer.setSpeed(velocidad);

  motorIzq.run(BACKWARD);
  motorDer.run(BACKWARD);
}

void giroIzquierda(int velocidad) {
  motorIzq.setSpeed(velocidad);
  motorDer.setSpeed(velocidad);

  motorIzq.run(BACKWARD);
  motorDer.run(FORWARD);
}

void giroDerecha(int velocidad) {
  motorIzq.setSpeed(velocidad);
  motorDer.setSpeed(velocidad);

  motorIzq.run(FORWARD);
  motorDer.run(BACKWARD);
}

void curvaIzquierda(int velocidad) {
  motorIzq.setSpeed(velocidad * 0.25);
  motorDer.setSpeed(velocidad);

  motorIzq.run(FORWARD);
  motorDer.run(FORWARD);
}

void curvaDerecha(int velocidad) {
  motorIzq.setSpeed(velocidad);
  motorDer.setSpeed(velocidad * 0.25);

  motorIzq.run(FORWARD);
  motorDer.run(FORWARD);
}

void parar() {
  motorIzq.run(RELEASE);
  motorDer.run(RELEASE);
}


// ================= MOVIMIENTO LOCO =================

enum Movimiento {
  ADELANTE,
  ATRAS,
  IZQUIERDA,
  DERECHA,
  CURVA_IZQ,
  CURVA_DER
};

Movimiento movimientoActual;

unsigned long siguienteCambio = 0;

void nuevoMovimiento() {

  movimientoActual = (Movimiento)random(0, 6);

  unsigned long duracion = random(150, 1400);

  siguienteCambio = millis() + duracion;
}


// ================= SETUP =================

void setup() {

  randomSeed(analogRead(A0));

  nuevoMovimiento();
}


// ================= LOOP =================

void loop() {

  unsigned long ahora = millis();

  // Cambiar de comportamiento
  if (ahora >= siguienteCambio) {
    nuevoMovimiento();
  }

  switch (movimientoActual) {

    case ADELANTE:
      adelante(VELOCIDAD_PWM);
      break;

    case ATRAS:
      atras(VELOCIDAD_PWM);
      break;

    case IZQUIERDA:
      giroIzquierda(VELOCIDAD_PWM);
      break;

    case DERECHA:
      giroDerecha(VELOCIDAD_PWM);
      break;

    case CURVA_IZQ:
      curvaIzquierda(VELOCIDAD_PWM);
      break;

    case CURVA_DER:
      curvaDerecha(VELOCIDAD_PWM);
      break;
  }
}