#include "HMDay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

HMDay::HMDay(RenderWindow& window) : window(window), fadeTrans(window), dPressed(false),
aPressed(true), dampingFactor(0.3f), goingMainGate(false), pauseMenu(window),
gamePaused(false), showTask4(false), ghostMove(false), dialogueBox(window), 
showDialogue(false), goingHM2nd(false), goingCBA(false), hide1(false), hide3(false),
hide2(false), inv(window), hide4(false){

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task2.setFont(font);
	task4.setFont(font);
	collectScraps.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\hm1.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	ghostTex.loadFromFile("sprites\\enemies\\ghost1.1.png");
	ghost.setTexture(ghostTex);

	switchTime = 0.3f;
	totalTime = 0.0f;
	currentImage.x = 0;
	ghostRect.width = ghostTex.getSize().x / 3;
	ghostRect.height = ghostTex.getSize().y / 1;

	item1Tex.loadFromFile("sprites\\items\\match.png");
	item2Tex.loadFromFile("sprites\\items\\ice.png");
	item3Tex.loadFromFile("sprites\\items\\metal.png");

	match1.setTexture(item1Tex);
	ice1.setTexture(item2Tex);
	metal1.setTexture(item3Tex);
	metal2.setTexture(item3Tex);

	itemBuffer.loadFromFile("sprites\\sfx\\item-plop.ogg");
	itemSFX.setBuffer(itemBuffer);

	initPlayer();
}

HMDay::~HMDay() {

}

Vector2f lerrpp(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void HMDay::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause CAS3Night");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	task2.setString("!\tGo to the CAS building");
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

	ghostPos.x = 775;
	ghostPos.y = 250;
	ghost.setPosition(ghostPos);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(330, 230);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	float rectAlpha = 0.0f;
	// big upper
	rectangles.push_back(Rectangle(250, -10, 3000, 100, rectAlpha));
	// big lower 1
	rectangles.push_back(Rectangle(250, 420, 365, 600, rectAlpha));
	rectangles.push_back(Rectangle(735, 420, 2800, 600, rectAlpha)); // big lower 2
	rectangles.push_back(Rectangle(200, 100, 40, 700, rectAlpha)); // big left
	rectangles.push_back(Rectangle(2920, 100, 40, 700, rectAlpha)); // big right
	
	// columns up
	rectangles.push_back(Rectangle(388, 95, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(928, 95, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1111, 95, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1288, 95, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1473, 95, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1658, 95, 10, 10, rectAlpha));

	rectangles.push_back(Rectangle(1840, 95, 188, 10, rectAlpha));

	rectangles.push_back(Rectangle(2200, 95, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2383, 95, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2563, 95, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2748, 95, 10, 10, rectAlpha));

	rectangles.push_back(Rectangle(572, 100, 190, 10, rectAlpha));

	// columns down
	rectangles.push_back(Rectangle(388, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(570, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(750, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(928, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1111, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1288, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1473, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1658, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1840, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2018, 395, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2200, 395, 10, 10, rectAlpha));

	rectangles.push_back(Rectangle(2383, 395, 190, 10, rectAlpha));
	rectangles.push_back(Rectangle(2443, 380, 70, 10, rectAlpha));

	rectangles.push_back(Rectangle(2748, 395, 10, 10, rectAlpha));

	// stairs
	rectangles.push_back(Rectangle(600, 490, 150, 10, rectAlpha));

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

void HMDay::handleInput() {
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

	// 300, 230
	if (playerSprite.getPosition().x <= 300 && playerSprite.getPosition().x >= -20 && playerSprite.getPosition().y <= 440 && playerSprite.getPosition().y >= 100) {
		goingMainGate = true;
	}

	// 600 470 - 750 550
	if (playerSprite.getPosition().x <= 750 && playerSprite.getPosition().x >= 600 && playerSprite.getPosition().y <= 550 && playerSprite.getPosition().y >= 450) {
		goingHM2nd = true;
	}

	// 2870
	if (playerSprite.getPosition().x <= 3000 && playerSprite.getPosition().x >= 2870 && playerSprite.getPosition().y <= 440 && playerSprite.getPosition().y >= 100) {
		goingCBA = true;
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

	//635 290
	if (playerSprite.getPosition().x <= 800 && playerSprite.getPosition().x >= 600 && playerSprite.getPosition().y <= 500 && playerSprite.getPosition().y >= 100 && showTask4 && !ghostMove) {
		showDialogue = true;
	}

	if (playerSprite.getPosition().x <= 800 && playerSprite.getPosition().x >= 600 && playerSprite.getPosition().y <= 500 && playerSprite.getPosition().y >= 100 && showTask4) {
		ghostMove = true;
	}

	float item1Distance = inv.calcuDistance(playerSprite.getPosition(), match1.getPosition());
	if (item1Distance < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem1();
		match1.setPosition(9999, 9999);
		hide1 = true;
	}

	float item2Distance = inv.calcuDistance(playerSprite.getPosition(), ice1.getPosition());
	if (item2Distance < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem2();
		ice1.setPosition(9999, 9999);
		hide2 = true;
	}

	float item3Distance1 = inv.calcuDistance(playerSprite.getPosition(), metal1.getPosition());
	if (item3Distance1 < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem3();
		metal1.setPosition(9999, 9999);
		hide3 = true;
	}

	float item3Distance2 = inv.calcuDistance(playerSprite.getPosition(), metal2.getPosition());
	if (item3Distance2 < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem3();
		metal2.setPosition(9999, 9999);
		hide4 = true;
	}
}

void HMDay::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 920, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 800, camera.getCenter().y - window.getSize().y / 1.80f);
	collectScraps.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.60f);
}

void HMDay::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerrpp(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void HMDay::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	//ector2f ghostPos (775, 250);

	if (ghostMove) {
		ghost.move(ghostPos);
		ghostPos.x += 3;
		ghost.setPosition(ghostPos);
	}
}

void HMDay::animUpdate(float dt) {
	currentImage.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if(currentImage.x >= 3){
			currentImage.x = 0;
		}
	}

	ghostRect.left = currentImage.x * ghostRect.width;
	ghostRect.top = currentImage.y * ghostRect.height;
}

bool HMDay::gotoMainGate() {
	return goingMainGate;
}

void HMDay::playerPosFromMainGate() {
	playerSprite.setPosition(330, 230);
}

void HMDay::goingMainGateFalse() {
	goingMainGate = false;
}

bool HMDay::gotoHM2nd() {
	return goingHM2nd;
}

void HMDay::playerPosFromHM2nd() {
	playerSprite.setPosition(680, 380);
}

void HMDay::goingHM2ndFalse() {
	goingHM2nd = false;
}

bool HMDay::gotoCBA() {
	return goingCBA;
}

void HMDay::playerPosFromCBA() {
	playerSprite.setPosition(2850, 230);
}

void HMDay::goingCBAFalse() {
	goingCBA = false;
}

bool HMDay::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void HMDay::goingHM(bool papersPlaced) {
	if (papersPlaced) {
		showTask4 = true;
	}
}

void HMDay::handleCollision(const Rectangle& rect) {
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

void HMDay::dialogue() {
	dialogueBox.initDialogue("???");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		showDialogue = false;
		dialogueBox.reset();
	}
}

void HMDay::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(1.3f, 1.3f);
	playerSprite.setScale(1.75f, 1.75f);
	ghost.setTextureRect(ghostRect);
	ghost.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);

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

	window.draw(playerSprite);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	if (showTask4) {
		window.draw(ghost);
	}

	window.setView(window.getDefaultView());
	if (!showTask4) {
		window.draw(task2);
	}
	if (showTask4) {
		window.draw(task4);
	}

	inv.updateTextPos();
	inv.render();

	window.draw(quitText);
	window.draw(pauseText);
	window.draw(collectScraps);

	if (showDialogue) {
		dialogue();
	}
}