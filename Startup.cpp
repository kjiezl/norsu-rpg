#include "Startup.h"
#include "BlackFadeTransition.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Startup::Startup(RenderWindow& window) : window(window), startLogo(false), startCount(false), animComplete(false), logoComplete(false) {
	logoTexture.loadFromFile("sprites\\ui\\sglogo-anim.png");
	logo1Texture.loadFromFile("sprites\\ui\\sglogo.png");
	logoSprite.setTexture(logoTexture);
	logo1Sprite.setTexture(logo1Texture);
	totalTime = 0.0f;
	switchTime = 0.07f;
	currentImage.x = 0;
	logoRect.width = logoTexture.getSize().x / 6;
	logoRect.height = logoTexture.getSize().y / 2;

	whiteBG.setFillColor(Color::White);
	whiteBG.setSize(Vector2f(window.getSize().x, window.getSize().y));
	logoSprite.setScale(Vector2f(0.5f, 0.5f));
	logo1Sprite.setScale(Vector2f(0.5f, 0.5f));
	logoSprite.setPosition(450, 150);
	logo1Sprite.setPosition(450, 150);

	logoBuffer.loadFromFile("sprites\\bgm\\logo.flac");
	logoBGM.setBuffer(logoBuffer);
}

Startup::~Startup() {

}

void Startup::handleInput () {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}
	}
}

void Startup::update() {
	float timeElapsed = clock.getElapsedTime().asSeconds();

	if (timeElapsed >= 9) {
		startLogo = true;
	}
	if (startCount) {
		cout << "Time elapsed: " << timeElapsed << endl;
		if (timeElapsed >= 17) {
			logoComplete = true;
		}
	}
}

void Startup::animUpdate(float dt) {

	if (startLogo) {
		currentImage.y = 0;
		totalTime += dt;
		if (totalTime >= switchTime) {
			totalTime -= switchTime;
			currentImage.x++;
			if (currentImage.x >= 6) {
				animComplete = true;
			}
		}

		logoRect.left = currentImage.x * logoRect.width;
		logoRect.top = currentImage.y * logoRect.height;
	}
}

void Startup::render() {
	logoSprite.setTextureRect(logoRect);
	window.setView(window.getDefaultView());
	window.draw(whiteBG);
	if (startLogo) {
		window.draw(logoSprite);
	}

	if (animComplete) {
		startCount = true;
		window.draw(logo1Sprite);
	}
}

bool Startup::startComplete() {
	return logoComplete;
}