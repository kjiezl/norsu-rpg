#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

Menu::Menu(RenderWindow& window) : window(window), selectedButton(-1), startPressed(false) {

	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");
	button.loadFromFile("sprites\\ui\\button.png");
	bgTexture.loadFromFile("sprites\\background\\menubg.png");
	button1.loadFromFile("sprites\\ui\\button.png");
	petalsTexture.loadFromFile("sprites\\background\\petals.png");
	menuBuffer.loadFromFile("sprites\\bgm\\menu.flac");
	/*titleTex.loadFromFile("sprites\\ui\\title.png");
	title.setTexture(titleTex);*/
	menuBGM.setBuffer(menuBuffer);

	startScale = Vector2f(0.5f, 0.5f);

	totalTime = 0.0f;
	switchTime = 0.3f;
	bgRect.width = bgTexture.getSize().x / 6;
	bgRect.height = bgTexture.getSize().y;
	currentImage.x = 0;
	
	totalTime2 = 0.0f;
	switchTime2 = 0.4f;
	currentImage2.x = 0;
	petalsRect.width = petalsTexture.getSize().x / 9;
	petalsRect.height = petalsTexture.getSize().y;

	initButtons();
}

Menu::~Menu() {

}

void Menu::initButtons() {
	buttonText.setFont(font);
	button1Text.setFont(font);
	buttonText.setString("START");
	button1Text.setString("EXIT");
	buttonText.setCharacterSize(100);
	button1Text.setCharacterSize(100);
	bg.setTexture(bgTexture);
	petals.setTexture(petalsTexture);
	startButton.setTexture(button);
	startButton.setPosition(450, 300);

	exitButton.setTexture(button1);
	exitButton.setPosition(450, 500);

	buttonText.setPosition(520, 300);
	button1Text.setPosition(545, 500);

	bg.setPosition(0, 0);

	//title.setPosition(200, 200);
}

void Menu::handleInput() {
	Event event;

	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}

		else if (Keyboard::isKeyPressed(Keyboard::Up)) {
			moveUp();
		} 
		
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			moveDown();
		}

		else if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			
			if (selectedButton == 0) {
				startPressed = true;
			}
			else if (selectedButton == 1) {
				window.close();
			}
		}
	}

	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f worldPos = window.mapPixelToCoords(pixelPos);
	//Vector2i mousePos = Mouse::getPosition(window);

	if (startButton.getGlobalBounds().contains(static_cast<Vector2f>(worldPos))) {
		selectedButton = 0;
		if (Mouse::isButtonPressed(Mouse::Left)) {
			startPressed = true;
		}
	}
	else if (exitButton.getGlobalBounds().contains(static_cast<Vector2f>(worldPos))) {
		selectedButton = 1;
		if (Mouse::isButtonPressed(Mouse::Left)) {
			window.close();
		}
	}
}

void Menu::moveUp() {
	if (selectedButton > 0) {
		startButton.setColor(Color::White);
		exitButton.setColor(Color::White);
		selectedButton--;

		if (selectedButton == 0) {
			startButton.setColor(Color::Blue);
		}
		else if (selectedButton == 1) {
			exitButton.setColor(Color::Blue);
		}
	}
}

void Menu::moveDown() {
	if (selectedButton < 1) {
		startButton.setColor(Color::White);
		exitButton.setColor(Color::White);
		selectedButton++;

		if (selectedButton == 0) {
			startButton.setColor(Color::Blue);
		}
		else if (selectedButton == 1) {
			exitButton.setColor(Color::Blue);
		}
	}
}

void Menu::updateButtonState() {
	if (selectedButton == 0) {
		startButton.setColor(Color::Blue);
		exitButton.setColor(Color::White);
	}
	else if (selectedButton == 1) {
		startButton.setColor(Color::White);
		exitButton.setColor(Color::Blue);
	}
	else {
		startButton.setColor(Color::White);
		exitButton.setColor(Color::White);
	}
}

void Menu::update(float dt) {

	currentImage.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= 6) {
			currentImage.x = 0;
		}
	}

	bgRect.left = currentImage.x * bgRect.width;
	bgRect.top = currentImage.y * bgRect.height;

	updateButtonState();
}

void Menu::update2(float dt) {

	currentImage2.y = 0;
	totalTime2 += dt;

	if (totalTime2 >= switchTime2) {
		totalTime2 -= switchTime2;
		currentImage2.x++;
		if (currentImage2.x >= 9) {
			currentImage2.x = 0;
		}
	}

	petalsRect.left = currentImage2.x * petalsRect.width;
	petalsRect.top = currentImage2.y * petalsRect.height;
}

void Menu::render() {
	window.clear();
	startButton.setScale(startScale);
	exitButton.setScale(startScale);
	//bg.setTextureRect(bgRect);
	bg.setScale(0.68f, 0.67f);
	window.draw(bg);
	petals.setTextureRect(petalsRect);
	window.draw(petals);
	//title.setScale(0.2f, 0.2f);
	//window.draw(title);
	window.draw(startButton);
	window.draw(exitButton);
	window.draw(buttonText);
	window.draw(button1Text);
	//window.display();
}

bool Menu::startButtonPressed() const {
	return startPressed;
}