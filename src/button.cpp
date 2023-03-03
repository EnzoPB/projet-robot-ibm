#include <Arduino.h>
#include <button.h>

Button::Button(int pin) {
	this->pin = pin;
	pinMode(this->pin, INPUT_PULLUP);
}

bool Button::isPressed() {
	bool state = !digitalRead(this->pin);
	bool previousState = this->previousState;
	this->previousState = state;

	if (state && !previousState) {
		return true;
	}

	return false;
}