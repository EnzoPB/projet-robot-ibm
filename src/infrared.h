class Infrared {
private:
    int pin;
    bool lastState;
public:
    void init(int pin);
    void tick();
    int count = 0;
};