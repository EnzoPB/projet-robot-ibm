#include <infrared.h>
#include <Arduino.h>

void Infrared::init(int pin) {
	this->pin = pin;
	pinMode(pin, INPUT);
	this->lastState = digitalRead(pin);
}

void Infrared::tick() {
	if (this->lastState == 0 && digitalRead(this->pin)) {
		this->count++;
	}
	this->lastState = digitalRead(this->pin);

}