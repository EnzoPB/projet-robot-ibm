// https://github.com/MarkSherstan/MPU-6050-9250-I2C-CompFilter

#include <accelerometer.h>
#include <Arduino.h>
#include <Wire.h>

// 250 deg/s --> 131.0, 500 deg/s --> 65.5, 1000 deg/s --> 32.8, 2000 deg/s --> 16.4
const long scaleFactorGyro = 65.5;

// 2g --> 16384 , 4g --> 8192 , 8g --> 4096, 16g --> 2048
const long scaleFactorAccel = 8192;


void Accelerometer::init() {
	Wire.begin();

	// setup the registers of the MPU-6050
	this->setup_mpu_registers();

	this->callibrate();
}

int loopTimer2;

void Accelerometer::loop() {
	// we have to respect a frequency of 250hz
	// so we wait until it has not been 4000us (period of 250hz) since the last loop

	
	if (4000 - (micros() - loopTimer) > 0)
		delayMicroseconds(4000 - (micros() - loopTimer));


	freq = 1/((micros() - loopTimer) * 1e-6);
	loopTimer = micros();
	dt = 1/freq;

	// read the raw data from the MPU
	this->read_mpu_data();

	// subtract the offset calibration value
	gyro_x -= gyro_x_cal; // ( freq / 250.0 );
	gyro_y -= gyro_y_cal; // ( freq / 250.0 );
	gyro_z -= gyro_z_cal; // ( freq / 250.0 );


	// convert to instantaneous degrees per second
	//rotation_x = (double)gyro_x / (double)scaleFactorGyro;
	//rotation_y = (double)gyro_y / (double)scaleFactorGyro;
	rotation_z = (double)gyro_z / (double)scaleFactorGyro;

	// convert to g force
	accel_x = (double)acc_x / (double)scaleFactorAccel;
	accel_y = (double)acc_y / (double)scaleFactorAccel;
	accel_z = (double)acc_z / (double)scaleFactorAccel;

	// complementary filter
	//accelPitch = atan2(accel_y, accel_z) * RAD_TO_DEG;
	//accelRoll = atan2(accel_x, accel_z) * RAD_TO_DEG;
	accelYaw = atan2(accel_z, accel_x) * RAD_TO_DEG;

	//pitch = (tau)*(pitch + rotation_x*dt) + (1-tau)*(accelPitch);
	//roll = (tau)*(roll - rotation_y*dt) + (1-tau)*(accelRoll);
	yaw = (tau)*(yaw - rotation_z*dt) + (1-tau)*(accelYaw);

	//gyroPitch += rotation_x*dt;
	//gyroRoll -= rotation_y*dt;
	gyroYaw += rotation_z*dt;
}

void Accelerometer::reset() {
	//gyroPitch = 0;
	//gyroRoll = 0;
	gyroYaw = 0;
	accelYaw = 0;
	rotation_z = 0;
	yaw = 0;

	accel_x = 0;
	accel_y = 0;
	accel_z = 0;

	acc_x = 0;
	acc_y = 0;
	acc_z = 0;

	gyro_x = 0;
	gyro_y = 0;
	gyro_z = 0;
}

void Accelerometer::read_mpu_data() {
	// subroutine for reading the raw data
	Wire.beginTransmission(0x68);
	Wire.write(0x3B);
	Wire.endTransmission();
	Wire.requestFrom(0x68, 14);

	// read & save data 
	acc_x = Wire.read() << 8 | Wire.read();
	acc_y = Wire.read() << 8 | Wire.read();
	acc_z = Wire.read() << 8 | Wire.read();
	temperature = (Wire.read() << 8 | Wire.read()) / 340.0 + 36.53;
	gyro_x = Wire.read() << 8 | Wire.read();
	gyro_y = Wire.read() << 8 | Wire.read();
	gyro_z = Wire.read() << 8 | Wire.read();
}

void Accelerometer::callibrate() {
	// take 'cal_count' readings for each coordinate and then find average offset
	loopTimer = micros();
	for (int cal_int = 0; cal_int < cal_count; cal_int ++) {
		delayMicroseconds(10000 - (micros() - loopTimer));

		loopTimer = micros();

		this->read_mpu_data();
		gyro_x_cal += gyro_x;
		gyro_y_cal += gyro_y;
		gyro_z_cal += gyro_z;

	}

	// Average the values
	gyro_x_cal /= cal_count;
	gyro_y_cal /= cal_count;
	gyro_z_cal /= cal_count;
	delay(2000);
}


void Accelerometer::setup_mpu_registers() {
  // activate the MPU-6050
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  // configure the accelerometer
  // 2g --> 0x00, 4g --> 0x08, 8g --> 0x10, 16g --> 0x18
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x08);
  Wire.endTransmission();

  // configure the gyro
  // 250 deg/s --> 0x00, 500 deg/s --> 0x08, 1000 deg/s --> 0x10, 2000 deg/s --> 0x18
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
}
