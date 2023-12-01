#include <Arduino.h>
#include <SoftwareSerial.h>

#include "accelerometer.h"
#include "motor.h"

// initialisation des librairies
SoftwareSerial communication(5, 6); // communication sans fil (moniteur série)
Accelerometer accelerometer; // accéléromètre et gyroscope
MotorWrapper motor(4); // contrôle du moteur

unsigned long timer = 0;

#define STATE_STOP 0
#define STATE_AVANCER 1
#define STATE_DEMI_TOUR 2
unsigned short state = STATE_STOP;

void setup() {
	motor.init(); // initialisation moteur
	communication.println(F("Calibration demarree"));
	accelerometer.init(); // initialisation & calibration acceleromètre
	// ATTENTION: la calibration prends ~10 secondes
	communication.println(F("Calibration terminee"));
	communication.begin(9600); // initialisation communication série
	communication.listen(); // on force l'écoute du port série

	timer = millis();
}

float speedFactor = 1.0; // facteur de vitesse, à augmenter si le robot n'est pas assez rapide
void loop() {
	if (state == STATE_STOP) {
		motor.setSpeed(0);
	}

	if (state == STATE_AVANCER)	{
		motor.setSpeed(50*speedFactor);
		if (millis() - timer > 30000) { // si ca fait plus de 30 secondes qu'on avance
			communication.println(F("Changement de mode: DEMI TOUR"));
			state = STATE_DEMI_TOUR; // on change le mode en "demi tour"
			timer = millis(); // on réinitialise le timer
		}
	}

	if (state == STATE_DEMI_TOUR)	{
		// on tourne à gauche
		motor.setMotorSpeed(motor.left, 20*speedFactor);
		motor.setMotorSpeed(motor.right, 90*speedFactor);

		if (abs(accelerometer.gyroYaw) > 178) { // si on à fait demi-tour (180°)
			communication.println(F("Changement de mode: AVANCER"));
			state = STATE_AVANCER; // on change le mode en "avancer"
			timer = millis(); // on réinitialise le timer
			accelerometer.reset(); // on remet le gyro à 0
		}
	}

	accelerometer.loop(); // on fait tourner les calculs pour le filtre de l'accéléromètre

	if (communication.available() > 0) { // s'il y a des données dans le port série
		short input = communication.read(); // on lit ces données
		if (input == STATE_STOP) {
			communication.println(F("Changement de mode: STOP"));
			state = STATE_STOP;
		} else if (input == STATE_AVANCER) {
			communication.println(F("Changement de mode: AVANCER"));
			state = STATE_AVANCER;
		} else if (input == STATE_DEMI_TOUR) {
			communication.println(F("Changement de mode: DEMI TOUR"));
			state = STATE_DEMI_TOUR;
		}

		// on "nettoie" le port série (on lit les données résiduelles)
		while (communication.available() > 0) {
			communication.read();
		}
	}

	delay(10);
}