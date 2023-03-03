#include <telemetry.h>
#include <SoftwareSerial.h>

void Telemetry::init() {
    this->serial.begin(9600);
    this->serial.println("XBee started");
}

void Telemetry::sendData(String data[]) {

}