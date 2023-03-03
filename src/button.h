class Button {
private:
	bool previousState;
public:
	int pin;
	Button(int pin);
	bool isPressed();
};