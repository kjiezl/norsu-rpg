#include "LoadingScreen.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

LoadingScreen::LoadingScreen(RenderWindow& window) : window(window), loadComplete(false) {
	blackTexture.loadFromFile("sprites\\background\\black.png");
	black.setTexture(blackTexture);
	black.setScale(Vector2f(window.getSize().x, window.getSize().y));
	charTexture.loadFromFile("sprites\\characters\\elrico.png");
	charbwTexture.loadFromFile("sprites\\characters\\elricobw.png");
	charSprite.setTexture(charTexture);
	char2.setTexture(charbwTexture);
	char3.setTexture(charbwTexture);

	currentImage.x = 0;
	totalTime = 0;
	switchTime = 0.1f;

	charRect.width = charTexture.getSize().x / 4;
	charRect.height = charTexture.getSize().y / 4;

	char2.setColor(Color(255, 255, 255, 115));
	char3.setColor(Color(255, 255, 255, 70));
}

LoadingScreen::~LoadingScreen() {

}

void LoadingScreen::initLoadingScreen() {
	loadComplete = false;
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}
	}

	charSprite.setPosition(Vector2f(1000, 500));
	char2.setPosition(Vector2f(900, 500));
	char3.setPosition(Vector2f(800, 500));
}

void LoadingScreen::update(float dt) {
	loadComplete = false;
	currentImage.y = 0;
	totalTime += dt;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= 4) {
			currentImage.x = 0;
		}
	}

	charRect.left = currentImage.x * charRect.width;
	charRect.top = currentImage.y * charRect.height;

	float getElapsedTime = clock.getElapsedTime().asSeconds();

	if (getElapsedTime >= 2) {
		loadComplete = true;
	}
	std::cout << "elapsed time: " << getElapsedTime << std::endl;
}

void LoadingScreen::render() {
	charSprite.setScale(4.0f, 4.0f);
	//char2.setScale(4.5f, 4.5f);
	//char3.setScale(4.0f, 4.0f);
	char2.setScale(4.0f, 4.0f);
	char3.setScale(4.0f, 4.0f);
	window.draw(black);
	charSprite.setTextureRect(charRect);
	char2.setTextureRect(charRect);
	char3.setTextureRect(charRect);
	window.draw(char3);
	window.draw(char2);
	window.draw(charSprite);
}

bool LoadingScreen::loadingComplete() const {
	return loadComplete;
}

void LoadingScreen::clockRestart() {
	clock.restart();
}

void LoadingScreen::loadCompleteFalse() {
	loadComplete = false;
}