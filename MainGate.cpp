#include "MainGate.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "CircTrans.h"
#include "PauseMenu.h"
#include "Skylab.h"

using namespace sf;
using namespace std;

MainGate::MainGate(RenderWindow& window, const string& pName) : window(window), 
circTrans(window), pauseMenu(window), pName(pName), gamePaused(false), 
dampingFactor(0.3f), dPressed(true), aPressed(false), going3rdCAS(false), 
day2(false), goingHM(false), showTask4(false), goingCBA(false), inv(window) {
	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	task2.setFont(font);
	task4.setFont(font);
	collectScraps.setFont(font);
	playerName.setString("");
	playerName.setFont(font);

	bgTexture1.loadFromFile("sprites\\maps\\maingate1-1.png");
	bgTexture2.loadFromFile("sprites\\maps\\maingate1-2.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico.png");
	rectTexture.loadFromFile("sprites\\ui\\border.png");
	arrowTexture.loadFromFile("sprites\\ui\\guide-arrow.png");
	wasdTexture.loadFromFile("sprites\\ui\\wasd.png");

	bgSprite1.setTexture(bgTexture1);
	bgSprite2.setTexture(bgTexture2);
	playerSprite.setTexture(playerTexture);
	rectSprite.setTexture(rectTexture);
	arrowSprite.setTexture(arrowTexture);
	arrowSprite1.setTexture(arrowTexture);
	arrowSprite2.setTexture(arrowTexture);
	wasdSprite.setTexture(wasdTexture);

	blackBG.setFillColor(Color(0, 0, 0, 140));
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	switchTime = 0.2f;
	totalTime = 0.0f;
	currentImage.x = 0;
	arrowRect.width = arrowTexture.getSize().x / 4;
	arrowRect.height = arrowTexture.getSize().y / 1;

	switchTimeWASD = 0.5f;
	currentImageWASD.x = 0;
	wasdRect.width = wasdTexture.getSize().x / 10;
	wasdRect.height = wasdTexture.getSize().y / 1;

	initPlayer();
}

MainGate::~MainGate() {

}

Vector2f ler(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void MainGate::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	task1.setString("!\tGo to skylab room for your class");
	task1.setCharacterSize(25);
	task1.setOutlineColor(Color::Black);
	task1.setOutlineThickness(3);

	task2.setString("!\tGo to the CAS building");
	task2.setCharacterSize(25);
	task2.setOutlineColor(Color::Black);
	task2.setOutlineThickness(3);

	task4.setString("!\tGo to your next class in HM building");
	task4.setCharacterSize(25);
	task4.setOutlineColor(Color::Black);
	task4.setOutlineThickness(3);

	collectScraps.setString("!\tPress E to collect scraps for crafting");
	collectScraps.setCharacterSize(20);
	collectScraps.setOutlineColor(Color::Black);
	collectScraps.setOutlineThickness(3);

	bgSprite1.setPosition(250, 0);
	bgSprite2.setPosition(250, 0);

	playerSprite.setPosition(600, 595);
	rectSprite.setPosition(355, 0);

	wasdSprite.setPosition(300, 300);

	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));
	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);


	float rectAlpha = 0.0f;
	rectangles.push_back(Rectangle(250,-35, 1500, -50, rectAlpha)); //up
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

void MainGate::handleInput() {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}
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
	
	// 275 0
	if (playerSprite.getPosition().x <= 315 && playerSprite.getPosition().x >= 235 && playerSprite.getPosition().y <= 10 && playerSprite.getPosition().y >= -20) {
		going3rdCAS = true;
	}

	// 1615 0
	if (playerSprite.getPosition().x <= 1655 && playerSprite.getPosition().x >= 1575 && playerSprite.getPosition().y <= 10 && playerSprite.getPosition().y >= -20 && day2) {
		goingHM = true;
	}

	// 1640 300
	if (playerSprite.getPosition().x <= 1700 && playerSprite.getPosition().x >= 1640 && playerSprite.getPosition().y <= 330 && playerSprite.getPosition().y >= 280 && day2) {
		goingCBA = true;
	}

	for (auto& rect : rectangles) {
		handleCollision(rect);
	}
}

void MainGate::updateTextPos() {

	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 850, camera.getCenter().y - window.getSize().y / 1.80f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 920, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 800, camera.getCenter().y - window.getSize().y / 1.80f);
	collectScraps.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.60f);
}

void MainGate::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = ler(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void MainGate::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	playerName.setString(pName);
	playerName.setPosition(playerSprite.getPosition().x - 5 - playerName.getLocalBounds().width / 2, playerSprite.getPosition().y - 50);
}

void MainGate::animUpdate(float dt) {
	currentImage.y = 0;
	currentImageWASD.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime || totalTime >= switchTimeWASD) {
		totalTime -= switchTime;
		totalTime -= switchTimeWASD;
		currentImage.x++;
		currentImageWASD.x++;
		if (currentImage.x >= 4) {
			currentImage.x = 0;
		}
		if (currentImageWASD.x >= 8) {
			currentImageWASD.x = 3;
		}
	}

	arrowRect.left = currentImage.x * arrowRect.width;
	arrowRect.top = currentImage.y * arrowRect.height;
	wasdRect.left = currentImageWASD.x * wasdRect.width;
	wasdRect.top = currentImageWASD.y * wasdRect.height;
}

bool MainGate::goto3rdCAS() {
	return going3rdCAS;
}

bool MainGate::gotoHM() {
	return goingHM;
}

bool MainGate::gotoCBA() {
	return goingCBA;
}

void MainGate::playerPosFrom3rdCAS() {
	playerSprite.setPosition(275, 15);
}

void MainGate::playerPosFromHM() {
	playerSprite.setPosition(1615, 15);
}

void MainGate::playerPosFromCBA() {
	playerSprite.setPosition(1630, 300);
}

void MainGate::going3rdCASFalse() {
	going3rdCAS = false;
}

void MainGate::goingHMFalse() {
	goingHM = false;
}

void MainGate::goingCBAFalse() {
	goingCBA = false;
}

bool MainGate::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void MainGate::handleCollision(const Rectangle& rect) {
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

void MainGate::day2Start() {
	day2 = true;
	playerSprite.setPosition(600, 595);
	going3rdCAS = false;
}

void MainGate::show4(bool papersPlaced) {
	if (papersPlaced) {
		showTask4 = true;
	}
}

void MainGate::render() {
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite1.setScale(0.7f, 0.7f);
	bgSprite2.setScale(0.7f, 0.7f);
	playerSprite.setScale(1.75f, 1.75f);
	rectSprite.setScale(0.1f, 0.1f);
	arrowSprite.setScale(1.0f, 1.0f);
	arrowSprite1.setScale(1.0f, 1.0f);
	arrowSprite2.setScale(1.0f, 1.0f);
	wasdSprite.setScale(4.0f, 4.0f);
	wasdSprite.setTextureRect(wasdRect);
	window.draw(blackBG);
	window.draw(bgSprite1);
	window.draw(arrowSprite);

	if (day2) {
		window.draw(arrowSprite1);
		window.draw(arrowSprite2);
		arrowSprite1.setPosition(1615, 0);
		arrowSprite2.setPosition(1640, 300);
	}
	window.draw(playerSprite);
	window.draw(bgSprite2);
	window.draw(playerName);
	//window.draw(rectSprite);
	arrowSprite.setPosition(275, 0);

	arrowSprite.setTextureRect(arrowRect);
	arrowSprite1.setTextureRect(arrowRect);
	arrowSprite2.setTextureRect(arrowRect);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.setView(window.getDefaultView());
	if (!day2) {
		window.draw(wasdSprite);
		window.draw(task1);
	}

	if(day2 && !showTask4) {
		window.draw(task2);
	}

	if (showTask4 && day2) {
		window.draw(task4);
	}

	if (day2) {
		inv.updateTextPos();
		inv.render();
		window.draw(collectScraps);
	}

	window.draw(quitText);
	window.draw(pauseText);

	//window.display();
}