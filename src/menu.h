#include <Adafruit_SSD1306.h>

class Menu {
private:
	int maxItems = 4; // nombre max d'élements par page
	int itemHeight = 32/this->maxItems;
	int page = 0;
	int maxPages;
	Adafruit_SSD1306 display;
public:
	int position;
	Menu(): display(128, 32, &Wire) {}
	void init();
	void draw(String menuArr[10], int menuSize);
};