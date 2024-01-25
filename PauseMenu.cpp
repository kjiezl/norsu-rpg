#include "PauseMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

PauseMenu::PauseMenu(RenderWindow& window) : window(window), resumePressed(false), quitGamePressed(false), selectedButton(-1) {
	font.loadFromFile("C:\\Users\\kjiez\\OneDrive\\Desktop\\ehh\\font\\pixeboy-font\\Pixeboy-z8XGD.ttf");

	overlay.setSize(Vector2f(window.getSize().x, window.getSize().y));
	overlay.setFillColor(Color(0, 0, 0, 4));

	initPauseMenu();
}

PauseMenu::~PauseMenu() {

}

void PauseMenu::initPauseMenu() {

	//overlay.setSize(Vector2f(window.getSize().x, window.getSize().y));
	//overlay.setFillColor(Color(0, 0, 0, 4));

	resumeText.setFont(font);
	resumeText.setCharacterSize(30);
	resumeText.setString("Resume");
	resumeText.setPosition(window.getSize().x / 2 - resumeText.getLocalBounds().width / 2, window.getSize().y / 2 - 50);

	quitGameText.setFont(font);
	quitGameText.setCharacterSize(30);
	quitGameText.setString("Quit Game");
	quitGameText.setPosition(window.getSize().x / 2 - quitGameText.getLocalBounds().width / 2, window.getSize().y / 2 + 50);

	gamePausedText.setFont(font);
	gamePausedText.setCharacterSize(90);
	gamePausedText.setString("GAME PAUSED");
	gamePausedText.setPosition(window.getSize().x / 2 - gamePausedText.getLocalBounds().width / 2, window.getSize().y / 2 - 250);
	gamePausedText.setFillColor(Color::Yellow);
}

void PauseMenu::handleInput() {

	resumePressed = false;

	Event event;

	if (window.pollEvent(event)) {
		//cout << "in pause handle input" << endl;
		if (event.type == Event::Closed) {
			window.close();
		}

		if (event.type == Event::KeyPressed) {

			if (event.key.code == Keyboard::Up) {
				moveUp();
			}
			else if (event.key.code == Keyboard::Down) {
				moveDown();
			}
			else if (event.key.code == Keyboard::Enter) {
				if (selectedButton == 0) {
					resumePressed = true;
					selectedButton = -1;
				}
				else if (selectedButton == 1) {
					quitGamePressed = true;
				}
			}
		}

		if (event.type == Event::MouseButtonPressed) {
			Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
			
			if (resumeText.getGlobalBounds().contains(mousePos)) {
				resumePressed = true;
				selectedButton = -1;
			}
			else if (quitGameText.getGlobalBounds().contains(mousePos)) {
				quitGamePressed = true;
			}
		}

		if (event.type == Event::MouseMoved) {
			Vector2i mousePos = Mouse::getPosition(window);
			if (resumeText.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				selectedButton = 0;
			}
			else if (quitGameText.getGlobalBounds().contains(static_cast<Vector2f>(mousePos))) {
				selectedButton = 1;
			}
		}
	}
}

void PauseMenu::moveUp() {
	if (selectedButton > 0) {
		resumeText.setFillColor(Color::White);
		quitGameText.setFillColor(Color::White);
		selectedButton--;

		if (selectedButton == 0) {
			resumeText.setFillColor(Color::Blue);
		}
		else if (selectedButton == 1) {
			quitGameText.setFillColor(Color::Blue);
		}
	}
}

void PauseMenu::moveDown() {
	if (selectedButton < 1) {
		resumeText.setFillColor(Color::White);
		quitGameText.setFillColor(Color::White);
		selectedButton++;

		if (selectedButton == 0) {
			resumeText.setFillColor(Color::Blue);
		}
		else if (selectedButton == 1) {
			quitGameText.setFillColor(Color::Blue);
		}
	}
}

void PauseMenu::updateButtonState() {
	if (selectedButton == 0) {
		resumeText.setFillColor(Color::Blue);
		quitGameText.setFillColor(Color::White);
	}
	else if (selectedButton == 1) {
		resumeText.setFillColor(Color::White);
		quitGameText.setFillColor(Color::Blue);
	}
	else {
		resumeText.setFillColor(Color::White);
		quitGameText.setFillColor(Color::White);
	}
}

void PauseMenu::update() {
	updateButtonState();
}

void PauseMenu::render() {
	window.draw(overlay);
	window.draw(gamePausedText);
	window.draw(resumeText);
	window.draw(quitGameText);
	window.display();
}

bool PauseMenu::resumeButtonPressed()const {
	return resumePressed;
}

bool PauseMenu::quitGameButtonPressed() const {
	return quitGamePressed;
}