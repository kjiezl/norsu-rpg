#include "Inventory.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

int Inventory::item1Count = 0;
int Inventory::item2Count = 0;
int Inventory::item3Count = 0;

Inventory::Inventory(RenderWindow& window) : window(window), crafted1(false),
crafted2(false), crafted3(false), crafted4(false), crafted5(false), crafted6(false) {
	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");

	item1Text.setFont(font);
	item2Text.setFont(font);
	item3Text.setFont(font);

	item1Tex.loadFromFile("sprites\\items\\match.png");
	item2Tex.loadFromFile("sprites\\items\\ice.png");
	item3Tex.loadFromFile("sprites\\items\\metal.png");

	item1.setTexture(item1Tex);
	item2.setTexture(item2Tex);
	item3.setTexture(item3Tex);

	init();
}

Inventory::~Inventory() {

}

void Inventory::init() {

	item1Text.setString(" " + to_string(item1Count));
	item1Text.setCharacterSize(20);
	item1Text.setOutlineColor(Color::Black);
	item1Text.setOutlineThickness(3);

	item2Text.setString(" " + to_string(item2Count));
	item2Text.setCharacterSize(20);
	item2Text.setOutlineColor(Color::Black);
	item2Text.setOutlineThickness(3);

	item3Text.setString(" " + to_string(item3Count));
	item3Text.setCharacterSize(20);
	item3Text.setOutlineColor(Color::Black);
	item3Text.setOutlineThickness(3);

	item1.setPosition(1200, 400);
	item2.setPosition(1200, 450);
	item3.setPosition(1200, 500);

	item1.setScale(2.0f, 2.0f);
	item2.setScale(2.0f, 2.0f);
	item3.setScale(2.0f, 2.0f);
}

void Inventory::addItem1() {
	item1Count += 1;
}

void Inventory::addItem2() {
	item2Count += 1;
}

void Inventory::addItem3() {
	item3Count += 1;
}

void Inventory::weapon1Crafted() {
	if (!crafted1) {
		item1Count -= 2;
		item3Count -= 1;
		crafted1 = true;
	}
}

void Inventory::weapon2Crafted() {
	if (!crafted2) {
		item2Count -= 2;
		item3Count -= 1;
		crafted2 = true;
	}
}

void Inventory::weapon3Crafted() {
	if (!crafted3) {
		item3Count -= 4;
		crafted3 = true;
	}
}

void Inventory::weapon4Crafted() {
	if (!crafted4) {
		item1Count -= 4;
		item3Count -= 2;
		crafted4 = true;
	}
}

void Inventory::weapon5Crafted() {
	if (!crafted5) {
		item2Count -= 4;
		item3Count -= 2;
		crafted5 = true;
	}
}

void Inventory::weapon6Crafted() {
	if (!crafted6) {
		item3Count -= 8;
		crafted6 = true;
	}
}

void Inventory::updateTextPos() {
	item1Text.setPosition(1175, 405);
	item2Text.setPosition(1175, 455);
	item3Text.setPosition(1175, 505);
}

void Inventory::render() {
	item1Text.setString(" " + to_string(item1Count));
	item2Text.setString(" " + to_string(item2Count));
	item3Text.setString(" " + to_string(item3Count));

	window.draw(item1);
	window.draw(item2);
	window.draw(item3);

	window.draw(item1Text);
	window.draw(item2Text);
	window.draw(item3Text);
}

int Inventory::item1Total() {
	return item1Count;
}

int Inventory::item2Total() {
	return item2Count;
}

int Inventory::item3Total() {
	return item3Count;
}

float Inventory::calcuDistance(Vector2f v1, Vector2f v2) {
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	return sqrt(dx * dx + dy * dy);
}