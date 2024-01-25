#include "HMRoom1.h"
#include "HMDay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

HMRoom1::HMRoom1(RenderWindow& window) : window(window), fadeTrans(window),
dPressed(false), aPressed(true), dampingFactor(0.3f), pauseMenu(window),
gamePaused(false), dialogueBox(window), goingHM(false), bossDefeated(false),
weapon1Show(false), weapon2Show(false), weapon3Show(false) {

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\hm-room1-night.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico-night.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	shakeTime = 0.1f;
	shakeMagnitude = 0.1f;

	broomItemTexture.loadFromFile("sprites\\items\\broom-night.png");
	broomItemSprite.setTexture(broomItemTexture);
	broomItemSprite.setOrigin(broomItemTexture.getSize().x / 2.0f, broomItemTexture.getSize().y / 2.0f);
	
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

	ghostDeathBuffer.loadFromFile("sprites\\sfx\\ghost-death.ogg");
	ghostDeathSFX.setBuffer(ghostDeathBuffer);
	shootBuffer.loadFromFile("sprites\\sfx\\gun-laser.ogg");
	shootSFX.setBuffer(shootBuffer);

	initPlayer();
}

HMRoom1::~HMRoom1() {

}

Vector2f lerp3(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void HMRoom1::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	task1.setString("!\t???");
	task1.setCharacterSize(25);
	task1.setOutlineColor(Color::Black);
	task1.setOutlineThickness(3);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(345, 500);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	projectile.setSize(Vector2f(5.0f, 2.0f));
	projectile.setFillColor(Color::Yellow);

	broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);

	float rectAlpha = 0.0f;

	rectangles.push_back(Rectangle(250, 20, 1000, 100, rectAlpha)); // upper
	rectangles.push_back(Rectangle(250, 538, 1000, 100, rectAlpha)); // lower
	rectangles.push_back(Rectangle(200, 100, 60, 500, rectAlpha)); // left
	rectangles.push_back(Rectangle(820, 100, 60, 500, rectAlpha)); // right

	// items
	rectangles.push_back(Rectangle(367, 420, 76, 10, rectAlpha));
	rectangles.push_back(Rectangle(340, 219, 10, 60, rectAlpha));
	rectangles.push_back(Rectangle(668, 312, 10, 68, rectAlpha));
	rectangles.push_back(Rectangle(676, 238, 71, 20, rectAlpha));

	// columns
	rectangles.push_back(Rectangle(436, 127, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(628, 127, 10, 10, rectAlpha));

	updateTextPos();
}

void HMRoom1::handleInput() {
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
		//broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		playerSprite.move(moveSpeed, 0);
		//broomItemSprite.move(moveSpeed, 0);
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
		//broomItemSprite.setPosition(playerSprite.getPosition().x - 4, playerSprite.getPosition().y + 7.5);
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		playerSprite.move(-moveSpeed, 0);
		//broomItemSprite.move(-moveSpeed, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		int pos = 0;
		pos = (int)playerSprite.getPosition().y / 35 % 4;
		pos = pos * 32;
		if (weapon1Show) {
			weapon1Sprite.move(0, moveSpeed);
		}
		if (weapon2Show) {
			weapon2Sprite.move(0, moveSpeed);
		}
		if (weapon3Show) {
			weapon3Sprite.move(0, moveSpeed);
		}
		if (dPressed) {
			playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		}
		if (aPressed) {
			playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		}
		playerSprite.move(0, moveSpeed);
		//broomItemSprite.move(0, moveSpeed);
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		int pos = 0;
		pos = (int)playerSprite.getPosition().y / 35 % 4;
		pos = pos * 32;
		if (weapon1Show) {
			weapon1Sprite.move(0, -moveSpeed);
		}
		if (weapon2Show) {
			weapon2Sprite.move(0, -moveSpeed);
		}
		if (weapon3Show) {
			weapon3Sprite.move(0, -moveSpeed);
		}
		if (dPressed) {
			playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		}
		if (aPressed) {
			playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		}
		playerSprite.move(0, -moveSpeed);
		//broomItemSprite.move(0, -moveSpeed);
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && !projectileShot || Mouse::isButtonPressed(Mouse::Left) && !projectileShot) {
		//cout << "projectile shot false\n";
		shootSFX.pause();
		shootSFX.play();
		shakeClock.restart();
		isShaking = true;
		if (weapon1Show) {
			projectileDirection = mousePos - weapon1Sprite.getPosition();
		}
		if (weapon2Show) {
			projectileDirection = mousePos - weapon2Sprite.getPosition();
		}
		if (weapon3Show) {
			projectileDirection = mousePos - weapon3Sprite.getPosition();
		}
		//projectileDirection = mousePos - broomItemSprite.getPosition();
		float length = sqrt(projectileDirection.x * projectileDirection.x + projectileDirection.y * projectileDirection.y);
		projectileDirection /= length;
		if (dPressed) {
			if (weapon1Show) {
				projectile.setPosition(weapon1Sprite.getPosition().x + 10.0f, weapon1Sprite.getPosition().y - 5.0f);
			}
			if (weapon2Show) {
				projectile.setPosition(weapon2Sprite.getPosition().x + 10.0f, weapon2Sprite.getPosition().y - 5.0f);
			}
			if (weapon3Show) {
				projectile.setPosition(weapon3Sprite.getPosition().x + 10.0f, weapon3Sprite.getPosition().y - 5.0f);
			}
			//projectile.setPosition(broomItemSprite.getPosition().x + 10.0f, broomItemSprite.getPosition().y - 5.0f);
		}
		if (aPressed) {
			if (weapon1Show) {
				projectile.setPosition(weapon1Sprite.getPosition().x - 20.0f, weapon1Sprite.getPosition().y - 5.0f);
			}
			if (weapon2Show) {
				projectile.setPosition(weapon2Sprite.getPosition().x - 20.0f, weapon2Sprite.getPosition().y - 5.0f);
			}
			if (weapon3Show) {
				projectile.setPosition(weapon3Sprite.getPosition().x - 20.0f, weapon3Sprite.getPosition().y - 5.0f);
			}
			//projectile.setPosition(broomItemSprite.getPosition().x - 20.0f, broomItemSprite.getPosition().y - 5.0f);
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

	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		bossDefeated = true;
	}
	// 730x - 770x, 525y
	if (bossDefeated && playerSprite.getPosition().x <= 780 && playerSprite.getPosition().x >= 710 && playerSprite.getPosition().y <= 650 && playerSprite.getPosition().y >= 480 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingHM = true;
	}

	//305x - 350x, 525y
	if (bossDefeated && playerSprite.getPosition().x <= 370 && playerSprite.getPosition().x >= 290 && playerSprite.getPosition().y <= 650 && playerSprite.getPosition().y >= 480 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingHM = true;
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

void HMRoom1::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 880, camera.getCenter().y - window.getSize().y / 1.80f);
}

void HMRoom1::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp3(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void HMRoom1::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	if (weapon1Show) {
		broomToMouse = mousePos - weapon1Sprite.getPosition();
	}
	if (weapon2Show) {
		broomToMouse = mousePos - weapon2Sprite.getPosition();
	}
	if (weapon3Show) {
		broomToMouse = mousePos - weapon3Sprite.getPosition();
	}
	//broomToMouse = mousePos - broomItemSprite.getPosition();
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

	if (bossDefeated) {
		dialogue = true;
	}
}

void HMRoom1::animUpdate(float dt) {

}

bool HMRoom1::gotoHM() {
	return goingHM;
}

void HMRoom1::playerPosFromHM() {
	playerSprite.setPosition(325, 500);
}

void HMRoom1::goingHMFalse() {
	goingHM = false;
}

bool HMRoom1::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void HMRoom1::handleCollision(const Rectangle& rect) {
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

void HMRoom1::showDialogue() {
	dialogueBox.initDialogue("\n\tYou feel uneasy... you need to escape...");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		dialogue = false;
		dialogueBox.reset();
	}
}

bool HMRoom1::bossDead() {
	return bossDefeated;
}

void HMRoom1::setWeapon1() {
	weapon1Show = true;
}

void HMRoom1::setWeapon2() {
	weapon2Show = true;
}

void HMRoom1::setWeapon3() {
	weapon3Show = true;
}

void HMRoom1::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(0.6f, 0.6f);
	playerSprite.setScale(1.75f, 1.75f);
	broomItemSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
	if (weapon1Show) {
		window.draw(weapon1Sprite);
	}
	if (weapon2Show) {
		window.draw(weapon2Sprite);
	}
	if (weapon3Show) {
		window.draw(weapon3Sprite);
	}
	//window.draw(broomItemSprite);
	window.draw(playerSprite);
	window.draw(projectile);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.setView(window.getDefaultView());

	window.draw(quitText);
	window.draw(pauseText);
	if (!bossDefeated) {
		window.draw(task1);
	}
	if (dialogue) {
		showDialogue();
	}
}