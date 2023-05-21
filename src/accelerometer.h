class Accelerometer {
private:
	void setup_mpu_registers();
	void read_mpu_data();

	long loopTimer;

	long acc_x, acc_y, acc_z;

	long gyro_x_cal, gyro_y_cal, gyro_z_cal;

	//double rotation_x;
	//double rotation_y;
	double rotation_z;

	double tau = 0.98;

	const int cal_count = 1000;
public:
	void init();
	void callibrate();
	void loop();
	void reset();

	double freq, dt;

	double temperature;

	double accel_x, accel_y, accel_z;

	int gyro_x, gyro_y, gyro_z;

	//double roll = 0
	//double pitch = 0
	double yaw = 0;

	//double gyroRoll
	//double gyroPitch;
	double gyroYaw;

	//double accelPitch;
	//double accelRoll;
	double accelYaw;
};