#include "HM2nd.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

HM2nd::HM2nd(RenderWindow& window) : window(window), fadeTrans(window), dPressed(false),
aPressed(true), dampingFactor(0.3f), pauseMenu(window), showDialogue(false),
gamePaused(false), showTask4(false), dialogueBox(window), showBlack(false),
doneDialogue(false), inv(window), hide1(false), hide2(false), hide3(false), hide4(false), 
hide5(false), hide6(false){

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task2.setFont(font);
	task4.setFont(font);
	collectScraps.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\hm2.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico.png");
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

	item1Tex.loadFromFile("sprites\\items\\match.png");
	item2Tex.loadFromFile("sprites\\items\\ice.png");
	item3Tex.loadFromFile("sprites\\items\\metal.png");

	match1.setTexture(item1Tex);
	match2.setTexture(item1Tex);
	ice1.setTexture(item2Tex);
	metal1.setTexture(item3Tex);
	metal2.setTexture(item3Tex);
	metal3.setTexture(item3Tex);

	itemBuffer.loadFromFile("sprites\\sfx\\item-plop.ogg");
	itemSFX.setBuffer(itemBuffer);

	initPlayer();
}

HM2nd::~HM2nd() {

}

Vector2f lerrrp(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void HM2nd::initPlayer() {
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
	
	arrowSprite.setPosition(2420, 125);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(330, 230);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	float rectAlpha = 0.0f;
	// big upper
	rectangles.push_back(Rectangle(250, -20, 3000, 100, rectAlpha));
	// big lower 1
	rectangles.push_back(Rectangle(355, 400, 2427, 600, rectAlpha));
	rectangles.push_back(Rectangle(200, 100, 40, 700, rectAlpha)); // big left
	rectangles.push_back(Rectangle(2920, 100, 40, 700, rectAlpha)); // big right

	// columns up
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

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 1800 + 250);
		float y = static_cast<float>(rand() % 200 + 100);
		match1.setPosition(Vector2f(x, y));
		item1.push_back(match1);
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 1300 + 250);
		float y = static_cast<float>(rand() % 250 + 100);
		match2.setPosition(Vector2f(x, y));
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 1500 + 250);
		float y = static_cast<float>(rand() % 200 + 100);
		ice1.setPosition(Vector2f(x, y));
		item2.push_back(ice1);
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 2000 + 250);
		float y = static_cast<float>(rand() % 250 + 100);
		metal1.setPosition(Vector2f(x, y));
		item3.push_back(metal1);
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 1000 + 250);
		float y = static_cast<float>(rand() % 200 + 100);
		metal2.setPosition(Vector2f(x, y));
	}

	for (int i = 0; i < 1; i++) {
		float x = static_cast<float>(rand() % 2500 + 250);
		float y = static_cast<float>(rand() % 250 + 100);
		metal3.setPosition(Vector2f(x, y));
	}

	updateTextPos();
}

void HM2nd::handleInput() {
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

	// 250-340x 390 
	if (playerSprite.getPosition().x <= 360 && playerSprite.getPosition().x >= 230 && playerSprite.getPosition().y <= 500 && playerSprite.getPosition().y >= 420) {
		goingHM = true;
	}

	// 660x
	if (!doneDialogue && showTask4 && playerSprite.getPosition().x <= 800 && playerSprite.getPosition().x >= 650 && playerSprite.getPosition().y <= 500 && playerSprite.getPosition().y >= 100) {
		showDialogue = true;
	}

	// 2420 130
	if (playerSprite.getPosition().x <= 2470 && playerSprite.getPosition().x >= 2370 && playerSprite.getPosition().y <= 150 && playerSprite.getPosition().y >= 80 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingHMRoom2 = true;
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

	float item1Distance2 = inv.calcuDistance(playerSprite.getPosition(), match2.getPosition());
	if (item1Distance2 < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem1();
		match2.setPosition(9999, 9999);
		hide5 = true;
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

	float item3Distance3 = inv.calcuDistance(playerSprite.getPosition(), metal3.getPosition());
	if (item3Distance3 < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem3();
		metal3.setPosition(9999, 9999);
		hide6 = true;
	}
}

void HM2nd::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 920, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 800, camera.getCenter().y - window.getSize().y / 1.80f);
	collectScraps.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.60f);
}

void HM2nd::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerrrp(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void HM2nd::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);
}

void HM2nd::animUpdate(float dt) {
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

bool HM2nd::gotoHM() {
	return goingHM;
}

void HM2nd::playerPosFromHM() {
	playerSprite.setPosition(300, 350);
}

void HM2nd::goingHMFalse() {
	goingHM = false;
}

bool HM2nd::gotoHMRoom2() {
	return goingHMRoom2;
}

void HM2nd::playerPosFromHMRoom2() {
	playerSprite.setPosition(2420, 150);
}

void HM2nd::goingHMRoom2False() {
	goingHMRoom2 = false;
}

bool HM2nd::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void HM2nd::show4(bool papersPlaced) {
	if (papersPlaced) {
		showTask4 = true;
	}
}

void HM2nd::handleCollision(const Rectangle& rect) {
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

void HM2nd::dialogue() {
	dialogueBox.initDialogue("You feel something strange.");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		showDialogue = false;
		showBlack = true;
		dialogueBox.reset();
	}
}

bool HM2nd::showBlackScene() {
	return showBlack;
}

void HM2nd::showBlackFalse() {
	showBlack = false;
	doneDialogue = true;
}

void HM2nd::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	arrowSprite.setTextureRect(arrowRect);
	bgSprite.setScale(1.3f, 1.3f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
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
		window.draw(match2);
	}

	if (!hide6) {
		window.draw(metal3);
	}

	window.draw(playerSprite);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.setView(window.getDefaultView());
	inv.updateTextPos();
	inv.render();
	if (!showTask4) {
		window.draw(task2);
	}
	if (showTask4) {
		window.draw(task4);
	}
	window.draw(quitText);
	window.draw(pauseText);
	window.draw(collectScraps);

	if (showDialogue) {
		dialogue();
	}
}
