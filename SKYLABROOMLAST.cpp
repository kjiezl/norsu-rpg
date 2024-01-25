#include "SKYLABROOMLAST.h"
#include "PauseMenu.h"
#include "PlayerName.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "NPC.h"
#include "Skylab.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

SKYLABROOMLAST::SKYLABROOMLAST(RenderWindow& window) : window(window),
dialogueBoolKit(false), dialogueBoolAmeru(false), dialogueBoolCJ(false),
dialogueBoolDes(false), dialogueBoolKweh(false),
pauseMenu(window), gamePaused(false), fadeTrans(window), npc(window),
dialogueBox(window), dampingFactor(0.3f), dPressed(true), aPressed(false),
startCredits(false), dialogue(false) {
	//cout << endl << pName << endl;

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		cout << "no font" << endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	bgTexture.loadFromFile("sprites\\maps\\skylabroom.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico.png");
	roomScale = Vector2f(0.65f, 0.65f);
	playerScale = Vector2f(1.75f, 1.75f);

	totalTime = 0.0f;

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	initPlayer();
}

Vector2f lerp7(const Vector2f& start, const Vector2f& end) {
	float t = 0.3f;
	return start + t * (end - start);
}

SKYLABROOMLAST::~SKYLABROOMLAST() {

}

void SKYLABROOMLAST::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	dialogue = true;

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(360, 280);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 96, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

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

void SKYLABROOMLAST::handleInput() {
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

	Vector2f playerPos = playerSprite.getPosition();
	Vector2f kwehPos = npc.kwehPos3();
	Vector2f desPos = npc.desPos3();
	Vector2f cjPos = npc.cjPos3();
	Vector2f ameruPos = npc.ameruPos3();
	Vector2f kitPos = npc.kitPos3();

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

	if (Keyboard::isKeyPressed(Keyboard::E) && playerSprite.getPosition().x <= 850 && playerSprite.getPosition().x >= 750 && playerSprite.getPosition().y <= 600 && playerSprite.getPosition().y >= 550) {
		startCredits = true;
	}

	for (auto& rect : rectangles) {
		handleCollision(rect);
	}
}

void SKYLABROOMLAST::updateTextPos() {

	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
}

void SKYLABROOMLAST::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp7(currentCenter, targetCenter);
	camera.setCenter(newCenter);
}

void SKYLABROOMLAST::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);
}

void SKYLABROOMLAST::animUpdate(float dt) {
	
}

void SKYLABROOMLAST::kwehDialogueBox() {
	dialogueBox.initDialogue("KWEH: \n\tNaol natulog");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowKweh3();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolKweh = false;
			dialogueBox.reset();
		}
	}
}

void SKYLABROOMLAST::desDialogueBox() {
	dialogueBox.initDialogue("DESU: \n\tTaysa ngano init kaayo ka? Gihilanat ka?");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowDes3();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolDes = false;
			dialogueBox.reset();
		}
	}
}

void SKYLABROOMLAST::cjDialogueBox() {
	dialogueBox.initDialogue("SIJEH: \n\tHoi mata na bai");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowCJ3();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolCJ = false;
			dialogueBox.reset();
		}
	}
}

void SKYLABROOMLAST::ameruDialogueBox() {
	dialogueBox.initDialogue("AMERU-KUN: \n\tLuspad lagi ka... mura kag nakakita ug abat..");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowAmeru3();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolAmeru = false;
			dialogueBox.reset();
		}
	}
}

void SKYLABROOMLAST::kitDialogueBox() {
	dialogueBox.initDialogue("KIT: \n\tTara uli nata, pahuway unya pag-abot ha?");
	dialogueBox.update();
	dialogueBox.render();
	window.setView(camera);
	npc.showArrowKit3();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBoolKit = false;
			dialogueBox.reset();
		}
	}
}

bool SKYLABROOMLAST::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void SKYLABROOMLAST::handleCollision(const Rectangle& rect) {
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

void SKYLABROOMLAST::npcUpdate(float dt) {
	npc.animUpdate(dt);
	npc.update();
}

bool SKYLABROOMLAST::gotoCredits() {
	return startCredits;
}

void SKYLABROOMLAST::showDialogue() {
	dialogueBox.initDialogue("\n\tYou were woken up.");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		dialogue = false;
		dialogueBox.reset();
	}
}

void SKYLABROOMLAST::render() {

	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(roomScale);
	playerSprite.setScale(playerScale);
	window.draw(blackBG);
	window.draw(bgSprite);
	npc.renderKweh3();
	npc.renderDes3();
	npc.renderCJ3();
	npc.renderAmeru3();
	npc.renderKit3();
	window.draw(playerSprite);

	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);

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

	if (dialogue) {
		showDialogue();
	}

	if (!fadeTrans.isFadedOut()) {
		fadeTrans.updateOut(dt);
		fadeTrans.renderOut();
	}
}
