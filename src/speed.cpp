#include <Arduino.h>
#include <speed.h>

void Speed::init() {
	this->infrared.init();
}

void Speed::tick() {
	this->infrared.tick();
	if (millis() % this->dt == 0) { // toutes les dt ms
		this->currentSpeed = this->infrared.count / this->dt;
	}
	this->infrared.reset();
}