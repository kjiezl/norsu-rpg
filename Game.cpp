#include "Game.h"
#include "PauseMenu.h"
#include "PlayerName.h"
#include "CircTrans.h"
#include "CircleTransition.h"
#include "DialogueBox.h"
#include "NPC.h"
#include "Skylab.h"
#include "Inventory.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;  
using namespace std;


Game::Game(RenderWindow& window, const string& pName) : window(window),
goingMainGate(false), fadeTrans(window), pName(pName), pauseMenu(window),
gamePaused(false), circTrans(window), npc(window), dialogueBox(window),
dampingFactor(0.3f), isChasing(false), dialogueBoolCat(false), dPressed(true),
aPressed(false), projectileShot(false), goingSkylab(false), day2(false), 
dialogueBoolCJ(false), hwComplete(false), cjCollected(false), hide2(false),
showCJ(false), showTask4(false), inv(window), hide1(false), hide3(false), 
hide4(false){
	//cout << endl << pName << endl;

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	task2.setFont(font);
	task4.setFont(font);
	collectScraps.setFont(font);
	playerName.setString("");
	playerName.setFont(font); 
	roomTexture.loadFromFile("sprites\\maps\\cas-3rd.png");
	texture.loadFromFile("sprites\\characters\\elrico.png");
	vignetteTexture.loadFromFile("sprites\\ui\\vignette1.png");
	roomScale = Vector2f(1.6f, 1.6f);
	playerScale = Vector2f(1.75f, 1.75f);

	hwCountText.setFont(font);
	hwCount = 0;
	
	totalTime = 0.0f;
	currentImage.x = 0;

	animTexture.loadFromFile("sprites\\enemies\\ghosts.png");
	borderTexture.loadFromFile("sprites\\ui\\border.png");
	animSprite.setTexture(animTexture);
	animRect.width = animTexture.getSize().x / 3;
	animRect.height = animTexture.getSize().y / 3;
	switchTime = 0.3f;


	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	vignetteScale = Vector2f(0.34f, 0.34f);

	topLeft.setTexture(borderTexture);
	topLeft.setScale(Vector2f(0.1f, 0.1f));
	bottomLeft.setTexture(borderTexture);
	bottomLeft.setScale(Vector2f(0.1f, 0.1f));
	topRight.setTexture(borderTexture);
	topRight.setScale(Vector2f(0.1f, 0.1f));
	bottomRight.setTexture(borderTexture);
	bottomRight.setScale(Vector2f(0.1f, 0.1f));

	borderShape.setFillColor(Color(0, 0, 0, 50));
	borderShape.setSize(Vector2f(425, 205));

	projectile.setRadius(4.0f);
	projectile.setFillColor(Color::Yellow);

	broomTexture.loadFromFile("sprites\\items\\broom.png");
	broomSprite.setTexture(broomTexture);
	broomSprite.setOrigin(broomTexture.getSize().x / 2.0f, broomTexture.getSize().y / 2.0f);

	item1Tex.loadFromFile("sprites\\items\\match.png");
	item2Tex.loadFromFile("sprites\\items\\ice.png");
	item3Tex.loadFromFile("sprites\\items\\metal.png");

	match1.setTexture(item1Tex);
	ice1.setTexture(item2Tex);
	metal1.setTexture(item3Tex);
	metal2.setTexture(item3Tex);

	paperBuffer.loadFromFile("sprites\\sfx\\paper1.ogg");
	paperSFX.setBuffer(paperBuffer);
	itemBuffer.loadFromFile("sprites\\sfx\\item-plop.ogg");
	itemSFX.setBuffer(itemBuffer);

	initPlayer();
}

Vector2f lerp(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

Game::~Game() {

}

void Game::initPlayer() {
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

	task2.setString("!\tCollect the assignments from your classmates");
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

	hwCountText.setCharacterSize(20);
	hwCountText.setOutlineColor(Color::Black);
	hwCountText.setOutlineThickness(3);

	playerName.setCharacterSize(10);
	playerName.setFillColor(Color::White);
	playerName.setOutlineColor(Color::Black);
	playerName.setOutlineThickness(1.0);
	playerName.setLetterSpacing(4);

	room.setTexture(roomTexture);
	room.setPosition(250, 0);

	vignette.setTexture(vignetteTexture);

	elrico.setPosition(1800, 150);
	elrico.setTexture(texture);
	elrico.setTextureRect(IntRect(0, 64, 32, 32));

	ghostPos.x = 1500;
	ghostPos.y = 200;

	animSprite.setPosition(ghostPos);
	xVeloGhost = 3;
	yVeloGhost = 3;

	playerBounds = elrico.getLocalBounds();
	elrico.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	topLeft.setPosition(1600, 50);
	topRight.setPosition(1950, 0);
	//topLeft.setPosition(1300, 100); //for border
	bottomLeft.setPosition(1300, 280);
	//topRight.setPosition(1700, 100); // for border
	bottomRight.setPosition(1700, 280);

	borderShape.setPosition(1300, 100);

	broomSprite.setPosition(elrico.getPosition().x + 4, elrico.getPosition().y + 7.5);

	arrowTexture.loadFromFile("sprites\\ui\\guide-arrow.png");
	arrowSprite.setTexture(arrowTexture);
	arrowSprite.setTexture(arrowTexture);
	switchTime2 = 0.2f;
	arrowRect.width = arrowTexture.getSize().x / 4;
	arrowRect.height = arrowTexture.getSize().y / 1;
	currentImageArrow.x = 0;
	arrowSprite.setPosition(285, 450);
	arrowSprite2.setPosition(3450, 450);
	
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
	rectangles.push_back(Rectangle(3391, 390, -25, 50, rectAlpha));

	rectangles.push_back(Rectangle(363, 390, 3028, 20, rectAlpha));
	rectangles.push_back(Rectangle(3283, -20, 128, -20, rectAlpha));

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 3000 + 250);
		float y = static_cast<float>(rand() % 250 + 145);
		match1.setPosition(Vector2f(x, y));
		item1.push_back(match1);
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 3000 + 250);
		float y = static_cast<float>(rand() % 250 + 145);
		ice1.setPosition(Vector2f(x, y));
		item2.push_back(ice1);
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 3000 + 250);
		float y = static_cast<float>(rand() % 250 + 145);
		metal1.setPosition(Vector2f(x, y));
		item3.push_back(metal1);
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 3000 + 250);
		float y = static_cast<float>(rand() % 250 + 145);
		metal2.setPosition(Vector2f(x, y));
	}

	updateTextPos();

}

void Game::handleInput() {
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
		broomSprite.setPosition(elrico.getPosition().x + 4, elrico.getPosition().y + 7.5);
		int pos = 0;
		pos = (int)elrico.getPosition().x / 35 % 4;
		pos = pos * 32;
		elrico.setTextureRect(IntRect(pos, 0, 32, 32));
		elrico.move(moveSpeed, 0);
		broomSprite.move(moveSpeed, 0);
	}
	else {
		if (dPressed) {
			elrico.setTextureRect(IntRect(0, 64, 32, 32));
		}
		if (aPressed) {
			elrico.setTextureRect(IntRect(0, 96, 32, 32));
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		aPressed = true;
		dPressed = false;
		broomSprite.setPosition(elrico.getPosition().x - 4, elrico.getPosition().y + 7.5);
		int pos = 0;
		pos = (int)elrico.getPosition().x / 35 % 4;
		pos = pos * 32;
		elrico.setTextureRect(IntRect(pos, 32, 32, 32));
		elrico.move(-moveSpeed, 0);
		broomSprite.move(-moveSpeed, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		int pos = 0;
		pos = (int)elrico.getPosition().y / 35 % 4;
		pos = pos * 32;
		if (dPressed) {
			elrico.setTextureRect(IntRect(pos, 0, 32, 32));
		}
		if (aPressed) {
			elrico.setTextureRect(IntRect(pos, 32, 32, 32));
		}
		elrico.move(0, moveSpeed);
		broomSprite.move(0, moveSpeed);
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		int pos = 0;
		pos = (int)elrico.getPosition().y / 35 % 4;
		pos = pos * 32;
		if (dPressed) {
			elrico.setTextureRect(IntRect(pos, 0, 32, 32));
		}
		if (aPressed) {
			elrico.setTextureRect(IntRect(pos, 32, 32, 32));
		}
		elrico.move(0, -moveSpeed);
		broomSprite.move(0, -moveSpeed);
	}

	Vector2f playerPos = elrico.getPosition();
	Vector2f catPos = npc.catPos();

	float distance = sqrt((playerPos.x - catPos.x) * (playerPos.x - catPos.x) + (playerPos.y - catPos.y) * (playerPos.y - catPos.y));
	
	if (distance <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolCat = true;
	}

	if (distance >= 90.0f && dialogueBoolCat) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolCat = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && !projectileShot || Mouse::isButtonPressed(Mouse::Left) && !projectileShot) {
		//cout << "projectile shot false\n";
		projectileDirection = mousePos - broomSprite.getPosition();
		float length = sqrt(projectileDirection.x * projectileDirection.x + projectileDirection.y * projectileDirection.y);
		projectileDirection /= length;
		if (dPressed) {
			projectile.setPosition(broomSprite.getPosition().x + 10.0f, broomSprite.getPosition().y - 5.0f);
		}
		if (aPressed) {
			projectile.setPosition(broomSprite.getPosition().x - 20.0f, broomSprite.getPosition().y - 5.0f);
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
			projectileShot = false;
			cooldown.restart();
			projectile.setPosition(9000, 9000);
		}
	}

	if (elrico.getPosition().x <= 355 && elrico.getPosition().x >= 250 && elrico.getPosition().y <= 500 && elrico.getPosition().y >= 460) {
		goingSkylab = true;
	}

	//1600, 50);1950, 0);
	if (elrico.getPosition().x <= 1950 && elrico.getPosition().x >= 1600 && elrico.getPosition().y <= 50 && elrico.getPosition().y >= 0) {
		goingMainGate = true;
	}
	
	//3450, 450
	if (elrico.getPosition().x <= 3550 && elrico.getPosition().x >= 3350 && elrico.getPosition().y <= 500 && elrico.getPosition().y >= 440) {
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

	Vector2f cjPos = npc.cjPos();

	float distance1 = sqrt((playerPos.x - cjPos.x) * (playerPos.x - cjPos.x) + (playerPos.y - cjPos.y) * (playerPos.y - cjPos.y));
	
	if (distance1 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E) && showCJ) {
		dialogueBoolCJ = true;
	}

	if (distance1 >= 90.0f && dialogueBoolCJ) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolCJ = false;
	}

	float item1Distance = inv.calcuDistance(elrico.getPosition(), match1.getPosition());
	if (item1Distance < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem1();
		match1.setPosition(9999, 9999);
		hide1 = true;
	}

	float item2Distance = inv.calcuDistance(elrico.getPosition(), ice1.getPosition());
	if (item2Distance < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem2();
		ice1.setPosition(9999, 9999);
		hide2 = true;
	}

	float item3Distance1 = inv.calcuDistance(elrico.getPosition(), metal1.getPosition());
	if (item3Distance1 < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem3();
		metal1.setPosition(9999, 9999);
		hide3 = true;
	}

	float item3Distance2 = inv.calcuDistance(elrico.getPosition(), metal2.getPosition());
	if (item3Distance2 < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem3();
		metal2.setPosition(9999, 9999);
		hide4 = true;
	}
}

void Game::updateTextPos() {

	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 850, camera.getCenter().y - window.getSize().y / 1.80f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 700, camera.getCenter().y - window.getSize().y / 1.80f);
	hwCountText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1100, camera.getCenter().y - window.getSize().y / 2.50f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 800, camera.getCenter().y - window.getSize().y / 1.80f);
	collectScraps.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.60f);
}

void Game::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - elrico.getPosition();
	targetCenter = elrico.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void Game::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(elrico.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	playerName.setString(pName);
	playerName.setPosition(elrico.getPosition().x - 5 - playerName.getLocalBounds().width / 2, elrico.getPosition().y - 50);

	if (elrico.getPosition().x > borderShape.getPosition().x && elrico.getPosition().x < borderShape.getPosition().x + borderShape.getSize().x &&
		elrico.getPosition().y > borderShape.getPosition().y && elrico.getPosition().y < borderShape.getPosition().y + borderShape.getSize().y) {
		isChasing = true;
	}
	else {
		isChasing = false;
	}

	broomToMouse = mousePos - broomSprite.getPosition();
	float angle = atan2(broomToMouse.y, broomToMouse.x) * 180.0f / 3.14159265f;
	broomSprite.setRotation(angle);

	if (hwCount <= 5 && day2 && showCJ) {
		hwCountText.setString("Collected: " + to_string(hwCount) + " / 5");
	}
}

void Game::catDialogueBox() {
	dialogueBox.initDialogue("Mr. Ming: \n\tmeow~ purr~ hiss~");
	dialogueBox.update();
	dialogueBox.render();

	if (dialogueBox.isTextComplete()) {
		if(Keyboard::isKeyPressed(Keyboard::Enter)){
			dialogueBox.isEnterPressed(true);
			dialogueBoolCat = false;
		}
	}
}

void Game::animUpdate(float dt) {
	currentImage.y = 1;
	currentImageArrow.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime || totalTime >= switchTime2) {
		totalTime -= switchTime;
		totalTime -= switchTime2;
		currentImage.x++;
		currentImageArrow.x++;
		if (currentImage.x >= 3) {
			currentImage.x = 0;
		}

		if (currentImageArrow.x >= 4) {
			currentImageArrow.x = 0;
		}
	}

	animRect.left = currentImage.x * animRect.width;
	animRect.top = currentImage.y * animRect.height;
	arrowRect.left = currentImageArrow.x * arrowRect.width;
	arrowRect.top = currentImageArrow.y * arrowRect.height;

	if (isChasing) {
		//cout << "is chasing true" << endl;

		xVeloGhost = abs(xVeloGhost);
		
		float angle = atan2(elrico.getPosition().y - animSprite.getPosition().y, elrico.getPosition().x - animSprite.getPosition().x);
		float x = xVeloGhost * cos(angle);
		float y = yVeloGhost * sin(angle);
		animSprite.move(x, y);
	}
	else if(!isChasing) {
		animSprite.move(ghostPos);

		if (ghostPos.x < 1400 || ghostPos.x > 1600) {
			xVeloGhost *= -1;
		}

		ghostPos.x -= xVeloGhost;
		animSprite.setPosition(ghostPos);
	}
}

void Game::catUpdate(float dt) {
	npc.catUpdate(dt);
	npc.update();

	npc.animUpdate(dt);
	npc.update();
}

bool Game::gotoSkylab() {
	return goingSkylab;
}

void Game::playerPosFromSkylab() {
	elrico.setPosition(300, 400);
	broomSprite.setPosition(300, 400);
}

void Game::goingSkylabFalse() {
	goingSkylab = false;
}

bool Game::gotoMainGate() {
	return goingMainGate;
}

void Game::playerPosFromMainGate() {
	elrico.setPosition(1800, 150);
	broomSprite.setPosition(1800, 150);
}

void Game::goingMainGateFalse() {
	goingMainGate = false;
}

bool Game::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void Game::handleCollision(const Rectangle& rect) {
	charBounds = elrico.getGlobalBounds();
	rectBounds = rect.shape.getGlobalBounds();

	intersection;
	if (charBounds.intersects(rectBounds, intersection)) {
		if (intersection.width < intersection.height) {

			if (charBounds.left < rectBounds.left) {
				elrico.setPosition(elrico.getPosition().x - intersection.width, elrico.getPosition().y);
			}
			else {
				elrico.setPosition(elrico.getPosition().x + intersection.width, elrico.getPosition().y);
			}
		}
		else {
			if (charBounds.top < rectBounds.top) {
				elrico.setPosition(elrico.getPosition().x, elrico.getPosition().y - intersection.height);
			}
			else {
				elrico.setPosition(elrico.getPosition().x, elrico.getPosition().y + intersection.height);
			}
		}
	}
}

void Game::day2Start() {
	day2 = true;
	npc.day2Start();
	showCJ = true;
	elrico.setPosition(1800, 150);
	goingSkylab = false;
	goingMainGate = false;
}

void Game::cjDialogueBox() {
	if (!cjCollected) {
		paperSFX.pause();
		paperSFX.play();
		hwCount += 1;
		cjCollected = true;
	}
	dialogueBox.initDialogue("SIJEH: \n\tUgma lagi naa nakoy assignment... tuo lang nako gud");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowCJ();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolCJ = false;
			dialogueBox.reset();
		}
	}
}

bool Game::isCJCollected() {
	return cjCollected;
}

void Game::goingHM(bool papersPlaced) {
	if (papersPlaced) {
		showCJ = false;
		showTask4 = true;
	}
}

void Game::render() {

	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	room.setScale(roomScale);
	elrico.setScale(playerScale);
	broomSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(room);
	if (!day2) {
		npc.render();
	}
	if (day2 && showCJ) {
		npc.renderCJ();
	}
	window.draw(arrowSprite);
	window.draw(arrowSprite2);

	if (day2) {
		if (!hide1) {
			for (const auto& match1 : item1) {
				window.draw(match1);
			}
		}

		if (!hide2) {
			for (const auto& ice1 : item2) {
				window.draw(ice1);
			}
		}

		if (!hide3) {
			for (const auto& metal1 : item3) {
				window.draw(metal1);
			}
		}

		if (!hide4) {
			window.draw(metal2);
		}
	}

	//window.draw(broomSprite);
	window.draw(elrico);
	animSprite.setTextureRect(animRect);
	arrowSprite.setTextureRect(arrowRect);
	//arrowSprite2.setTextureRect(arrowRect);
	animSprite.setScale(1.75f, 1.75f);
	//window.draw(animSprite);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	//window.draw(topLeft); window.draw(bottomLeft); window.draw(topRight); window.draw(bottomRight);
	//window.draw(borderShape);
	//window.draw(topLeft);
	//window.draw(topRight);
	//window.draw(nightTint);
	window.draw(projectile);
	window.draw(playerName);
	window.setView(window.getDefaultView());

	if (day2) {
		inv.updateTextPos();
		inv.render();
		window.draw(collectScraps);
	}

	vignette.setScale(vignetteScale);
	//window.draw(vignette);
	window.draw(quitText);
	window.draw(pauseText);
	if (!day2) {
		window.draw(task1);
	}

	if(day2 && showCJ) {
		window.draw(task2);
		window.draw(hwCountText);
	}

	if (showTask4 && !showCJ && day2) {
		window.draw(task4);
	}

	if (dialogueBoolCat && !day2) {
		catDialogueBox();
	}

	if (dialogueBoolCJ) {
		cjDialogueBox();
	}

	/*if (pName == "elrico") {
		playerName.setString("elrico");
	}
	else {
		playerName.setString(pName);
	}*/

	/*if (!circTrans.isOutTransComplete()) {
		circTrans.update(dt);
		circTrans.render();
	}*/
}