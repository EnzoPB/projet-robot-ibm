#include <Arduino.h>

#include <telemetry.h>
#include <accelerometer.h>
#include <motor.h>
#include <speed.h>
#include <button.h>

#ifdef MENU_ENABLE
#include <menu.h>
#include <menuList.h>
#endif

#define DIAMETRE_ROUE = 6.5
#define CIRC_ROUE = 6.5 * 3.14

Telemetry telemetry(2, 3);
// SoftwareSerial xbee(2, 3);
Accelerometer accelerometer;
MotorWrapper motor(4);
Speed speed(5, 20);
Button button(6);

#ifdef MENU_ENABLE
Menu menu;
#endif

unsigned long timer = 0;
int state = 0;

void setup()
{
	motor.init();
	telemetry.init();
	telemetry.serial.println("0,-1,0,0,0,0,0,0,0,0,0");
	telemetry.serial.println("msg,Telemetrie prete");
	telemetry.serial.println("msg,Calibration du gyroscope");
	accelerometer.init();
	telemetry.serial.println("msg,Initialisation terminée");

#ifdef MENU_ENABLE
	menu.init();
#endif

	timer = millis();
}

float speedFactor = 1.0;
bool sens = false;
void loop()
{
	if (state == 1)	{ // forward
		motor.setSpeed(50*speedFactor);
		if (millis() - timer > 30000)
		{
			state = 2;
			timer = millis();
		}
	}
	if (state == 2)	{ // turn
			motor.setMotorSpeed(motor.left, 20*speedFactor);
			motor.setMotorSpeed(motor.right, 90*speedFactor);

		if (abs(accelerometer.gyroYaw) > 178)
		{
			state = 1;
			timer = millis();
			accelerometer.reset();
		}
	}

	accelerometer.loop();
	telemetry.serial.print(millis());
	telemetry.serial.print(",");
	telemetry.serial.print(state);
	telemetry.serial.print(",");
	telemetry.serial.print(accelerometer.accel_x);
	telemetry.serial.print(",");
	telemetry.serial.print(accelerometer.accel_y);
	telemetry.serial.print(",");
	telemetry.serial.print(accelerometer.accel_z);
	telemetry.serial.print(",");
	telemetry.serial.print(accelerometer.gyro_x / 100);
	telemetry.serial.print(",");
	telemetry.serial.print(accelerometer.gyro_y / 100);
	telemetry.serial.print(",");
	telemetry.serial.print(accelerometer.gyroYaw);
	telemetry.serial.print(",");
	telemetry.serial.print(accelerometer.temperature);
	telemetry.serial.print(",");
	telemetry.serial.print(motor.leftSpeed);
	telemetry.serial.print(",");
	telemetry.serial.println(motor.rightSpeed);
	if (telemetry.serial.available() > 0) {
		int telemetryInput = telemetry.serial.read();
		while (telemetry.serial.available() > 0) {
			telemetry.serial.read();
		}
		if (telemetryInput == 48) {
			telemetry.serial.println("msg,Accelerometer reset");
			accelerometer.reset();
		}
		if (telemetryInput == 51) { // start
			state = 1;
			timer = millis();
			telemetry.serial.println("msg,Start");
		}
		if (telemetryInput == 52) { // stop
			state = 0;
			motor.setSpeed(0);
			telemetry.serial.println("msg,Stop");
		}
		if (telemetryInput == 49) { // incspeed
			speedFactor = speedFactor + 0.1;
			telemetry.serial.print("msg,Facteur vitesse: ");
			telemetry.serial.println(speedFactor);
		}
		if (telemetryInput == 50) { //decspeed
			speedFactor = speedFactor - 0.1;
			telemetry.serial.print("msg,Facteur vitesse: ");
			telemetry.serial.println(speedFactor);
		}
	}
	delay(10);
}