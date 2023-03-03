#include <SoftwareSerial.h>

class SoftwareSerial; //this might be unnecessary, but doesn't hurt to have it.
class Telemetry {
public:
    Telemetry(int rx, int tx): serial(rx, tx) {}

    void sendData(String data[]);
    void init();

private:
    SoftwareSerial serial;
};