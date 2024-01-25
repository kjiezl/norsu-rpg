#include "HealthCount.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

HealthCount::HealthCount(RenderWindow& window) : window(window), showText(true) {
	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");
	healthText.setFont(font);

	init();
}

HealthCount::~HealthCount() {

}

void HealthCount::init() {
	healthText.setFillColor(Color::White);
	healthText.setCharacterSize(30);
	healthText.setOutlineColor(Color::Black);
	healthText.setOutlineThickness(2);
}

void HealthCount::showHealth(Vector2f ghostPos, int count) {
	showText = true;
	healthText.setPosition(ghostPos.x + 10, ghostPos.y - 30);
	healthText.setString(to_string(count - 1));
}

void HealthCount::showHealthBoss(Vector2f ghostPos, int count) {
	showText = true;
	healthText.setPosition(ghostPos.x + 200, ghostPos.y + 10);
	healthText.setString(to_string(count - 1));
}

void HealthCount::showHealthBoss2(Vector2f ghostPos, int count) {
	showText = true;
	healthText.setPosition(ghostPos.x + 200, ghostPos.y + 10);
	healthText.setString(to_string(count - 1));
}

void HealthCount::disableCount() {
	showText = false;
}

void HealthCount::render() {
	if (showText) {
		window.draw(healthText);
	}
}