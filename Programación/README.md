# Programación
#include <AFMotor.h>
#include <Servo.h>

// Motores
AF_DCMotor motor1(1); // Motor principal conectado en M1

// Servo para direcci贸n
Servo direccionServo;
int pinServoDireccion = 10;

// Pines de sensores ultras贸nicos
#define trigPinFront A1
#define echoPinFront A0
#define trigPinLeft A2
#define echoPinLeft A3
#define trigPinRight A4
#define echoPinRight A5

// Funci贸n para medir distancia
long medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duracion = pulseIn(echoPin, HIGH, 25000); // 25 ms timeout
  long distancia = duracion * 0.034 / 2;
  if (distancia == 0 || distancia > 200) distancia = 200;
  return distancia;
}

// Movimiento
void avanzar() {
  motor1.setSpeed(75); // Velocidad reducida para avanzar
  motor1.run(FORWARD);
}

void retrocederLargo() {
  motor1.setSpeed(130);
  motor1.run(BACKWARD);
  delay(800);
  motor1.run(RELEASE);
}

void detener() {
  motor1.run(RELEASE);
}

void girarIzquierda() {
  direccionServo.write(60);
  motor1.setSpeed(170);
  motor1.run(FORWARD);
  delay(1700);
  direccionServo.write(90);
  motor1.run(RELEASE);
}

void girarDerecha() {
  direccionServo.write(130);
  motor1.setSpeed(170);
  motor1.run(FORWARD);
  delay(1700);
  direccionServo.write(90);
  motor1.run(RELEASE);
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
  direccionServo.attach(pinServoDireccion);
  direccionServo.write(90); // Direcci贸n recta
  delay(500);
}

void loop() {
  long frente = medirDistancia(trigPinFront, echoPinFront);
  long izquierda = medirDistancia(trigPinLeft, echoPinLeft);
  long derecha = medirDistancia(trigPinRight, echoPinRight);

  Serial.print("Frente: "); Serial.print(frente);
  Serial.print(" | Izquierda: "); Serial.print(izquierda);
  Serial.print(" | Derecha: "); Serial.println(derecha);

  // Detecci贸n de callej贸n sin salida o esquina cerrada
  if (frente < 20 && izquierda < 20 && derecha < 20) {
    detener();
    retrocederLargo();
    girarIzquierda();
    return;
  }

  if (frente < 30) {
    detener();
    retrocederLargo();
    if (izquierda > derecha) {
      girarIzquierda();
    } else {
      girarDerecha();
    }
  } else {
    // Avance con leve correcci贸n
    if (izquierda < 20 && derecha > 25) {
      direccionServo.write(130);
      motor1.run(FORWARD);
      delay (100);
    } else if (derecha < 20 && izquierda > 25) {
      direccionServo.write(40);
      motor1.run(FORWARD);
      delay (100);
    } else {
      direccionServo.write(90);
    }
    avanzar();
  }

  delay(100);
}
