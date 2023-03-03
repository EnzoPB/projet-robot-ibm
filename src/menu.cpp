#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <menu.h>

void Menu::init() {
	this->display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	this->display.clearDisplay();

	// text display tests
	this->display.setTextSize(1);
	this->display.setTextColor(WHITE);
}

void Menu::draw(String menuArr[10], int menuSize) {
	this->display.clearDisplay();
	this->display.setTextColor(WHITE);

	if (this->position == this->maxItems*(this->page+1)) { // si on arrive a la fin de la page
		this->page++;
	}

	if (this->position == menuSize) { // si on arrive à la fin de toute les pages
		this->position = 0;
		this->page = 0;
	}

	for (int i = 0; i < this->maxItems; i++) { // on affiche 4 élements par page
		int pagePos = (this->maxItems*this->page) + i;
		if (pagePos == menuSize) {
			break;
		}

		if (pagePos == this->position) {
			this->display.drawRect(0, this->itemHeight*i, 128, this->itemHeight, WHITE);
		}
		this->display.setCursor(2, this->itemHeight*i);
		this->display.println(menuArr[pagePos]);

		
	}


	this->display.setTextColor(BLACK);
	this->display.fillRect(128-18, 32-this->itemHeight, 18, this->itemHeight, WHITE);
	this->display.setCursor(128-18, 32-this->itemHeight);
	this->display.print(this->position+1);
	this->display.print("/");
	this->display.println(menuSize);

	this->display.display();

}