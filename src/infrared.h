class Infrared {
private:
    int pin;
    bool lastState;
    int startTime;
    int countPerTurn;
public:
    Infrared(int pin, int countPerTurn);
    void init();
    void tick();
    void reset();
    float count = 0;
};