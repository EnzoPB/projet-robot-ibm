#include <Sabertooth.h>
#include <SoftwareSerial.h>

class MotorWrapper {
private:
	int leftSpeed = 0;
	int rightSpeed = 0;

	SoftwareSerial serial;
	Sabertooth st;
public:
	const int left = 1;
	const int right = 2;

	const int forward = 1;
	const int backward = -1;

	MotorWrapper(int tx): serial(NOT_A_PIN, tx), st(128, this->serial) {}
	void init();
	void setSpeed(int speed);
	void setMotorSpeed(int motor, int speed);
	int getMotorSpeed(int motor);
	void setDirection(int motor, int direction);
};