#include "HMRoom2Night.h"
#include "HMDay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

HMRoom2Night::HMRoom2Night(RenderWindow& window) : window(window), fadeTrans(window),
dPressed(false), aPressed(true), dampingFactor(0.3f), pauseMenu(window),
gamePaused(false), dialogueBox(window), goingHM2nd(false), dialogue1(false) {

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\hm-room1-night.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico-night.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	initPlayer();
}

HMRoom2Night::~HMRoom2Night() {

}

Vector2f lerrrpp(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void HMRoom2Night::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(345, 200);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	dialogue1 = true;

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

void HMRoom2Night::handleInput() {
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

	// 730x - 770x, 525y
	if (playerSprite.getPosition().x <= 780 && playerSprite.getPosition().x >= 710 && playerSprite.getPosition().y <= 650 && playerSprite.getPosition().y >= 480 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingHM2nd = true;
	}

	//305x - 350x, 525y
	if (playerSprite.getPosition().x <= 370 && playerSprite.getPosition().x >= 290 && playerSprite.getPosition().y <= 650 && playerSprite.getPosition().y >= 480 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingHM2nd = true;
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

void HMRoom2Night::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
}

void HMRoom2Night::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerrrpp(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void HMRoom2Night::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);
}

void HMRoom2Night::animUpdate(float dt) {
	/*currentImageArrow.y = 0;
	totalTime += dt;

	if (totalTime >= switchTimeArrow) {
		totalTime -= switchTimeArrow;
		currentImageArrow.x++;

		if (currentImageArrow.x >= 4) {
			currentImageArrow.x = 0;
		}
	}

	arrowRect.left = currentImageArrow.x * arrowRect.width;
	arrowRect.top = currentImageArrow.y * arrowRect.height;*/
}

bool HMRoom2Night::gotoHM2nd() {
	return goingHM2nd;
}

void HMRoom2Night::playerPosFromHM2nd() {
	playerSprite.setPosition(325, 500);
}

void HMRoom2Night::goingHM2ndFalse() {
	goingHM2nd = false;
}

bool HMRoom2Night::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void HMRoom2Night::handleCollision(const Rectangle& rect) {
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

void HMRoom2Night::showDialogueBox() {
	dialogueBox.initDialogue("\n\tYou didn't realize it was already dark.");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		dialogue1 = false;
		dialogueBox.reset();
	}
}

void HMRoom2Night::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(0.6f, 0.6f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);

	window.draw(playerSprite);

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.setView(window.getDefaultView());

	window.draw(quitText);
	window.draw(pauseText);

	if (dialogue1) {
		showDialogueBox();
	}
}