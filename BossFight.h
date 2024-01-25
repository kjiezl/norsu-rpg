#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DialogueBox.h"
#include "BlackFadeTransition.h"
#include "PauseMenu.h"
#include "Skylab.h"
#include "HealthCount.h"
#include "HP.h"

using namespace sf;

class BossFight
{
public:
	BossFight(RenderWindow& window);
	~BossFight();

	void handleInput();
	void update();
	void animUpdate(float dt);
	void Camera();
	void render();

	bool bossDead();
	bool sceneComplete();

	bool stopBGM();

	void setWeapon1();
	void setWeapon2();
	void setWeapon3();

	void restart();

private:
	RenderWindow& window;
	BlackFadeTransition fadeTrans;
	Texture playerTexture;
	Sprite playerSprite;
	Texture bgTexture;
	Sprite bgSprite;

	View camera;
	float zoom;
	Text quitText;
	Text pauseText;
	Text task1;
	Text task2;

	PauseMenu pauseMenu;
	bool gamePaused;

	HP hp;
	bool showHP;
	HealthCount healthCount;

	bool dPressed;
	bool aPressed;

	Clock clock;
	float dt;

	FloatRect playerBounds;

	float dampingFactor;

	Vector2f mousePos;
	Vector2f playerToMouse;
	Vector2f targetCenter;
	Vector2f currentCenter;
	Vector2f newCenter;

	DialogueBox dialogueBox;

	RectangleShape blackBG;

	RectangleShape shape;
	bool isIntersecting(const FloatRect& rect1, const FloatRect& rect2);
	void handleCollision(const Rectangle& rect);
	FloatRect charBounds;
	FloatRect rectBounds;
	FloatRect intersection;
	vector<Rectangle> rectangles;

	void initPlayer();
	void updateTextPos();

	Font font;

	Clock cooldown;
	RectangleShape projectile;
	bool projectileShot;
	Vector2f projectileDirection;
	float shakeTime;
	float shakeMagnitude;
	bool isShaking;
	Clock shakeClock;
	vector<RectangleShape> projectiles;

	Texture broomItemTexture;
	Sprite broomItemSprite;
	Vector2f broomToMouse;

	bool weapon1Show;
	bool weapon2Show;
	bool weapon3Show;

	Texture weapon1Texture;
	Sprite weapon1Sprite;
	Texture weapon2Texture;
	Sprite weapon2Sprite;
	Texture weapon3Texture;
	Sprite weapon3Sprite;

	SoundBuffer ghostDeathBuffer;
	Sound ghostDeathSFX;
	SoundBuffer shootBuffer;
	Sound shootSFX;
	SoundBuffer shakeBuffer;
	Sound shakeSFX;
	SoundBuffer deathBuffer;
	Sound deathSFX;
	SoundBuffer illBuffer;
	Sound illSFX;

	bool bossDefeated;

	bool startCountdown1;
	bool startCountdown;
	bool isShakingAfter;

	Clock countdown;
	bool fadeOut;

	Texture bossTex;
	Sprite bossSprite;
	Sprite bossSprite2;
	Sprite bossSprite3;
	Sprite bossSprite4;
	Sprite bossSprite5;
	Sprite bossSprite6;

	Vector2u currentImage;
	float totalTime;
	float switchTime;
	IntRect bossRect;

	Clock countdown1;

	bool startFirst;
	bool firstCompleted;
	bool secondCompleted;
	bool thirdCompleted;

	bool first1;
	bool first2;
	bool first3;
	bool first4;
	bool first5;

	bool second1;

	bool third1;
	bool third2;
	bool third3;

	int hitCount;
	int hitCount2;
	int hitCount3;
	int hitCount4;
	int hitCount5;
	int hitCount6;

	void firstAttack();
	void secondAttack();
	void thirdAttack();

	Vector2f bossPos;
	float xVeloBoss;
	float yVeloBoss;

	Texture ghost1Texture;
	Texture ghost2Texture;
	Texture ghost3Texture;
	Sprite ghost1Sprite;
	Sprite ghost2Sprite;
	Sprite ghost3Sprite;
	Sprite ghost4Sprite;
	Sprite ghost5Sprite;
	Sprite ghost6Sprite;
	Sprite ghost7Sprite;
	Vector2u currentImageGhost;
	float switchTimeGhost;
	IntRect ghostRect;

	bool showGhost1;
	bool showGhost2;
	bool showGhost3;
	bool showGhost4;
	bool showGhost5;
	bool showGhost6;
	bool showGhost7;

	bool isChasing;

	int health1;
	int health2;
	int health3;
	int health4;
	int health5;
	int health6;
	int health7;
};

