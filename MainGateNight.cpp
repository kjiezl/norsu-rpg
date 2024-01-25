#include "MainGateNight.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "BlackFadeTransition.h"
#include "PauseMenu.h"
#include "Skylab.h"

using namespace sf;
using namespace std;

MainGateNight::MainGateNight(RenderWindow& window, const string& pName) : window(window), 
fadeOut(false), isShaking(false), fadeTrans(window), pauseMenu(window), pName(pName), 
gamePaused(false), dampingFactor(0.3f), dPressed(true), aPressed(false), 
going3rdCAS(false) {
	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	playerName.setString("");
	playerName.setFont(font);

	bgTexture1.loadFromFile("sprites\\maps\\maingate1-1-night.png");
	bgTexture2.loadFromFile("sprites\\maps\\maingate1-2-night.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico-night.png");
	rectTexture.loadFromFile("sprites\\ui\\border.png");

	bgSprite1.setTexture(bgTexture1);
	bgSprite2.setTexture(bgTexture2);
	playerSprite.setTexture(playerTexture);
	rectSprite.setTexture(rectTexture);

	blackBG.setFillColor(Color(0, 0, 0, 140));
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	dfTexture.loadFromFile("sprites\\enemies\\boss-final1.png");
	dfSprite.setTexture(dfTexture);
	currentImage.x = 0;
	dfRect.width = dfTexture.getSize().x / 4;
	dfRect.height = dfTexture.getSize().y / 1;
	totalTime = 0;
	switchTime = 0.2f;

	shakeMagnitude = 0.3f;

	initPlayer();
}

MainGateNight::~MainGateNight() {

}

Vector2f lerr(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void MainGateNight::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	task1.setString("!\tGo home");
	task1.setCharacterSize(25);
	task1.setOutlineColor(Color::Black);
	task1.setOutlineThickness(3);

	bgSprite1.setPosition(250, 0);
	bgSprite2.setPosition(250, 0);

	playerSprite.setPosition(275, 15);
	rectSprite.setPosition(355, 0);

	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));
	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	dfSprite.setScale(1.2f, 1.2f);
	dfSprite.setPosition(3500, 0);

	float rectAlpha = 0.0f;
	/*rectangles.push_back(Rectangle(250, -35, 1000, -50, rectAlpha));
	rectangles.push_back(Rectangle(250, 278, 1000, 50, rectAlpha));

	rectangles.push_back(Rectangle(221, 150, 90, 300, rectAlpha));
	rectangles.push_back(Rectangle(398, 150, 45, 300, rectAlpha));
	rectangles.push_back(Rectangle(1067, 150, 53, 300, rectAlpha));
	rectangles.push_back(Rectangle(1203, 150, 40, 300, rectAlpha));
	rectangles.push_back(Rectangle(459, 208, 600, 300, rectAlpha));

	rectangles.push_back(Rectangle(221, 0, 15, 1000, rectAlpha));
	rectangles.push_back(Rectangle(1284, 0, 15, 500, rectAlpha));*/

	rectangles.push_back(Rectangle(250, -35, 1500, -50, rectAlpha)); //up
	rectangles.push_back(Rectangle(250, 693, 1500, 50, rectAlpha)); //down
	rectangles.push_back(Rectangle(190, 0, 50, 700, rectAlpha)); //left
	rectangles.push_back(Rectangle(1690, 0, 50, 700, rectAlpha)); //right

	//gate
	rectangles.push_back(Rectangle(250, 590, 235, 70, rectAlpha));
	rectangles.push_back(Rectangle(1400, 590, 260, 70, rectAlpha));
	rectangles.push_back(Rectangle(426, 500, 55, 100, rectAlpha));
	rectangles.push_back(Rectangle(490, 510, 77, 77, rectAlpha));
	rectangles.push_back(Rectangle(644, 510, 65, 77, rectAlpha));

	rectangles.push_back(Rectangle(720, 520, 450, 22, rectAlpha));

	rectangles.push_back(Rectangle(1180, 510, 67, 77, rectAlpha));
	rectangles.push_back(Rectangle(1322, 510, 65, 77, rectAlpha));
	rectangles.push_back(Rectangle(1400, 500, 65, 100, rectAlpha));

	//stage
	rectangles.push_back(Rectangle(330, -15, 1245, -50, rectAlpha)); //up
	//brown
	rectangles.push_back(Rectangle(342, 30, 20, 50, rectAlpha));
	rectangles.push_back(Rectangle(528, 30, 20, 50, rectAlpha));
	rectangles.push_back(Rectangle(1357, 30, 20, 50, rectAlpha));
	rectangles.push_back(Rectangle(1544, 30, 20, 50, rectAlpha));
	//stairs
	rectangles.push_back(Rectangle(648, 93, 35, 20, rectAlpha));
	rectangles.push_back(Rectangle(1225, 93, 35, 20, rectAlpha));
	//edge
	rectangles.push_back(Rectangle(700, 213, 115, 30, rectAlpha));
	rectangles.push_back(Rectangle(1090, 213, 120, 30, rectAlpha));
	//edge2
	rectangles.push_back(Rectangle(805, 230, 290, 45, rectAlpha));

	updateTextPos();
}

void MainGateNight::handleInput() {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}
	}

	if (!isShaking) {
		countdown.restart();
	}

	float elapsedTime = countdown.getElapsedTime().asSeconds();
	cout << elapsedTime << endl;

	if (elapsedTime >= 2) {
		fadeOut = true;
	}

	float moveSpeed = 3.5;

	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		moveSpeed += 2;
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dPressed = true;
		aPressed = false;
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		playerSprite.move(moveSpeed, 0);
	}
	else {
		if (dPressed) {
			playerSprite.setTextureRect(IntRect(0, 64, 32, 32));
		}
		if (aPressed) {
			playerSprite.setTextureRect(IntRect(0, 96, 32, 32));
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		aPressed = true;
		dPressed = false;
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		playerSprite.move(-moveSpeed, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		int pos = 0;
		pos = (int)playerSprite.getPosition().y / 35 % 4;
		pos = pos * 32;
		if (dPressed) {
			playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		}
		if (aPressed) {
			playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		}
		playerSprite.move(0, moveSpeed);
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		int pos = 0;
		pos = (int)playerSprite.getPosition().y / 35 % 4;
		pos = pos * 32;
		if (dPressed) {
			playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		}
		if (aPressed) {
			playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		}
		playerSprite.move(0, -moveSpeed);
	}

	window.setView(camera);
	Vector2i pixelMousePosition = Mouse::getPosition(window);
	if (static_cast<unsigned>(pixelMousePosition.x) < window.getSize().x &&
		static_cast<unsigned>(pixelMousePosition.y) < window.getSize().y) {
		if (Keyboard::isKeyPressed(Keyboard::T)) {
			Vector2f worldMousePosition = window.mapPixelToCoords(pixelMousePosition);
			cout << "Mouse Coordinates: (" << worldMousePosition.x << ", " << worldMousePosition.y << ")" << endl;
		}
	}

	if (playerSprite.getPosition().x <= 355 && playerSprite.getPosition().x >= 250 && playerSprite.getPosition().y <= 10 && playerSprite.getPosition().y >= 0) {
		//going3rdCAS = true;
	}

	if (dfSprite.getPosition().x - playerSprite.getPosition().x <= 10 && dfSprite.getPosition().y - playerSprite.getPosition().y <= 10) {
		isShaking = true;
	}

	for (auto& rect : rectangles) {
		handleCollision(rect);
	}
}

void MainGateNight::updateTextPos() {

	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1100, camera.getCenter().y - window.getSize().y / 1.80f);
}

void MainGateNight::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerr(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void MainGateNight::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	playerName.setString(pName);
	playerName.setPosition(playerSprite.getPosition().x - 5 - playerName.getLocalBounds().width / 2, playerSprite.getPosition().y - 50);

	float angle = atan2(playerSprite.getPosition().y - 50 - dfSprite.getPosition().y, playerSprite.getPosition().x - 20 - dfSprite.getPosition().x);
	float x = 5 * cos(angle);
	float y = 5 * sin(angle);
	dfSprite.move(x, y);

	if (isShaking) {
		float offsetX = (rand() % 200 - 100) * shakeMagnitude;
		float offsetY = (rand() % 200 - 100) * shakeMagnitude;

		camera.move(offsetX, offsetY);
	}
}

void MainGateNight::animUpdate(float dt) {
	currentImage.y = 0;
	totalTime += dt;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= 4) {
			currentImage.x = 0;
		}
	}

	dfRect.left = currentImage.x * dfRect.width;
	dfRect.top = currentImage.y * dfRect.height;
}

bool MainGateNight::goto3rdCAS() {
	return going3rdCAS;
}

void MainGateNight::playerPosFrom3rdCAS() {
	playerSprite.setPosition(300, 15);
}

void MainGateNight::going3rdCASFalse() {
	going3rdCAS = false;
}

bool MainGateNight::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

bool MainGateNight::sceneComplete() {
	return fadeOut;
}

void MainGateNight::handleCollision(const Rectangle& rect) {
	charBounds = playerSprite.getGlobalBounds();
	rectBounds = rect.shape.getGlobalBounds();

	intersection;
	if (charBounds.intersects(rectBounds, intersection)) {
		if (intersection.width < intersection.height) {

			if (charBounds.left < rectBounds.left) {
				playerSprite.setPosition(playerSprite.getPosition().x - intersection.width, playerSprite.getPosition().y);
			}
			else {
				playerSprite.setPosition(playerSprite.getPosition().x + intersection.width, playerSprite.getPosition().y);
			}
		}
		else {
			if (charBounds.top < rectBounds.top) {
				playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y - intersection.height);
			}
			else {
				playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + intersection.height);
			}
		}
	}
}

void MainGateNight::render() {
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite1.setScale(0.35f, 0.35f);
	bgSprite2.setScale(0.35f, 0.35f);
	playerSprite.setScale(1.75f, 1.75f);
	rectSprite.setScale(0.1f, 0.1f);
	window.draw(blackBG);
	window.draw(bgSprite1);
	window.draw(playerSprite);
	window.draw(bgSprite2);
	window.draw(playerName);
	dfSprite.setTextureRect(dfRect);
	window.draw(dfSprite);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);
	window.draw(task1);

	if (fadeOut) {
		sceneComplete();
	}
}