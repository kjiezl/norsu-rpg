#include "SkylabNight.h"
#include "PauseMenu.h"
#include "PlayerName.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "NPC.h"
#include "Skylab.h"
#include "SkylabRoomNight.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

SkylabNight::SkylabNight(RenderWindow& window, const string& pName) : window(window), 
isChasing2(false), showGhost7(false), showGhost6(false), showGhost5(false), 
showGhost4(false), showGhost3(false), showGhost1(false), showGhost2(false), 
projectileShot(false), isShaking(false), broomPicked(false), blockStairs(false), 
dialogue(false), showGoHome(true), phoneTask(false), showEnterText(false), 
going3rdCAS(false), goingSkylabRoom(false), playerNameClass(window), pName(pName),
pauseMenu(window), gamePaused(false), fadeTrans(window), dialogueBox(window), 
dampingFactor(0.3f), dPressed(true), aPressed(false) {
	//cout << endl << pName << endl;

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	phoneText.setFont(font);
	playerName.setString("");
	playerName.setFont(font);
	bgTexture.loadFromFile("sprites\\maps\\skylab-night.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico-night.png");

	totalTime = 0.0f;

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	enterDoorText.setFont(font);

	broomItemTexture.loadFromFile("sprites\\items\\broom-night.png");
	broomItemSprite.setTexture(broomItemTexture);
	broomItemSprite.setOrigin(broomItemTexture.getSize().x / 2.0f, broomItemTexture.getSize().y / 2.0f);
	broomItemSprite.setScale(1.75f, 1.75f);

	ghost1Texture.loadFromFile("sprites\\enemies\\ghost1.1.png");
	ghost1Sprite.setTexture(ghost1Texture);
	ghost2Sprite.setTexture(ghost1Texture);
	ghost3Sprite.setTexture(ghost1Texture);
	ghost4Sprite.setTexture(ghost1Texture);
	ghost5Sprite.setTexture(ghost1Texture);
	ghost6Sprite.setTexture(ghost1Texture);
	ghost7Sprite.setTexture(ghost1Texture);
	switchTimeGhost = 0.3f;
	currentImageGhost.x = 0;
	ghostRect.width = ghost1Texture.getSize().x / 3;
	ghostRect.height = ghost1Texture.getSize().y / 1;
	ghost1Sprite.setScale(1.7f, 1.7f);
	ghost2Sprite.setScale(1.7f, 1.7f);
	ghost3Sprite.setScale(1.7f, 1.7f);
	ghost4Sprite.setScale(1.7f, 1.7f);
	ghost5Sprite.setScale(1.7f, 1.7f);
	ghost6Sprite.setScale(1.7f, 1.7f);
	ghost7Sprite.setScale(1.7f, 1.7f);

	shakeTime = 0.1f;
	shakeMagnitude = 0.1f;

	ghostDeathBuffer.loadFromFile("sprites\\sfx\\ghost-death.ogg");
	ghostDeathSFX.setBuffer(ghostDeathBuffer);
	shootBuffer.loadFromFile("sprites\\sfx\\gun-laser.ogg");
	shootSFX.setBuffer(shootBuffer);

	initPlayer();
}

Vector2f lerppp(const Vector2f& start, const Vector2f& end) {
	float t = 0.3f;
	return start + t * (end - start);
}

SkylabNight::~SkylabNight() {

}

void SkylabNight::initPlayer() {
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

	phoneText.setString("!\tGo back to skylab room and retrieve your phone");
	phoneText.setCharacterSize(25);
	phoneText.setOutlineColor(Color::Black);
	phoneText.setOutlineThickness(3);

	playerName.setCharacterSize(10);
	playerName.setFillColor(Color::White);
	playerName.setOutlineColor(Color::Black);
	playerName.setOutlineThickness(1.0);
	playerName.setLetterSpacing(4);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(1800, 150);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	//ghost1Sprite.setPosition();

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	arrowTexture.loadFromFile("sprites\\ui\\guide-arrow.png");
	arrowSprite.setTexture(arrowTexture);
	switchTimeArrow = 0.2f;
	arrowRect.width = arrowTexture.getSize().x / 4;
	arrowRect.height = arrowTexture.getSize().y / 1;
	currentImageArrow.x = 0;
	arrowSprite.setPosition(1802, 150);

	ghost1Sprite.setPosition(1480, 300);
	ghost2Sprite.setPosition(2090, 300);
	ghost3Sprite.setPosition(450, 175);
	ghost4Sprite.setPosition(300, 300);
	ghost5Sprite.setPosition(800, 320);
	ghost6Sprite.setPosition(3100, 200);
	ghost7Sprite.setPosition(2600, 320);

	borderGhost.setFillColor(Color::Green);
	borderGhost.setSize(Vector2f(1500, 400));
	borderGhost.setPosition(1000, 100);

	borderGhost2.setFillColor(Color::Green);
	borderGhost2.setSize(Vector2f(1000, 300));
	borderGhost2.setPosition(2300, 100);

	borderGhost3.setFillColor(Color::Green);
	borderGhost3.setSize(Vector2f(1000, 300));
	borderGhost3.setPosition(200, 100);

	projectile.setSize(Vector2f(5.0f, 2.0f));
	projectile.setFillColor(Color::Yellow);

	float rectAlpha = 0.0f;
	rectangles.push_back(Rectangle(250, 0, 3050, 100, rectAlpha));
	rectangles.push_back(Rectangle(3395, 0, 350, 100, rectAlpha));
	rectangles.push_back(Rectangle(3545, 0, 350, 600, rectAlpha));
	rectangles.push_back(Rectangle(150, 0, 90, 600, rectAlpha));

	rectangles.push_back(Rectangle(250, 347, 110, 300, rectAlpha));
	rectangles.push_back(Rectangle(480, 392, 10, 300, rectAlpha));
	rectangles.push_back(Rectangle(1302, 392, 10, 300, rectAlpha));
	rectangles.push_back(Rectangle(1807, 392, 10, 300, rectAlpha));
	rectangles.push_back(Rectangle(2217, 392, 10, 300, rectAlpha));
	rectangles.push_back(Rectangle(684, 100, 20, 20, rectAlpha));

	rectangles.push_back(Rectangle(2460, 100, 100, 20, rectAlpha));
	rectangles.push_back(Rectangle(400, 100, 185, 20, rectAlpha));
	rectangles.push_back(Rectangle(2292, 390, 1300, 20, rectAlpha));
	rectangles.push_back(Rectangle(473, 429, 3700, 20, rectAlpha));
	rectangles.push_back(Rectangle(947, 346, 262, 40, rectAlpha));
	rectangles.push_back(Rectangle(1441, 346, 262, 40, rectAlpha));
	rectangles.push_back(Rectangle(1891, 346, 262, 40, rectAlpha));

	rectangles.push_back(Rectangle(300, 430, 200, 50, rectAlpha));

	updateTextPos();

}

void SkylabNight::handleInput() {
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
		if (broomPicked) {
			broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);
			broomItemSprite.move(moveSpeed, 0);
		}
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
		if (broomPicked) {
			broomItemSprite.setPosition(playerSprite.getPosition().x - 4, playerSprite.getPosition().y + 7.5);
			broomItemSprite.move(-moveSpeed, 0);
		}
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		playerSprite.move(-moveSpeed, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		int pos = 0;
		if (broomPicked) {
			broomItemSprite.move(0, moveSpeed);
		}
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
		if (broomPicked) {
			broomItemSprite.move(0, -moveSpeed);
		}
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

	if (playerSprite.getPosition().x <= 475 && playerSprite.getPosition().x >= 370 && playerSprite.getPosition().y <= 430 && playerSprite.getPosition().y >= 380 && broomPicked) {
		going3rdCAS = true;
	}

	if (playerSprite.getPosition().x >= 1750 && playerSprite.getPosition().x <= 1850 && playerSprite.getPosition().y >= 100 && playerSprite.getPosition().y <= 180) {
		showEnterText = true;

		if (Keyboard::isKeyPressed(Keyboard::E)) {
			goingSkylabRoom = true;
		}
	}
	else {
		showEnterText = false;
	}

	// 300 - 550, 100 - 500
	if (playerSprite.getPosition().x >= 300 && playerSprite.getPosition().x <= 550 && playerSprite.getPosition().y >= 100 && playerSprite.getPosition().y <= 500 && !broomPicked) {
		dialogue = true;
		showGoHome = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && !projectileShot && broomPicked || Mouse::isButtonPressed(Mouse::Left) && !projectileShot && broomPicked) {
		//cout << "projectile shot false\n";
		shootSFX.pause();
		shootSFX.play();
		shakeClock.restart();
		isShaking = true;
		projectileDirection = mousePos - broomItemSprite.getPosition();
		float length = sqrt(projectileDirection.x * projectileDirection.x + projectileDirection.y * projectileDirection.y);
		projectileDirection /= length;
		if (dPressed) {
			projectile.setPosition(broomItemSprite.getPosition().x + 10.0f, broomItemSprite.getPosition().y - 5.0f);
		}
		if (aPressed) {
			projectile.setPosition(broomItemSprite.getPosition().x - 20.0f, broomItemSprite.getPosition().y - 5.0f);
		}
		projectileShot = true;
	}

	float firerate = cooldown.getElapsedTime().asSeconds();

	if (projectileShot) {																																																							
		//cout << "projectile shot true\n";
		float projectileSpeed = 50.0f;
		if (firerate < 0.5f) {
			projectile.move(projectileDirection * projectileSpeed);
		}
		if (firerate > 0.5f) {
			shootSFX.stop();
			projectileShot = false;
			cooldown.restart();
			projectile.setPosition(9000, 9000);
		}
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

void SkylabNight::updateTextPos() {

	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1100, camera.getCenter().y - window.getSize().y / 1.80f);
	phoneText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 700, camera.getCenter().y - window.getSize().y / 1.80f);
}

void SkylabNight::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerppp(currentCenter, targetCenter);
	camera.setCenter(newCenter);
}

void SkylabNight::update() {
	//cout << pName << endl;
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	playerName.setString(pName);
	playerName.setPosition(playerSprite.getPosition().x - 5 - playerName.getLocalBounds().width / 2, playerSprite.getPosition().y - 50);

	if (playerSprite.getPosition().x > borderGhost.getPosition().x && playerSprite.getPosition().x < borderGhost.getPosition().x + borderGhost.getSize().x &&
		playerSprite.getPosition().y > borderGhost.getPosition().y && playerSprite.getPosition().y < borderGhost.getPosition().y + borderGhost.getSize().y && showGhost1 || showGhost2) {
		isChasing = true;
	}
	else {
		isChasing = false;
	}

	if (isChasing) {

		float angle1 = atan2(playerSprite.getPosition().y - ghost1Sprite.getPosition().y, playerSprite.getPosition().x - ghost1Sprite.getPosition().x);
		float x1 = 1.5 * cos(angle1);
		float y1 = 1.5 * sin(angle1);
		ghost1Sprite.move(x1, y1);

		float angle2 = atan2(playerSprite.getPosition().y - ghost2Sprite.getPosition().y, playerSprite.getPosition().x - ghost2Sprite.getPosition().x);
		float x2 = 1.5 * cos(angle2);
		float y2 = 1.5 * sin(angle2);
		ghost2Sprite.move(x2, y2);
	}

	if (playerSprite.getPosition().x > borderGhost2.getPosition().x && playerSprite.getPosition().x < borderGhost2.getPosition().x + borderGhost2.getSize().x &&
		playerSprite.getPosition().y > borderGhost2.getPosition().y && playerSprite.getPosition().y < borderGhost2.getPosition().y + borderGhost2.getSize().y && showGhost6 || showGhost7) {
		isChasing2 = true;
	}
	else {
		isChasing2 = false;
	}

	if (isChasing2) {

		float angle1 = atan2(playerSprite.getPosition().y - ghost6Sprite.getPosition().y, playerSprite.getPosition().x - ghost6Sprite.getPosition().x);
		float x1 = 1.5 * cos(angle1);
		float y1 = 1.5 * sin(angle1);
		ghost6Sprite.move(x1, y1);

		float angle2 = atan2(playerSprite.getPosition().y - ghost7Sprite.getPosition().y, playerSprite.getPosition().x - ghost7Sprite.getPosition().x);
		float x2 = 1.5 * cos(angle2);
		float y2 = 1.5 * sin(angle2);
		ghost7Sprite.move(x2, y2);
	}

	if (playerSprite.getPosition().x > borderGhost3.getPosition().x && playerSprite.getPosition().x < borderGhost3.getPosition().x + borderGhost3.getSize().x &&
		playerSprite.getPosition().y > borderGhost3.getPosition().y && playerSprite.getPosition().y < borderGhost3.getPosition().y + borderGhost3.getSize().y && showGhost3 || showGhost4 || showGhost5) {
		isChasing3 = true;
	}
	else {
		isChasing3 = false;
	}

	if (isChasing3) {

		float angle1 = atan2(playerSprite.getPosition().y - ghost3Sprite.getPosition().y, playerSprite.getPosition().x - ghost3Sprite.getPosition().x);
		float x1 = 1.5 * cos(angle1);
		float y1 = 1.5 * sin(angle1);
		ghost3Sprite.move(x1, y1);

		float angle2 = atan2(playerSprite.getPosition().y - ghost4Sprite.getPosition().y, playerSprite.getPosition().x - ghost4Sprite.getPosition().x);
		float x2 = 1.5 * cos(angle2);
		float y2 = 1.5 * sin(angle2);
		ghost4Sprite.move(x2, y2);

		float angle3 = atan2(playerSprite.getPosition().y - ghost5Sprite.getPosition().y, playerSprite.getPosition().x - ghost5Sprite.getPosition().x);
		float x3 = 1.5 * cos(angle3);
		float y3 = 1.5 * sin(angle3);
		ghost5Sprite.move(x3, y3);
	}

	broomToMouse = mousePos - broomItemSprite.getPosition();
	float angle = atan2(broomToMouse.y, broomToMouse.x) * 180.0f / 3.14159265f;
	broomItemSprite.setRotation(angle);

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost1Sprite.getGlobalBounds())) {
		showGhost1 = false;
		ghost1Sprite.setPosition(9000, 9000);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost2Sprite.getGlobalBounds())) {
		showGhost2 = false;
		ghost2Sprite.setPosition(9000, 9000);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost3Sprite.getGlobalBounds())) {
		showGhost3 = false;
		ghost3Sprite.setPosition(9000, 9000);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost4Sprite.getGlobalBounds())) {
		showGhost4 = false;
		ghost4Sprite.setPosition(9000, 9000);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost5Sprite.getGlobalBounds())) {
		showGhost5 = false;
		ghost5Sprite.setPosition(9000, 9000);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost6Sprite.getGlobalBounds())) {
		showGhost6 = false;
		ghost6Sprite.setPosition(9000, 9000);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost7Sprite.getGlobalBounds())) {
		showGhost7 = false;
		ghost7Sprite.setPosition(9000, 9000);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (isShaking) {
		float elapsedShakeTime = shakeClock.getElapsedTime().asSeconds();
		if (elapsedShakeTime < shakeTime) {
			float offsetX = (rand() % 200 - 100) * shakeMagnitude * (1.0f - elapsedShakeTime / shakeTime);
			float offsetY = (rand() % 200 - 100) * shakeMagnitude * (1.0f - elapsedShakeTime / shakeTime);

			// Apply the displacement to the view
			camera.move(offsetX, offsetY);
		}
		else {
			// Stop shaking after the specified duration
			isShaking = false;
		}
	}
}

void SkylabNight::animUpdate(float dt) {
	currentImageArrow.y = 0;
	currentImageGhost.y = 0;
	totalTime += dt;

	if (totalTime >= switchTimeArrow || totalTime >= switchTimeGhost) {
		totalTime -= switchTimeArrow;
		totalTime -= switchTimeGhost;
		currentImageArrow.x++;
		currentImageGhost.x++;

		if (currentImageArrow.x >= 4) {
			currentImageArrow.x = 0;
		}

		if (currentImageGhost.x >= 3) {
			currentImageGhost.x = 0;
		}
	}

	arrowRect.left = currentImageArrow.x * arrowRect.width;
	arrowRect.top = currentImageArrow.y * arrowRect.height;
	ghostRect.left = currentImageGhost.x * ghostRect.width;
	ghostRect.top = currentImageGhost.y * ghostRect.height;
}

bool SkylabNight::goto3rdCAS() {
	return going3rdCAS;
}

void SkylabNight::playerPosFrom3rdCAS() {
	playerSprite.setPosition(420, 390);
	if (broomPicked) {
		broomItemSprite.setPosition(420, 390);
	}
}

void SkylabNight::going3rdCASFalse() {
	going3rdCAS = false;
}

bool SkylabNight::gotoSkylabRoom() {
	return goingSkylabRoom;
}

void SkylabNight::goingSkylabRoomFalse() {
	goingSkylabRoom = false;
}

void SkylabNight::enterText() {
	cout << "show enter door text" << endl;
	enterDoorText.setCharacterSize(20);
	enterDoorText.setFillColor(Color::White);
	enterDoorText.setString("Press E to enter skylab room");
	enterDoorText.setOutlineColor(Color::Black);
	enterDoorText.setOutlineThickness(2);
	window.setView(window.getDefaultView());
	enterDoorText.setPosition(750, 300);
	window.draw(enterDoorText);
}

bool SkylabNight::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void SkylabNight::handleCollision(const Rectangle& rect) {
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

void SkylabNight::showDialogueBox() {

	dialogueBox.initDialogue("You forgot your phone.");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		phoneTask = true;
		dialogue = false;
		dialogueBox.reset();
	}
}

void SkylabNight::showPhoneTask() {
	blockStairs = true;
	window.draw(phoneText);
}

bool SkylabNight::changeTextRoom() {
	return phoneTask;
}

void SkylabNight::startSpawn() {
	dialogue = false;
	broomPicked = true;
	showGoHome = true;
	phoneTask = false;
	showGhost1 = true;
	showGhost2 = true;
	showGhost3 = true;
	showGhost4 = true;
	showGhost5 = true;
	showGhost6 = true;
	showGhost7 = true;
}

void SkylabNight::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(1.6f, 1.6f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
	arrowSprite.setTextureRect(arrowRect);
	ghost1Sprite.setTextureRect(ghostRect);
	ghost2Sprite.setTextureRect(ghostRect);
	ghost3Sprite.setTextureRect(ghostRect);
	ghost4Sprite.setTextureRect(ghostRect);
	ghost5Sprite.setTextureRect(ghostRect);
	ghost6Sprite.setTextureRect(ghostRect);
	ghost7Sprite.setTextureRect(ghostRect);
	//window.draw(arrowSprite);

	if (broomPicked) {
		window.draw(broomItemSprite);
	}

	window.draw(playerSprite);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	if (showGhost1) {
		window.draw(ghost1Sprite);
	}

	if (showGhost2) {
		window.draw(ghost2Sprite);
	}

	if (showGhost3) {
		window.draw(ghost3Sprite);
	}

	if (showGhost4) {
		window.draw(ghost4Sprite);
	}

	if (showGhost5) {
		window.draw(ghost5Sprite);
	}

	if (showGhost6) {
		window.draw(ghost6Sprite);
	}

	if (showGhost7) {
		window.draw(ghost7Sprite);
	}

	window.draw(projectile);
	window.draw(playerName);

	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);

	if (showGoHome) {
		window.draw(task1);
	}

	if (dialogue) {
		showDialogueBox();
	}

	if (phoneTask) {
		showPhoneTask();
	}

	if (showEnterText) {
		enterText();
	}
}