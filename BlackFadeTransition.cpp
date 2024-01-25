#include "BlackFadeTransition.h"
#include <SFML/Graphics.hpp>

using namespace sf;

BlackFadeTransition::BlackFadeTransition(RenderWindow& window) : window(window), fadedIn(false), fadedOut(false){
	fadeTexture.loadFromFile("sprites\\ui\\fade.png");
	fade.setTexture(fadeTexture);
	fade.setScale(Vector2f(window.getSize().x, window.getSize().y));

	totalTime = 0;
	switchTime = 0.3f;

	fadeRect.width = fadeTexture.getSize().x / 6;
	fadeRect.height = fadeTexture.getSize().y / 2;

	currentImage.x = 0;

	fade2.setTexture(fadeTexture);
	fade2.setScale(Vector2f(window.getSize().x, window.getSize().y));

	totalTime2 = 0;
	switchTime2 = 0.3f;

	fadeRect2.width = fadeTexture.getSize().x / 6;
	fadeRect2.height = fadeTexture.getSize().y / 2;

	currentImage2.x = 0;
}

BlackFadeTransition::~BlackFadeTransition() {

}

void BlackFadeTransition::updateIn(float dt) {
	currentImage.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= 6) {
			fadedIn = true;
		}
	}

	fadeRect.left = currentImage.x * fadeRect.width;
	fadeRect.top = currentImage.y * fadeRect.height;
}

void BlackFadeTransition::renderIn() {
	fade.setTextureRect(fadeRect);
	window.draw(fade);
}

bool BlackFadeTransition::isFadedIn() const {
	return fadedIn;
}

void BlackFadeTransition::updateOut(float dt) {
	currentImage2.y = 1;
	totalTime2 += dt;

	if (totalTime2 >= switchTime2) {
		totalTime2 -= switchTime2;
		currentImage2.x++;
		if (currentImage2.x >= 6) {
			fadedOut = true;
		}
	}

	fadeRect2.left = currentImage2.x * fadeRect2.width;
	fadeRect2.top = currentImage2.y * fadeRect2.height;
}

void BlackFadeTransition::renderOut() {
	fade2.setTextureRect(fadeRect2);
	window.draw(fade2);
}

bool BlackFadeTransition::isFadedOut() const {
	return fadedOut;
}

void BlackFadeTransition::fadedInFalse() {
	fadedIn = false;
	currentImage.x = 0;
	currentImage.y = 0;
}

void BlackFadeTransition::fadedOutFalse() {
	fadedOut = false;
	currentImage2.x = 0;
	currentImage2.y = 1;
}