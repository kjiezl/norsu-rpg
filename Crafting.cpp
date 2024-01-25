#include "Crafting.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PauseMenu.h"

Crafting::Crafting(RenderWindow& window) : window(window), pauseMenu(window),
showSecond(false), showBox1(false), showBox2(false), showBox3(false), inv(window),
weapon1Clicked(false), weapon2Clicked(false), weapon3Clicked(false), weapon4Clicked(false),
playerChosen(false), playerChosen2(false), weapon5Clicked(false), weapon6Clicked(false) {
	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");

	craftText.setFont(font);
	weapon1Text.setFont(font);
	weapon2Text.setFont(font);
	weapon3Text.setFont(font);
	weapon4Text.setFont(font);
	weapon5Text.setFont(font);
	weapon6Text.setFont(font);

	craftWinTex1.loadFromFile("sprites\\ui\\crafting1.png");
	craftWinTex2.loadFromFile("sprites\\ui\\crafting2.png");

	craftWin1.setTexture(craftWinTex1);
	craftWin2.setTexture(craftWinTex2);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	box2.setFillColor(Color::Black);
	box3.setFillColor(Color::Black);

	init();
}

Crafting::~Crafting() {

}

void Crafting::init() {
	craftWin1.setScale(5.0f, 5.0f);
	craftWin2.setScale(5.0f, 5.0f);

	craftWin1.setPosition(100, 150);
	craftWin2.setPosition(100, 150);

	craftText.setString("Choose a weapon to craft");
	craftText.setCharacterSize(25);
	craftText.setOutlineColor(Color::Black);
	craftText.setOutlineThickness(3);
	craftText.setPosition(250, 100);

	box1.setFillColor(Color(255, 255, 255, 0));
	box1.setOutlineColor(Color::White);
	box1.setOutlineThickness(5);
	box1.setPosition(105, 155);
	box1.setSize(Vector2f(525, 155));

	weapon1Text.setString("< RANGED LIGHTER >\n\t\tDeals continuous damage overtime");
	weapon1Text.setCharacterSize(25);
	weapon1Text.setOutlineColor(Color::Black);
	weapon1Text.setOutlineThickness(3);
	weapon1Text.setPosition(750, 300);

	box2.setFillColor(Color(255, 255, 255, 0));
	box2.setOutlineColor(Color::White);
	box2.setOutlineThickness(5);
	box2.setPosition(105, 320);
	box2.setSize(Vector2f(525, 150));

	weapon2Text.setString("< FROSTED SPITBALL >\n\t\tSlows the enemies for a few seconds");
	weapon2Text.setCharacterSize(25);
	weapon2Text.setOutlineColor(Color::Black);
	weapon2Text.setOutlineThickness(3);
	weapon2Text.setPosition(750, 300);

	box3.setFillColor(Color(255, 255, 255, 0));
	box3.setOutlineColor(Color::White);
	box3.setOutlineThickness(5);
	box3.setPosition(105, 480);
	box3.setSize(Vector2f(525, 150));

	weapon3Text.setString("< STAPLER GUN >\n\t\tDeals more damage, but less firerate");
	weapon3Text.setCharacterSize(25);
	weapon3Text.setOutlineColor(Color::Black);
	weapon3Text.setOutlineThickness(3);
	weapon3Text.setPosition(750, 300);

	weapon4Text.setString("< PEPPER GUN >\n\t\tDeals continuous damage overtime");
	weapon4Text.setCharacterSize(25);
	weapon4Text.setOutlineColor(Color::Black);
	weapon4Text.setOutlineThickness(3);
	weapon4Text.setPosition(750, 300);

	weapon5Text.setString("< ICE GUN >\n\t\tSlows the enemies for a few seconds");
	weapon5Text.setCharacterSize(25);
	weapon5Text.setOutlineColor(Color::Black);
	weapon5Text.setOutlineThickness(3);
	weapon5Text.setPosition(750, 300);

	weapon6Text.setString("< NAIL GUN >\n\t\tDeals more damage, but less firerate");
	weapon6Text.setCharacterSize(25);
	weapon6Text.setOutlineColor(Color::Black);
	weapon6Text.setOutlineThickness(3);
	weapon6Text.setPosition(750, 300);
}

void Crafting::handleInput() {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}

		if (event.type == Event::MouseButtonPressed) {
			//Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(pixelPos);

			if (box1.getGlobalBounds().contains(worldPos)) {
				if (!showSecond) {
					weapon1Clicked = true;
					playerChosen = true;
				} 
				else{
					weapon4Clicked = true;
					playerChosen2 = true;
				}
				//std::cout << "weapon1 chosen" << std::endl;
			}
			else if (box2.getGlobalBounds().contains(worldPos)) {
				if (!showSecond) {
					weapon2Clicked = true;
					playerChosen = true;
				}
				else {
					weapon5Clicked = true;
					playerChosen2 = true;
				}
				//std::cout << "weapon2 chosen" << std::endl;
			}
			else if (box3.getGlobalBounds().contains(worldPos)) {
				if (!showSecond) {
					weapon3Clicked = true;
					playerChosen = true;
				}
				else {
					weapon6Clicked = true;
					playerChosen2 = true;
				}
				//std::cout << "weapon3 chosen" << std::endl;
			}
		}

		if (event.type == Event::MouseMoved) {
			Vector2i pixelPos = Mouse::getPosition(window);
			Vector2f worldPos = window.mapPixelToCoords(pixelPos);
			if (box1.getGlobalBounds().contains(static_cast<Vector2f>(worldPos))) {
				showBox1 = true;
			}
			else if (box2.getGlobalBounds().contains(static_cast<Vector2f>(worldPos))) {
				showBox2 = true;
				showBox1 = false;
				showBox3 = false;
			}
			else if (box3.getGlobalBounds().contains(static_cast<Vector2f>(worldPos))) {
				showBox3 = true;
				showBox1 = false;
				showBox2 = false;
			}
			else {
				showBox1 = false;
				showBox2 = false;
				showBox3 = false;
			}
		}
	}
}

void Crafting::update() {
	
}

bool Crafting::weapon1Chosen() {
	return weapon1Clicked;
}

bool Crafting::weapon2Chosen() {
	return weapon2Clicked;
}

bool Crafting::weapon3Chosen() {
	return weapon3Clicked;
}

bool Crafting::doneChoosing() {
	return playerChosen;
}

bool Crafting::weapon4Chosen() {
	return weapon4Clicked;
}

bool Crafting::weapon5Chosen() {
	return weapon5Clicked;
}

bool Crafting::weapon6Chosen() {
	return weapon6Clicked;
}

bool Crafting::doneChoosing2() {
	return playerChosen2;
}

void Crafting::showSecondSet(bool yes) {
	if (yes) {
		showSecond = true;
		playerChosen = false;
		weapon1Clicked = false;
		weapon2Clicked = false;
		weapon3Clicked = false;
	}
}

void Crafting::render() {
	window.setView(window.getDefaultView());
	if (!showSecond) {
		window.draw(blackBG);
		window.draw(craftWin1);
		if (showBox1) {
			window.draw(box1);
			window.draw(weapon1Text);
		}
		else if (showBox2) {
			window.draw(box2);
			window.draw(weapon2Text);
		}
		else if (showBox3) {
			window.draw(box3);
			window.draw(weapon3Text);
		}
		window.draw(craftText);
	}
	else {
		window.draw(blackBG);
		window.draw(craftWin2);
		if (showBox1) {
			window.draw(box1);
			window.draw(weapon4Text);
		}
		else if (showBox2) {
			window.draw(box2);
			window.draw(weapon5Text);
		}
		else if (showBox3) {
			window.draw(box3);
			window.draw(weapon6Text);
		}
		window.draw(craftText);
	}

	inv.updateTextPos();
	inv.render();
}