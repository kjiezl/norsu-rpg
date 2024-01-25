#include "HMNight.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

HMNight::HMNight(RenderWindow& window) : window(window), fadeTrans(window), dPressed(false),
aPressed(true), dampingFactor(0.3f), pauseMenu(window), gamePaused(false),
dialogueBox(window), goingHM2nd(false), startLevel2(false), startLevel3(false),
levelComplete3(false), levelComplete2(false), levelComplete1(false),
showGhost13(true), showGhost12(true), showGhost11(true), showGhost10(true),
showGhost9(true), showGhost8(true), showGhost7(true), showGhost6(true),
showGhost5(true), showGhost4(true), showGhost3(true), showGhost1(true),
showGhost2(true), projectileShot(false), isShaking(false), showGhost15(true),
showGhost14(true), goingRoom1(false), showScores(true), bossDead(false),
dialogue(false), showCat(false), npc(window), task4Show(false), goingCBA(false),
healthCount(window), weapon1Show(false), weapon2Show(false), weapon3Show(false),
start5(false), start6(false), start7(false), start8(false), start9(false), start10(false),
start11(false) , start12(false), start13(false) , start14(false), start15(false),
slowed5(false), slowed6(false), slowed7(false), slowed8(false), slowed9(false), 
slowed10(false), slowed11(false), slowed12(false), slowed13(false), slowed14(false),
slowed15(false), hp(window, 100.0), showHP(true) {

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}
	// 2865
	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	task2.setFont(font);
	task3.setFont(font);
	task4.setFont(font);
	score1.setFont(font);
	score2.setFont(font);
	score3.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\hm1-night.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico-night.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	totalTime = 0.0f;
	currentImage.x = 0;

	ghost1Score = 0;
	ghost2Score = 0;
	ghost3Score = 0;

	ghostTexture1.loadFromFile("sprites\\enemies\\ghost1.1.png");
	ghostTexture2.loadFromFile("sprites\\enemies\\ghost1.2.png");
	ghostTexture3.loadFromFile("sprites\\enemies\\ghost1.3.png");
	ghost1Sprite.setTexture(ghostTexture1);
	ghost2Sprite.setTexture(ghostTexture1);
	ghost3Sprite.setTexture(ghostTexture1);
	ghost4Sprite.setTexture(ghostTexture1);
	ghost5Sprite.setTexture(ghostTexture1);
	ghost6Sprite.setTexture(ghostTexture1);
	ghost7Sprite.setTexture(ghostTexture2);
	ghost8Sprite.setTexture(ghostTexture2);
	ghost9Sprite.setTexture(ghostTexture2);
	ghost10Sprite.setTexture(ghostTexture2);
	ghost11Sprite.setTexture(ghostTexture2);
	ghost12Sprite.setTexture(ghostTexture3);
	ghost13Sprite.setTexture(ghostTexture3);
	ghost14Sprite.setTexture(ghostTexture3);
	ghost15Sprite.setTexture(ghostTexture3);
	ghostRect.width = ghostTexture1.getSize().x / 3;
	ghostRect.height = ghostTexture1.getSize().y / 1;
	switchTime = 0.3f;

	shakeTime = 0.1f;
	shakeMagnitude = 0.1f;

	broomItemTexture.loadFromFile("sprites\\items\\broom-night.png");
	broomItemSprite.setTexture(broomItemTexture);
	broomItemSprite.setOrigin(broomItemTexture.getSize().x / 2.0f, broomItemTexture.getSize().y / 2.0f);
	
	weapon1Texture.loadFromFile("sprites\\items\\lighter.png");
	weapon1Sprite.setTexture(weapon1Texture);
	weapon1Sprite.setOrigin(weapon1Texture.getSize().x / 2.0f, weapon1Texture.getSize().y / 2.0f);
	weapon1Sprite.setScale(1.2f, 1.2f);

	weapon2Texture.loadFromFile("sprites\\items\\spitball.png");
	weapon2Sprite.setTexture(weapon2Texture);
	weapon2Sprite.setOrigin(weapon2Texture.getSize().x / 2.0f, weapon2Texture.getSize().y / 2.0f);
	weapon2Sprite.setScale(1.2f, 1.2f);

	weapon3Texture.loadFromFile("sprites\\items\\stapler.png");
	weapon3Sprite.setTexture(weapon3Texture);
	weapon3Sprite.setOrigin(weapon3Texture.getSize().x / 2.0f, weapon3Texture.getSize().y / 2.0f);
	weapon3Sprite.setScale(1.2f, 1.2f);

	ghostDeathBuffer.loadFromFile("sprites\\sfx\\ghost-death.ogg");
	ghostDeathSFX.setBuffer(ghostDeathBuffer);
	shootBuffer.loadFromFile("sprites\\sfx\\gun-laser.ogg");
	shootSFX.setBuffer(shootBuffer);

	arrowTex.loadFromFile("sprites\\ui\\guide-arrow.png");
	arrowSprite.setTexture(arrowTex);
	currentImageArrow.x = 0;
	arrowRect.width = arrowTex.getSize().x / 4;
	arrowRect.height = arrowTex.getSize().y / 1;
	switchTimeArrow = 0.2f;

	levelBuffer.loadFromFile("sprites\\sfx\\levelcomplete.ogg");
	levelSFX.setBuffer(levelBuffer);

	health1 = 1;
	health2 = 1;
	health3 = 1;
	health4 = 1;
	health5 = 2;
	health6 = 2;

	health7 = 2;
	health8 = 2;
	health9 = 2;
	health10 = 3;
	health11 = 3;

	health12 = 4;
	health13 = 3;
	health14 = 3;
	health15 = 3;

	speed1 = 1.5;
	speed2 = 1.5;
	speed3 = 1.5;
	speed4 = 1.5;
	speed5 = 1.5;
	speed6 = 1.5;
	speed7 = 1.5;
	speed8 = 1.5;
	speed9 = 1.5;
	speed10 = 1.5;
	speed11 = 1.5;
	speed12 = 1.5;
	speed13 = 1.5;
	speed14 = 1.5;
	speed15 = 1.5;

	initPlayer();
}

HMNight::~HMNight() {

}

Vector2f lerp2(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void HMNight::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	score1.setCharacterSize(20);
	score1.setOutlineColor(Color::Black);
	score1.setOutlineThickness(3);

	score2.setCharacterSize(20);
	score2.setOutlineColor(Color::Black);
	score2.setOutlineThickness(3);

	score3.setCharacterSize(20);
	score3.setOutlineColor(Color::Black);
	score3.setOutlineThickness(3);

	arrowSprite.setPosition(2515, 130);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(330, 230);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	ghost1Sprite.setPosition(800, 300); //
	ghost1Sprite.setScale(1.75f, 1.75f);
	ghost2Sprite.setPosition(-300, 250); //
	ghost2Sprite.setScale(1.75f, 1.75f);
	ghost3Sprite.setPosition(1000, 200); //
	ghost3Sprite.setScale(1.75f, 1.75f);
	ghost4Sprite.setPosition(-300, 100); //
	ghost4Sprite.setScale(1.75f, 1.75f);
	ghost5Sprite.setPosition(800, 50); //
	ghost5Sprite.setScale(1.75f, 1.75f);
	ghost6Sprite.setPosition(-500, 250); //
	ghost6Sprite.setScale(1.75f, 1.75f);
	ghost7Sprite.setPosition(1500, 300); // 
	ghost7Sprite.setScale(1.75f, 1.75f);
	ghost8Sprite.setPosition(1700, 100); // 
	ghost8Sprite.setScale(1.75f, 1.75f);
	ghost9Sprite.setPosition(-600, 100); // 
	ghost9Sprite.setScale(1.75f, 1.75f);
	ghost10Sprite.setPosition(1700, 250); //
	ghost10Sprite.setScale(1.75f, 1.75f);
	ghost11Sprite.setPosition(1900, 50); //
	ghost11Sprite.setScale(1.75f, 1.75f);
	ghost12Sprite.setPosition(2300, 1000); //
	ghost12Sprite.setScale(1.75f, 1.75f);
	ghost13Sprite.setPosition(1500, -800); //
	ghost13Sprite.setScale(1.75f, 1.75f);
	ghost14Sprite.setPosition(1500, -300); //
	ghost14Sprite.setScale(1.75f, 1.75f);
	ghost15Sprite.setPosition(1500, 500); //
	ghost15Sprite.setScale(1.75f, 1.75f);

	projectile.setSize(Vector2f(5.0f, 2.0f));
	projectile.setFillColor(Color::Yellow);

	broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);

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

	updateTextPos();
}

void HMNight::disableGhosts() {
	showGhost1 = false;
	showGhost2 = false;
	showGhost3 = false;
	showGhost4 = false;
	showGhost5 = false;
	showGhost6 = false;
	showGhost7 = false;
	showGhost8 = false;
	showGhost9 = false;
	showGhost10 = false;
	showGhost11 = false;
	showGhost12 = false;
	showGhost13 = false;
	showGhost14 = false;
	showGhost15 = false;

	ghost1Sprite.setPosition(9000, 9000);
	ghost2Sprite.setPosition(9000, 9000);
	ghost3Sprite.setPosition(9000, 9000);
	ghost4Sprite.setPosition(9000, 9000);
	ghost5Sprite.setPosition(9000, 9000);
	ghost6Sprite.setPosition(9000, 9000);
	ghost7Sprite.setPosition(9000, 9000);
	ghost8Sprite.setPosition(9000, 9000);
	ghost9Sprite.setPosition(9000, 9000);
	ghost10Sprite.setPosition(9000, 9000);
	ghost11Sprite.setPosition(9000, 9000);
	ghost12Sprite.setPosition(9000, 9000);
	ghost13Sprite.setPosition(9000, 9000);
	ghost14Sprite.setPosition(9000, 9000);
	ghost15Sprite.setPosition(9000, 9000);
}

void HMNight::showTask1() {
	task1.setString("!\tEliminate ghosts");
	task1.setCharacterSize(25);
	task1.setOutlineColor(Color::Black);
	task1.setOutlineThickness(3);
	window.setView(window.getDefaultView());
	window.draw(task1);
}

void HMNight::showTask2() {
	task2.setString("!\tGo inside the room");
	task2.setCharacterSize(25);
	task2.setOutlineColor(Color::Black);
	task2.setOutlineThickness(3);
	window.setView(camera);
	arrowSprite.setTextureRect(arrowRect);
	window.draw(arrowSprite);
	window.setView(window.getDefaultView());
	window.draw(task2);
	disableGhosts();
}

void HMNight::showTask3() {
	task3.setString("!\tGo Home");
	task3.setCharacterSize(25);
	task3.setOutlineColor(Color::Black);
	task3.setOutlineThickness(3);
	window.setView(camera);
	arrowSprite.setTextureRect(arrowRect);
	window.draw(arrowSprite);
	window.setView(window.getDefaultView());
	window.draw(task3);
}

void HMNight::showTask4() {
	task4.setString("!\tGo to the CBA building");
	task4.setCharacterSize(25);
	task4.setOutlineColor(Color::Black);
	task4.setOutlineThickness(3);
	window.setView(camera);
	arrowSprite.setTextureRect(arrowRect);
	window.draw(arrowSprite);
	window.setView(window.getDefaultView());
	window.draw(task4);
}

void HMNight::handleInput() {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}
	}

	if (playerSprite.getGlobalBounds().intersects(ghost1Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost2Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost3Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost4Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost5Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost6Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost7Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost8Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost9Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost10Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost11Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost12Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost13Sprite.getGlobalBounds()) ||
		playerSprite.getGlobalBounds().intersects(ghost14Sprite.getGlobalBounds()) || 
		playerSprite.getGlobalBounds().intersects(ghost15Sprite.getGlobalBounds())) {
		hp.damage(0.5);
	}

	float moveSpeed = 3.5;

	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		moveSpeed += 2;
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dPressed = true;
		aPressed = false;
		//broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);
		if (weapon1Show) {
			weapon1Sprite.setPosition(playerSprite.getPosition().x + 12, playerSprite.getPosition().y + 7.5);
			weapon1Sprite.move(moveSpeed, 0);
		}
		if (weapon2Show) {
			weapon2Sprite.setPosition(playerSprite.getPosition().x + 12, playerSprite.getPosition().y + 7.5);
			weapon2Sprite.move(moveSpeed, 0);
		}
		if (weapon3Show) {
			weapon3Sprite.setPosition(playerSprite.getPosition().x + 12, playerSprite.getPosition().y + 7.5);
			weapon3Sprite.move(moveSpeed, 0);
		}
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		playerSprite.move(moveSpeed, 0);
		//broomItemSprite.move(moveSpeed, 0);
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
		//broomItemSprite.setPosition(playerSprite.getPosition().x - 4, playerSprite.getPosition().y + 7.5);
		if (weapon1Show) {
			weapon1Sprite.setPosition(playerSprite.getPosition().x - 12, playerSprite.getPosition().y + 7.5);
			weapon1Sprite.move(-moveSpeed, 0);
		}
		if (weapon2Show) {
			weapon2Sprite.setPosition(playerSprite.getPosition().x - 12, playerSprite.getPosition().y + 7.5);
			weapon2Sprite.move(-moveSpeed, 0);
		}
		if (weapon3Show) {
			weapon3Sprite.setPosition(playerSprite.getPosition().x - 12, playerSprite.getPosition().y + 7.5);
			weapon3Sprite.move(-moveSpeed, 0);
		}
		int pos = 0;
		pos = (int)playerSprite.getPosition().x / 35 % 4;
		pos = pos * 32;
		playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		playerSprite.move(-moveSpeed, 0);
		//broomItemSprite.move(-moveSpeed, 0);
	}

	if (Keyboard::isKeyPressed(Keyboard::S)) {
		int pos = 0;
		pos = (int)playerSprite.getPosition().y / 35 % 4;
		pos = pos * 32;
		if (weapon1Show) {
			weapon1Sprite.move(0, moveSpeed);
		}
		if (weapon2Show) {
			weapon2Sprite.move(0, moveSpeed);
		}
		if (weapon3Show) {
			weapon3Sprite.move(0, moveSpeed);
		}
		if (dPressed) {
			playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		}
		if (aPressed) {
			playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		}
		playerSprite.move(0, moveSpeed);
		//broomItemSprite.move(0, moveSpeed);
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		int pos = 0;
		pos = (int)playerSprite.getPosition().y / 35 % 4;
		pos = pos * 32;
		if (weapon1Show) {
			weapon1Sprite.move(0, -moveSpeed);
		}
		if (weapon2Show) {
			weapon2Sprite.move(0, -moveSpeed);
		}
		if (weapon3Show) {
			weapon3Sprite.move(0, -moveSpeed);
		}
		if (dPressed) {
			playerSprite.setTextureRect(IntRect(pos, 0, 32, 32));
		}
		if (aPressed) {
			playerSprite.setTextureRect(IntRect(pos, 32, 32, 32));
		}
		playerSprite.move(0, -moveSpeed);
		//broomItemSprite.move(0, -moveSpeed);
	}

	if (Keyboard::isKeyPressed(Keyboard::Space) && !projectileShot || Mouse::isButtonPressed(Mouse::Left) && !projectileShot) {
		//cout << "projectile shot false\n";
		shootSFX.pause();
		shootSFX.play();
		shakeClock.restart();
		isShaking = true;
		//projectileDirection = mousePos - broomItemSprite.getPosition();
		if (weapon1Show) {
			projectileDirection = mousePos - weapon1Sprite.getPosition();
		}
		if (weapon2Show) {
			projectileDirection = mousePos - weapon2Sprite.getPosition();
		}
		if (weapon3Show) {
			projectileDirection = mousePos - weapon3Sprite.getPosition();
		}
		float length = sqrt(projectileDirection.x * projectileDirection.x + projectileDirection.y * projectileDirection.y);
		projectileDirection /= length;
		if (dPressed) {
			if (weapon1Show) {
				projectile.setPosition(weapon1Sprite.getPosition().x + 10.0f, weapon1Sprite.getPosition().y - 5.0f);
			}
			if (weapon2Show) {
				projectile.setPosition(weapon2Sprite.getPosition().x + 10.0f, weapon2Sprite.getPosition().y - 5.0f);
			}
			if (weapon3Show) {
				projectile.setPosition(weapon3Sprite.getPosition().x + 10.0f, weapon3Sprite.getPosition().y - 5.0f);
			}
			//projectile.setPosition(broomItemSprite.getPosition().x + 10.0f, broomItemSprite.getPosition().y - 5.0f);
		}
		if (aPressed) {
			if (weapon1Show) {
				projectile.setPosition(weapon1Sprite.getPosition().x - 20.0f, weapon1Sprite.getPosition().y - 5.0f);
			}
			if (weapon2Show) {
				projectile.setPosition(weapon2Sprite.getPosition().x - 20.0f, weapon2Sprite.getPosition().y - 5.0f);
			}
			if (weapon3Show) {
				projectile.setPosition(weapon3Sprite.getPosition().x - 20.0f, weapon3Sprite.getPosition().y - 5.0f);
			}
			//projectile.setPosition(broomItemSprite.getPosition().x - 20.0f, broomItemSprite.getPosition().y - 5.0f);
		}
		projectileShot = true;
	}

	float firerate = cooldown.getElapsedTime().asSeconds();

	if (projectileShot) {
		//cout << "projectile shot true\n";
		float projectileSpeed = 50.0f;
		if (weapon3Show) {
			if (firerate < 0.65f) {
				projectile.move(projectileDirection * projectileSpeed);
			}
			if (firerate > 0.65f) {
				shootSFX.stop();
				projectileShot = false;
				cooldown.restart();
				projectile.setPosition(9000, 9000);
			}
		}
		else {
			if (firerate < 0.35f) {
				projectile.move(projectileDirection * projectileSpeed);
			}
			if (firerate > 0.35f) {
				shootSFX.stop();
				projectileShot = false;
				cooldown.restart();
				projectile.setPosition(9000, 9000);
			}
		}
	}

	//
	if (bossDead && playerSprite.getPosition().x <= 370 && playerSprite.getPosition().x >= -20 && playerSprite.getPosition().y <= 440 && playerSprite.getPosition().y >= 100) {
		dialogue = true;
	}

	// 600 470 - 750 550
	if (playerSprite.getPosition().x <= 750 && playerSprite.getPosition().x >= 600 && playerSprite.getPosition().y <= 550 && playerSprite.getPosition().y >= 450 && levelComplete3) {
		goingHM2nd = true;
	}

	//2515 130
	if (playerSprite.getPosition().x <= 2570 && playerSprite.getPosition().x >= 2480 && playerSprite.getPosition().y <= 160 && playerSprite.getPosition().y >= 100 && levelComplete3 && Keyboard::isKeyPressed(Keyboard::E)) {
		goingRoom1 = true;
	}

	// 2865
	if (playerSprite.getPosition().x <= 3000 && playerSprite.getPosition().x >= 2860 && playerSprite.getPosition().y <= 550 && playerSprite.getPosition().y >= 100 && levelComplete3 && bossDead && task4Show) {
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

	Vector2f playerPos = playerSprite.getPosition();
	Vector2f catPos = npc.catPos2();

	float distance = sqrt((playerPos.x - catPos.x) * (playerPos.x - catPos.x) + (playerPos.y - catPos.y) * (playerPos.y - catPos.y));

	if (distance <= 60.0f && Keyboard::isKeyPressed(Keyboard::E)) {
		dialogueBoolCat = true;
	}

	if (distance >= 90.0f && dialogueBoolCat) {
		dialogueBox.farFromPlayer(true);
		dialogueBoolCat = false;
	}
}

void HMNight::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1000, camera.getCenter().y - window.getSize().y / 1.80f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1000, camera.getCenter().y - window.getSize().y / 1.80f);
	task3.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1100, camera.getCenter().y - window.getSize().y / 1.80f);
	task4.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 790, camera.getCenter().y - window.getSize().y / 1.80f);
	score1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1150, camera.getCenter().y - window.getSize().y / 2.50f);
	score2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1150, camera.getCenter().y - window.getSize().y / 2.70f);
	score3.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1150, camera.getCenter().y - window.getSize().y / 2.90f);
}

void HMNight::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp2(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void HMNight::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	isChasing = true;

	if (weapon1Show) {
		broomToMouse = mousePos - weapon1Sprite.getPosition();
	}
	if (weapon2Show) {
		broomToMouse = mousePos - weapon2Sprite.getPosition();
	}
	if (weapon3Show) {
		broomToMouse = mousePos - weapon3Sprite.getPosition();
	}
	//broomToMouse = mousePos - broomItemSprite.getPosition();
	float angle = atan2(broomToMouse.y, broomToMouse.x) * 180.0f / 3.14159265f;
	if (weapon1Show) {
		weapon1Sprite.setRotation(angle);
	}
	if (weapon2Show) {
		weapon2Sprite.setRotation(angle);
	}
	if (weapon3Show) {
		weapon3Sprite.setRotation(angle);
	}
	//broomItemSprite.setRotation(angle);

	if (isShaking) {
		float elapsedShakeTime = shakeClock.getElapsedTime().asSeconds();
		if (elapsedShakeTime < shakeTime) {
			float offsetX = (rand() % 200 - 100) * shakeMagnitude * (1.0f - elapsedShakeTime / shakeTime);
			float offsetY = (rand() % 200 - 100) * shakeMagnitude * (1.0f - elapsedShakeTime / shakeTime);

			// Apply the displacement to the view
			camera.move(offsetX, offsetY);
		}
		else {
			// Stop shaking after the specified duration
			isShaking = false;
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost1Sprite.getGlobalBounds())) {
		//showGhost1 = false;
		healthCount.showHealth(ghost1Sprite.getPosition(), health1);
		health1 -= 1;
		if (health1 <= 0) {
			ghost1Score += 1;
			ghost1Sprite.setPosition(-1000, 200);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health1 = 1;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost2Sprite.getGlobalBounds())) {
		//showGhost2 = false;
		healthCount.showHealth(ghost2Sprite.getPosition(), health2);
		health2 -= 1;
		if (health2 <= 0) {
			ghost1Score += 1;
			ghost2Sprite.setPosition(-1200, 100);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health2 = 1;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost3Sprite.getGlobalBounds())) {
		//showGhost3 = false;
		healthCount.showHealth(ghost3Sprite.getPosition(), health3);
		health3 -= 1;
		if (health3 <= 0) {
			ghost1Score += 1;
			ghost3Sprite.setPosition(-700, 300);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health3 = 1;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost4Sprite.getGlobalBounds())) {
		//showGhost4 = false;
		healthCount.showHealth(ghost4Sprite.getPosition(), health4);
		health4 -= 1;
		if (health4 <= 0) {
			ghost1Score += 1;
			ghost4Sprite.setPosition(500, -500);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health4 = 1;
			healthCount.disableCount();
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost5Sprite.getGlobalBounds())) {
		//showGhost5 = false;
		healthCount.showHealth(ghost5Sprite.getPosition(), health5);
		if (weapon3Show) {
			health5 -= 2;
		}
		else {
			health5 -= 1;
		}
		if (health5 <= 0) {
			ghost1Score += 1;
			ghost5Sprite.setPosition(1500, 1000);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health5 = 2;
			healthCount.disableCount();
			slowed5 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start5 = true;
		}
		if (weapon2Show) {
			slowed5 = true;
		}
	}

	if (!slowed5) {
		c5.restart();
		speed5 = 1.5;
		ghost5Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed5 = 1.0;
		ghost5Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e5 = c5.getElapsedTime().asSeconds();

	if (e5 >= 1) {
		speed5 = 1.5;
		slowed5 = false;
	}

	if (!start5) {
		clock5.restart();
	}

	float elapsedTime5 = clock5.getElapsedTime().asSeconds();

	if (elapsedTime5 >= 0.8) {
		cout << elapsedTime5 << endl;
		healthCount.showHealth(ghost5Sprite.getPosition(), health5);
		health5 -= 1;
		start5 = false;
		if (health5 <= 0) {
			ghost1Score += 1;
			ghost5Sprite.setPosition(1500, 1000);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health5 = 2;
			healthCount.disableCount();
			speed5 = 1.5;
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost6Sprite.getGlobalBounds())) {
		//showGhost6 = false;
		healthCount.showHealth(ghost6Sprite.getPosition(), health6);
		if (weapon3Show) {
			health6 -= 2;
		}
		else {
			health6 -= 1;
		}
		if (health6 <= 0) {
			ghost1Score += 1;
			ghost6Sprite.setPosition(1600, 800);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health6 = 2;
			healthCount.disableCount();
			slowed6 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start6 = true;
		}
		if (weapon2Show) {
			slowed6 = true;
		}
	}

	if (!slowed6) {
		c6.restart();
		speed6 = 1.5;
		ghost6Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed6 = 1.0;
		ghost6Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e6 = c6.getElapsedTime().asSeconds();

	if (e6 >= 1) {
		speed6 = 1.5;
		slowed6 = false;
	}

	if (!start6) {
		clock6.restart();
	}

	float elapsedTime6 = clock6.getElapsedTime().asSeconds();

	if (elapsedTime6 >= 0.8) {
		cout << elapsedTime6 << endl;
		healthCount.showHealth(ghost6Sprite.getPosition(), health6);
		health6 -= 1;
		start6 = false;
		if (health6 <= 0) {
			ghost1Score += 1;
			ghost6Sprite.setPosition(1600, 800);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health6 = 2;
			healthCount.disableCount();
			speed6 = 1.5;
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost7Sprite.getGlobalBounds())) {
		//showGhost7 = false;
		healthCount.showHealth(ghost7Sprite.getPosition(), health7);
		if (weapon3Show) {
			health7 -= 2;
		}
		else {
			health7 -= 1;
		}
		if (health7 <= 0) {
			ghost2Score += 1;
			ghost7Sprite.setPosition(2000, 700);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health7 = 2;
			healthCount.disableCount();
			slowed7 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start7 = true;
		}
		if (weapon2Show) {
			slowed7 = true;
		}
	}

	if (!slowed7) {
		c7.restart();
		speed7 = 1.5;
		ghost7Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed7 = 1.0;
		ghost7Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e7 = c7.getElapsedTime().asSeconds();

	if (e7 >= 1) {
		speed7 = 1.5;
		slowed7 = false;
	}

	if (!start7) {
		clock7.restart();
	}

	float elapsedTime7 = clock7.getElapsedTime().asSeconds();

	if (elapsedTime7 >= 0.8) {
		cout << elapsedTime7 << endl;
		healthCount.showHealth(ghost7Sprite.getPosition(), health7);
		health7 -= 1;
		start7 = false;
		if (health7 <= 0) {
			ghost2Score += 1;
			ghost7Sprite.setPosition(2000, 700);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health7 = 2;
			healthCount.disableCount();
			speed7 = 1.5;
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost8Sprite.getGlobalBounds())) {
		//showGhost8 = false;
		healthCount.showHealth(ghost8Sprite.getPosition(), health8);
		if (weapon3Show) {
			health8 -= 2;
		}
		else {
			health8 -= 1;
		}
		if (health8 <= 0) {
			ghost2Score += 1;
			ghost8Sprite.setPosition(2000, -300);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health8 = 2;
			healthCount.disableCount();
			slowed8 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start8 = true;
		}
		if (weapon2Show) {
			slowed8 = true;
		}
	}

	if (!slowed8) {
		c8.restart();
		speed8 = 1.5;
		ghost8Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed8 = 1.0;
		ghost8Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e8 = c8.getElapsedTime().asSeconds();

	if (e8 >= 1) {
		speed8 = 1.5;
		slowed8 = false;
	}

	if (!start8) {
		clock8.restart();
	}

	float elapsedTime8 = clock8.getElapsedTime().asSeconds();

	if (elapsedTime8 >= 0.8) {
		healthCount.showHealth(ghost8Sprite.getPosition(), health8);
		health8 -= 1;
		start8 = false;
		if (health8 <= 0) {
			ghost2Score += 1;
			ghost8Sprite.setPosition(2000, -300);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health8 = 2;
			healthCount.disableCount();
			speed8 = 1.5;
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost9Sprite.getGlobalBounds())) {
		//showGhost9 = false;
		healthCount.showHealth(ghost9Sprite.getPosition(), health9);
		if (weapon3Show) {
			health9 -= 2;
		}
		else {
			health9 -= 1;
		}
		if (health9 <= 0) {
			ghost2Score += 1;
			ghost9Sprite.setPosition(400, -300);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health9 = 2;
			healthCount.disableCount();
			slowed9 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start9 = true;
		}
		if (weapon2Show) {
			if (health9 <= 0) {
				slowed9 = false;
			}
		}
	}

	if (!slowed9) {
		c9.restart();
		speed9 = 1.5;
		ghost9Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed9 = 1.0;
		ghost9Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e9 = c9.getElapsedTime().asSeconds();

	if (e9 >= 1) {
		speed9 = 1.5;
		slowed9 = false;
	}

	if (!start9) {
		clock9.restart();
	}

	float elapsedTime9 = clock9.getElapsedTime().asSeconds();

	if (elapsedTime9 >= 0.8) {
		healthCount.showHealth(ghost9Sprite.getPosition(), health9);
		health9 -= 1;
		start9 = false;
		if (health9 <= 0) {
			ghost2Score += 1;
			ghost9Sprite.setPosition(400, -300);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health9 = 2;
			healthCount.disableCount();
			speed9 = 1.5;
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost10Sprite.getGlobalBounds())) {
		//showGhost10 = false;
		healthCount.showHealth(ghost10Sprite.getPosition(), health10);
		if (weapon3Show) {
			health10 -= 2;
		}
		else {
			health10 -= 1;
		}
		if (health10 <= 0) {
			ghost2Score += 1;
			ghost10Sprite.setPosition(3500, -100);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health10 = 3;
			healthCount.disableCount();
			slowed10 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start10 = true;
		}
		if (weapon2Show) {
			if (health10 <= 0) {
				slowed10 = false;
			}
		}
	}

	if (!slowed10) {
		c10.restart();
		speed10 = 1.5;
		ghost10Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed10 = 1.0;
		ghost10Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e10 = c10.getElapsedTime().asSeconds();

	if (e10 >= 1) {
		speed10 = 1.5;
		slowed10 = false;
	}

	if (!start10) {
		clock10.restart();
	}

	float elapsedTime10 = clock10.getElapsedTime().asSeconds();

	if (elapsedTime10 >= 0.8) {
		healthCount.showHealth(ghost10Sprite.getPosition(), health10);
		health10 -= 1;
		start10 = false;
		if (health10 <= 0) {
			ghost2Score += 1;
			ghost10Sprite.setPosition(3500, -100);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health10 = 3;
			healthCount.disableCount();
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost11Sprite.getGlobalBounds())) {
		//showGhost11 = false;
		healthCount.showHealth(ghost11Sprite.getPosition(), health11);
		if (weapon3Show) {
			health11 -= 2;
		}
		else {
			health11 -= 1;
		}
		if (health11 <= 0) {
			ghost2Score += 1;
			ghost11Sprite.setPosition(2700, -200);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health11 = 3;
			healthCount.disableCount();
			slowed11 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start11 = true;
		}
		if (weapon2Show) {
			slowed11 = true;
		}
	}

	if (!slowed11) {
		c11.restart();
		speed11 = 1.5;
		ghost11Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed11 = 1.0;
		ghost11Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e11 = c11.getElapsedTime().asSeconds();

	if (e11 >= 1) {
		speed11 = 1.5;
		slowed11 = false;
	}

	if (!start11) {
		clock11.restart();
	}

	float elapsedTime11 = clock11.getElapsedTime().asSeconds();

	if (elapsedTime11 >= 0.8) {
		healthCount.showHealth(ghost11Sprite.getPosition(), health11);
		health11 -= 1;
		start11 = false;
		if (health11 <= 0) {
			ghost2Score += 1;
			ghost11Sprite.setPosition(2700, -200);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health11 = 3;
			healthCount.disableCount();
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost12Sprite.getGlobalBounds())) {
		//showGhost12 = false;
		healthCount.showHealth(ghost12Sprite.getPosition(), health12);
		if (weapon3Show) {
			health12 -= 2;
		}
		else {
			health12 -= 1;
		}
		if (health12 <= 0) {
			ghost3Score += 1;
			ghost12Sprite.setPosition(2000, 1200);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health12 = 4;
			healthCount.disableCount();
			slowed12 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start12 = true;
		}
		if (weapon2Show) {
			slowed12 = true;
		}
	}

	if (!slowed12) {
		c12.restart();
		speed12 = 1.5;
		ghost12Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed12 = 1.0;
		ghost12Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e12 = c12.getElapsedTime().asSeconds();

	if (e12 >= 1) {
		speed12 = 1.5;
		slowed12 = false;
	}

	if (!start12) {
		clock12.restart();
	}

	float elapsedTime12 = clock12.getElapsedTime().asSeconds();

	if (elapsedTime12 >= 0.8) {
		healthCount.showHealth(ghost12Sprite.getPosition(), health12);
		health12 -= 1;
		start12 = false;
		if (health12 <= 0) {
			ghost3Score += 1;
			ghost12Sprite.setPosition(2000, 1200);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health12 = 4;
			healthCount.disableCount();
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost13Sprite.getGlobalBounds())) {
		//showGhost13 = false;
		healthCount.showHealth(ghost13Sprite.getPosition(), health13);
		if (weapon3Show) {
			health13 -= 2;
		}
		else {
			health13 -= 1;
		}
		if (health13 <= 0) {
			ghost3Score += 1;
			ghost13Sprite.setPosition(1500, -1000);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health13 = 3;
			healthCount.disableCount();
			slowed13 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start13 = true;
		}
		if (weapon2Show) {
			slowed13 = true;
		}
	}

	if (!slowed13) {
		c13.restart();
		speed13 = 1.5;
		ghost13Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed13 = 1.0;
		ghost13Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e13 = c13.getElapsedTime().asSeconds();

	if (e13 >= 1) {
		speed13 = 1.5;
		slowed13 = false;
	}

	if (!start13) {
		clock13.restart();
	}

	float elapsedTime13 = clock13.getElapsedTime().asSeconds();

	if (elapsedTime13 >= 0.8) {
		cout << elapsedTime13 << endl;
		healthCount.showHealth(ghost13Sprite.getPosition(), health13);
		health13 -= 1;
		start13 = false;
		if (health13 <= 0) {
			ghost3Score += 1;
			ghost13Sprite.setPosition(1500, -1000);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health13 = 3;
			healthCount.disableCount();
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost14Sprite.getGlobalBounds())) {
		//showGhost13 = false;
		healthCount.showHealth(ghost14Sprite.getPosition(), health14);
		if (weapon3Show) {
			health14 -= 2;
		}
		else {
			health14 -= 1;
		}
		if (health14 <= 0) {
			ghost3Score += 1;
			ghost14Sprite.setPosition(1500, -600);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health14 = 3;
			healthCount.disableCount();
			slowed14 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start14 = true;
		}
		if (weapon2Show) {
			slowed14 = true;
		}
	}

	if (!slowed14) {
		c14.restart();
		speed14 = 1.5;
		ghost14Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed14 = 1.0;
		ghost14Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e14 = c14.getElapsedTime().asSeconds();

	if (e14 >= 1) {
		speed14 = 1.5;
		slowed14 = false;
	}

	if (!start14) {
		clock14.restart();
	}

	float elapsedTime14 = clock14.getElapsedTime().asSeconds();

	if (elapsedTime14 >= 0.8) {
		cout << elapsedTime14 << endl;
		healthCount.showHealth(ghost14Sprite.getPosition(), health14);
		health14 -= 1;
		start14 = false;
		if (health14 <= 0) {
			ghost3Score += 1;
			ghost14Sprite.setPosition(1500, -600);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health14 = 3;
			healthCount.disableCount();
		}
	}

	if (projectileShot && projectile.getGlobalBounds().intersects(ghost15Sprite.getGlobalBounds())) {
		//showGhost13 = false;
		healthCount.showHealth(ghost15Sprite.getPosition(), health15);
		if (weapon3Show) {
			health15 -= 2;
		}
		else {
			health15 -= 1;
		}
		if (health15 <= 0) {
			ghost3Score += 1;
			ghost15Sprite.setPosition(2000, 500);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health15 = 3;
			healthCount.disableCount();
			slowed15 = false;
		}
		projectiles.clear();
		projectile.setPosition(9000, 9000);
		if (weapon1Show) {
			start15 = true;
		}
		if (weapon2Show) {
			slowed15 = true;
		}
	}

	if (!slowed15) {
		c15.restart();
		speed15 = 1.5;
		ghost15Sprite.setColor(Color(255, 255, 255, 255));
	}
	else {
		speed15 = 1.0;
		ghost15Sprite.setColor(Color(85, 160, 255, 200));
	}

	float e15 = c15.getElapsedTime().asSeconds();

	if (e15 >= 1) {
		speed15 = 1.5;
		slowed15 = false;
	}

	if (!start15) {
		clock15.restart();
	}

	float elapsedTime15 = clock15.getElapsedTime().asSeconds();

	if (elapsedTime15 >= 0.8) {
		cout << elapsedTime15 << endl;
		healthCount.showHealth(ghost15Sprite.getPosition(), health15);
		health15 -= 1;
		start15 = false;
		if (health15 <= 0) {
			ghost3Score += 1;
			ghost15Sprite.setPosition(2000, 500);
			ghostDeathSFX.pause();
			ghostDeathSFX.play();
			health15 = 3;
			healthCount.disableCount();
		}
	}

	// 5 3 1
	if (ghost1Score <= 5 && !levelComplete1) {
		score1.setString("White: " + to_string(ghost1Score) + " / 5");
	}

	if (ghost2Score <= 3 && !levelComplete1) {
		score2.setString("Blue: " + to_string(ghost2Score) + " / 3");
	}

	if (ghost3Score <= 1 && !levelComplete1) {
		score3.setString("Black: " + to_string(ghost3Score) + " / 1");
	}

	if (ghost1Score >= 5 && !levelComplete1) {
		score1.setString("White: 5 / 5");
		score1.setFillColor(Color::Green);
	}

	if (ghost2Score >= 3 && !levelComplete1) {
		score2.setString("Blue: 3 / 3");
		score2.setFillColor(Color::Green);
	}

	if (ghost3Score >= 1 && !levelComplete1) {
		score3.setString("Black: 1 / 1");
		score3.setFillColor(Color::Green);
	}

	//7 5 3
	if (ghost1Score <= 7 && !levelComplete2 && levelComplete1) {
		score1.setString("White: " + to_string(ghost1Score) + " / 7");
	}

	if (ghost2Score <= 5 && !levelComplete2 && levelComplete1) {
		score2.setString("Blue: " + to_string(ghost2Score) + " / 5");
	}

	if (ghost3Score <= 3 && !levelComplete2 && levelComplete1) {
		score3.setString("Black: " + to_string(ghost3Score) + " / 3");
	}

	if (ghost1Score >= 7 && !levelComplete2 && levelComplete1) {
		score1.setString("White: 7 / 7");
		score1.setFillColor(Color::Green);
	}

	if (ghost2Score >= 5 && !levelComplete2 && levelComplete1) {
		score2.setString("Blue: 5 / 5");
		score2.setFillColor(Color::Green);
	}

	if (ghost3Score >= 3 && !levelComplete2 && levelComplete1) {
		score3.setString("Black: 3 / 3");
		score3.setFillColor(Color::Green);
	}

	//10 8 5
	if (ghost1Score <= 10 && !levelComplete3 && levelComplete2) {
		score1.setString("White: " + to_string(ghost1Score) + " / 10");
	}

	if (ghost2Score <= 8 && !levelComplete3 && levelComplete2) {
		score2.setString("Blue: " + to_string(ghost2Score) + " / 8");
	}

	if (ghost3Score <= 5 && !levelComplete3 && levelComplete2) {
		score3.setString("Black: " + to_string(ghost3Score) + " / 5");
	}

	if (ghost1Score >= 10 && !levelComplete3 && levelComplete2) {
		score1.setString("White: 10 / 10");
		score1.setFillColor(Color::Green);
	}

	if (ghost2Score >= 8 && !levelComplete3 && levelComplete2) {
		score2.setString("Blue: 8 / 8");
		score2.setFillColor(Color::Green);
	}

	if (ghost3Score >= 5 && !levelComplete3 && levelComplete2) {
		score3.setString("Black: 5 / 5");
		score3.setFillColor(Color::Green);
	}

	//5 3 1
	if (ghost1Score >= 5 && ghost2Score >= 3 && ghost3Score >= 1 && !levelComplete1 && !levelComplete3) {
		levelComplete1 = true;
		startLevel2 = true;

		ghost1Score = 0;
		ghost2Score = 0;
		ghost3Score = 0;

		score1.setFillColor(Color::White);
		score2.setFillColor(Color::White);
		score3.setFillColor(Color::White);

		levelSFX.pause();
		levelSFX.play();

		ghost1Sprite.setPosition(-1000, 200);
		ghost2Sprite.setPosition(-1200, 100);
		ghost3Sprite.setPosition(-700, 300);
		ghost4Sprite.setPosition(500, -500);
		ghost5Sprite.setPosition(1500, 1000);
		ghost6Sprite.setPosition(1600, 800);
		ghost7Sprite.setPosition(2000, 700);
		ghost8Sprite.setPosition(2000, -300);
		ghost9Sprite.setPosition(400, -300);
		ghost10Sprite.setPosition(3500, -100);
		ghost11Sprite.setPosition(2700, -200);
		ghost12Sprite.setPosition(2000, 1200);
		ghost13Sprite.setPosition(1500, -1000);
		ghost14Sprite.setPosition(1500, -800);
		ghost15Sprite.setPosition(1500, 500);
	}

	//7 5 3
	if (ghost1Score >= 7 && ghost2Score >= 5 && ghost3Score >= 3 && levelComplete1 && startLevel2 && !startLevel3 && !levelComplete3) {
		levelComplete2 = true;
		startLevel3 = true;

		ghost1Score = 0;
		ghost2Score = 0;
		ghost3Score = 0;

		score1.setFillColor(Color::White);
		score2.setFillColor(Color::White);
		score3.setFillColor(Color::White);

		levelSFX.pause();
		levelSFX.play();

		ghost1Sprite.setPosition(-1000, 200);
		ghost2Sprite.setPosition(-1200, 100);
		ghost3Sprite.setPosition(-700, 300);
		ghost4Sprite.setPosition(500, -500);
		ghost5Sprite.setPosition(1500, 1000);
		ghost6Sprite.setPosition(1600, 800);
		ghost7Sprite.setPosition(2000, 700);
		ghost8Sprite.setPosition(2000, -300);
		ghost9Sprite.setPosition(400, -300);
		ghost10Sprite.setPosition(3500, -100);
		ghost11Sprite.setPosition(2700, -200);
		ghost12Sprite.setPosition(2000, 1200);
		ghost13Sprite.setPosition(1500, -1000);
		ghost14Sprite.setPosition(1500, -800);
		ghost15Sprite.setPosition(1500, 500);
	}

	//10 8 5
	if (ghost1Score >= 10 && ghost2Score >= 8 && ghost3Score >= 5 && levelComplete2 && startLevel3 && !levelComplete3) {
		levelComplete3 = true;
		showHP = false;
		levelSFX.pause();
		levelSFX.play();
	}
}

void HMNight::animUpdate(float dt) {
	currentImage.y = 0;
	currentImageArrow.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime || totalTime >= switchTimeArrow) {
		totalTime -= switchTime;
		totalTime -= switchTimeArrow;
		currentImage.x++;
		currentImageArrow.x++;
		if (currentImage.x >= 3) {
			currentImage.x = 0;
		}
		if (currentImageArrow.x >= 4) {
			currentImageArrow.x = 0;
		}
	}

	ghostRect.left = currentImage.x * ghostRect.width;
	ghostRect.top = currentImage.y * ghostRect.height;
	arrowRect.left = currentImageArrow.x * arrowRect.width;
	arrowRect.top = currentImageArrow.y * arrowRect.height;

	if (isChasing) {
		//cout << "is chasing true" << endl;

		float angle = atan2(playerSprite.getPosition().y - ghost1Sprite.getPosition().y, playerSprite.getPosition().x - ghost1Sprite.getPosition().x);
		float x = speed1 * cos(angle);
		float y = speed1 * sin(angle);
		ghost1Sprite.move(x, y);

		float angle2 = atan2(playerSprite.getPosition().y - ghost2Sprite.getPosition().y, playerSprite.getPosition().x - ghost2Sprite.getPosition().x);
		float x2 = speed2 * cos(angle2);
		float y2 = speed2 * sin(angle2);
		ghost2Sprite.move(x2, y2);

		float angle3 = atan2(playerSprite.getPosition().y - ghost3Sprite.getPosition().y, playerSprite.getPosition().x - ghost3Sprite.getPosition().x);
		float x3 = speed3 * cos(angle3);
		float y3 = speed3 * sin(angle3);
		ghost3Sprite.move(x3, y3);

		float angle4 = atan2(playerSprite.getPosition().y - ghost4Sprite.getPosition().y, playerSprite.getPosition().x - ghost4Sprite.getPosition().x);
		float x4 = speed4 * cos(angle4);
		float y4 = speed4 * sin(angle4);
		ghost4Sprite.move(x4, y4);

		float angle5 = atan2(playerSprite.getPosition().y - ghost5Sprite.getPosition().y, playerSprite.getPosition().x - ghost5Sprite.getPosition().x);
		float x5 = speed5 * cos(angle5);
		float y5 = speed5 * sin(angle5);
		ghost5Sprite.move(x5, y5);

		float angle6 = atan2(playerSprite.getPosition().y - ghost6Sprite.getPosition().y, playerSprite.getPosition().x - ghost6Sprite.getPosition().x);
		float x6 = speed6 * cos(angle6);
		float y6 = speed6 * sin(angle6);
		ghost6Sprite.move(x6, y6);

		float angle7 = atan2(playerSprite.getPosition().y - ghost7Sprite.getPosition().y, playerSprite.getPosition().x - ghost7Sprite.getPosition().x);
		float x7 = speed7 * cos(angle7);
		float y7 = speed7 * sin(angle7);
		ghost7Sprite.move(x7, y7);

		float angle8 = atan2(playerSprite.getPosition().y - ghost8Sprite.getPosition().y, playerSprite.getPosition().x - ghost8Sprite.getPosition().x);
		float x8 = speed8 * cos(angle8);
		float y8 = speed8 * sin(angle8);
		ghost8Sprite.move(x8, y8);

		float angle9 = atan2(playerSprite.getPosition().y - ghost9Sprite.getPosition().y, playerSprite.getPosition().x - ghost9Sprite.getPosition().x);
		float x9 = speed9 * cos(angle9);
		float y9 = speed9 * sin(angle9);
		ghost9Sprite.move(x9, y9);

		float angle10 = atan2(playerSprite.getPosition().y - ghost10Sprite.getPosition().y, playerSprite.getPosition().x - ghost10Sprite.getPosition().x);
		float x10 = speed10 * cos(angle10);
		float y10 = speed10 * sin(angle10);
		ghost10Sprite.move(x10, y10);

		float angle11 = atan2(playerSprite.getPosition().y - ghost11Sprite.getPosition().y, playerSprite.getPosition().x - ghost11Sprite.getPosition().x);
		float x11 = speed11 * cos(angle11);
		float y11 = speed11 * sin(angle11);
		ghost11Sprite.move(x11, y11);

		float angle12 = atan2(playerSprite.getPosition().y - ghost12Sprite.getPosition().y, playerSprite.getPosition().x - ghost12Sprite.getPosition().x);
		float x12 = speed12 * cos(angle12);
		float y12 = speed12 * sin(angle12);
		ghost12Sprite.move(x12, y12);

		float angle13 = atan2(playerSprite.getPosition().y - ghost13Sprite.getPosition().y, playerSprite.getPosition().x - ghost13Sprite.getPosition().x);
		float x13 = speed13 * cos(angle13);
		float y13 = speed13 * sin(angle13);
		ghost13Sprite.move(x13, y13);

		float angle14 = atan2(playerSprite.getPosition().y - ghost14Sprite.getPosition().y, playerSprite.getPosition().x - ghost14Sprite.getPosition().x);
		float x14 = speed14 * cos(angle14);
		float y14 = speed14 * sin(angle14);
		ghost14Sprite.move(x14, y14);

		float angle15 = atan2(playerSprite.getPosition().y - ghost15Sprite.getPosition().y, playerSprite.getPosition().x - ghost15Sprite.getPosition().x);
		float x15 = speed15 * cos(angle15);
		float y15 = speed15 * sin(angle15);
		ghost15Sprite.move(x15, y15);
	}

	npc.catUpdate(dt);
	npc.update();
}

bool HMNight::gotoHM2nd() {
	return goingHM2nd;
}

void HMNight::playerPosFromHM2nd() {
	playerSprite.setPosition(680, 380);
}

void HMNight::goingHM2ndFalse() {
	goingHM2nd = false;
}

bool HMNight::gotoRoom1() {
	return goingRoom1;
}

void HMNight::playerPosFromRoom1() {
	playerSprite.setPosition(2525, 160);
}

void HMNight::goingRoom1False() {
	goingRoom1 = false;
}

bool HMNight::gotoCBA() {
	return goingCBA;
}

void HMNight::playerPosFromCBA() {
	playerSprite.setPosition(2855, 230);
}

void HMNight::goingCBAFalse() {
	goingCBA = false;
}

bool HMNight::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void HMNight::handleCollision(const Rectangle& rect) {
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

void HMNight::bossDefeated(bool yes) {
	if (yes) {
		showScores = false;
		bossDead = true;
	}
}

void HMNight::showDialogue() {
	dialogueBox.initDialogue("\n\tYou can't enter this area.");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		dialogue = false;
		showCat = true;
		dialogueBox.reset();
	}
}

void HMNight::catDialogueBox() {
	dialogueBox.initDialogue("Mr. Ming: \n\tIf you want to leave, there's a way in the CBA building... But beware, because \n\tthe ghosts there are frightening...  I mean meow~");
	dialogueBox.update();
	dialogueBox.render();

	if (dialogueBox.isTextComplete()) {
		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			dialogueBox.isEnterPressed(true);
			task4Show = true;
			dialogueBoolCat = false;
		}
	}
}

bool HMNight::stopBGM() {
	return levelComplete3;
}

void HMNight::setWeapon1() {
	weapon1Show = true;
}

void HMNight::setWeapon2() {
	weapon2Show = true;
}

void HMNight::setWeapon3() {
	weapon3Show = true;
}

void HMNight::restart() {
	//cout << "restart" << endl;
	playerSprite.setPosition(680, 380);
	hp.resetHealth();
	levelComplete1 = false;
	levelComplete2 = false;
	levelComplete3 = false;
	startLevel2 = false;
	startLevel3 = false;

	ghost1Score = 0;
	ghost2Score = 0;
	ghost3Score = 0;

	score1.setFillColor(Color::White);
	score2.setFillColor(Color::White);
	score3.setFillColor(Color::White);

	ghost1Sprite.setPosition(-1000, 200);
	ghost2Sprite.setPosition(-1200, 100);
	ghost3Sprite.setPosition(-700, 300);
	ghost4Sprite.setPosition(500, -500);
	ghost5Sprite.setPosition(1500, 1000);
	ghost6Sprite.setPosition(1600, 800);
	ghost7Sprite.setPosition(2000, 700);
	ghost8Sprite.setPosition(2000, -300);
	ghost9Sprite.setPosition(400, -300);
	ghost10Sprite.setPosition(3500, -100);
	ghost11Sprite.setPosition(2700, -200);
	ghost12Sprite.setPosition(2000, 1200);
	ghost13Sprite.setPosition(1500, -1000);
	ghost14Sprite.setPosition(1500, -800);
	ghost15Sprite.setPosition(1500, 500);
}

void HMNight::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	broomItemSprite.setScale(1.75f, 1.75f);
	bgSprite.setScale(1.3f, 1.3f);
	playerSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);

	if (showCat && bossDead) {
		npc.renderCat();
	}
	//window.draw(broomItemSprite);
	if (weapon1Show) {
		window.draw(weapon1Sprite);
	}
	if (weapon2Show) {
		window.draw(weapon2Sprite);
	}
	if (weapon3Show) {
		window.draw(weapon3Sprite);
	}
	window.draw(playerSprite);
	ghost1Sprite.setTextureRect(ghostRect);
	ghost2Sprite.setTextureRect(ghostRect);
	ghost3Sprite.setTextureRect(ghostRect);
	ghost4Sprite.setTextureRect(ghostRect);
	ghost5Sprite.setTextureRect(ghostRect);
	ghost6Sprite.setTextureRect(ghostRect);
	ghost7Sprite.setTextureRect(ghostRect);
	ghost8Sprite.setTextureRect(ghostRect);
	ghost9Sprite.setTextureRect(ghostRect);
	ghost10Sprite.setTextureRect(ghostRect);
	ghost11Sprite.setTextureRect(ghostRect);
	ghost12Sprite.setTextureRect(ghostRect);
	ghost13Sprite.setTextureRect(ghostRect);
	ghost14Sprite.setTextureRect(ghostRect);
	ghost15Sprite.setTextureRect(ghostRect);

	if (showGhost1) {
		window.draw(ghost1Sprite);
	}

	if (showGhost2) {
		window.draw(ghost2Sprite);
	}

	if (showGhost3) {
		window.draw(ghost3Sprite);
	}

	if (showGhost4) {
		window.draw(ghost4Sprite);
	}

	if (showGhost5) {
		window.draw(ghost5Sprite);
	}

	if (showGhost6) {
		window.draw(ghost6Sprite);
	}

	if (showGhost7) {
		window.draw(ghost7Sprite);
	}

	if (showGhost8) {
		window.draw(ghost8Sprite);
	}

	if (showGhost9) {
		window.draw(ghost9Sprite);
	}

	if (showGhost10) {
		window.draw(ghost10Sprite);
	}

	if (showGhost11) {
		window.draw(ghost11Sprite);
	}

	if (showGhost12) {
		window.draw(ghost12Sprite);
	}

	if (showGhost13) {
		window.draw(ghost13Sprite);
	}

	if (showGhost14) {
		window.draw(ghost14Sprite);
	}

	if (showGhost15) {
		window.draw(ghost15Sprite);
	}

	healthCount.render();

	window.draw(projectile);

	window.setView(window.getDefaultView());
	window.draw(quitText);
	window.draw(pauseText);

	if (showScores) {
		window.draw(score1);
		window.draw(score2);
		window.draw(score3);
	}

	if (!levelComplete3 && showScores) {
		showTask1();
	}
	else if(levelComplete3 && showScores) {
		showTask2();
	}

	if (bossDead && !showScores && !task4Show) {
		showTask3();
	}

	if (bossDead && dialogue) {
		showDialogue();
	}

	if (dialogueBoolCat && bossDead) {
		catDialogueBox();
	}

	if (task4Show) {
		showTask4();
	}

	/*if (showHP) {
		hp.update();
		hp.setHealth(100.0);
		hp.render();
	}*/

	if (hp.noHP()) {
		restart();
	}
	else if (showHP && !hp.noHP()) {
		hp.update();
		hp.setHealth(100.0);
		hp.render();
	}
}