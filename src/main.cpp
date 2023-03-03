#include <Arduino.h>

#ifdef MENU_ENABLE
#include <menu.h>
#include <menuList.h>
#endif
#include <button.h>
#include <motor.h>
#include <telemetry.h>

#define DIAMETRE_ROUE = 6.5
#define CIRC_ROUE = 6.5*3.14

Telemetry telemetry(2, 3);
MotorWrapper motor(5);
Button button(6);
#ifdef MENU_ENABLE
Menu menu;
#endif

void setup()
{
	Serial.begin(9600);

	telemetry.init();
	motor.init();
	#ifdef MENU_ENABLE
	menu.init();
	#endif

	Serial.println(F("Serial started"));
}

void loop() {
	/*if(xbee.available()) {
		String input = xbee.readString();
		int command = input.substring(0, 2).toInt();
		int value = input.substring(2).toInt();

		switch (command)
		{
		case 13:
			Serial.println("cmd13");
			break;
		
		default:
			break;
		}

	}*/
	
}


/*
int currentMenu = 0;

void loop() {
	switch (currentMenu) {
	case 0: // menu principal
		menu.draw(mainMenu, 2);
		break;
	case 1: // menu communication
		menu.draw(commMenu, 4);
		break;
	case 99: // pas de menu
		display.clearDisplay();
		delay(100);
		display.setCursor(0,0);
		display.println("ok");
		Serial.println("aok");
		break;
	default:
		break;
	}

	if (button1.isPressed()) { // boutton navigation
		menu.position++;
	}

	if (button2.isPressed()) { // boutton validation
		if (currentMenu == 99) {
			currentMenu = 0;
			menu.position = 0;
			Serial.println("vieeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeete");
		} else if(currentMenu == 0 && menu.position == 0) { // accueil -> communications
			currentMenu = 1;
			menu.position = 0;
		} else if (currentMenu == 1 && menu.position == 3) { // communication -> accueil
			currentMenu = 0;
			menu.position = 0;
		} else if (currentMenu == 1 && menu.position == 1) { // données reçues
			currentMenu = 99;

		}
	}
}
*/