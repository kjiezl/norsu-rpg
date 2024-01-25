#include "HM2ndNight.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

HM2ndNight::HM2ndNight(RenderWindow& window) : window(window), fadeTrans(window), dPressed(false),
aPressed(true), dampingFactor(0.3f), pauseMenu(window), gamePaused(false),
dialogueBox(window), showGhost7(true), showGhost6(true), showGhost5(true),
showGhost4(true), showGhost3(true), showGhost1(true), showGhost2(true),
projectileShot(false), isShaking(false), isChasing(false), weapon1Show(false),
weapon2Show(false), weapon3Show(false), inv(window) {

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\hm2-night.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico-night.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	arrowTex.loadFromFile("sprites\\ui\\guide-arrow.png");
	arrowSprite.setTexture(arrowTex);

	totalTime = 0.0f;

	switchTimeArrow = 0.2f;
	currentImageArrow.x = 0;
	arrowRect.width = arrowTex.getSize().x / 4;
	arrowRect.height = arrowTex.getSize().y / 1;

	broomItemTexture.loadFromFile("sprites\\items\\broom-night.png");
	broomItemSprite.setTexture(broomItemTexture);
	broomItemSprite.setOrigin(broomItemTexture.getSize().x / 2.0f, broomItemTexture.getSize().y / 2.0f);
	broomItemSprite.setScale(1.75f, 1.75f);
	//broomItemSprite.setPosition(2420, 125);

	weapon1Texture.loadFromFile("sprites\\items\\lighter.png");
	weapon1Sprite.setTexture(weapon1Texture);
	weapon1Sprite.setOrigin(weapon1Texture.getSize().x / 2.0f, weapon1Texture.getSize().y / 2.0f);
	weapon1Sprite.setScale(1.2f, 1.2f);

	weapon2Texture.loadFromFile("sprites\\items\\spitball.png");
	weapon2Sprite.setTexture(weapon2Texture);
	weapon2Sprite.setOrigin(weapon2Texture.getSize().x / 2.0f, weapon2Texture.getSize().y / 2.0f);
	weapon2Sprite.setScale(1.2f, 1.2f);

	weapon3Texture.loadFromFile("sprites\\items\\stapler.png");
	weapon3Sprite.setTexture(weapon3Texture);
	weapon3Sprite.setOrigin(weapon3Texture.getSize().x / 2.0f, weapon3Texture.getSize().y / 2.0f);
	weapon3Sprite.setScale(1.2f, 1.2f);

	ghost1Texture.loadFromFile("sprites\\enemies\\ghost1.1.png");
	ghost2Texture.loadFromFile("sprites\\enemies\\ghost1.2.png");
	ghost1Sprite.setTexture(ghost1Texture);
	ghost2Sprite.setTexture(ghost1Texture);
	ghost3Sprite.setTexture(ghost1Texture);
	ghost4Sprite.setTexture(ghost2Texture);
	ghost5Sprite.setTexture(ghost2Texture);
	ghost6Sprite.setTexture(ghost2Texture);
	ghost7Sprite.setTexture(ghost2Texture);
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

HM2ndNight::~HM2ndNight() {

}

Vector2f lerp1(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void HM2ndNight::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	task.setString("!\tGo home");
	task.setCharacterSize(25);
	task.setOutlineColor(Color::Black);
	task.setOutlineThickness(3);

	arrowSprite.setPosition(2420, 125);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(330, 230);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	ghost1Sprite.setPosition(1480, 300);
	ghost2Sprite.setPosition(2090, 300);
	ghost3Sprite.setPosition(450, 175);
	ghost4Sprite.setPosition(300, 300);
	ghost5Sprite.setPosition(800, 320);
	ghost6Sprite.setPosition(3100, 200);
	ghost7Sprite.setPosition(2600, 320);

	projectile.setSize(Vector2f(5.0f, 2.0f));
	projectile.setFillColor(Color::Yellow);

	float rectAlpha = 0.0f;
	// big upper
	rectangles.push_back(Rectangle(250, -20, 3000, 100, rectAlpha));
	// big lower 1
	rectangles.push_back(Rectangle(355, 400, 2427, 600, rectAlpha));
	rectangles.push_back(Rectangle(200, 100, 40, 700, rectAlpha)); // big left
	rectangles.push_back(Rectangle(2920, 100, 40, 700, rectAlpha)); // big right

	// columns up
	//rectangles.push_back(Rectangle(388, 95, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(246, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(450, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(655, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(860, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1065, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1268, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1471, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1681, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1884, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2090, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2293, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2497, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2704, 85, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2907, 85, 10, 10, rectAlpha));

	rectangles.push_back(Rectangle(2635, 75, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1320, 85, 40, 10, rectAlpha));
	rectangles.push_back(Rectangle(1138, 85, 72, 10, rectAlpha));

	// columns down
	rectangles.push_back(Rectangle(450, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(450, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(655, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(860, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1065, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1268, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1471, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1681, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1884, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2090, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2293, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2497, 379, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2704, 379, 10, 10, rectAlpha));

	// stairs
	rectangles.push_back(Rectangle(200, 455, 200, 10, rectAlpha));
	rectangles.push_back(Rectangle(2700, 455, 200, 10, rectAlpha));

	updateTextPos();
}

void HM2ndNight::handleInput() {
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
		/*broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);
		broomItemSprite.move(moveSpeed, 0);*/
		if (weapon1Show) {
			weapon1Sprite.setPosition(playerSprite.getPosition().x + 12, playerSprite.getPosition().y + 7.5);
			weapon1Sprite.move(moveSpeed, 0);
		}
		if (weapon2Show) {
			weapon2Sprite.setPosition(playerSprite.getPosition().x + 12, playerSprite.getPosition().y + 7.5);
			weapon2Sprite.move(moveSpeed, 0);
		}
		if (weapon3Show) {
			weapon3Sprite.setPosition(playerSprite.getPosition().x + 12, playerSprite.getPosition().y + 7.5);
			weapon3Sprite.move(moveSpeed, 0);
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
		/*broomItemSprite.setPosition(playerSprite.getPosition().x - 4, playerSprite.getPosition().y + 7.5);
		broomItemSprite.move(-moveSpeed, 0);*/
		if (weapon1Show) {
			weapon1Sprite.setPosition(playerSprite.getPosition().x - 12, playerSprite.getPosition().y + 7.5);
			weapon1Sprite.move(-moveSpeed, 0);
		}
		if (weapon2Show) {
			weapon2Sprite.setPosition(playerSprite.getPosition().x - 12, playerSprite.getPosition().y + 7.5);
			weapon2Sprite.move(-moveSpeed, 0);
		}
		if (weapon3Show) {
			weapon3Sprite.setPosition(playerSprite.getPosition().x - 12, playerSprite.getPosition().y + 7.5);
			weapon3Sprite.move(-moveSpeed, 0);
		}
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		playerSprite.move(-moveSpeed, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		int pos = 0;
		/*broomItemSprite.move(0, moveSpeed);*/
		if (weapon1Show) {
			weapon1Sprite.move(0, moveSpeed);
		}
		if (weapon2Show) {
			weapon2Sprite.move(0, moveSpeed);
		}
		if (weapon3Show) {
			weapon3Sprite.move(0, moveSpeed);
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
		/*broomItemSprite.move(0, -moveSpeed);*/
		if (weapon1Show) {
			weapon1Sprite.move(0, -moveSpeed);
		}
		if (weapon2Show) {
			weapon2Sprite.move(0, -moveSpeed);
		}
		if (weapon3Show) {
			weapon3Sprite.move(0, -moveSpeed);
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

	// 250-340x 390 
	if (playerSprite.getPosition().x <= 360 && playerSprite.getPosition().x >= 230 && playerSprite.getPosition().y <= 500 && playerSprite.getPosition().y >= 420) {
		goingHM = true;
	}

	// 2420 130
	if (playerSprite.getPosition().x <= 2470 && playerSprite.getPosition().x >= 2370 && playerSprite.getPosition().y <= 150 && playerSprite.getPosition().y >= 80 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingHMRoom2 = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && !projectileShot || Mouse::isButtonPressed(Mouse::Left) && !projectileShot) {
		//cout << "projectile shot false\n";
		shootSFX.pause();
		shootSFX.play();
		shakeClock.restart();
		isShaking = true;
		//projectileDirection = mousePos - broomItemSprite.getPosition();
		if (weapon1Show) {
			projectileDirection = mousePos - weapon1Sprite.getPosition();
		}
		if (weapon2Show) {
			projectileDirection = mousePos - weapon2Sprite.getPosition();
		}
		if (weapon3Show) {
			projectileDirection = mousePos - weapon3Sprite.getPosition();
		}
		float length = sqrt(projectileDirection.x * projectileDirection.x + projectileDirection.y * projectileDirection.y);
		projectileDirection /= length;
		if (dPressed) {
			//projectile.setPosition(broomItemSprite.getPosition().x + 10.0f, broomItemSprite.getPosition().y - 5.0f);
			if (weapon1Show) {
				projectile.setPosition(weapon1Sprite.getPosition().x + 10.0f, weapon1Sprite.getPosition().y - 5.0f);
			}
			if (weapon2Show) {
				projectile.setPosition(weapon2Sprite.getPosition().x + 10.0f, weapon2Sprite.getPosition().y - 5.0f);
			}
			if (weapon3Show) {
				projectile.setPosition(weapon3Sprite.getPosition().x + 10.0f, weapon3Sprite.getPosition().y - 5.0f);
			}
		}
		if (aPressed) {
			//projectile.setPosition(broomItemSprite.getPosition().x - 20.0f, broomItemSprite.getPosition().y - 5.0f);
			if (weapon1Show) {
				projectile.setPosition(weapon1Sprite.getPosition().x - 20.0f, weapon1Sprite.getPosition().y - 5.0f);
			}
			if (weapon2Show) {
				projectile.setPosition(weapon2Sprite.getPosition().x - 20.0f, weapon2Sprite.getPosition().y - 5.0f);
			}
			if (weapon3Show) {
				projectile.setPosition(weapon3Sprite.getPosition().x - 20.0f, weapon3Sprite.getPosition().y - 5.0f);
			}
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

void HM2ndNight::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1100, camera.getCenter().y - window.getSize().y / 1.80f);
}

void HM2ndNight::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp1(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void HM2ndNight::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	isChasing = true;

	//broomToMouse = mousePos - broomItemSprite.getPosition();
	if (weapon1Show) {
		broomToMouse = mousePos - weapon1Sprite.getPosition();
	}
	if (weapon2Show) {
		broomToMouse = mousePos - weapon2Sprite.getPosition();
	}
	if (weapon3Show) {
		broomToMouse = mousePos - weapon3Sprite.getPosition();
	}
	float angle = atan2(broomToMouse.y, broomToMouse.x) * 180.0f / 3.14159265f;
	if (weapon1Show) {
		weapon1Sprite.setRotation(angle);
	}
	if (weapon2Show) {
		weapon2Sprite.setRotation(angle);
	}
	if (weapon3Show) {
		weapon3Sprite.setRotation(angle);
	}
	//broomItemSprite.setRotation(angle);

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
	}

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
}

void HM2ndNight::animUpdate(float dt) {
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

bool HM2ndNight::gotoHM() {
	return goingHM;
}

void HM2ndNight::playerPosFromHM() {
	playerSprite.setPosition(300, 350);
}

void HM2ndNight::goingHMFalse() {
	goingHM = false;
}

bool HM2ndNight::gotoHMRoom2() {
	return goingHMRoom2;
}

void HM2ndNight::playerPosFromHMRoom2() {
	playerSprite.setPosition(2420, 150);
}

void HM2ndNight::goingHMRoom2False() {
	goingHMRoom2 = false;
}

bool HM2ndNight::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void HM2ndNight::handleCollision(const Rectangle& rect) {
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

void HM2ndNight::setWeapon1() {
	weapon1Show = true;
}

void HM2ndNight::setWeapon2() {
	weapon2Show = true;
}

void HM2ndNight::setWeapon3() {
	weapon3Show = true;
}

void HM2ndNight::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	arrowSprite.setTextureRect(arrowRect);
	ghost1Sprite.setTextureRect(ghostRect);
	ghost2Sprite.setTextureRect(ghostRect);
	ghost3Sprite.setTextureRect(ghostRect);
	ghost4Sprite.setTextureRect(ghostRect);
	ghost5Sprite.setTextureRect(ghostRect);
	ghost6Sprite.setTextureRect(ghostRect);
	ghost7Sprite.setTextureRect(ghostRect);
	bgSprite.setScale(1.3f, 1.3f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
	window.draw(arrowSprite);
	//window.draw(broomItemSprite);
	if (weapon1Show) {
		window.draw(weapon1Sprite);
	}
	if (weapon2Show) {
		window.draw(weapon2Sprite);
	}
	if (weapon3Show) {
		window.draw(weapon3Sprite);
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

	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);
	window.draw(task);
	
	/*inv.updateTextPos();
	inv.render();*/
}