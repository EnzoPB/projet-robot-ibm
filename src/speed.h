#include <infrared.h>

class Speed {
private:
    Infrared infrared;
    int dt = 1000;
public:
    float currentSpeed;
    Speed(int pin, int countPerTurn): infrared(pin, countPerTurn) {}
    void init();
    void tick();
};