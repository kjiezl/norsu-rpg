#include "SkylabRoom.h"
#include "PauseMenu.h"
#include "PlayerName.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "NPC.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;
using namespace std;

SkylabRoom::SkylabRoom(RenderWindow& window, const string& pName) : window(window), 
dialogueBoolKit(false), dialogueBoolAmeru(false), dialogueBoolCJ(false), 
dialogueBoolDes(false), dialogueBoolKweh(false), startCutScene(false), 
showExitText(false), goingSkylab(false), playerNameClass(window), pName(pName), 
pauseMenu(window), gamePaused(false), fadeTrans(window), npc(window), 
dialogueBox(window), dampingFactor(0.3f), dPressed(true), showPaper(false),
aPressed(false), day2(false), showTask4(false),
completePapers(false), inv(window) {
	//cout << endl << pName << endl;

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		cout << "no font" << endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	task2.setFont(font);
	task3.setFont(font);
	task4.setFont(font);
	playerName.setFont(font);
	roomTexture.loadFromFile("sprites\\maps\\skylabroom.png");
	texture.loadFromFile("sprites\\characters\\elrico.png");
	roomScale = Vector2f(0.65f, 0.65f);
	playerScale = Vector2f(1.75f, 1.75f);

	totalTime = 0.0f;

	nightTint.setFillColor(Color(20, 15, 50, 140));
	nightTint.setSize(Vector2f(window.getSize().x, window.getSize().y));

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	exitDoorText.setFont(font);

	paperTex.loadFromFile("sprites\\items\\papers.png");
	paperStack.setTexture(paperTex);

	paperPlacedBuffer.loadFromFile("sprites\\sfx\\paper-placed.ogg");
	paperPlacedSFX.setBuffer(paperPlacedBuffer);

	initPlayer();
}

Vector2f ler(const Vector2f& start, const Vector2f& end) {
	float t = 0.3f;
	return start + t * (end - start);
}

SkylabRoom::~SkylabRoom() {

}

void SkylabRoom::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	task1.setString("!\tGo to your seat");
	task1.setCharacterSize(25);
	task1.setOutlineColor(Color::Black);
	task1.setOutlineThickness(3);

	task2.setString("!\tCollect the assignments from your classmates first");
	task2.setCharacterSize(25);
	task2.setOutlineColor(Color::Black);
	task2.setOutlineThickness(3);

	task3.setString("!\tPass the papers on the table");
	task3.setCharacterSize(25);
	task3.setOutlineColor(Color::Black);
	task3.setOutlineThickness(3);

	task4.setString("!\tGo to your next class in HM building");
	task4.setCharacterSize(25);
	task4.setOutlineColor(Color::Black);
	task4.setOutlineThickness(3);

	paperStack.setPosition(720, 365);

	playerName.setCharacterSize(10);
	playerName.setFillColor(Color::White);
	playerName.setOutlineColor(Color::Black);
	playerName.setOutlineThickness(1.0);
	playerName.setLetterSpacing(4);

	room.setTexture(roomTexture);
	room.setPosition(250, 0);

	elrico.setPosition(800, 565);
	elrico.setTexture(texture);
	elrico.setTextureRect(IntRect(0, 96, 32, 32));

	playerBounds = elrico.getLocalBounds();
	elrico.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	arrowTexture.loadFromFile("sprites\\ui\\guide-arrow.png");
	arrowSprite.setTexture(arrowTexture);
	arrowSprite2.setTexture(arrowTexture);
	switchTimeArrow = 0.2f;
	arrowRect.width = arrowTexture.getSize().x / 4;
	arrowRect.height = arrowTexture.getSize().y / 1;
	currentImageArrow.x = 0;
	arrowSprite.setPosition(297, 280);
	arrowSprite2.setPosition(710, 280);

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
	
	updateTextPos();

}

void SkylabRoom::handleInput() {
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
	Vector2i pixelMousePosition = Mouse::getPosition(window);
	if (static_cast<unsigned>(pixelMousePosition.x) < window.getSize().x &&
		static_cast<unsigned>(pixelMousePosition.y) < window.getSize().y) {
		if (Keyboard::isKeyPressed(Keyboard::T)) {
			Vector2f worldMousePosition = window.mapPixelToCoords(pixelMousePosition);
			cout << "Mouse Coordinates: (" << worldMousePosition.x << ", " << worldMousePosition.y << ")" << endl;
		}
	}

	Vector2f playerPos = elrico.getPosition();
	Vector2f catPos = npc.catPos();
	Vector2f blehPos = npc.blehPos();
	Vector2f kwehPos = npc.kwehPos();
	Vector2f desPos = npc.desPos();
	Vector2f cjPos = npc.cjPos();
	Vector2f ameruPos = npc.ameruPos();
	Vector2f kitPos = npc.kitPos();

	float distance3 = sqrt((playerPos.x - kwehPos.x) * (playerPos.x - kwehPos.x) + (playerPos.y - kwehPos.y) * (playerPos.y - kwehPos.y));
	float distance4 = sqrt((playerPos.x - desPos.x) * (playerPos.x - desPos.x) + (playerPos.y - desPos.y) * (playerPos.y - desPos.y));
	float distance5 = sqrt((playerPos.x - cjPos.x) * (playerPos.x - cjPos.x) + (playerPos.y - cjPos.y) * (playerPos.y - cjPos.y));
	float distance6 = sqrt((playerPos.x - ameruPos.x) * (playerPos.x - ameruPos.x) + (playerPos.y - ameruPos.y) * (playerPos.y - ameruPos.y));
	float distance7 = sqrt((playerPos.x - kitPos.x) * (playerPos.x - kitPos.x) + (playerPos.y - kitPos.y) * (playerPos.y - kitPos.y));

	if (distance3 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolKweh = true;
	}

	if (distance4 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolDes = true;
	}

	if (distance5 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolCJ = true;
	}

	if (distance6 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolAmeru = true;
	}

	if (distance7 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolKit = true;
	}

	if (distance3 >= 90.0f && dialogueBoolKweh) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolKweh = false;
	}

	if (distance4 >= 90.0f && dialogueBoolDes) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolDes = false;
	}

	if (distance5 >= 90.0f && dialogueBoolCJ) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolCJ = false;
	}

	if (distance6 >= 90.0f && dialogueBoolAmeru) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolAmeru = false;
	}

	if (distance7 >= 90.0f && dialogueBoolKit) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolKit = false;
	}

	// 750 850 560 580
	if (elrico.getPosition().x <= 850 && elrico.getPosition().x >= 750 && elrico.getPosition().y <= 600 && elrico.getPosition().y >= 550) {
		showExitText = true;
		if (Keyboard::isKeyPressed(Keyboard::E)) {
			goingSkylab = true;
		}
	}
	else {
		showExitText = false;
	}

	//295 280
	if (elrico.getPosition().x <= 350 && elrico.getPosition().x >= 280 && elrico.getPosition().y <= 300 && elrico.getPosition().y >= 250 && !day2) {
		startCutScene = true;
	}

	if (elrico.getPosition().x <= 750 && elrico.getPosition().x >= 600 && elrico.getPosition().y <= 300 && elrico.getPosition().y >= 250 && day2 && !showTask4 && completePapers) {
		paperPlacedSFX.pause();
		paperPlacedSFX.play();
		showTask4 = true;
		showPaper = true;
	}

	for (auto& rect : rectangles) {
		handleCollision(rect);
	}
}

void SkylabRoom::updateTextPos() {

	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1000, camera.getCenter().y - window.getSize().y / 1.80f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 650, camera.getCenter().y - window.getSize().y / 1.80f);
	task3.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 780, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 800, camera.getCenter().y - window.getSize().y / 1.80f);
}

void SkylabRoom::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - elrico.getPosition();
	targetCenter = elrico.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = ler(currentCenter, targetCenter);
	camera.setCenter(newCenter);
}

void SkylabRoom::update() {
	nightTint.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(elrico.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);
}

void SkylabRoom::animUpdate(float dt) {
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
}

bool SkylabRoom::gotoSkylab() {
	return goingSkylab;
}

void SkylabRoom::goingSkylabFalse() {
	goingSkylab = false;
}

void SkylabRoom::exitText() {
	exitDoorText.setCharacterSize(20);
	exitDoorText.setFillColor(Color::White);
	exitDoorText.setString("Press E to exit skylab room");
	exitDoorText.setOutlineColor(Color::Black);
	exitDoorText.setOutlineThickness(2);
	window.setView(window.getDefaultView());
	exitDoorText.setPosition(750, 300);
	window.draw(exitDoorText);
}

bool SkylabRoom::startScene() {
	return startCutScene;
}

void SkylabRoom::kwehDialogueBox() {
	dialogueBox.initDialogue("KWEH: \n\tGutom ko T-T");
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

void SkylabRoom::desDialogueBox() {
	dialogueBox.initDialogue("DESU: \n\tMagshift nlang kog architecture TwT");
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

void SkylabRoom::cjDialogueBox() {
	dialogueBox.initDialogue("SIJEH: \n\tMatulog natag sayo :<");
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

void SkylabRoom::ameruDialogueBox() {
	dialogueBox.initDialogue("AMERU-KUN: \n\tHmmm... ang texture...");
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

void SkylabRoom::kitDialogueBox() {
	dialogueBox.initDialogue("KIT: \n\tHatag makaon plsss");
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

bool SkylabRoom::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void SkylabRoom::handleCollision(const Rectangle& rect) {
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

void SkylabRoom::npcUpdate(float dt) {
	npc.animUpdate(dt);
	npc.update();
}

void SkylabRoom::day2Start() {
	elrico.setPosition(800, 565);
	day2 = true;
	goingSkylab = false;
	startCutScene = false;
}

void SkylabRoom::papersComplete(bool areComplete) {
	if (areComplete && day2 && !showTask4) {
		window.draw(task3);
		window.setView(camera);
		window.draw(arrowSprite2);
		completePapers = true;
	}
	if(!areComplete && day2 && !showTask4){
		window.draw(task2);
	}
}

bool SkylabRoom::papersPlaced() {
	return showTask4;
}

void SkylabRoom::render() {

	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	room.setScale(roomScale);
	elrico.setScale(playerScale);
	window.draw(blackBG);
	window.draw(room);
	if (showPaper) {
		window.draw(paperStack);
	}
	arrowSprite.setTextureRect(arrowRect);
	arrowSprite2.setTextureRect(arrowRect);
	if (!day2) {
		npc.renderKweh();
		npc.renderDes();
		npc.renderCJ();
		npc.renderAmeru();
		npc.renderKit();
		window.draw(arrowSprite);
	}
	window.draw(elrico);
	window.draw(playerName);

	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);

	if (day2) {
		inv.updateTextPos();
		inv.render();
	}

	if (!day2) {
		window.draw(task1);
	}
	if (showTask4) {
		window.draw(task4);
	}

	if (dialogueBoolKweh) {
		kwehDialogueBox();
	}
	if (dialogueBoolDes) {
		desDialogueBox();
	}
	if (dialogueBoolCJ) {
		cjDialogueBox();
	}
	if (dialogueBoolAmeru) {
		ameruDialogueBox();
	}
	if (dialogueBoolKit) {
		kitDialogueBox();
	}

	if (showExitText) {
		exitText();
	}

	if (!fadeTrans.isFadedOut()) {
		fadeTrans.updateOut(dt);
		fadeTrans.renderOut();
	}
}