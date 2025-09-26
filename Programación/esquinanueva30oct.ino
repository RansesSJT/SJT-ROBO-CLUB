#include <AFMotor.h>
#include <Servo.h>

// Motores
AF_DCMotor motor1(1); // Motor principal conectado en M1

// Servo para dirección (llantas delanteras)
Servo direccionServo;
int pinServoDireccion = 10;

// Pines de sensor ultrasónico frontal
#define trigPinFront 22
#define echoPinFront 23

// ---------- FUNCIONES DE MOVIMIENTO ----------

void avanzar() {
  motor1.setSpeed(95); // Velocidad reducida para avanzar
  motor1.run(FORWARD);
}

void retrocederLargo() {
  motor1.setSpeed(110);
  motor1.run(BACKWARD);
  delay(1000); // retrocede 1 segundo
  motor1.run(RELEASE);
}

void detener() {
  motor1.run(RELEASE);
}

void detenerLargo() {
  motor1.run(RELEASE);
  delay(2000); // detenerse 2 segundos
}

void girarIzquierda() {
  direccionServo.write(60);  // Girar llantas izquierda
  motor1.setSpeed(150);
  motor1.run(FORWARD);
  delay(1300);
  direccionServo.write(90);  // Volver al centro
  motor1.run(RELEASE);
}

void girarDerecha() {
  direccionServo.write(130); // Girar llantas derecha
  motor1.setSpeed(160);
  motor1.run(FORWARD);
  delay(1700);
  direccionServo.write(90);  // Volver al centro
  motor1.run(RELEASE);
}

// ---------- SENSOR ULTRASÓNICO ----------
long medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000); // timeout 30 ms
  long distancia = duracion * 0.034 / 2; // en cm
  return distancia;
}

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);

  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);

  // Servo centrado (llantas rectas)
  direccionServo.attach(pinServoDireccion);
  direccionServo.write(90);

  detener();
}

// ---------- LOOP ----------
void loop() {
  long distanciaFront = medirDistancia(trigPinFront, echoPinFront);
  Serial.print("Distancia frente: ");
  Serial.println(distanciaFront);

  if (distanciaFront > 40 || distanciaFront == 0) {
    avanzar();
  } else {
    detener();
    delay(500);
    retrocederLargo();
      direccionServo.write(0);
       motor1.setSpeed(170);
     motor1.run(FORWARD);
      delay (1200);
      direccionServo.write(90);
      motor1.run(BACKWARD);
      delay (1000);
             motor1.setSpeed(170);
             direccionServo.write(0);
     motor1.run(FORWARD);
      delay (1200);
       direccionServo.write(90);
      motor1.run(BACKWARD);
      delay (1000);
 motor1.setSpeed(170);
 direccionServo.write(0);
     motor1.run(FORWARD);
      delay (1200);
       direccionServo.write(90);
      motor1.run(BACKWARD);
      delay (1000);
direccionServo.write(90);
motor1.run(FORWARD);
  }
}
