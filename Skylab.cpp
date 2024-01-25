#include "Skylab.h"
#include "PauseMenu.h"
#include "PlayerName.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "Game.h"
#include "NPC.h"
#include "Inventory.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

Skylab::Skylab(RenderWindow& window, const string& pName) : window(window),
showEnterText(false), going3rdCAS(false), goingSkylabRoom(false), playerNameClass(window), 
pName(pName), pauseMenu(window), gamePaused(false), fadeTrans(window), dialogueBox(window), 
dampingFactor(0.3f), dPressed(true), aPressed(false), cjCollected(false), 
desCollected(false), kwehCollected(false), kitCollected(false), ameruCollected(false), 
npc(window), day2(false), dialogueBoolDes(false), dialogueBoolKweh(false), dialogueBoolKit(false), 
dialogueBoolAmeru(false), showNPCs(false), showCJ(false), dialogueBoolCJ(false), showTask4(false),
hide1(false), hide2(false), inv(window), hide3(false), hide4(false), hide5(false) {
	//cout << endl << pName << endl;

	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	task2.setFont(font);
	task3.setFont(font);
	task4.setFont(font);
	collectScraps.setFont(font);
	playerName.setString("");
	playerName.setFont(font);
	roomTexture.loadFromFile("sprites\\maps\\skylab.png");
	texture.loadFromFile("sprites\\characters\\elrico.png");
	roomScale = Vector2f(1.6f, 1.6f);
	playerScale = Vector2f(1.75f, 1.75f);

	totalTime = 0.0f;

	hwCountText.setFont(font);
	hwCount = 0;

	nightTint.setFillColor(Color(20, 15, 50, 140));
	nightTint.setSize(Vector2f(window.getSize().x, window.getSize().y));

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	enterDoorText.setFont(font);

	item1Tex.loadFromFile("sprites\\items\\match.png");
	item2Tex.loadFromFile("sprites\\items\\ice.png");
	item3Tex.loadFromFile("sprites\\items\\metal.png");

	match1.setTexture(item1Tex);
	ice1.setTexture(item2Tex);
	metal1.setTexture(item3Tex);
	metal2.setTexture(item3Tex);
	metal3.setTexture(item3Tex);

	paper1Buffer.loadFromFile("sprites\\sfx\\paper1.ogg");
	paper2Buffer.loadFromFile("sprites\\sfx\\paper2.ogg");

	paper1SFX.setBuffer(paper1Buffer);
	paper2SFX.setBuffer(paper2Buffer);

	itemBuffer.loadFromFile("sprites\\sfx\\item-plop.ogg");
	itemSFX.setBuffer(itemBuffer);

	initPlayer();
}

Vector2f lerp(const Vector2f& start, const Vector2f& end) {
	float t = 0.3f;
	return start + t * (end - start);
}

Skylab::~Skylab() {

}

void Skylab::isCJCollected(bool isCollected) {
	if (isCollected) {
		cjCollected = true;
	}

	if (cjCollected && hwCount == 0) {
		hwCount += 1;
	}
}

void Skylab::initPlayer() {
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

	task3.setString("!\tGo to Skylab room and pass all the papers");
	task3.setCharacterSize(25);
	task3.setOutlineColor(Color::Black);
	task3.setOutlineThickness(3);

	task4.setString("!\tGo to your next class in HM building");
	task4.setCharacterSize(25);
	task4.setOutlineColor(Color::Black);
	task4.setOutlineThickness(3);

	hwCountText.setCharacterSize(20);
	hwCountText.setOutlineColor(Color::Black);
	hwCountText.setOutlineThickness(3);

	collectScraps.setString("!\tPress E to collect scraps for crafting");
	collectScraps.setCharacterSize(20);
	collectScraps.setOutlineColor(Color::Black);
	collectScraps.setOutlineThickness(3);

	playerName.setCharacterSize(10);
	playerName.setFillColor(Color::White);
	playerName.setOutlineColor(Color::Black);
	playerName.setOutlineThickness(1.0);
	playerName.setLetterSpacing(4);

	room.setTexture(roomTexture);
	room.setPosition(250, 0);

	elrico.setPosition(450, 350);
	elrico.setTexture(texture);
	elrico.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = elrico.getLocalBounds();
	elrico.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	arrowTexture.loadFromFile("sprites\\ui\\guide-arrow.png");
	arrowSprite.setTexture(arrowTexture);
	switchTimeArrow = 0.2f;
	arrowRect.width = arrowTexture.getSize().x / 4;
	arrowRect.height = arrowTexture.getSize().y / 1;
	currentImageArrow.x = 0;
	arrowSprite.setPosition(1802, 150);

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

	rectangles.push_back(Rectangle(3300, -60, 100, 40, rectAlpha));
	
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
		float y = static_cast<float>(rand() % 200 + 145);
		metal1.setPosition(Vector2f(x, y));
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 2000 + 250);
		float y = static_cast<float>(rand() % 200 + 145);
		metal2.setPosition(Vector2f(x, y));
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 1000 + 250);
		float y = static_cast<float>(rand() % 200 + 145);
		metal3.setPosition(Vector2f(x, y));
	}

	updateTextPos();

}

void Skylab::handleInput() {
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
		pos = (int)elrico.getPosition().x / 35 % 4;
		pos = pos * 32;
		elrico.setTextureRect(IntRect(pos, 0, 32, 32));
		elrico.move(moveSpeed, 0);
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
		int pos = 0;
		pos = (int)elrico.getPosition().x / 35 % 4;
		pos = pos * 32;
		elrico.setTextureRect(IntRect(pos, 32, 32, 32));
		elrico.move(-moveSpeed, 0);
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
	}

	window.setView(camera);
	if (Keyboard::isKeyPressed(Keyboard::T)) {
		Vector2i mousePos = Mouse::getPosition(window);
		Vector2f worldPos = window.mapPixelToCoords(mousePos);
		cout << "Mouse Coordinates (Window): " << worldPos.x << ", " << worldPos.y << endl;
	}

	if (elrico.getPosition().x <= 475 && elrico.getPosition().x >= 370 && elrico.getPosition().y <= 430 && elrico.getPosition().y >= 410) {
		going3rdCAS = true;
	}

	if (elrico.getPosition().x >= 1750 && elrico.getPosition().x <= 1850 && elrico.getPosition().y >= 100 && elrico.getPosition().y <= 180) {
		showEnterText = true;
		
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			goingSkylabRoom = true;
		}
	}
	else {
		showEnterText = false;
	}

	for (auto& rect : rectangles) {
		handleCollision(rect);
	}

	Vector2f playerPos = elrico.getPosition();
	Vector2f kwehPos = npc.kwehPos();
	Vector2f desPos = npc.desPos();
	Vector2f ameruPos = npc.ameruPos();
	Vector2f kitPos = npc.kitPos();

	float distance1 = sqrt((playerPos.x - kwehPos.x) * (playerPos.x - kwehPos.x) + (playerPos.y - kwehPos.y) * (playerPos.y - kwehPos.y));
	float distance2 = sqrt((playerPos.x - desPos.x) * (playerPos.x - desPos.x) + (playerPos.y - desPos.y) * (playerPos.y - desPos.y));
	float distance3 = sqrt((playerPos.x - kitPos.x) * (playerPos.x - kitPos.x) + (playerPos.y - kitPos.y) * (playerPos.y - kitPos.y));
	float distance4 = sqrt((playerPos.x - ameruPos.x) * (playerPos.x - ameruPos.x) + (playerPos.y - ameruPos.y) * (playerPos.y - ameruPos.y));
	
	if (distance1 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E) && showNPCs) {
		dialogueBoolKweh = true;
	}

	if (distance2 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E) && showNPCs) {
		dialogueBoolDes = true;
	}

	if (distance3 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E) && showNPCs) {
		dialogueBoolKit = true;
	}

	if (distance4 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E) && showNPCs) {
		dialogueBoolAmeru = true;
	}

	if (distance1 >= 90.0f && dialogueBoolKweh) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolKweh = false;
	}

	if (distance2 >= 90.0f && dialogueBoolDes) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolDes = false;
	}

	if (distance3 >= 90.0f && dialogueBoolKit) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolKit = false;
	}

	if (distance4 >= 90.0f && dialogueBoolAmeru) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolAmeru = false;
	}

	Vector2f cjPos = npc.cjPos();

	float distance5 = sqrt((playerPos.x - cjPos.x) * (playerPos.x - cjPos.x) + (playerPos.y - cjPos.y) * (playerPos.y - cjPos.y));

	if (distance5 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E) && showCJ) {
		dialogueBoolCJ = true;
	}

	if (distance5 >= 90.0f && dialogueBoolCJ) {
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

	float item3Distance3 = inv.calcuDistance(elrico.getPosition(), metal3.getPosition());
	if (item3Distance3 < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem3();
		metal3.setPosition(9999, 9999);
		hide5 = true;
	}
}

void Skylab::updateTextPos() {

	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 850, camera.getCenter().y - window.getSize().y / 1.80f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 700, camera.getCenter().y - window.getSize().y / 1.80f);
	hwCountText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1100, camera.getCenter().y - window.getSize().y / 2.50f);
	task3.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 720, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 800, camera.getCenter().y - window.getSize().y / 1.80f);
	collectScraps.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.60f);
}

void Skylab::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - elrico.getPosition();
	targetCenter = elrico.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp(currentCenter, targetCenter);
	camera.setCenter(newCenter);
}

void Skylab::update() {
	//cout << pName << endl;
	nightTint.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(elrico.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	playerName.setString(pName);
	//playerName.setString(playerNameClass.getPlayerName());
	playerName.setPosition(elrico.getPosition().x - 5 - playerName.getLocalBounds().width / 2, elrico.getPosition().y - 50);

	if (hwCount <= 5 && day2 && !showTask3) {
		hwCountText.setString("Collected: " + to_string(hwCount) + " / 5");
	}

	if (hwCount >= 5 && day2 && !showTask3) {
		hwCountText.setString("Collected: 5 / 5");
		hwCountText.setFillColor(Color::Green);
		showTask3 = true;
	}
}

void Skylab::animUpdate(float dt) {
	currentImageArrow.y = 0;
	totalTime += dt;

	if (totalTime >= switchTimeArrow) {
		totalTime -= switchTimeArrow;
		currentImageArrow.x++;

		if (currentImageArrow.x >= 4) {
			currentImageArrow.x = 0;
		}
	}

	arrowRect.left = currentImageArrow.x * arrowRect.width;
	arrowRect.top = currentImageArrow.y * arrowRect.height;

	npc.animUpdate(dt);
	npc.update();
}

bool Skylab::goto3rdCAS() {
	return going3rdCAS;
}

void Skylab::playerPosFrom3rdCAS() {
	elrico.setPosition(420, 390);
}

void Skylab::going3rdCASFalse() {
	going3rdCAS = false;
}

bool Skylab::gotoSkylabRoom() {
	return goingSkylabRoom;
}

void Skylab::goingSkylabRoomFalse() {
	goingSkylabRoom = false;
}

void Skylab::enterText() {
	//cout << "show enter door text" << endl;
	enterDoorText.setCharacterSize(20);
	enterDoorText.setFillColor(Color::White);
	enterDoorText.setString("Press E to enter skylab room");
	enterDoorText.setOutlineColor(Color::Black);
	enterDoorText.setOutlineThickness(2);
	window.setView(window.getDefaultView());
	enterDoorText.setPosition(750, 300);
	window.draw(enterDoorText);
}

bool Skylab::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void Skylab::handleCollision(const Rectangle& rect) {
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

void Skylab::day2Start() {
	showNPCs = true;
	day2 = true;
	npc.day2Start();
	elrico.setPosition(450, 350);
	going3rdCAS = false;
	goingSkylabRoom = false;
}

void Skylab::kwehDialogueBox() {
	if (!kwehCollected) {
		paper2SFX.pause();
		paper2SFX.play();
		hwCount += 1;
		kwehCollected = true;
	}
	dialogueBox.initDialogue("KWEH: \n\t... Ha?");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowKweh();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolKweh = false;
			dialogueBox.reset();
		}
	}
}

void Skylab::desDialogueBox() {
	if (!desCollected) {
		paper2SFX.pause();
		paper2SFX.play();
		hwCount += 1;
		desCollected = true;
	}
	dialogueBox.initDialogue("DESU: \n\tOkie dokie... btw ok ra ka?");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowDes();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolDes = false;
			dialogueBox.reset();
		}
	}
}

void Skylab::ameruDialogueBox() {
	if (!ameruCollected) {
		paper1SFX.pause();
		paper1SFX.play();
		hwCount += 1;
		ameruCollected = true;
	}
	dialogueBox.initDialogue("AMERU-KUN: \n\tWa kay tulog? Parehas rata");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowAmeru();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolAmeru = false;
			dialogueBox.reset();
		}
	}
}

void Skylab::kitDialogueBox() {
	if (!kitCollected) {
		paper1SFX.pause();
		paper1SFX.play();
		hwCount += 1;
		kitCollected = true;
	}
	dialogueBox.initDialogue("KIT: \n\tOkay hereee");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowKit();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolKit = false;
			dialogueBox.reset();
		}
	}
}

void Skylab::cjDialogueBox() {
	dialogueBox.initDialogue("SIJEH: \n\tNinglakaw na sila sa next class ninyo bai");
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

bool Skylab::papersComplete() {
	return showTask3;
}

void Skylab::cjDialogue(bool papersPlaced) {
	if (papersPlaced) {
		showNPCs = false;
		showCJ = true;
		showTask4 = true;
	}
}

void Skylab::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	room.setScale(roomScale);
	elrico.setScale(playerScale);
	window.draw(blackBG);
	window.draw(room);

	if (day2 && showNPCs) {
		npc.renderDes();
		npc.renderKweh();
		npc.renderKit();
		npc.renderAmeru();
	}

	if (day2 && showCJ) {
		npc.renderCJ();
	}

	arrowSprite.setTextureRect(arrowRect);
	window.draw(arrowSprite);

	if (day2) {
		if (!hide2) {
			for (const auto& ice1 : item2) {
				window.draw(ice1);
			}
		}

		if (!hide1) {
			for (const auto& match1 : item1) {
				window.draw(match1);
			}
		}

		if (!hide3) {
			window.draw(metal1);
		}

		if (!hide4) {
			window.draw(metal2);
		}

		if (!hide5) {
			window.draw(metal3);
		}
	}


	window.draw(elrico);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.draw(playerName);
	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);

	if (!day2) {
		window.draw(task1);
	}
	else if(!showTask3 && day2 && showNPCs){
		window.draw(task2);
		window.draw(hwCountText);
	}
	else if (showTask3 && day2 && showNPCs) {
		window.draw(task3);
		window.draw(hwCountText);
	}

	if (showTask4 && day2 && showCJ) {
		window.draw(task4);
	}

	if (day2) {
		inv.updateTextPos();
		inv.render();
		window.draw(collectScraps);
	}

	if (showEnterText) {
		enterText();
	}

	if (dialogueBoolKweh) {
		kwehDialogueBox();
	}

	if (dialogueBoolDes) {
		desDialogueBox();
	}

	if (dialogueBoolKit) {
		kitDialogueBox();
	}

	if (dialogueBoolAmeru) {
		ameruDialogueBox();
	}

	if (dialogueBoolCJ) {
		cjDialogueBox();
	}
}