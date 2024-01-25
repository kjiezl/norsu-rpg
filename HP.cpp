#include "HP.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

using namespace sf;
using namespace std;

HP::HP(RenderWindow& window, float maxHealth) : window(window), dead(false),
maxHealth(maxHealth), currentHealth(maxHealth) {
	
	barTex.loadFromFile("sprites\\ui\\hp-bar.png");
	fillTex.loadFromFile("sprites\\ui\\hp-fill.png");

	barSprite.setTexture(barTex);
	fillSprite.setTexture(fillTex);

	init();
}

HP::~HP() {

}

void HP::init() {
	barSprite.setScale(0.15f, 0.15f);
	fillSprite.setScale(0.15f, 0.15f);

	barSprite.setPosition(5, 50);
	fillSprite.setPosition(5, 50);
}

void HP::update() {
	if (currentHealth <= 0) {
		dead = true;
	}
}

bool HP::noHP() {
	return dead;
}

void HP::damage(float hit) {
	setHealth(currentHealth - hit);
}

void HP::resetHealth() {
	currentHealth = maxHealth;
	float scale = 1.0f;
	fillSprite.setScale(scale * 0.15f, 0.15f);
	dead = false;
}

void HP::setHealth(float maxH) {
	//cout << maxHealth << endl;
	cout << currentHealth << endl;
	currentHealth = max(0.0f, min(maxH, currentHealth));
	float scale = currentHealth / maxHealth;
	fillSprite.setScale(scale * 0.15f, 0.15f);
}

void HP::render() {
	window.draw(barSprite);
	window.draw(fillSprite);
}