#include "BossFight.h"
#include "HMDay.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

BossFight::BossFight(RenderWindow& window) : window(window), fadeTrans(window),
dPressed(false), aPressed(true), dampingFactor(0.3f), pauseMenu(window),
gamePaused(false), dialogueBox(window), bossDefeated(false), isShaking(false),
fadeOut(false), isShakingAfter(false), startCountdown(false), startFirst(false),
firstCompleted(false), first1(true), first2(false), first3(false), first4(false),
first5(false), healthCount(window), secondCompleted(false), second1(true), third1(true),
third2(false), third3(false), showGhost7(true), showGhost6(true), showGhost5(true),
showGhost4(true), showGhost3(true), showGhost1(true), showGhost2(true), isChasing(true),
thirdCompleted(false), startCountdown1(false), weapon1Show(false), weapon2Show(false), 
weapon3Show(false), hp(window, 100.0), showHP(true) {

	if (!font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf")) {
		std::cout << "no font" << std::endl;
	}

	quitText.setFont(font);
	pauseText.setFont(font);
	task1.setFont(font);
	task2.setFont(font);

	bgTexture.loadFromFile("sprites\\maps\\opencourt-night.png");
	playerTexture.loadFromFile("sprites\\characters\\elrico-night.png");
	bgSprite.setTexture(bgTexture);
	playerSprite.setTexture(playerTexture);

	blackBG.setFillColor(Color::Black);
	blackBG.setSize(Vector2f(window.getSize().x, window.getSize().y));

	shakeTime = 0.1f;
	shakeMagnitude = 0.1f;

	broomItemTexture.loadFromFile("sprites\\items\\broom-night.png");
	broomItemSprite.setTexture(broomItemTexture);
	broomItemSprite.setOrigin(broomItemTexture.getSize().x / 2.0f, broomItemTexture.getSize().y / 2.0f);

	weapon1Texture.loadFromFile("sprites\\items\\firegun.png");
	weapon1Sprite.setTexture(weapon1Texture);
	weapon1Sprite.setOrigin(weapon1Texture.getSize().x / 2.0f, weapon1Texture.getSize().y / 2.0f);
	weapon1Sprite.setScale(1.2f, 1.2f);

	weapon2Texture.loadFromFile("sprites\\items\\icegun.png");
	weapon2Sprite.setTexture(weapon2Texture);
	weapon2Sprite.setOrigin(weapon2Texture.getSize().x / 2.0f, weapon2Texture.getSize().y / 2.0f);
	weapon2Sprite.setScale(1.2f, 1.2f);

	weapon3Texture.loadFromFile("sprites\\items\\nailgun.png");
	weapon3Sprite.setTexture(weapon3Texture);
	weapon3Sprite.setOrigin(weapon3Texture.getSize().x / 2.0f, weapon3Texture.getSize().y / 2.0f);
	weapon3Sprite.setScale(1.2f, 1.2f);

	ghostDeathBuffer.loadFromFile("sprites\\sfx\\ghost-death.ogg");
	ghostDeathSFX.setBuffer(ghostDeathBuffer);
	shootBuffer.loadFromFile("sprites\\sfx\\gun-laser.ogg");
	shootSFX.setBuffer(shootBuffer);

	shakeBuffer.loadFromFile("sprites\\sfx\\shake.ogg");
	shakeSFX.setBuffer(shakeBuffer);

	deathBuffer.loadFromFile("sprites\\sfx\\boss-death1.flac");
	deathSFX.setBuffer(deathBuffer);
	illBuffer.loadFromFile("sprites\\sfx\\boss-ill.flac");
	illSFX.setBuffer(illBuffer);

	illSFX.setVolume(60);
	deathSFX.setVolume(70);

	bossTex.loadFromFile("sprites\\enemies\\boss-final.png");
	bossSprite.setTexture(bossTex);
	bossSprite2.setTexture(bossTex);
	bossSprite3.setTexture(bossTex);
	bossSprite4.setTexture(bossTex);
	bossSprite5.setTexture(bossTex);
	bossSprite6.setTexture(bossTex);

	bossSprite2.setColor(Color(255, 255, 255, 170));
	bossSprite3.setColor(Color(255, 255, 255, 170));
	bossSprite4.setColor(Color(255, 255, 255, 170));

	totalTime = 0.0f;
	switchTime = 0.2f;
	currentImage.x = 0;
	bossRect.width = bossTex.getSize().x / 4;
	bossRect.height = bossTex.getSize().y / 1;

	ghost1Texture.loadFromFile("sprites\\enemies\\ghost1.1.png");
	ghost2Texture.loadFromFile("sprites\\enemies\\ghost1.2.png");
	ghost3Texture.loadFromFile("sprites\\enemies\\ghost1.3.png");
	ghost1Sprite.setTexture(ghost1Texture);
	ghost2Sprite.setTexture(ghost1Texture);
	ghost3Sprite.setTexture(ghost1Texture);
	ghost4Sprite.setTexture(ghost2Texture);
	ghost5Sprite.setTexture(ghost2Texture);
	ghost6Sprite.setTexture(ghost3Texture);
	ghost7Sprite.setTexture(ghost3Texture);
	switchTimeGhost = 0.3f;
	currentImageGhost.x = 0;
	ghostRect.width = ghost1Texture.getSize().x / 3;
	ghostRect.height = ghost1Texture.getSize().y / 1;
	ghost1Sprite.setScale(1.7f, 1.7f);
	ghost2Sprite.setScale(1.7f, 1.7f);
	ghost3Sprite.setScale(1.7f, 1.7f);
	ghost4Sprite.setScale(1.7f, 1.7f);
	ghost5Sprite.setScale(1.7f, 1.7f);
	ghost6Sprite.setScale(1.7f, 1.7f);
	ghost7Sprite.setScale(1.7f, 1.7f);

	hitCount = 7;
	hitCount2 = 7;
	hitCount3 = 10;
	hitCount4 = 10;
	hitCount5 = 15;
	hitCount6 = 50;

	bossPos.x = 500;
	bossPos.y = 200;
	xVeloBoss = 3;
	yVeloBoss = 3;
	bossSprite5.setPosition(bossPos);

	health1 = 10;
	health2 = 10;
	health3 = 10;
	health4 = 15;
	health5 = 15;
	health6 = 20;
	health7 = 20;

	initPlayer();
}

BossFight::~BossFight() {

}

Vector2f lerp6(const Vector2f& start, const Vector2f& end, float t) {
	return start + t * (end - start);
}

void BossFight::firstAttack() {
	if (first1) {
		window.setView(window.getDefaultView());
		bossSprite.setScale(3.0f, 3.0f);
		bossSprite2.setScale(3.0f, 3.0f);
		bossSprite3.setScale(3.0f, 3.0f);
		bossSprite4.setScale(3.0f, 3.0f);
		window.draw(bossSprite);
		window.draw(bossSprite2);
		window.draw(bossSprite3);
		window.draw(bossSprite4);

		bossSprite.setPosition(700, 10);
		bossSprite2.setPosition(130, 10);
		bossSprite3.setPosition(700, 300);
		bossSprite4.setPosition(130, 300);

		if (projectileShot && projectile.getGlobalBounds().intersects(bossSprite.getGlobalBounds())) {
			healthCount.showHealthBoss(bossSprite.getPosition(), hitCount);
			hitCount -= 1;
			if (hitCount <= 0) {
				first1 = false;
				first2 = true;
				healthCount.disableCount();
				illSFX.pause();
				illSFX.play();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}
	}
	else if (first2) {
		window.setView(window.getDefaultView());
		bossSprite.setScale(3.0f, 3.0f);
		bossSprite2.setScale(3.0f, 3.0f);
		bossSprite3.setScale(3.0f, 3.0f);
		bossSprite4.setScale(3.0f, 3.0f);
		window.draw(bossSprite);
		window.draw(bossSprite2);
		window.draw(bossSprite3);
		window.draw(bossSprite4);

		bossSprite2.setPosition(700, 10);
		bossSprite3.setPosition(130, 10);
		bossSprite.setPosition(700, 300);
		bossSprite4.setPosition(130, 300);

		if (projectileShot && projectile.getGlobalBounds().intersects(bossSprite.getGlobalBounds())) {
			healthCount.showHealthBoss(bossSprite.getPosition(), hitCount2);
			hitCount2 -= 1;
			if (hitCount2 <= 0) {
				first2 = false;
				first3 = true;
				healthCount.disableCount();
				illSFX.pause();
				illSFX.play();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}
	}
	else if (first3) {
		window.setView(window.getDefaultView());
		bossSprite.setScale(3.0f, 3.0f);
		bossSprite2.setScale(3.0f, 3.0f);
		bossSprite3.setScale(3.0f, 3.0f);
		bossSprite4.setScale(3.0f, 3.0f);
		window.draw(bossSprite);
		window.draw(bossSprite2);
		window.draw(bossSprite3);
		window.draw(bossSprite4);

		bossSprite3.setPosition(700, 10);
		bossSprite4.setPosition(130, 10);
		bossSprite2.setPosition(700, 300);
		bossSprite.setPosition(130, 300);

		if (projectileShot && projectile.getGlobalBounds().intersects(bossSprite.getGlobalBounds())) {
			healthCount.showHealthBoss(bossSprite.getPosition(), hitCount3);
			hitCount3 -= 1;
			if (hitCount3 <= 0) {
				first3 = false;
				first4 = true;
				healthCount.disableCount();
				illSFX.pause();
				illSFX.play();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}
	}
	else if (first4) {
		window.setView(window.getDefaultView());
		bossSprite.setScale(3.0f, 3.0f);
		bossSprite2.setScale(3.0f, 3.0f);
		bossSprite3.setScale(3.0f, 3.0f);
		bossSprite4.setScale(3.0f, 3.0f);
		window.draw(bossSprite);
		window.draw(bossSprite2);
		window.draw(bossSprite3);
		window.draw(bossSprite4);

		bossSprite3.setPosition(700, 10);
		bossSprite2.setPosition(130, 10);
		bossSprite.setPosition(700, 300);
		bossSprite4.setPosition(130, 300);

		if (projectileShot && projectile.getGlobalBounds().intersects(bossSprite.getGlobalBounds())) {
			healthCount.showHealthBoss(bossSprite.getPosition(), hitCount4);
			hitCount4 -= 1;
			if (hitCount4 <= 0) {
				first4 = false;
				first5 = true;
				healthCount.disableCount();
				illSFX.pause();
				illSFX.play();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}
	}
	else if (first5) {
		window.setView(window.getDefaultView());
		bossSprite.setScale(3.0f, 3.0f);
		bossSprite2.setScale(3.0f, 3.0f);
		bossSprite3.setScale(3.0f, 3.0f);
		bossSprite4.setScale(3.0f, 3.0f);
		window.draw(bossSprite);
		window.draw(bossSprite2);
		window.draw(bossSprite3);
		window.draw(bossSprite4);

		bossSprite3.setPosition(700, 10);
		bossSprite.setPosition(130, 10);
		bossSprite2.setPosition(700, 300);
		bossSprite4.setPosition(130, 300);

		if (projectileShot && projectile.getGlobalBounds().intersects(bossSprite.getGlobalBounds())) {
			healthCount.showHealthBoss(bossSprite.getPosition(), hitCount5);
			hitCount5 -= 1;
			if (hitCount5 <= 0) {
				first5 = false;
				firstCompleted = true;
				healthCount.disableCount();
				illSFX.pause();
				illSFX.play();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}
	}
}

void BossFight::secondAttack() {
	if (second1) {
		window.draw(bossSprite5);
		if (projectileShot && projectile.getGlobalBounds().intersects(bossSprite5.getGlobalBounds())) {
			window.setView(camera);
			healthCount.showHealthBoss2(bossSprite.getPosition(), hitCount6);
			hitCount6 -= 1;
			if (hitCount6 <= 0) {
				healthCount.disableCount();
				secondCompleted = true;
				second1 = false;
				illSFX.pause();
				illSFX.play();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}
	}
}

void BossFight::thirdAttack() {

	if (third1) {
		if (showGhost1) {
			window.draw(ghost1Sprite);
		}

		if (showGhost2) {
			window.draw(ghost2Sprite);
		}

		if (showGhost3) {
			window.draw(ghost3Sprite);
		}

		if (isChasing) {
			float angle = atan2(playerSprite.getPosition().y - ghost1Sprite.getPosition().y, playerSprite.getPosition().x - ghost1Sprite.getPosition().x);
			float x = 1.5 * cos(angle);
			float y = 1.5 * sin(angle);
			ghost1Sprite.move(x, y);

			float angle2 = atan2(playerSprite.getPosition().y - ghost2Sprite.getPosition().y, playerSprite.getPosition().x - ghost2Sprite.getPosition().x);
			float x2 = 1.5 * cos(angle2);
			float y2 = 1.5 * sin(angle2);
			ghost2Sprite.move(x2, y2);

			float angle3 = atan2(playerSprite.getPosition().y - ghost3Sprite.getPosition().y, playerSprite.getPosition().x - ghost3Sprite.getPosition().x);
			float x3 = 1.5 * cos(angle3);
			float y3 = 1.5 * sin(angle3);
			ghost3Sprite.move(x3, y3);
		}

		if (projectileShot && projectile.getGlobalBounds().intersects(ghost1Sprite.getGlobalBounds())) {
			//showGhost1 = false;
			window.setView(camera);
			//healthCount.showHealth(ghost1Sprite.getPosition(), health1);
			health1 -= 1;
			if (health1 <= 0) {
				ghost1Sprite.setPosition(9000, 9000);
				showGhost1 = false;
				ghostDeathSFX.pause();
				ghostDeathSFX.play();
				healthCount.disableCount();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}

		if (projectileShot && projectile.getGlobalBounds().intersects(ghost2Sprite.getGlobalBounds())) {
			//showGhost2 = false;
			window.setView(camera);
			//healthCount.showHealth(ghost2Sprite.getPosition(), health2);
			health2 -= 1;
			if (health2 <= 0) {
				ghost2Sprite.setPosition(9000, 9000);
				showGhost2 = false;
				ghostDeathSFX.pause();
				ghostDeathSFX.play();
				healthCount.disableCount();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}

		if (projectileShot && projectile.getGlobalBounds().intersects(ghost3Sprite.getGlobalBounds())) {
			//showGhost3 = false;
			window.setView(camera);
			//healthCount.showHealth(ghost3Sprite.getPosition(), health3);
			health3 -= 1;
			if (health3 <= 0) {
				ghost3Sprite.setPosition(9000, 9000);
				showGhost3 = false;
				ghostDeathSFX.pause();
				ghostDeathSFX.play();
				healthCount.disableCount();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}

		if (!showGhost1 && !showGhost2 && !showGhost3) {
			third1 = false;
			third2 = true;
			illSFX.pause();
			illSFX.play();
		}
	}

	if (third2) {
		if (showGhost4) {
			window.draw(ghost4Sprite);
		}

		if (showGhost5) {
			window.draw(ghost5Sprite);
		}

		if (isChasing) {
			float angle4 = atan2(playerSprite.getPosition().y - ghost4Sprite.getPosition().y, playerSprite.getPosition().x - ghost4Sprite.getPosition().x);
			float x4 = 1.5 * cos(angle4);
			float y4 = 1.5 * sin(angle4);
			ghost4Sprite.move(x4, y4);

			float angle5 = atan2(playerSprite.getPosition().y - ghost5Sprite.getPosition().y, playerSprite.getPosition().x - ghost5Sprite.getPosition().x);
			float x5 = 1.5 * cos(angle5);
			float y5 = 1.5 * sin(angle5);
			ghost5Sprite.move(x5, y5);
		}

		if (projectileShot && projectile.getGlobalBounds().intersects(ghost4Sprite.getGlobalBounds())) {
			//showGhost4 = false;
			window.setView(camera);
			//healthCount.showHealth(ghost4Sprite.getPosition(), health4);
			health4 -= 1;
			if (health4 <= 0) {
				ghost4Sprite.setPosition(9000, 9000);
				showGhost4 = false;
				ghostDeathSFX.pause();
				ghostDeathSFX.play();
				healthCount.disableCount();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}

		if (projectileShot && projectile.getGlobalBounds().intersects(ghost5Sprite.getGlobalBounds())) {
			//showGhost5 = false;
			window.setView(camera);
			//healthCount.showHealth(ghost5Sprite.getPosition(), health5);
			health5 -= 1;
			if (health5 <= 0) {
				ghost5Sprite.setPosition(9000, 9000);
				showGhost5 = false;
				ghostDeathSFX.pause();
				ghostDeathSFX.play();
				healthCount.disableCount();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}

		if (!showGhost4 && !showGhost5) {
			third2 = false;
			third3 = true;
			illSFX.pause();
			illSFX.play();
		}
	}

	if (third3) {
		if (showGhost6) {
			window.draw(ghost6Sprite);
		}

		if (showGhost7) {
			window.draw(ghost7Sprite);
		}

		if (isChasing) {
			float angle6 = atan2(playerSprite.getPosition().y - ghost6Sprite.getPosition().y, playerSprite.getPosition().x - ghost6Sprite.getPosition().x);
			float x6 = 1.5 * cos(angle6);
			float y6 = 1.5 * sin(angle6);
			ghost6Sprite.move(x6, y6);

			float angle7 = atan2(playerSprite.getPosition().y - ghost7Sprite.getPosition().y, playerSprite.getPosition().x - ghost7Sprite.getPosition().x);
			float x7 = 1.5 * cos(angle7);
			float y7 = 1.5 * sin(angle7);
			ghost7Sprite.move(x7, y7);
		}

		if (projectileShot && projectile.getGlobalBounds().intersects(ghost6Sprite.getGlobalBounds())) {
			//showGhost6 = false;
			window.setView(camera);
			//healthCount.showHealth(ghost6Sprite.getPosition(), health6);
			health6 -= 1;
			if (health6 <= 0) {
				ghost6Sprite.setPosition(9000, 9000);
				showGhost6 = false;
				ghostDeathSFX.pause();
				ghostDeathSFX.play();
				healthCount.disableCount();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}

		if (projectileShot && projectile.getGlobalBounds().intersects(ghost7Sprite.getGlobalBounds())) {
			//showGhost7 = false;
			window.setView(camera);
			//healthCount.showHealth(ghost7Sprite.getPosition(), health7);
			health7 -= 1;
			if (health7 <= 0) {
				ghost7Sprite.setPosition(9000, 9000);
				showGhost7 = false;
				ghostDeathSFX.pause();
				ghostDeathSFX.play();
				healthCount.disableCount();
			}
			projectiles.clear();
			projectile.setPosition(9000, 9000);
		}

		if (!showGhost6 && !showGhost7) {
			third3 = false;
			thirdCompleted = true;
			illSFX.pause();
			illSFX.play();
		}
	}
}

void BossFight::initPlayer() {
	camera.setSize(window.getSize().x / 2.4f, window.getSize().y / 2.4f);

	quitText.setString("Press Q to quit");
	quitText.setCharacterSize(15);
	quitText.setOutlineColor(Color::Black);
	quitText.setOutlineThickness(3);

	pauseText.setString("Press P to pause game");
	pauseText.setCharacterSize(15);
	pauseText.setOutlineColor(Color::Black);
	pauseText.setOutlineThickness(3);

	task1.setString("!\tDefeat the boss");
	task1.setCharacterSize(25);
	task1.setOutlineColor(Color::Black);
	task1.setOutlineThickness(3);

	task2.setString("!\t???");
	task2.setCharacterSize(25);
	task2.setOutlineColor(Color::Black);
	task2.setOutlineThickness(3);

	bossSprite.setPosition(500, 200);

	bossSprite6.setPosition(500, 200);
	ghost1Sprite.setPosition(300, 100);
	ghost2Sprite.setPosition(600, 150);
	ghost3Sprite.setPosition(400, 200);
	ghost4Sprite.setPosition(500, 200);
	ghost5Sprite.setPosition(350, 150);
	ghost6Sprite.setPosition(600, 200);
	ghost7Sprite.setPosition(400, 250);

	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(250, 0);

	playerSprite.setPosition(345, 500);
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(IntRect(0, 64, 32, 32));

	playerBounds = playerSprite.getLocalBounds();
	playerSprite.setOrigin(playerBounds.width / 2.0f, playerBounds.height / 2.0f);

	projectile.setSize(Vector2f(5.0f, 2.0f));
	projectile.setFillColor(Color::Yellow);

	broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);

	float rectAlpha = 0.0f;

	rectangles.push_back(Rectangle(250, -130, 1000, 100, rectAlpha)); // upper
	rectangles.push_back(Rectangle(250, 600, 1000, 100, rectAlpha)); // lower
	rectangles.push_back(Rectangle(190, 0, 60, 700, rectAlpha)); // left
	rectangles.push_back(Rectangle(1070, 0, 60, 700, rectAlpha)); // right

	// objects
	rectangles.push_back(Rectangle(264, 45, 50, 270, rectAlpha)); // left
	rectangles.push_back(Rectangle(995, 180, 50, 270, rectAlpha)); // right

	updateTextPos();
}

void BossFight::handleInput() {
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
		playerSprite.getGlobalBounds().intersects(ghost7Sprite.getGlobalBounds())) {
		hp.damage(0.2);
	}

	if (Keyboard::isKeyPressed(Keyboard::E)) {
		startCountdown1 = true;
	}

	if(!startCountdown1) {
		countdown1.restart();
	}

	float elapsedTime1 = countdown1.getElapsedTime().asSeconds();

	if (elapsedTime1 >= 5) {
		cout << elapsedTime1 << endl;
		startFirst = true;
	}

	if (!startCountdown) {
		countdown.restart();
	}

	float elapsedTime = countdown.getElapsedTime().asSeconds();
	//cout << elapsedTime << endl;

	if (elapsedTime >= 4) {
		isShakingAfter = true;

		if (elapsedTime >= 7) {
			fadeOut = true;
		}
	}

	float moveSpeed = 3.5;

	if (Keyboard::isKeyPressed(Keyboard::LShift)) {
		moveSpeed += 2;
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dPressed = true;
		aPressed = false;
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
		//broomItemSprite.setPosition(playerSprite.getPosition().x + 4, playerSprite.getPosition().y + 7.5);
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
		//broomItemSprite.setPosition(playerSprite.getPosition().x - 4, playerSprite.getPosition().y + 7.5);
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
		if (weapon1Show) {
			projectileDirection = mousePos - weapon1Sprite.getPosition();
		}
		if (weapon2Show) {
			projectileDirection = mousePos - weapon2Sprite.getPosition();
		}
		if (weapon3Show) {
			projectileDirection = mousePos - weapon3Sprite.getPosition();
		}
		//projectileDirection = mousePos - broomItemSprite.getPosition();
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
		if (firerate < 0.2f) {
			projectile.move(projectileDirection * projectileSpeed);
		}
		if (firerate > 0.2f) {
			shootSFX.stop();
			projectileShot = false;
			cooldown.restart();
			projectile.setPosition(9000, 9000);
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Tab)) {
		bossDefeated = true;
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

void BossFight::updateTextPos() {
	quitText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.45f);
	pauseText.setPosition(camera.getCenter().x - window.getSize().x / 2.6f, camera.getCenter().y - window.getSize().y / 1.50f);
	task1.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 900, camera.getCenter().y - window.getSize().y / 1.80f);
	task2.setPosition(camera.getCenter().x - window.getSize().x / 2.6f + 1100, camera.getCenter().y - window.getSize().y / 1.80f);
}

void BossFight::Camera() {
	mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
	playerToMouse = mousePos - playerSprite.getPosition();
	targetCenter = playerSprite.getPosition() + 0.2f * playerToMouse;
	currentCenter = camera.getCenter();
	newCenter = lerp6(currentCenter, targetCenter, dampingFactor);
	camera.setCenter(newCenter);
}

void BossFight::update() {
	blackBG.setPosition(camera.getCenter().x - 500.0f, camera.getCenter().y - 500.0f);
	camera.setCenter(playerSprite.getPosition());
	dt = clock.restart().asSeconds();
	camera.setCenter(newCenter);
	window.setView(camera);

	if (firstCompleted && secondCompleted && thirdCompleted) {
		bossDefeated = true;
		showHP = false;
	}

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

	if (isShakingAfter) {
		shakeSFX.pause();
		shakeSFX.play();
		float offsetX = (rand() % 200 - 100) * shakeMagnitude;
		float offsetY = (rand() % 200 - 100) * shakeMagnitude;

		camera.move(offsetX, offsetY);
	}

	if (bossDefeated) {
		startCountdown = true;
		deathSFX.pause();
		deathSFX.play();
	}
}

void BossFight::animUpdate(float dt) {
	currentImage.y = 0;
	totalTime += dt;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= 4) {
			currentImage.x = 0;
		}
	}

	bossRect.left = currentImage.x * bossRect.width;
	bossRect.top = currentImage.y * bossRect.height;


	if (firstCompleted) {
		bossSprite5.move(bossPos);

		if (bossPos.x < 400 || bossPos.x > 700) {
			xVeloBoss *= -1;
		}

		bossPos.x -= xVeloBoss;
		bossSprite5.setPosition(bossPos);
	}
}

bool BossFight::isIntersecting(const FloatRect& rect1, const FloatRect& rect2) {
	return rect1.intersects(rect2);
}

void BossFight::handleCollision(const Rectangle& rect) {
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

bool BossFight::bossDead() {
	return bossDefeated;
}

bool BossFight::sceneComplete() {
	return fadeOut;
}

bool BossFight::stopBGM() {
	return bossDefeated;
}

void BossFight::setWeapon1() {
	weapon1Show = true;
}

void BossFight::setWeapon2() {
	weapon2Show = true;
}

void BossFight::setWeapon3() {
	weapon3Show = true;
}

void BossFight::restart() {
	hp.resetHealth();
	playerSprite.setPosition(345, 500);
	firstCompleted = false;
	secondCompleted = false;
	thirdCompleted = false;
	startCountdown1 = false;
}

void BossFight::render() {
	View initialView(FloatRect(0, 0, window.getSize().x, window.getSize().y));
	window.setView(initialView);
	window.clear();
	camera.setCenter(newCenter);
	window.setView(camera);
	bgSprite.setScale(0.6f, 0.6f);
	playerSprite.setScale(1.75f, 1.75f);
	broomItemSprite.setScale(1.75f, 1.75f);
	window.draw(blackBG);
	window.draw(bgSprite);
	if (weapon1Show) {
		window.draw(weapon1Sprite);
	}
	if (weapon2Show) {
		window.draw(weapon2Sprite);
	}
	if (weapon3Show) {
		window.draw(weapon3Sprite);
	}
	//window.draw(broomItemSprite);
	window.draw(playerSprite);

	bossSprite.setTextureRect(bossRect);
	bossSprite2.setTextureRect(bossRect);
	bossSprite3.setTextureRect(bossRect);
	bossSprite4.setTextureRect(bossRect);
	bossSprite5.setTextureRect(bossRect);
	bossSprite6.setTextureRect(bossRect);
	//bossSprite.setScale(1.4f, 1.4f);
	bossSprite.setScale(1.5f, 1.5f);
	bossSprite5.setScale(1.5f, 1.5f);
	bossSprite6.setScale(1.5f, 1.5f);

	ghost1Sprite.setTextureRect(ghostRect);
	ghost2Sprite.setTextureRect(ghostRect);
	ghost3Sprite.setTextureRect(ghostRect);
	ghost4Sprite.setTextureRect(ghostRect);
	ghost5Sprite.setTextureRect(ghostRect);
	ghost6Sprite.setTextureRect(ghostRect);
	ghost7Sprite.setTextureRect(ghostRect);

	if (!startFirst) {
		window.draw(bossSprite);
	}

	if (firstCompleted && !thirdCompleted) {
		thirdAttack();
		window.draw(bossSprite6);
	}

	if (thirdCompleted) {
		secondAttack();
	}

	for (const auto& rect : rectangles) {
		window.draw(rect.shape);
	}

	window.draw(projectile);

	window.setView(window.getDefaultView());

	window.draw(quitText);
	window.draw(pauseText);
	if (startFirst) {
		firstAttack();
	}
	healthCount.render();
	if (firstCompleted) {
		startFirst = false;
	}
	if (!bossDefeated) {
		window.draw(task1);
	}
	else {
		window.draw(task2);
	}

	if (fadeOut) {
		sceneComplete();
	}

	if (hp.noHP()) {
		restart();
	}
	else if (showHP && !hp.noHP()) {
		hp.update();
		hp.setHealth(100.0);
		hp.render();
	}
}
