#include "PlayerName.h"
#include "Game.h"
#include "Skylab.h"
#include "SkylabRoom.h"
#include "BlackFadeTransition.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

PlayerName::PlayerName(RenderWindow& window) : window(window), playerName(""), showElrico(true), nameEntered(false), fadeTrans(window) {

	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");

	bgTexture.loadFromFile("sprites\\background\\samplebg5.gif");
	bg.setTexture(bgTexture);
	//bgScale = Vector2f(2.4f, 2.6f); //samplebg.jpg
	//bgScale = Vector2f(2.4f, 2.2f); //samplebg2.jpg
	//bgScale = Vector2f(2.35f, 1.5f); //samplebg3.jpg
	//bgScale = Vector2f(2.4f, 2.55f); //samplebg4.jpg
	bgScale = Vector2f(1.8f, 1.7f); //samplebg5.gif
	
	nameInputTexture.loadFromFile("sprites\\ui\\button.png");
	nameInput.setTexture(nameInputTexture);
	nameScale = Vector2f(0.5f, 0.5f);

	elricoText.setFont(font);
	elricoText.setCharacterSize(70);
	elricoText.setString("Elrico");
	Color elricoTextColor(193, 45, 87);
	elricoText.setFillColor(elricoTextColor);

	playerNameText.setFont(font);
	playerNameText.setCharacterSize(70);
	playerNameText.setString("");
	playerNameText.setFillColor(Color::White);

	initPlayer();
}

PlayerName::~PlayerName() {

}

void PlayerName::initPlayer() {
	//elricoText.setPosition(window.getSize().y - 180, window.getSize().x / 4);
	elricoText.setPosition(camera.getCenter().x - elricoText.getLocalBounds().width / 2, camera.getCenter().y - 50);

	//nameInput.setPosition(window.getSize().x / 2 - 185, window.getSize().y / 4 + 120);
	nameInput.setPosition(camera.getCenter().x - 185, camera.getCenter().y - 70);
}

void PlayerName::handleInput() {
	Event event;

	camera.setSize(window.getSize().x, window.getSize().y);

	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}

		if (event.type == Event::TextEntered) {
			if (showElrico) {
				playerName.clear();
				showElrico = false;
			}

			// for backspace
			if (event.text.unicode == 8 && !playerName.empty()) {
				playerName.pop_back();
			}
			// add ascii characters
			else if (event.text.unicode < 128) {
				playerName += static_cast<char>(event.text.unicode);
			}
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Enter)){
			nameEntered = true;
		}
	}

	if (!playerName.empty()) {
		playerNameText.setPosition(camera.getCenter().x - playerNameText.getLocalBounds().width / 2, camera.getCenter().y - 50);
	}
}

void PlayerName::update() {
	dt = clock.restart().asSeconds();
}

void PlayerName::render() {
	window.clear();
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.setView(camera);
	bg.setScale(bgScale);
	nameInput.setScale(nameScale);
	window.setView(window.getDefaultView());
	window.draw(bg);
	window.setView(camera);
	window.draw(nameInput);

	if (showElrico) {
		window.draw(elricoText);
	}
	else {
		playerNameText.setString(playerName);
		window.draw(playerNameText);
	}

	if (!fadeTrans.isFadedOut()) {
		window.setView(window.getDefaultView());
		fadeTrans.updateOut(dt);
		fadeTrans.renderOut();
	}


	window.display();
}

bool PlayerName::getEnter() const {
	return nameEntered;
}

const string& PlayerName::getPlayerName() const {
	return playerName;
}

void PlayerName::setSkylab() {
	//Skylab skylab(window, playerName);
}

void PlayerName::setSkylabRoom() {
	SkylabRoom skylabRoom(window, playerName);
}