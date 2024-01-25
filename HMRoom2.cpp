#include "HMRoom2.h"
#include "HMDay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

HMRoom2::HMRoom2(RenderWindow& window) : window(window), fadeTrans(window), 
dPressed(false), aPressed(true), dampingFactor(0.3f), pauseMenu(window),
gamePaused(false), showTask4(false), dialogueBox(window), goingHM2nd(false), 
dialogueBoolKit(false), dialogueBoolAmeru(false), dialogueBoolDes(false), 
dialogueBoolKweh(false), showNPCs(false), npc(window), startScene(false) {

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task2.setFont(font);
	task4.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\hm-room1.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	arrowTexture.loadFromFile("sprites\\ui\\guide-arrow.png");
	arrowSprite.setTexture(arrowTexture);
	totalTime = 0.0f;
	switchTimeArrow = 0.2f;
	currentImageArrow.x = 0;
	arrowRect.width = arrowTexture.getSize().x / 4;
	arrowRect.height = arrowTexture.getSize().y / 1;

	initPlayer();
}

HMRoom2::~HMRoom2() {

}

Vector2f lerrppp(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void HMRoom2::initPlayer() {
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

	task4.setString("!\tGo to your seat");
	task4.setCharacterSize(25);
	task4.setOutlineColor(Color::Black);
	task4.setOutlineThickness(3);

	arrowSprite.setPosition(300, 200);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(345, 500);
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
	rectangles.push_back(Rectangle(340, 219, 10, 60, rectAlpha));
	rectangles.push_back(Rectangle(668, 312, 10, 68, rectAlpha));
	rectangles.push_back(Rectangle(676, 238, 71, 20, rectAlpha));

	// columns
	rectangles.push_back(Rectangle(436, 127, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(628, 127, 10, 10, rectAlpha));

	updateTextPos();
}

void HMRoom2::handleInput() {
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

	Vector2f playerPos = playerSprite.getPosition();
	Vector2f catPos = npc.catPos();
	Vector2f blehPos = npc.blehPos();
	Vector2f kwehPos = npc.kwehPos();
	Vector2f desPos = npc.desPos();
	Vector2f ameruPos = npc.ameruPos();
	Vector2f kitPos = npc.kitPos();

	float distance1 = sqrt((playerPos.x - kwehPos.x) * (playerPos.x - kwehPos.x) + (playerPos.y - kwehPos.y) * (playerPos.y - kwehPos.y));
	float distance2 = sqrt((playerPos.x - desPos.x) * (playerPos.x - desPos.x) + (playerPos.y - desPos.y) * (playerPos.y - desPos.y));
	float distance3 = sqrt((playerPos.x - ameruPos.x) * (playerPos.x - ameruPos.x) + (playerPos.y - ameruPos.y) * (playerPos.y - ameruPos.y));
	float distance4 = sqrt((playerPos.x - kitPos.x) * (playerPos.x - kitPos.x) + (playerPos.y - kitPos.y) * (playerPos.y - kitPos.y));

	if (distance1 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolKweh = true;
	}

	if (distance2 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolDes = true;
	}

	if (distance3 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolAmeru = true;
	}

	if (distance4 <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolKit = true;
	}

	if (distance1 >= 90.0f && dialogueBoolKweh) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolKweh = false;
	}

	if (distance2 >= 90.0f && dialogueBoolDes) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolDes = false;
	}

	if (distance3 >= 90.0f && dialogueBoolAmeru) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolAmeru = false;
	}

	if (distance4 >= 90.0f && dialogueBoolKit) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolKit = false;
	}

	// 730x - 770x, 525y
	if (playerSprite.getPosition().x <= 780 && playerSprite.getPosition().x >= 710 && playerSprite.getPosition().y <= 650 && playerSprite.getPosition().y >= 480 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingHM2nd = true;
	}

	//305x - 350x, 525y
	if (playerSprite.getPosition().x <= 370 && playerSprite.getPosition().x >= 290 && playerSprite.getPosition().y <= 650 && playerSprite.getPosition().y >= 480 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingHM2nd = true;
	}

	// 300 200
	if (playerSprite.getPosition().x <= 350 && playerSprite.getPosition().x >= 200 && playerSprite.getPosition().y <= 300 && playerSprite.getPosition().y >= 100 && showTask4) {
		startScene = true;
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

void HMRoom2::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 920, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1000, camera.getCenter().y - window.getSize().y / 1.80f);
}

void HMRoom2::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerrppp(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void HMRoom2::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);
}

void HMRoom2::animUpdate(float dt) {
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

bool HMRoom2::gotoHM2nd() {
	return goingHM2nd;
}

void HMRoom2::playerPosFromHM2nd() {
	playerSprite.setPosition(325, 500);
}

void HMRoom2::goingHM2ndFalse() {
	goingHM2nd = false;
}

bool HMRoom2::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void HMRoom2::show4(bool papersPlaced) {
	if (papersPlaced) {
		showTask4 = true;
		showNPCs = true;
	}
}

void HMRoom2::handleCollision(const Rectangle& rect) {
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

void HMRoom2::kwehDialogueBox() {
	dialogueBox.initDialogue("KWEH: \n\tme.sleep();");
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

void HMRoom2::desDialogueBox() {
	dialogueBox.initDialogue("DESU: \n\tHai hai");
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

void HMRoom2::ameruDialogueBox() {
	dialogueBox.initDialogue("AMERU-KUN: \n\tOk raka bai?");
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

void HMRoom2::kitDialogueBox() {
	dialogueBox.initDialogue("KIT: \n\tHmm... Wala tay klase?");
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

bool HMRoom2::startCutScene() {
	return startScene;
}

void HMRoom2::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(0.6f, 0.6f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
	arrowSprite.setTextureRect(arrowRect);

	if (showNPCs) {
		npc.renderKweh();
		npc.renderDes();
		npc.renderAmeru();
		npc.renderKit();
		window.draw(arrowSprite);
	}

	window.draw(playerSprite);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.setView(window.getDefaultView());
	if (!showTask4) {
		window.draw(task2);
	}
	if (showTask4) {
		window.draw(task4);
	}

	if (dialogueBoolKweh && showTask4) {
		kwehDialogueBox();
	}
	if (dialogueBoolDes && showTask4) {
		desDialogueBox();
	}
	if (dialogueBoolAmeru && showTask4) {
		ameruDialogueBox();
	}
	if (dialogueBoolKit && showTask4) {
		kitDialogueBox();
	}

	window.draw(quitText);
	window.draw(pauseText);
}