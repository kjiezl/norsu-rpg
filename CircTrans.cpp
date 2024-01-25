#include "CircTrans.h"
#include <SFML/Graphics.hpp>

using namespace sf;

CircTrans::CircTrans(RenderWindow& window) : window(window), transComplete(false) {
	texture.loadFromFile("sprites\\ui\\circletrans2.png");
	circleTrans.setTexture(texture);

	totalTime = 0.0f;

	transRect.width = 1280;
	transRect.height = 720;
	currentImage.x = 0;

	switchTime = 0.6f;
}

CircTrans::~CircTrans() {

}
 
void CircTrans::update(float dt) {
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

void CircTrans::render() {
	circleTrans.setTextureRect(transRect);
	window.draw(circleTrans);
}

bool CircTrans::isOutTransComplete() const {
	return transComplete;
}