#include "OpenCourt.h"
#include "HMDay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

OpenCourt::OpenCourt(RenderWindow& window) : window(window), fadeTrans(window),
dPressed(false), aPressed(true), dampingFactor(0.3f), pauseMenu(window),
gamePaused(false), dialogueBox(window), goingCBA(false), inv(window), 
showTask4(false), hide1(false) {

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task2.setFont(font);
	task4.setFont(font);
	collectScraps.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\opencourt.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	itemTex.loadFromFile("sprites\\items\\ice.png");
	ice.setTexture(itemTex);

	itemBuffer.loadFromFile("sprites\\sfx\\item-plop.ogg");
	itemSFX.setBuffer(itemBuffer);

	initPlayer();
}

OpenCourt::~OpenCourt() {

}

Vector2f lerp10(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void OpenCourt::initPlayer() {
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

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(900, 530);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	float rectAlpha = 0.0f;

	rectangles.push_back(Rectangle(250, -130, 1000, 100, rectAlpha)); // upper
	rectangles.push_back(Rectangle(250, 600, 1000, 100, rectAlpha)); // lower
	rectangles.push_back(Rectangle(190, 0, 60, 700, rectAlpha)); // left
	rectangles.push_back(Rectangle(1070, 0, 60, 700, rectAlpha)); // right

	// objects
	rectangles.push_back(Rectangle(264, 45, 50, 270, rectAlpha)); // left
	rectangles.push_back(Rectangle(995, 180, 50, 270, rectAlpha)); // right

	ice.setPosition(400, 330);

	updateTextPos();
}

void OpenCourt::handleInput() {
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

	float item1Distance = inv.calcuDistance(playerSprite.getPosition(), ice.getPosition());
	if (item1Distance < 50 && Keyboard::isKeyPressed(Keyboard::E)) {
		itemSFX.pause();
		itemSFX.play();
		inv.addItem2();
		ice.setPosition(9999, 9999);
		hide1 = true;
	}

	for (auto& rect : rectangles) {
		handleCollision(rect);
	}

	// 1100 530
	if (playerSprite.getPosition().x <= 1300 && playerSprite.getPosition().x >= 1000 && playerSprite.getPosition().y <= 600 && playerSprite.getPosition().y >= 400) {
		goingCBA = true;
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

void OpenCourt::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 920, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 800, camera.getCenter().y - window.getSize().y / 1.80f);
	collectScraps.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.60f);
}

void OpenCourt::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp10(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void OpenCourt::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);
}

void OpenCourt::animUpdate(float dt) {
	
}

bool OpenCourt::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void OpenCourt::handleCollision(const Rectangle& rect) {
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

bool OpenCourt::gotoCBA() {
	return goingCBA;
}

void OpenCourt::playerPosFromCBA() {
	playerSprite.setPosition(900, 530);
}

void OpenCourt::goingCBAFalse() {
	goingCBA = false;
}

void OpenCourt::show4(bool papersPlaced) {
	if (papersPlaced) {
		showTask4 = true;
	}
}

void OpenCourt::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(0.6f, 0.6f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
	if (!hide1) {
		window.draw(ice);
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
