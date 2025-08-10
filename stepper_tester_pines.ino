#include <Stepper.h>

const int pasosPorVuelta = 64; // Ajustá si es necesario

// Pines conectados al motor
int motorPins[] = {8, 9, 10, 11}; //8,10,9,11
//int motorPins[] = {2, 3, 4, 5}; //2,5,3,4

// Todas las 24 combinaciones posibles de los 4 pines (permutaciones)
int permutaciones[24][4];
int contador = 0;

void generarPermutaciones() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (j == i) continue;
      for (int k = 0; k < 4; k++) {
        if (k == i || k == j) continue;
        for (int l = 0; l < 4; l++) {
          if (l == i || l == j || l == k) continue;
          permutaciones[contador][0] = motorPins[i];
          permutaciones[contador][1] = motorPins[j];
          permutaciones[contador][2] = motorPins[k];
          permutaciones[contador][3] = motorPins[l];
          contador++;
        }
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  generarPermutaciones();
}

void loop() {
  for (int i = 0; i < 24; i++) {
    Serial.print("Probando orden: ");
    Serial.print(permutaciones[i][0]); Serial.print(", ");
    Serial.print(permutaciones[i][1]); Serial.print(", ");
    Serial.print(permutaciones[i][2]); Serial.print(", ");
    Serial.println(permutaciones[i][3]);

    Stepper motor(pasosPorVuelta,
      permutaciones[i][0],
      permutaciones[i][1],
      permutaciones[i][2],
      permutaciones[i][3]
    );

    motor.setSpeed(10); // Bajá si hace ruido o se traba
    motor.step(50);     // Gira un poco
    delay(1500);
    motor.step(-50);    // Gira para atrás
    delay(1500);
  }

  // Termina y se detiene
  while (true);
}
