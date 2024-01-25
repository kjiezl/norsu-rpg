#include "CBARoomDay.h"
#include "HMDay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

CBARoomDay::CBARoomDay(RenderWindow& window) : window(window), fadeTrans(window),
dPressed(false), aPressed(true), dampingFactor(0.3f), pauseMenu(window),
gamePaused(false), dialogueBox(window), goingCBA(false), showTask4(false),
inv(window){

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task2.setFont(font);
	task4.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\cba-room1.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	initPlayer();
}

CBARoomDay::~CBARoomDay() {

}

Vector2f lerp9(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void CBARoomDay::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	task2.setString("!\tGo to the CAS building");
	task2.setCharacterSize(25);
	task2.setOutlineColor(Color::Black);
	task2.setOutlineThickness(3);

	task4.setString("!\tGo to your next class in HM building");
	task4.setCharacterSize(25);
	task4.setOutlineColor(Color::Black);
	task4.setOutlineThickness(3);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(750, 500);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	float rectAlpha = 0.0f;

	rectangles.push_back(Rectangle(250, 20, 1000, 100, rectAlpha)); // upper
	rectangles.push_back(Rectangle(250, 538, 1000, 100, rectAlpha)); // lower
	rectangles.push_back(Rectangle(200, 100, 60, 500, rectAlpha)); // left
	rectangles.push_back(Rectangle(820, 100, 60, 500, rectAlpha)); // right

	// items
	rectangles.push_back(Rectangle(367, 420, 76, 10, rectAlpha));
	rectangles.push_back(Rectangle(382, 295, 10, 35, rectAlpha));
	rectangles.push_back(Rectangle(421, 256, 10, 35, rectAlpha));
	rectangles.push_back(Rectangle(461, 217, 10, 75, rectAlpha));
	rectangles.push_back(Rectangle(676, 238, 71, 20, rectAlpha));

	// columns
	rectangles.push_back(Rectangle(436, 127, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(628, 127, 10, 10, rectAlpha));

	updateTextPos();
}

void CBARoomDay::handleInput() {
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

	// 730x - 770x, 525y
	if (playerSprite.getPosition().x <= 780 && playerSprite.getPosition().x >= 710 && playerSprite.getPosition().y <= 650 && playerSprite.getPosition().y >= 480 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingCBA = true;
	}

	for (auto& rect : rectangles) {
		handleCollision(rect);
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
}

void CBARoomDay::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 920, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 800, camera.getCenter().y - window.getSize().y / 1.80f);
}

void CBARoomDay::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp9(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void CBARoomDay::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);
}

void CBARoomDay::animUpdate(float dt) {
	
}

bool CBARoomDay::gotoCBA() {
	return goingCBA;
}

void CBARoomDay::playerPosFromCBA() {
	playerSprite.setPosition(750, 500);
}

void CBARoomDay::goingCBAFalse() {
	goingCBA = false;
}

bool CBARoomDay::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void CBARoomDay::handleCollision(const Rectangle& rect) {
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

void CBARoomDay::show4(bool yes) {
	if (yes) {
		showTask4 = true;
	}
}

void CBARoomDay::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(0.6f, 0.6f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
	window.draw(playerSprite);
	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.setView(window.getDefaultView());

	window.draw(quitText);
	window.draw(pauseText);
	inv.updateTextPos();
	inv.render();
	if (!showTask4) {
		window.draw(task2);
	}
	else {
		window.draw(task4);
	}
}
