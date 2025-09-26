#include <AFMotor.h>
#include <Servo.h>

// Motores
AF_DCMotor motor1(1); // Motor principal conectado en M1

// Servo para dirección
Servo direccionServo;
int pinServoDireccion = 10;

// Pines de sensores ultrasónicos
#define trigPinFront 22
#define echoPinFront 23
#define trigPinLeft 24
#define echoPinLeft 25
#define trigPinRight 26
#define echoPinRight 27

// Función para medir distancia
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
  motor1.setSpeed(95); // Velocidad reducida para avanzar
  motor1.run(FORWARD);
}

void retrocederLargo() {
  motor1.setSpeed(130);
  motor1.run(BACKWARD);
  delay(200);
  motor1.run(RELEASE);
}

void detener() {
  motor1.run(RELEASE);
}

void girarIzquierda() {
  direccionServo.write(60);
  motor1.setSpeed(150);
  motor1.run(FORWARD);
  delay(1300);
  direccionServo.write(90);
  motor1.run(RELEASE);
}

void girarDerecha() {
  direccionServo.write(130);
  motor1.setSpeed(160);
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
  direccionServo.write(90); // Dirección recta
  delay(500);

}

void loop() {
  long frente = medirDistancia(trigPinFront, echoPinFront);
  long izquierda = medirDistancia(trigPinLeft, echoPinLeft);
  long derecha = medirDistancia(trigPinRight, echoPinRight);

  Serial.print("Frente: "); Serial.print(frente);
  Serial.print(" | Izquierda: "); Serial.print(izquierda);
  Serial.print(" | Derecha: "); Serial.println(derecha);

  // Detección de callejón sin salida o esquina cerrada
  if (frente < 20 && izquierda < 20 && derecha < 20) {
    detener();
    retrocederLargo();
    girarIzquierda();
    return;
  }

  if (frente < 55) {
    detener();
    delay(300);
    retrocederLargo();
    if (izquierda > derecha) {
      girarIzquierda();
    } else {
      girarDerecha();
    }
  } else {
    // Corrección leve de dirección con retorno al centro
    if (izquierda < 35 && derecha > 36) {
      direccionServo.write(130);
      motor1.setSpeed(120); 
      motor1.run(FORWARD);
      delay(500);
      direccionServo.write(90);  // Regresa al centro
       motor1.run(RELEASE);
    } else if (derecha < 30 && izquierda > 31) {
      direccionServo.write(60);
      motor1.setSpeed(120); 
      motor1.run(FORWARD);
      delay(500);
      direccionServo.write(90);  // Regresa al centro
       motor1.run(RELEASE);
    } else {
      avanzar();
    }
  }

  delay(100);
}


