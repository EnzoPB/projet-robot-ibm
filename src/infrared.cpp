#include <infrared.h>
#include <Arduino.h>

Infrared::Infrared(int pin, int countPerTurn) {
	this->pin = pin;
	this->countPerTurn = countPerTurn;
}

void Infrared::init() {
	pinMode(pin, INPUT);
	this->lastState = digitalRead(pin);
	this->startTime = millis();
}

void Infrared::tick() {
	if (this->lastState == 0 && digitalRead(this->pin)) {
		this->count += 1 / this->countPerTurn;
	}
	this->lastState = digitalRead(this->pin);
}

void Infrared::reset() {
	this->startTime = millis();
	this->count = 0;
}