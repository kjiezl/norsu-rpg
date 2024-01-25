#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "Skylab.h"
#include "Inventory.h"

using namespace sf;

class HM2ndNight
{
public:
	HM2ndNight(RenderWindow& window);
	~HM2ndNight();

	void handleInput();
	void update();
	void animUpdate(float dt);
	void Camera();
	void render();

	bool gotoHM();
	void playerPosFromHM();
	void goingHMFalse();

	bool gotoHMRoom2();
	void playerPosFromHMRoom2();
	void goingHMRoom2False();

	void setWeapon1();
	void setWeapon2();
	void setWeapon3();

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
	Text task;
	Font font;

	Inventory inv;
	PauseMenu pauseMenu;
	bool gamePaused;

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

	bool goingHM;
	bool goingHMRoom2;

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

	Texture arrowTex;
	Sprite arrowSprite;
	float totalTime;
	float switchTimeArrow;
	Vector2u currentImageArrow;
	IntRect arrowRect;

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

	Texture ghost1Texture;
	Texture ghost2Texture;
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

	SoundBuffer ghostDeathBuffer;
	Sound ghostDeathSFX;
	SoundBuffer shootBuffer;
	Sound shootSFX;

	Clock cooldown;
	RectangleShape projectile;
	bool projectileShot;
	Vector2f projectileDirection;
	float shakeTime;
	float shakeMagnitude;
	bool isShaking;
	Clock shakeClock;
	vector<RectangleShape> projectiles;

	bool showGhost1;
	bool showGhost2;
	bool showGhost3;
	bool showGhost4;
	bool showGhost5;
	bool showGhost6;
	bool showGhost7;

	bool isChasing;
};

