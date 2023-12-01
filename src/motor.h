#include <Sabertooth.h>
#include <SoftwareSerial.h>

class MotorWrapper {
private:
	SoftwareSerial serial;
	Sabertooth st;
public:
	int leftSpeed = 0;
	int rightSpeed = 0;
	
	const short left = 2;
	const short right = 1;

	const short forward = 1;
	const short backward = -1;

	MotorWrapper(int tx): serial(NOT_A_PIN, tx), st(128, this->serial) {}
	void init();
	void setSpeed(int speed);
	void setMotorSpeed(short motor, int speed);
	int getMotorSpeed(short motor);
	void setDirection(short motor, short direction);
};