#include "CircleTransition.h"
#include <SFML/Graphics.hpp>

using namespace sf;

CircleTransition::CircleTransition(RenderWindow& window) : window(window), transComplete(false){
	texture.loadFromFile("sprites\\ui\\circletrans.png");
	circleTrans.setTexture(texture);
	totalTime = 0.0f;

	transRect.width = 1280;
	transRect.height = 720;
	currentImage.x = 0;

	switchTime = 0.07f;
}

CircleTransition::~CircleTransition() {

}

void CircleTransition::update(float dt) {
	currentImage.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= 6) {
			transComplete = true;
		}
	}

	transRect.left = currentImage.x * transRect.width;
	transRect.top = currentImage.y * transRect.height;
}

void CircleTransition::render() {
	window.setView(window.getDefaultView());
	circleTrans.setTextureRect(transRect);
	window.draw(circleTrans);
}

bool CircleTransition::isInTransComplete() const {
	return transComplete;
}