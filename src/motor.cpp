#include <Arduino.h>
#include <motor.h>
#include <Sabertooth.h>

void MotorWrapper::init() {
	this->serial.begin(9600);
	this->st.autobaud();
	this->setSpeed(0);
}

void MotorWrapper::setSpeed(int speed) {
	this->setMotorSpeed(this->left, speed);
	this->setMotorSpeed(this->right, speed);
}

int MotorWrapper::getMotorSpeed(int motor) {
	if (motor == this->left) {
		return this->leftSpeed;
	} else {
		return this->rightSpeed;
	}
}

void MotorWrapper::setMotorSpeed(int motor, int speed) {
	this->st.motor(motor, speed);

	if (motor == this->left) {
		this->leftSpeed = speed;
	} else if (motor == this->right) {
		this->rightSpeed = speed;
	}
}

void MotorWrapper::setDirection(int motor, int direction) {
	this->setMotorSpeed(motor, direction * this->getMotorSpeed(motor));
}