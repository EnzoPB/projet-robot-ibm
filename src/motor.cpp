#include <Arduino.h>
#include <motor.h>
#include <Sabertooth.h>

void MotorWrapper::init() {
	this->serial.begin(9600);
	this->st.autobaud();
	// sometimes the motors doesn't stop at init, this weird trick does it
	this->setSpeed(1);
	delay(1);
	this->setSpeed(0);
}

void MotorWrapper::setSpeed(int speed) {
	this->setMotorSpeed(this->left, speed);
	this->setMotorSpeed(this->right, speed);
}

int MotorWrapper::getMotorSpeed(short motor) {
	if (motor == this->left) {
		return this->leftSpeed;
	} else {
		return this->rightSpeed;
	}
}

void MotorWrapper::setMotorSpeed(short motor, int speed) {
	if (motor == this->left && this->leftSpeed != speed) {
		this->leftSpeed = speed;
		this->st.motor(motor, speed);
	} else if (motor == this->right && this->rightSpeed != speed) {
		this->rightSpeed = speed;
		this->st.motor(motor, speed);
	}
}

void MotorWrapper::setDirection(short motor, short direction) {
	this->setMotorSpeed(motor, direction * this->getMotorSpeed(motor));
}