#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "HealthCount.h"
#include "Skylab.h"
#include "HP.h"

using namespace sf;
using namespace std;

class CAS3Night
{
public:
	CAS3Night(RenderWindow& window, const string& pName);
	~CAS3Night();

	void handleInput();
	void update();
	void animUpdate(float dt);
	void Camera();
	void render();

	bool gotoSkylab();
	bool gotoMainGate();

	void playerPosFromSkylab();
	void goingSkylabFalse();

	void playerPosFromMainGate();
	void goingMainGateFalse();

	bool stopBGM();

	void restart();

private:
	RenderWindow& window;
	BlackFadeTransition fadeTrans;
	string pName;
	Sprite playerSprite;
	Texture playerTexture;
	Sprite bgSprite;
	Texture bgTexture;

	View camera;
	float zoom;
	Text quitText;
	Text pauseText;
	Text task1;
	Text task2;
	Font font;
	Text playerName;
	Text score1;
	Text score2;
	Text score3;
	Text unlocked;

	HealthCount healthCount;
	HP hp;

	PauseMenu pauseMenu;
	bool gamePaused;

	Texture ghostTexture1;
	Texture ghostTexture2;
	Texture ghostTexture3;
	Sprite ghost1Sprite;
	Sprite ghost2Sprite;
	Sprite ghost3Sprite;
	Sprite ghost4Sprite;
	Sprite ghost5Sprite;
	Sprite ghost6Sprite;
	Sprite ghost7Sprite;
	Sprite ghost8Sprite;
	Sprite ghost9Sprite;
	Sprite ghost10Sprite;
	Sprite ghost11Sprite;
	Sprite ghost12Sprite;
	Sprite ghost13Sprite;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
	IntRect ghostRect;

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

	RectangleShape borderShape;
	bool isChasing;

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

	bool goingSkylab;
	bool goingMainGate;

	RectangleShape blackBG;

	void initPlayer();
	void updateTextPos();

	RectangleShape shape;
	bool isIntersecting(const FloatRect& rect1, const FloatRect& rect2);
	void handleCollision(const Rectangle& rect);
	FloatRect charBounds;
	FloatRect rectBounds;
	FloatRect intersection;
	vector<Rectangle> rectangles;

	SoundBuffer ghostDeathBuffer;
	Sound ghostDeathSFX;
	SoundBuffer shootBuffer;
	Sound shootSFX;
	SoundBuffer windBuffer;
	Sound windSFX;
	SoundBuffer levelBuffer;
	Sound levelSFX;

	bool showGhost1;
	bool showGhost2;
	bool showGhost3;
	bool showGhost4;
	bool showGhost5;
	bool showGhost6;
	bool showGhost7;
	bool showGhost8;
	bool showGhost9;
	bool showGhost10;
	bool showGhost11;
	bool showGhost12;
	bool showGhost13;

	int ghost1Score;
	int ghost2Score;
	int ghost3Score;

	bool levelComplete1;
	bool levelComplete2;
	bool levelComplete3;

	bool startLevel2;
	bool startLevel3;

	bool playWindSFX;
	void showTask1();
	void showTask2();
	void disableGhosts();
	void playWind();
	Clock windClock;

	int health7;
	int health8;
	int health9;
	int health10;
	int health11;
	int health12;
	int health13;

	bool showHP;
};