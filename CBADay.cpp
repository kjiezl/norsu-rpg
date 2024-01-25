#include "CBADay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

CBADay::CBADay(RenderWindow& window) : window(window), fadeTrans(window), dPressed(false),
aPressed(true), dampingFactor(0.3f), pauseMenu(window), gamePaused(false),
dialogueBox(window), goingHM(false), goingRoom(false), showTask4(false), 
goingMainGate(false), inv(window), hide1(false), hide2(false), hide3(false), 
hide4(false), hide5(false), hide6(false), goingCourt(false) {

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}
	// 2865
	quitText.setFont(font);
	pauseText.setFont(font);\
	task2.setFont(font);
	task4.setFont(font);
	collectScraps.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\cba.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	totalTime = 0.0f;

	arrowTex.loadFromFile("sprites\\ui\\guide-arrow.png");
	arrowSprite.setTexture(arrowTex);
	currentImageArrow.x = 0;
	arrowRect.width = arrowTex.getSize().x / 4;
	arrowRect.height = arrowTex.getSize().y / 1;
	switchTimeArrow = 0.2f;

	item1Tex.loadFromFile("sprites\\items\\match.png");
	item2Tex.loadFromFile("sprites\\items\\ice.png");
	item3Tex.loadFromFile("sprites\\items\\metal.png");

	match1.setTexture(item1Tex);
	ice1.setTexture(item2Tex);
	ice2.setTexture(item2Tex);
	metal1.setTexture(item3Tex);
	metal2.setTexture(item3Tex);
	metal3.setTexture(item3Tex);

	itemBuffer.loadFromFile("sprites\\sfx\\item-plop.ogg");
	itemSFX.setBuffer(itemBuffer);

	initPlayer();
}

CBADay::~CBADay() {

}

Vector2f lerp8(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void CBADay::initPlayer() {
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

	task4.setString("!\tGo to your next class in HM building");
	task4.setCharacterSize(25);
	task4.setOutlineColor(Color::Black);
	task4.setOutlineThickness(3);

	collectScraps.setString("!\tPress E to collect scraps for crafting");
	collectScraps.setCharacterSize(20);
	collectScraps.setOutlineColor(Color::Black);
	collectScraps.setOutlineThickness(3);

	arrowSprite.setPosition(1757, 155);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(330, 230);
	//playerSprite.setPosition(1355, 450);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);
	
	float rectAlpha = 0.0f;
	
	// big upper
	rectangles.push_back(Rectangle(250, 10, 1030, 100, rectAlpha));
	rectangles.push_back(Rectangle(1432, 10, 1200, 100, rectAlpha)); // upper 2
	// big lower 1
	rectangles.push_back(Rectangle(200, 475, 1040, 600, rectAlpha));
	rectangles.push_back(Rectangle(1473, 475, 1200, 600, rectAlpha)); // lower 2
	rectangles.push_back(Rectangle(200, 100, 40, 700, rectAlpha)); // big left
	rectangles.push_back(Rectangle(2518, 100, 40, 700, rectAlpha)); // big right

	// columns up
	rectangles.push_back(Rectangle(283, 117, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(521, 117, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(757, 117, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(994, 117, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1230, 117, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1465, 117, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1706, 117, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1941, 117, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2179, 117, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2415, 117, 10, 10, rectAlpha));

	rectangles.push_back(Rectangle(2635, 75, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1138, 85, 72, 10, rectAlpha));

	// columns down
	rectangles.push_back(Rectangle(283, 450, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(521, 450, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(757, 450, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(994, 450, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1230, 450, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1465, 450, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1706, 450, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(1941, 450, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2179, 450, 10, 10, rectAlpha));
	rectangles.push_back(Rectangle(2415, 450, 10, 10, rectAlpha));

	// stairs
	rectangles.push_back(Rectangle(1230, 530, 200, 10, rectAlpha));
	rectangles.push_back(Rectangle(1270, -20, 200, 10, rectAlpha));

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 3000 + 250);
		float y = static_cast<float>(rand() % 250 + 145);
		match1.setPosition(Vector2f(x, y));
		item1.push_back(match1);
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 2000 + 250);
		float y = static_cast<float>(rand() % 200 + 100);
		ice2.setPosition(Vector2f(x, y));
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 1000 + 250);
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
		float x = static_cast<float>(rand() % 1000 + 250);
		float y = static_cast<float>(rand() % 200 + 145);
		metal2.setPosition(Vector2f(x, y));
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 2000 + 250);
		float y = static_cast<float>(rand() % 250 + 145);
		metal3.setPosition(Vector2f(x, y));
	}

	updateTextPos();
}

void CBADay::handleInput() {
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

	// 600 470 - 750 550
	if (playerSprite.getPosition().x <= 300 && playerSprite.getPosition().x >= -20 && playerSprite.getPosition().y <= 440 && playerSprite.getPosition().y >= 100) {
		goingHM = true;
	}

	// 1757 155
	if (playerSprite.getPosition().x <= 1785 && playerSprite.getPosition().x >= 1740 && playerSprite.getPosition().y <= 170 && playerSprite.getPosition().y >= 90 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingRoom = true;
	}

	// 1250x - 1470x, >500y
	if (playerSprite.getPosition().x <= 1470 && playerSprite.getPosition().x >= 1250 && playerSprite.getPosition().y <= 700 && playerSprite.getPosition().y >= 500) {
		goingMainGate = true;
	}

	// 1350 115
	if (playerSprite.getPosition().x <= 1470 && playerSprite.getPosition().x >= 1250 && playerSprite.getPosition().y <= 50 && playerSprite.getPosition().y >= -20) {
		goingCourt = true;
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

	float item2Distance2 = inv.calcuDistance(playerSprite.getPosition(), ice2.getPosition());
	if (item2Distance2 < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem2();
		ice2.setPosition(9999, 9999);
		hide5 = true;
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

	float item3Distance3 = inv.calcuDistance(playerSprite.getPosition(), metal3.getPosition());
	if (item3Distance3 < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem3();
		metal3.setPosition(9999, 9999);
		hide6 = true;
	}
}

void CBADay::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 920, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 800, camera.getCenter().y - window.getSize().y / 1.80f);
	collectScraps.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.60f);
}

void CBADay::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp8(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void CBADay::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);
}

void CBADay::animUpdate(float dt) {
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

bool CBADay::gotoHM() {
	return goingHM;
}

void CBADay::playerPosFromHM() {
	playerSprite.setPosition(360, 230);
}

void CBADay::goingHMFalse() {
	goingHM = false;
}

bool CBADay::gotoRoom() {
	return goingRoom;
}

void CBADay::playerPosFromRoom() {
	playerSprite.setPosition(1760, 155);
}

void CBADay::goingRoomFalse() {
	goingRoom = false;
}

bool CBADay::gotoCourt() {
	return goingCourt;
}

void CBADay::playerPosFromCourt() {
	playerSprite.setPosition(1350, 115);
}

void CBADay::goingCourtFalse() {
	goingCourt = false;
}

bool CBADay::gotoMainGate() {
	return goingMainGate;
}

void CBADay::playerPosFromMainGate() {
	playerSprite.setPosition(1355, 450);
}

void CBADay::goingMainGateFalse() {
	goingMainGate = false;
}

bool CBADay::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void CBADay::handleCollision(const Rectangle& rect) {
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

void CBADay::show4(bool papersPlaced) {
	if (papersPlaced) {
		showTask4 = true;
	}
}

void CBADay::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(1.1f, 1.1f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
	arrowSprite.setTextureRect(arrowRect);
	window.draw(arrowSprite);

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

	if (!hide5) {
		window.draw(ice2);
	}

	if (!hide6) {
		window.draw(metal3);
	}

	window.draw(playerSprite);
	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);
	window.draw(collectScraps);
	inv.updateTextPos();
	inv.render();
	if (!showTask4) {
		window.draw(task2);
	}
	else {
		window.draw(task4);
	}
}
