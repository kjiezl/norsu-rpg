#include "SkylabRoomNight.h"
#include "PauseMenu.h"
#include "PlayerName.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "SkylabNight.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

// FIX VECTORS

SkylabRoomNight::SkylabRoomNight(RenderWindow& window, const string& pName) : window(window), 
nightBGM(true), isShaking(false), projectileShot(false), dialogue2(false), dialogue(false), 
dialogueBox(window), showTutorText(false), showGhost2(false), showGhost1(false), 
broomPicked(false), showPickupText(false), showBroom(true), animBroom(false), showPhone(true), 
showPhoneTask(false), showGoHome(true), showExitText(false), goingSkylab(false), 
playerNameClass(window), pName(pName), pauseMenu(window), gamePaused(false), fadeTrans(window),
dampingFactor(0.3f), dPressed(true), aPressed(false) {
	cout << endl << pName << endl;

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		cout << "no font" << endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	task2.setFont(font);
	pickupItemText.setFont(font);
	tutorText.setFont(font);
	//playerName.setString("");
	playerName.setFont(font);
	bgTexture.loadFromFile("sprites\\maps\\skylabroom-night.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico-night.png");
	phoneTexture.loadFromFile("sprites\\items\\phone.png");
	broomTexture.loadFromFile("sprites\\items\\broom-bg.png");
	broomAnimTexture.loadFromFile("sprites\\items\\broom-highlight.png");
	ghost1Texture.loadFromFile("sprites\\enemies\\ghost1.1.png");
	windBuffer.loadFromFile("sprites\\sfx\\wind.ogg");
	windSFX.setBuffer(windBuffer);
	ghostDeathBuffer.loadFromFile("sprites\\sfx\\ghost-death.ogg");
	ghostDeathSFX.setBuffer(ghostDeathBuffer);
	shootBuffer.loadFromFile("sprites\\sfx\\gun-laser.ogg");
	shootSFX.setBuffer(shootBuffer);
	pickupBuffer.loadFromFile("sprites\\sfx\\pickup-items.ogg");
	pickupSFX.setBuffer(pickupBuffer);

	totalTime = 0.0f;
	switchTimeBroom = 0.2f;
	currentImageBroom.x = 0;
	broomRect.width = broomAnimTexture.getSize().x / 4;
	broomRect.height = broomAnimTexture.getSize().y / 1;

	switchTimeGhost1 = 0.2f;
	currentImageGhost1.x = 0;
	ghost1Rect.width = ghost1Texture.getSize().x / 3;
	ghost1Rect.height = ghost1Texture.getSize().y / 1;

	exitDoorText.setFont(font);




	broomItemTexture.loadFromFile("sprites\\items\\broom-night.png");
	items.push_back(broomItemTexture);
	lightsaberTexture.loadFromFile("sprites\\items\\lightsaber-night.png");
	items.push_back(lightsaberTexture);
	glockTexture.loadFromFile("sprites\\items\\glock-night.png");
	items.push_back(glockTexture);
	nerfTexture.loadFromFile("sprites\\items\\nerf-night.png");
	items.push_back(nerfTexture);
	pewpewTexture.loadFromFile("sprites\\items\\pewpew-night.png");
	items.push_back(pewpewTexture);

	shakeTime = 0.1f;
	shakeMagnitude = 0.1f;

	initPlayer();
}

Vector2f lerpp(const Vector2f& start, const Vector2f& end) {
	float t = 0.3f;
	return start + t * (end - start);
}

void SkylabRoomNight::switchItem() {
	itemIndex = (itemIndex + 1) % items.size();
	broomItemSprite.setTexture(items[itemIndex]);
	
	broomItemSprite.setOrigin(broomItemTexture.getSize().x / 2.0f, broomItemTexture.getSize().y / 2.0f);
	broomItemSprite.setScale(1.75f, 1.75f);
}

SkylabRoomNight::~SkylabRoomNight() {

}

bool SkylabRoomNight::startBGM() {
	return broomPicked;
}

void SkylabRoomNight::initPlayer() {
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

	task2.setString("!\tRetrieve your phone");
	task2.setCharacterSize(25);
	task2.setOutlineColor(Color::Black);
	task2.setOutlineThickness(3);

	playerName.setCharacterSize(10);
	playerName.setFillColor(Color::White);
	playerName.setOutlineColor(Color::Black);
	playerName.setOutlineThickness(1.0);
	playerName.setLetterSpacing(4);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	phoneSprite.setTexture(phoneTexture);
	phoneSprite.setPosition(305, 370);

	broomSprite.setTexture(broomTexture);
	broomSprite.setPosition(465, 200);
	broomSprite.setScale(1.75f, 1.75f);
	broomAnimSprite.setTexture(broomAnimTexture);
	broomAnimSprite.setPosition(465, 200);
	broomAnimSprite.setScale(1.75f, 1.75f);

	ghost1Sprite.setTexture(ghost1Texture);
	ghost1Sprite.setPosition(700, 260);
	ghost1Sprite.setScale(1.7f, 1.7f);
	ghost2Sprite.setTexture(ghost1Texture);
	ghost2Sprite.setPosition(520, 460);
	ghost2Sprite.setScale(1.7f, 1.7f);

	playerSprite.setPosition(530, 275);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 96, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	arrowTexture.loadFromFile("sprites\\ui\\guide-arrow.png");
	arrowSprite.setTexture(arrowTexture);
	switchTimeArrow = 0.2f;
	arrowRect.width = arrowTexture.getSize().x / 4;
	arrowRect.height = arrowTexture.getSize().y / 1;
	currentImageArrow.x = 0;
	arrowSprite.setPosition(297, 280);

	ghost2Border.setFillColor(Color::Green);
	ghost2Border.setSize(Vector2f(500, 200));
	ghost2Border.setPosition(500, 380);

	projectile.setSize(Vector2f(5.0f, 2.0f));
	projectile.setFillColor(Color::Yellow);



	broomItemSprite.setTexture(broomItemTexture);
	broomItemSprite.setOrigin(broomItemTexture.getSize().x / 2.0f, broomItemTexture.getSize().y / 2.0f);
	broomItemSprite.setScale(1.75f, 1.75f);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	/*ghost1Sprite.setTextureRect(ghost1Rect);
	ghost2Sprite.setTextureRect(ghost1Rect);*/
	/*enemies.resize(100);
	enemies.push_back(ghost1Sprite);
	enemies.push_back(ghost2Sprite);*/

	float rectAlpha = 0.0f;
	rectangles.push_back(Rectangle(269, 162, 1000, 30, rectAlpha));
	rectangles.push_back(Rectangle(269, 176, 125, 54, rectAlpha));
	rectangles.push_back(Rectangle(269, 176, 10, 400, rectAlpha));
	rectangles.push_back(Rectangle(533, 176, 653, 54, rectAlpha));
	rectangles.push_back(Rectangle(737, 318, -653, 118, rectAlpha));
	rectangles.push_back(Rectangle(737, 526, -653, 118, rectAlpha));
	rectangles.push_back(Rectangle(820, 269, 20, -133, rectAlpha));
	rectangles.push_back(Rectangle(843, 269, 20, 503, rectAlpha));
	rectangles.push_back(Rectangle(733, 586, 100, 503, rectAlpha));

	dialogue = true;

	updateTextPos();

}

void SkylabRoomNight::handleInput() {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::R)) {
		itemIndex++;
		switchItem();
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

	if (Keyboard::isKeyPressed(Keyboard::T)) {
		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f worldPos = window.mapPixelToCoords(mousePos);
		cout << "Mouse Coordinates (Window): " << worldPos.x << ", " << worldPos.y << endl;
	}

	// 750 850 560 580
	if (playerSprite.getPosition().x <= 850 && playerSprite.getPosition().x >= 750 && playerSprite.getPosition().y <= 600 && playerSprite.getPosition().y >= 550) {
		showExitText = true;
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			goingSkylab = true;
		}
	}
	else {
		showExitText = false;
	}

	if (playerSprite.getPosition().x <= 350 && playerSprite.getPosition().x >= 280 && playerSprite.getPosition().y <= 300 && playerSprite.getPosition().y >= 250 && showPhoneTask) {
		showGoHome = true;
		showPhoneTask = false;
		showPhone = false;
		animBroom = true;
		showGhost1 = true;
		showGhost2 = true;
		//spawnEnemies = true;
		dialogue2 = true;
		nightBGM = false;
		windSFX.pause();
		windSFX.play();
	}

	if (playerSprite.getPosition().x >= 450 && playerSprite.getPosition().x <= 550 && playerSprite.getPosition().y >= 150 && playerSprite.getPosition().y <= 260 && animBroom) {
		showPickupText = true;
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			showBroom = false;
			broomPicked = true;
			animBroom = false;
			pickupSFX.pause();
			pickupSFX.play();
		}
	}
	else {
		showPickupText = false;
	}

	if (broomPicked) {
		showPickupText = false;
		showTutorText = true;
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
}

void SkylabRoomNight::itemText() {
	//cout << "show text\n";
	pickupItemText.setCharacterSize(20);
	pickupItemText.setFillColor(Color::White);
	pickupItemText.setString("Press E to pick up items");
	pickupItemText.setOutlineColor(Color::Black);
	pickupItemText.setOutlineThickness(2);
	pickupItemText.setPosition(750, 300);
	window.setView(window.getDefaultView());
	window.draw(pickupItemText);
}

void SkylabRoomNight::showTutor() {
	//cout << "show text\n";
	tutorText.setCharacterSize(20);
	tutorText.setFillColor(Color::White);
	tutorText.setString("Use your mouse to aim.\nPress space bar or left click to attack");
	tutorText.setOutlineColor(Color::Black);
	tutorText.setOutlineThickness(2);
	tutorText.setPosition(800, 200);
	window.setView(window.getDefaultView());
	window.draw(tutorText);
}

void SkylabRoomNight::updateTextPos() {

	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1100, camera.getCenter().y - window.getSize().y / 1.80f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 900, camera.getCenter().y - window.getSize().y / 1.80f);
}

void SkylabRoomNight::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerpp(currentCenter, targetCenter);
	camera.setCenter(newCenter);
}

void SkylabRoomNight::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	playerName.setString(pName);
	playerName.setPosition(playerSprite.getPosition().x - 5 - playerName.getLocalBounds().width / 2, playerSprite.getPosition().y - 50);

	if (playerSprite.getPosition().x > ghost2Border.getPosition().x && playerSprite.getPosition().x < ghost2Border.getPosition().x + ghost2Border.getSize().x &&
		playerSprite.getPosition().y > ghost2Border.getPosition().y && playerSprite.getPosition().y < ghost2Border.getPosition().y + ghost2Border.getSize().y && showGhost2) {
		isChasing = true;
	}
	else {
		isChasing = false;
	}

	if (isChasing) {

		float angle = atan2(playerSprite.getPosition().y - ghost2Sprite.getPosition().y, playerSprite.getPosition().x - ghost2Sprite.getPosition().x);
		float x = 1.5 * cos(angle);
		float y = 1.5 * sin(angle);
		ghost2Sprite.move(x, y);
	}
	
	broomToMouse = mousePos - broomItemSprite.getPosition();
	float angle = atan2(broomToMouse.y, broomToMouse.x) * 180.0f / 3.14159265f;
	broomItemSprite.setRotation(angle);

	/*size_t i = 0;
	while (i < enemies.size()) {
		if (projectileShot && projectile.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
			enemies.erase(enemies.begin() + i);
			projectiles.clear();
			projectile.setPosition(1000, 1000);
		}
		else {
			i++;
		}
	}*/

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

void SkylabRoomNight::animUpdate(float dt) {
	currentImageArrow.y = 0;
	currentImageBroom.y = 0;
	currentImageGhost1.y = 0;
	totalTime += dt;

	if (totalTime >= switchTimeArrow || totalTime >= switchTimeBroom || totalTime >= switchTimeGhost1) {
		totalTime -= switchTimeArrow;
		totalTime -= switchTimeBroom;
		totalTime -= switchTimeGhost1;
		currentImageArrow.x++;
		currentImageBroom.x++;
		currentImageGhost1.x++;

		if (currentImageArrow.x >= 4) {
			currentImageArrow.x = 0;
		}

		if (currentImageBroom.x >= 4) {
			currentImageBroom.x = 0;
		}

		if (currentImageGhost1.x >= 3) {
			currentImageGhost1.x = 0;
		}
	}

	arrowRect.left = currentImageArrow.x * arrowRect.width;
	arrowRect.top = currentImageArrow.y * arrowRect.height;
	broomRect.left = currentImageBroom.x * broomRect.width;
	broomRect.top = currentImageBroom.y * broomRect.height;
	ghost1Rect.left = currentImageGhost1.x * ghost1Rect.width;
	ghost1Rect.top = currentImageGhost1.y * ghost1Rect.height;
}

bool SkylabRoomNight::gotoSkylab() {
	return goingSkylab;
}

void SkylabRoomNight::goingSkylabFalse() {
	goingSkylab = false;
}

void SkylabRoomNight::exitText() {
	exitDoorText.setCharacterSize(20);
	exitDoorText.setFillColor(Color::White);
	exitDoorText.setString("Press E to exit skylab room");
	exitDoorText.setOutlineColor(Color::Black);
	exitDoorText.setOutlineThickness(2);
	window.setView(window.getDefaultView());
	exitDoorText.setPosition(750, 300);
	window.draw(exitDoorText);
}

void SkylabRoomNight::goHomeFalse(){
	showGoHome = false;
	showPhoneTask = true;
}

void SkylabRoomNight::goHome() {
	window.draw(task1);
}

void SkylabRoomNight::phoneTask() {
	window.draw(task2);
	window.setView(camera);
	window.draw(arrowSprite);
	showPhone = true;
}

bool SkylabRoomNight::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void SkylabRoomNight::handleCollision(const Rectangle& rect) {
	charBounds = playerSprite.getGlobalBounds();
	//FloatRect itemBounds = broomItemSprite.getGlobalBounds();
	rectBounds = rect.shape.getGlobalBounds();

	intersection;
	//if (charBounds.intersects(rectBounds, intersection) || itemBounds.intersects(rectBounds, intersection)) {
	if (charBounds.intersects(rectBounds, intersection)) {
		if (intersection.width < intersection.height) {

			//if (charBounds.left < rectBounds.left || itemBounds.left < rectBounds.left) {
			if (charBounds.left < rectBounds.left) {
				playerSprite.setPosition(playerSprite.getPosition().x - intersection.width, playerSprite.getPosition().y);
				//broomItemSprite.setPosition(broomItemSprite.getPosition().x - intersection.width, broomItemSprite.getPosition().y);
			}
			else {
				playerSprite.setPosition(playerSprite.getPosition().x + intersection.width, playerSprite.getPosition().y);
				//broomItemSprite.setPosition(broomItemSprite.getPosition().x + intersection.width, broomItemSprite.getPosition().y);
			}
		}
		else {
			//if (charBounds.top < rectBounds.top || itemBounds.top < rectBounds.top) {
			if (charBounds.top < rectBounds.top) {
				playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y - intersection.height);
				//broomItemSprite.setPosition(broomItemSprite.getPosition().x, broomItemSprite.getPosition().y - intersection.height);
			}
			else {
				playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + intersection.height);
				//broomItemSprite.setPosition(broomItemSprite.getPosition().x, broomItemSprite.getPosition().y + intersection.height);
			}
		}
	}
}

bool SkylabRoomNight::gameStart() {
	return broomPicked;
}

void SkylabRoomNight::showDialogueBox() {
	dialogueBox.initDialogue("You fell asleep.");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		dialogue = false;
		dialogueBox.reset();
	}
}

void SkylabRoomNight::showDialogue2() {
	dialogueBox.initDialogue("You feel something strange.");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		dialogue2 = false;
		dialogueBox.reset();
		nightBGM = true;
	}
}

//void SkylabRoomNight::updateEnemies() {
//	if (playerSprite.getPosition().x > ghost2Border.getPosition().x && playerSprite.getPosition().x < ghost2Border.getPosition().x + ghost2Border.getSize().x &&
//		playerSprite.getPosition().y > ghost2Border.getPosition().y && playerSprite.getPosition().y < ghost2Border.getPosition().y + ghost2Border.getSize().y && showGhost2) {
//		isChasing = true;
//	}
//	else {
//		isChasing = false;
//	}
//
//	if (isChasing) {
//
//		float angle = atan2(playerSprite.getPosition().y - enemies[1].getPosition().y, playerSprite.getPosition().x - enemies[1].getPosition().x);
//		float x = 1.5 * cos(angle);
//		float y = 1.5 * sin(angle);
//		enemies[1].move(x, y);
//	}
//
//	size_t i = 0;
//	while (i < enemies.size()) {
//		if (projectileShot && projectile.getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
//			enemies.erase(enemies.begin() + i);
//			projectiles.clear();
//			projectile.setPosition(1000, 1000);
//		}
//		else {
//			i++;
//		}
//	}
//
//	/*enemies.push_back(ghost1Sprite);
//	enemies.push_back(ghost2Sprite);*/
//
//	for (size_t i = 0; i < enemies.size(); ++i) {
//		window.draw(enemies[i]);
//	}
//}

bool SkylabRoomNight::nightBGMFalse() {
	return nightBGM;
}

void SkylabRoomNight::render() {

	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(0.65f, 0.65f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);

	if (showBroom) {
		window.draw(broomSprite);
	}

	ghost1Sprite.setTextureRect(ghost1Rect);
	ghost2Sprite.setTextureRect(ghost1Rect);
	broomAnimSprite.setTextureRect(broomRect);

	if (animBroom) {
		window.draw(broomAnimSprite);
		showBroom = false;
	}

	if (showGhost1) {
		window.draw(ghost1Sprite);
	}

	if (showGhost2) {
		window.draw(ghost2Sprite);
	}

	/*if (spawnEnemies) {
		updateEnemies();
	}*/

	arrowSprite.setTextureRect(arrowRect);

	if (showPhone) {
		window.draw(phoneSprite);
	}

	if (broomPicked) {
	window.draw(broomItemSprite);
	}

	window.draw(playerSprite);
	window.draw(projectile);
	window.draw(playerName);

	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);

	if (showGoHome) {
		goHome();
	}

	if (showPhoneTask) {
		phoneTask();
	}

	if (showExitText) {
		exitText();
	}

	if (showPickupText) {
		itemText();
	}

	if (showTutorText) {
		showTutor();
	}

	if (dialogue) {
		showDialogueBox();
	}

	if (dialogue2) {
		showDialogue2();
	}

	if (!fadeTrans.isFadedOut()) {
		fadeTrans.updateOut(dt);
		fadeTrans.renderOut();
	}
}