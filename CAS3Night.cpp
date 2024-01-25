#include "CAS3Night.h"
#include "PauseMenu.h"
#include "PlayerName.h"
#include "Skylab.h"
#include "HealthCount.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;


CAS3Night::CAS3Night(RenderWindow& window, const string& pName) : window(window), 
playWindSFX(false), startLevel2(false), startLevel3(false), levelComplete3(false), 
levelComplete2(false), levelComplete1(false), showGhost13(true), showGhost12(true), 
showGhost11(true), showGhost10(true), showGhost9(true), showGhost8(true), 
showGhost7(true), showGhost6(true), showGhost5(true), showGhost4(true), 
showGhost3(true), showGhost1(true), showGhost2(true), projectileShot(false), 
isShaking(false), goingMainGate(false), fadeTrans(window), pName(pName), 
pauseMenu(window), gamePaused(false), dampingFactor(0.3f), isChasing(false), 
dPressed(true), aPressed(false), goingSkylab(false), healthCount(window),
hp(window, 100.0), showHP(true){

	cout << endl << pName << endl;

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	task2.setFont(font);
	score1.setFont(font);
	score2.setFont(font);
	score3.setFont(font);
	unlocked.setFont(font);
	playerName.setString("");
	playerName.setFont(font);
	bgTexture.loadFromFile("sprites\\maps\\cas-3rd-night.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico-night.png");
	windBuffer.loadFromFile("sprites\\sfx\\wind.ogg");
	windSFX.setBuffer(windBuffer);

	totalTime = 0.0f;
	currentImage.x = 0;

	ghost1Score = 0;
	ghost2Score = 0;
	ghost3Score = 0;

	ghostTexture1.loadFromFile("sprites\\enemies\\ghost1.1.png");
	ghostTexture2.loadFromFile("sprites\\enemies\\ghost1.2.png");
	ghostTexture3.loadFromFile("sprites\\enemies\\ghost1.3.png");
	ghost1Sprite.setTexture(ghostTexture1);
	ghost2Sprite.setTexture(ghostTexture1);
	ghost3Sprite.setTexture(ghostTexture1);
	ghost4Sprite.setTexture(ghostTexture1);
	ghost5Sprite.setTexture(ghostTexture1);
	ghost6Sprite.setTexture(ghostTexture1);
	ghost7Sprite.setTexture(ghostTexture2);
	ghost8Sprite.setTexture(ghostTexture2);
	ghost9Sprite.setTexture(ghostTexture2);
	ghost10Sprite.setTexture(ghostTexture2);
	ghost11Sprite.setTexture(ghostTexture2);
	ghost12Sprite.setTexture(ghostTexture3);
	ghost13Sprite.setTexture(ghostTexture3);
	ghostRect.width = ghostTexture1.getSize().x / 3;
	ghostRect.height = ghostTexture1.getSize().y / 1;
	switchTime = 0.3f;


	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	borderShape.setFillColor(Color(0, 0, 0, 50));
	borderShape.setSize(Vector2f(425, 205));

	shakeTime = 0.1f;
	shakeMagnitude = 0.1f;

	broomItemTexture.loadFromFile("sprites\\items\\broom-night.png");
	broomItemSprite.setTexture(broomItemTexture);
	broomItemSprite.setOrigin(broomItemTexture.getSize().x / 2.0f, broomItemTexture.getSize().y / 2.0f);

	ghostDeathBuffer.loadFromFile("sprites\\sfx\\ghost-death.ogg");
	ghostDeathSFX.setBuffer(ghostDeathBuffer);
	shootBuffer.loadFromFile("sprites\\sfx\\gun-laser.ogg");
	shootSFX.setBuffer(shootBuffer);
	levelBuffer.loadFromFile("sprites\\sfx\\levelcomplete.ogg");
	levelSFX.setBuffer(levelBuffer);

	health7 = 2;
	health8 = 2;
	health9 = 2;
	health10 = 2;
	health11 = 2;
	health12 = 3;
	health13 = 3;

	initPlayer();
}

Vector2f lerrp(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

CAS3Night::~CAS3Night() {

}

bool CAS3Night::stopBGM() {
	return levelComplete3;
}

void CAS3Night::playWind() {
	float elapsedTime = windClock.getElapsedTime().asSeconds();
	//cout << elapsedTime << endl;
	if (levelComplete3) {
		windSFX.pause();
		windSFX.play();
		if (elapsedTime >= 8) {
			windSFX.stop();
		}
	}
}

void CAS3Night::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	score1.setCharacterSize(20);
	score1.setOutlineColor(Color::Black);
	score1.setOutlineThickness(3);

	score2.setCharacterSize(20);
	score2.setOutlineColor(Color::Black);
	score2.setOutlineThickness(3);

	score3.setCharacterSize(20);
	score3.setOutlineColor(Color::Black);
	score3.setOutlineThickness(3);

	unlocked.setString("Stairs unlocked");
	unlocked.setCharacterSize(20);
	unlocked.setOutlineColor(Color::Black);
	unlocked.setOutlineThickness(3);
	unlocked.setFillColor(Color::Yellow);

	playerName.setCharacterSize(10);
	playerName.setFillColor(Color::White);
	playerName.setOutlineColor(Color::Black);
	playerName.setOutlineThickness(1.0);
	playerName.setLetterSpacing(4);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(300, 400);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	ghost1Sprite.setPosition(800, 300); //
	ghost1Sprite.setScale(1.75f, 1.75f);
	ghost2Sprite.setPosition(-300, 250); //
	ghost2Sprite.setScale(1.75f, 1.75f);
	ghost3Sprite.setPosition(1000, 200); //
	ghost3Sprite.setScale(1.75f, 1.75f);
	ghost4Sprite.setPosition(-300, 100); //
	ghost4Sprite.setScale(1.75f, 1.75f); 
	ghost5Sprite.setPosition(800, 50); //
	ghost5Sprite.setScale(1.75f, 1.75f);
	ghost6Sprite.setPosition(-500, 250); //
	ghost6Sprite.setScale(1.75f, 1.75f);
	ghost7Sprite.setPosition(1500, 300); // 
	ghost7Sprite.setScale(1.75f, 1.75f);
	ghost8Sprite.setPosition(1700, 100); // 
	ghost8Sprite.setScale(1.75f, 1.75f);
	ghost9Sprite.setPosition(-600, 100); // 
	ghost9Sprite.setScale(1.75f, 1.75f); 
	ghost10Sprite.setPosition(1700, 250); //
	ghost10Sprite.setScale(1.75f, 1.75f);
	ghost11Sprite.setPosition(2000, 50); //
	ghost11Sprite.setScale(1.75f, 1.75f);
	ghost12Sprite.setPosition(2300, 1000); //
	ghost12Sprite.setScale(1.75f, 1.75f);
	ghost13Sprite.setPosition(1500, -800); //
	ghost13Sprite.setScale(1.75f, 1.75f);

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	borderShape.setPosition(1300, 100);

	projectile.setSize(Vector2f(5.0f, 2.0f));
	projectile.setFillColor(Color::Yellow);

	broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);

	float rectAlpha = 0.0f;
	rectangles.push_back(Rectangle(250, 0, 1375, 100, rectAlpha));
	rectangles.push_back(Rectangle(1950, 0, 1360, 100, rectAlpha));

	rectangles.push_back(Rectangle(1275, 133, 25, 20, rectAlpha));
	rectangles.push_back(Rectangle(3395, 0, 350, 100, rectAlpha));
	rectangles.push_back(Rectangle(3545, 0, 350, 600, rectAlpha));
	rectangles.push_back(Rectangle(150, 0, 90, 600, rectAlpha));

	rectangles.push_back(Rectangle(1807, 392, 10, 300, rectAlpha));
	rectangles.push_back(Rectangle(2217, 392, 10, 300, rectAlpha));

	rectangles.push_back(Rectangle(664, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(462, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(1471, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(1271, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(867, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(1068, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(2079, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(2281, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(2485, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(2688, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(2889, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(3092, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(3293, 100, 20, 20, rectAlpha));
	rectangles.push_back(Rectangle(250, 100, 6, 20, rectAlpha));

	rectangles.push_back(Rectangle(1198, 100, 8, 20, rectAlpha));

	rectangles.push_back(Rectangle(345, 100, 100, 20, rectAlpha));
	rectangles.push_back(Rectangle(2369, 100, 8, 20, rectAlpha));
	rectangles.push_back(Rectangle(2780, 100, 65, 20, rectAlpha));
	rectangles.push_back(Rectangle(1958, 100, 20, 20, rectAlpha));

	rectangles.push_back(Rectangle(895, 350, 50, 20, rectAlpha));
	rectangles.push_back(Rectangle(2333, 350, 40, 20, rectAlpha));
	rectangles.push_back(Rectangle(2752, 350, 40, 20, rectAlpha));
	rectangles.push_back(Rectangle(2333, 350, 40, 20, rectAlpha));
	rectangles.push_back(Rectangle(3167, 100, 40, 20, rectAlpha));
	rectangles.push_back(Rectangle(3406, 100, 40, 20, rectAlpha));
	rectangles.push_back(Rectangle(2985, 100, 60, 30, rectAlpha));
	rectangles.push_back(Rectangle(364, 390, 60, 100, rectAlpha));

	rectangles.push_back(Rectangle(938, 100, 50, 20, rectAlpha));

	rectangles.push_back(Rectangle(1593, 100, 25, 20, rectAlpha));
	rectangles.push_back(Rectangle(3391, 390, -25, 80, rectAlpha));

	rectangles.push_back(Rectangle(363, 390, 3028, 20, rectAlpha));
	rectangles.push_back(Rectangle(3283, -20, 128, -20, rectAlpha));

	rectangles.push_back(Rectangle(1500, -20, 500, -20, rectAlpha));
	rectangles.push_back(Rectangle(3300, 510, 500, -20, rectAlpha));
	rectangles.push_back(Rectangle(200, 520, 500, -20, rectAlpha));

	updateTextPos();

}

void CAS3Night::disableGhosts(){
	showGhost1 = false;
	showGhost2 = false;
	showGhost3 = false;
	showGhost4 = false;
	showGhost5 = false;
	showGhost6 = false;
	showGhost7 = false;
	showGhost8 = false;
	showGhost9 = false;
	showGhost10 = false;
	showGhost11 = false;
	showGhost12 = false;
	showGhost13 = false;
	
	ghost1Sprite.setPosition(9000, 9000);
	ghost2Sprite.setPosition(9000, 9000);
	ghost3Sprite.setPosition(9000, 9000);
	ghost4Sprite.setPosition(9000, 9000);
	ghost5Sprite.setPosition(9000, 9000);
	ghost6Sprite.setPosition(9000, 9000);
	ghost7Sprite.setPosition(9000, 9000);
	ghost8Sprite.setPosition(9000, 9000);
	ghost9Sprite.setPosition(9000, 9000);
	ghost10Sprite.setPosition(9000, 9000);
	ghost11Sprite.setPosition(9000, 9000);
	ghost12Sprite.setPosition(9000, 9000);
	ghost13Sprite.setPosition(9000, 9000);
}

void CAS3Night::showTask1() {
	task1.setString("!\tEliminate ghosts");
	task1.setCharacterSize(25);
	task1.setOutlineColor(Color::Black);
	task1.setOutlineThickness(3);
	window.setView(window.getDefaultView());
	window.draw(task1);
}

void CAS3Night::showTask2() {
	task2.setString("!\tGo home");
	task2.setCharacterSize(25);
	task2.setOutlineColor(Color::Black);
	task2.setOutlineThickness(3);
	window.setView(window.getDefaultView());
	window.draw(task2);
	window.draw(unlocked);
	disableGhosts();
}

void CAS3Night::handleInput() {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}
	}

	if (playerSprite.getGlobalBounds().intersects(ghost1Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost2Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost3Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost4Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost5Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost6Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost7Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost8Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost9Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost10Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost11Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost12Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost13Sprite.getGlobalBounds()) ) {
		hp.damage(0.5);
	}

	if (!levelComplete3) {
		windClock.restart();
	}

	float moveSpeed = 3.5;

	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		moveSpeed += 2;
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dPressed = true;
		aPressed = false;
		broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		playerSprite.move(moveSpeed, 0);
		broomItemSprite.move(moveSpeed, 0);
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
		broomItemSprite.setPosition(playerSprite.getPosition().x - 4, playerSprite.getPosition().y + 7.5);
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		playerSprite.move(-moveSpeed, 0);
		broomItemSprite.move(-moveSpeed, 0);
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
		broomItemSprite.move(0, moveSpeed);
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
		broomItemSprite.move(0, -moveSpeed);
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && !projectileShot || Mouse::isButtonPressed(Mouse::Left) && !projectileShot) {
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

	if (playerSprite.getPosition().x <= 355 && playerSprite.getPosition().x >= 250 && playerSprite.getPosition().y <= 500 && playerSprite.getPosition().y >= 460 && levelComplete3) {
		goingSkylab = true;
	}

	//1600, 50);1950, 0);
	if (playerSprite.getPosition().x <= 1950 && playerSprite.getPosition().x >= 1600 && playerSprite.getPosition().y <= 50 && playerSprite.getPosition().y >= 0 && levelComplete3) {
		goingMainGate = true;
	}

	//3450, 450
	if (playerSprite.getPosition().x <= 3550 && playerSprite.getPosition().x >= 3350 && playerSprite.getPosition().y <= 500 && playerSprite.getPosition().y >= 440 && levelComplete3) {
		goingMainGate = true;
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

void CAS3Night::updateTextPos() {

	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1000, camera.getCenter().y - window.getSize().y / 1.80f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1100, camera.getCenter().y - window.getSize().y / 1.80f);
	score1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1150, camera.getCenter().y - window.getSize().y / 2.50f);
	score2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1150, camera.getCenter().y - window.getSize().y / 2.70f);
	score3.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1150, camera.getCenter().y - window.getSize().y / 2.90f);
	unlocked.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1120, camera.getCenter().y - window.getSize().y / 3.50f);

}

void CAS3Night::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerrp(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void CAS3Night::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	playerName.setString(pName);
	playerName.setPosition(playerSprite.getPosition().x - 5 - playerName.getLocalBounds().width / 2, playerSprite.getPosition().y - 50);

	isChasing = true;

	broomToMouse = mousePos - broomItemSprite.getPosition();
	float angle = atan2(broomToMouse.y, broomToMouse.x) * 180.0f / 3.14159265f;
	broomItemSprite.setRotation(angle);

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

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost1Sprite.getGlobalBounds())) {
		//showGhost1 = false;
		ghost1Score += 1;
		ghost1Sprite.setPosition(-1000, 200);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost2Sprite.getGlobalBounds())) {
		//showGhost2 = false;
		ghost1Score += 1;
		ghost2Sprite.setPosition(-1200, 100);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost3Sprite.getGlobalBounds())) {
		//showGhost3 = false;
		ghost1Score += 1;
		ghost3Sprite.setPosition(-700, 300);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost4Sprite.getGlobalBounds())) {
		//showGhost4 = false;
		ghost1Score += 1;
		ghost4Sprite.setPosition(500, -500);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost5Sprite.getGlobalBounds())) {
		//showGhost5 = false;
		ghost1Score += 1;
		ghost5Sprite.setPosition(1500, 1000);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost6Sprite.getGlobalBounds())) {
		//showGhost6 = false;
		ghost1Score += 1;
		ghost6Sprite.setPosition(1600, 800);
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		ghostDeathSFX.pause();
		ghostDeathSFX.play();
	}

	// ghost 2
	if (projectileShot && projectile.getGlobalBounds().intersects(ghost7Sprite.getGlobalBounds())) {
		//showGhost7 = false;
		healthCount.showHealth(ghost7Sprite.getPosition(), health7);
		health7 -= 1;
		if (health7 <= 0) {
			ghost2Score += 1;
			ghost7Sprite.setPosition(2000, 700);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health7 = 2;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost8Sprite.getGlobalBounds())) {
		//showGhost8 = false;
		healthCount.showHealth(ghost8Sprite.getPosition(), health8);
		health8 -= 1;
		if (health8 <= 0) {
			ghost2Score += 1;
			ghost8Sprite.setPosition(2000, -300);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health8 = 2;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}
	
	if (projectileShot && projectile.getGlobalBounds().intersects(ghost9Sprite.getGlobalBounds())) {
		//showGhost9 = false;
		healthCount.showHealth(ghost9Sprite.getPosition(), health9);
		health9 -= 1;
		if (health9 <= 0) {
			ghost2Score += 1;
			ghost9Sprite.setPosition(400, -300);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health9 = 2;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost10Sprite.getGlobalBounds())) {
		//showGhost10 = false;
		healthCount.showHealth(ghost10Sprite.getPosition(), health10);
		health10 -= 1;
		if (health10 <= 0) {
			ghost2Score += 1;
			ghost10Sprite.setPosition(3500, -100);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health10 = 2;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost11Sprite.getGlobalBounds())) {
		//showGhost11 = false;
		healthCount.showHealth(ghost11Sprite.getPosition(), health11);
		health11 -= 1;
		if (health11 <= 0) {
			ghost2Score += 1;
			ghost11Sprite.setPosition(2700, -200);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health11 = 2;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost12Sprite.getGlobalBounds())) {
		//showGhost12 = false;
		healthCount.showHealth(ghost12Sprite.getPosition(), health12);
		health12 -= 1;
		if (health12 <= 0) {
			ghost3Score += 1;
			ghost12Sprite.setPosition(2000, 1200);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health12 = 3;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost13Sprite.getGlobalBounds())) {
		//showGhost13 = false;
		healthCount.showHealth(ghost13Sprite.getPosition(), health13);
		health13 -= 1;
		if (health13 <= 0) {
			ghost3Score += 1;
			ghost13Sprite.setPosition(1500, -1000);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health13 = 3;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	// 5 3 1
	if (ghost1Score <= 5 && !levelComplete1) {
		score1.setString("White: " + to_string(ghost1Score) + " / 5");
	}

	if (ghost2Score <= 3 && !levelComplete1) {
		score2.setString("Blue: " + to_string(ghost2Score) + " / 3");
	}

	if (ghost3Score <= 1 && !levelComplete1) {
		score3.setString("Black: " + to_string(ghost3Score) + " / 1");
	}

	if (ghost1Score >= 5 && !levelComplete1) {
		score1.setString("White: 5 / 5");
		score1.setFillColor(Color::Green);
	}

	if (ghost2Score >= 3 && !levelComplete1) {
		score2.setString("Blue: 3 / 3");
		score2.setFillColor(Color::Green);
	}

	if (ghost3Score >= 1 && !levelComplete1) {
		score3.setString("Black: 1 / 1");
		score3.setFillColor(Color::Green);
	}

	//7 5 2
	if (ghost1Score <= 7 && !levelComplete2 && levelComplete1) {
		score1.setString("White: " + to_string(ghost1Score) + " / 7");
	}

	if (ghost2Score <= 5 && !levelComplete2 && levelComplete1) {
		score2.setString("Blue: " + to_string(ghost2Score) + " / 5");
	}

	if (ghost3Score <= 2 && !levelComplete2 && levelComplete1) {
		score3.setString("Black: " + to_string(ghost3Score) + " / 2");
	}

	if (ghost1Score >= 7 && !levelComplete2 && levelComplete1) {
		score1.setString("White: 7 / 7");
		score1.setFillColor(Color::Green);
	}

	if (ghost2Score >= 5 && !levelComplete2 && levelComplete1) {
		score2.setString("Blue: 5 / 5");
		score2.setFillColor(Color::Green);
	}

	if (ghost3Score >= 2 && !levelComplete2 && levelComplete1) {
		score3.setString("Black: 2 / 2");
		score3.setFillColor(Color::Green);
	}

	//10 8 5
	if (ghost1Score <= 10 && !levelComplete3 && levelComplete2) {
		score1.setString("White: " + to_string(ghost1Score) + " / 10");
	}

	if (ghost2Score <= 8 && !levelComplete3 && levelComplete2) {
		score2.setString("Blue: " + to_string(ghost2Score) + " / 8");
	}

	if (ghost3Score <= 5 && !levelComplete3 && levelComplete2) {
		score3.setString("Black: " + to_string(ghost3Score) + " / 5");
	}

	if (ghost1Score >= 10 && !levelComplete3 && levelComplete2) {
		score1.setString("White: 10 / 10");
		score1.setFillColor(Color::Green);
	}

	if (ghost2Score >= 8 && !levelComplete3 && levelComplete2) {
		score2.setString("Blue: 8 / 8");
		score2.setFillColor(Color::Green);
	}

	if (ghost3Score >= 5 && !levelComplete3 && levelComplete2) {
		score3.setString("Black: 5 / 5");
		score3.setFillColor(Color::Green);
	}

	//5 3 1
	if (ghost1Score >= 5 && ghost2Score >= 3 && ghost3Score >= 1 && !levelComplete1 && !levelComplete3) {
		levelComplete1 = true;
		startLevel2 = true;

		levelSFX.pause();
		levelSFX.play();

		ghost1Score = 0;
		ghost2Score = 0;
		ghost3Score = 0;

		score1.setFillColor(Color::White);
		score2.setFillColor(Color::White);
		score3.setFillColor(Color::White);

		ghost1Sprite.setPosition(-1000, 200);
		ghost2Sprite.setPosition(-1200, 100);
		ghost3Sprite.setPosition(-700, 300);
		ghost4Sprite.setPosition(500, -500);
		ghost5Sprite.setPosition(1500, 1000);
		ghost6Sprite.setPosition(1600, 800);
		ghost7Sprite.setPosition(2000, 700);
		ghost8Sprite.setPosition(2000, -300);
		ghost9Sprite.setPosition(400, -300);
		ghost10Sprite.setPosition(3500, -100);
		ghost11Sprite.setPosition(2700, -200);
		ghost12Sprite.setPosition(2000, 1200);
		ghost13Sprite.setPosition(1500, -1000);
	}

	//7 5 2
	if (ghost1Score >= 7 && ghost2Score >= 5 && ghost3Score >= 2 && levelComplete1 && startLevel2 && !startLevel3 && !levelComplete3) {
		levelComplete2 = true;
		startLevel3 = true;

		ghost1Score = 0;
		ghost2Score = 0;
		ghost3Score = 0;

		levelSFX.pause();
		levelSFX.play();

		score1.setFillColor(Color::White);
		score2.setFillColor(Color::White);
		score3.setFillColor(Color::White);

		ghost1Sprite.setPosition(-1000, 200);
		ghost2Sprite.setPosition(-1200, 100);
		ghost3Sprite.setPosition(-700, 300);
		ghost4Sprite.setPosition(500, -500);
		ghost5Sprite.setPosition(1500, 1000);
		ghost6Sprite.setPosition(1600, 800);
		ghost7Sprite.setPosition(2000, 700);
		ghost8Sprite.setPosition(2000, -300);
		ghost9Sprite.setPosition(400, -300);
		ghost10Sprite.setPosition(3500, -100);
		ghost11Sprite.setPosition(2700, -200);
		ghost12Sprite.setPosition(2000, 1200);
		ghost13Sprite.setPosition(1500, -1000);
	}

	//10 8 5
	if (ghost1Score >= 10 && ghost2Score >= 8 && ghost3Score >= 5 && levelComplete2 && startLevel3 && !levelComplete3) {
		levelComplete3 = true;
		showHP = false;
		levelSFX.pause();
		levelSFX.play();
	}
}


void CAS3Night::animUpdate(float dt) {
	currentImage.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= 3) {
			currentImage.x = 0;
		}
	}

	ghostRect.left = currentImage.x * ghostRect.width;
	ghostRect.top = currentImage.y * ghostRect.height;

	if (isChasing) {
		//cout << "is chasing true" << endl;

		float angle = atan2(playerSprite.getPosition().y - ghost1Sprite.getPosition().y, playerSprite.getPosition().x - ghost1Sprite.getPosition().x);
		float x = 1.5 * cos(angle);
		float y = 1.5 * sin(angle);
		ghost1Sprite.move(x, y);

		float angle2 = atan2(playerSprite.getPosition().y - ghost2Sprite.getPosition().y, playerSprite.getPosition().x - ghost2Sprite.getPosition().x);
		float x2 = 1.5 * cos(angle2);
		float y2 = 1.5 * sin(angle2);
		ghost2Sprite.move(x2, y2);

		float angle3 = atan2(playerSprite.getPosition().y - ghost3Sprite.getPosition().y, playerSprite.getPosition().x - ghost3Sprite.getPosition().x);
		float x3 = 1.5 * cos(angle3);
		float y3 = 1.5 * sin(angle3);
		ghost3Sprite.move(x3, y3);

		float angle4 = atan2(playerSprite.getPosition().y - ghost4Sprite.getPosition().y, playerSprite.getPosition().x - ghost4Sprite.getPosition().x);
		float x4 = 1.5 * cos(angle4);
		float y4 = 1.5 * sin(angle4);
		ghost4Sprite.move(x4, y4);

		float angle5 = atan2(playerSprite.getPosition().y - ghost5Sprite.getPosition().y, playerSprite.getPosition().x - ghost5Sprite.getPosition().x);
		float x5 = 1.5 * cos(angle5);
		float y5 = 1.5 * sin(angle5);
		ghost5Sprite.move(x5, y5);

		float angle6 = atan2(playerSprite.getPosition().y - ghost6Sprite.getPosition().y, playerSprite.getPosition().x - ghost6Sprite.getPosition().x);
		float x6 = 1.5 * cos(angle6);
		float y6 = 1.5 * sin(angle6);
		ghost6Sprite.move(x6, y6);

		float angle7 = atan2(playerSprite.getPosition().y - ghost7Sprite.getPosition().y, playerSprite.getPosition().x - ghost7Sprite.getPosition().x);
		float x7 = 1.5 * cos(angle7);
		float y7 = 1.5 * sin(angle7);
		ghost7Sprite.move(x7, y7);

		float angle8 = atan2(playerSprite.getPosition().y - ghost8Sprite.getPosition().y, playerSprite.getPosition().x - ghost8Sprite.getPosition().x);
		float x8 = 1.5 * cos(angle8);
		float y8 = 1.5 * sin(angle8);
		ghost8Sprite.move(x8, y8);

		float angle9 = atan2(playerSprite.getPosition().y - ghost9Sprite.getPosition().y, playerSprite.getPosition().x - ghost9Sprite.getPosition().x);
		float x9 = 1.5 * cos(angle9);
		float y9 = 1.5 * sin(angle9);
		ghost9Sprite.move(x9, y9);

		float angle10 = atan2(playerSprite.getPosition().y - ghost10Sprite.getPosition().y, playerSprite.getPosition().x - ghost10Sprite.getPosition().x);
		float x10 = 1.5 * cos(angle10);
		float y10 = 1.5 * sin(angle10);
		ghost10Sprite.move(x10, y10);

		float angle11 = atan2(playerSprite.getPosition().y - ghost11Sprite.getPosition().y, playerSprite.getPosition().x - ghost11Sprite.getPosition().x);
		float x11 = 1.5 * cos(angle11);
		float y11 = 1.5 * sin(angle11);
		ghost11Sprite.move(x11, y11);

		float angle12 = atan2(playerSprite.getPosition().y - ghost12Sprite.getPosition().y, playerSprite.getPosition().x - ghost12Sprite.getPosition().x);
		float x12 = 1.5 * cos(angle12);
		float y12 = 1.5 * sin(angle12);
		ghost12Sprite.move(x12, y12);

		float angle13 = atan2(playerSprite.getPosition().y - ghost13Sprite.getPosition().y, playerSprite.getPosition().x - ghost13Sprite.getPosition().x);
		float x13 = 1.5 * cos(angle13);
		float y13 = 1.5 * sin(angle13);
		ghost13Sprite.move(x13, y13);
	}
}

bool CAS3Night::gotoSkylab() {
	return goingSkylab;
}

void CAS3Night::playerPosFromSkylab() {
	playerSprite.setPosition(300, 400);
	broomItemSprite.setPosition(300, 400);
}

void CAS3Night::goingSkylabFalse() {
	goingSkylab = false;
}

bool CAS3Night::gotoMainGate() {
	return goingMainGate;
}

void CAS3Night::playerPosFromMainGate() {
	playerSprite.setPosition(1800, 150);
	broomItemSprite.setPosition(1800, 150);
}

void CAS3Night::goingMainGateFalse() {
	goingMainGate = false;
}

bool CAS3Night::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void CAS3Night::handleCollision(const Rectangle& rect) {
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

void CAS3Night::restart() {
	cout << "restart" << endl;
	playerSprite.setPosition(300, 400);
	hp.resetHealth();
	levelComplete1 = false;
	levelComplete2 = false;
	levelComplete3 = false;
	startLevel2 = false;
	startLevel3 = false;

	ghost1Score = 0;
	ghost2Score = 0;
	ghost3Score = 0;

	score1.setFillColor(Color::White);
	score2.setFillColor(Color::White);
	score3.setFillColor(Color::White);

	ghost1Sprite.setPosition(-1000, 200);
	ghost2Sprite.setPosition(-1200, 100);
	ghost3Sprite.setPosition(-700, 300);
	ghost4Sprite.setPosition(500, -500);
	ghost5Sprite.setPosition(1500, 1000);
	ghost6Sprite.setPosition(1600, 800);
	ghost7Sprite.setPosition(2000, 700);
	ghost8Sprite.setPosition(2000, -300);
	ghost9Sprite.setPosition(400, -300);
	ghost10Sprite.setPosition(3500, -100);
	ghost11Sprite.setPosition(2700, -200);
	ghost12Sprite.setPosition(2000, 1200);
	ghost13Sprite.setPosition(1500, -1000);
}

void CAS3Night::render() {

	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(1.6f, 1.6f);
	playerSprite.setScale(1.75f, 1.75f);
	broomItemSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
	window.draw(broomItemSprite);
	window.draw(playerSprite);
	ghost1Sprite.setTextureRect(ghostRect);
	ghost2Sprite.setTextureRect(ghostRect);
	ghost3Sprite.setTextureRect(ghostRect);
	ghost4Sprite.setTextureRect(ghostRect);
	ghost5Sprite.setTextureRect(ghostRect);
	ghost6Sprite.setTextureRect(ghostRect);
	ghost7Sprite.setTextureRect(ghostRect);
	ghost8Sprite.setTextureRect(ghostRect);
	ghost9Sprite.setTextureRect(ghostRect);
	ghost10Sprite.setTextureRect(ghostRect);
	ghost11Sprite.setTextureRect(ghostRect);
	ghost12Sprite.setTextureRect(ghostRect);
	ghost13Sprite.setTextureRect(ghostRect);


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

	if (showGhost8) {
		window.draw(ghost8Sprite);
	}

	if (showGhost9) {
		window.draw(ghost9Sprite);
	}

	if (showGhost10) {
		window.draw(ghost10Sprite);
	}

	if (showGhost11) {
		window.draw(ghost11Sprite);
	}

	if (showGhost12) {
		window.draw(ghost12Sprite);
	}

	if (showGhost13) {
		window.draw(ghost13Sprite);
	}

	healthCount.render();

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.draw(projectile);
	window.draw(playerName);

	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);
	window.draw(score1);
	window.draw(score2);
	window.draw(score3);

	if (!levelComplete3) {
		showTask1();
	}
	else {
		showTask2();
		playWind();
	}

	/*if (showHP) {
		hp.update();
		hp.setHealth(100.0);
		hp.render();
	}*/

	if (hp.noHP()) {
		restart();
	}
	else if(showHP && !hp.noHP()) {
		hp.update();
		hp.setHealth(100.0);
		hp.render();
	}
}