#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "Skylab.h"
#include "DialogueBox.h"
#include "HealthCount.h"
#include "HP.h"

using namespace std;

class HMNight
{
public:
	HMNight(RenderWindow& window);
	~HMNight();

	void handleInput();
	void animUpdate(float dt);
	void update();
	void Camera();
	void render();

	bool gotoHM2nd();
	void playerPosFromHM2nd();
	void goingHM2ndFalse();

	bool gotoRoom1();
	void playerPosFromRoom1();
	void goingRoom1False();

	bool gotoCBA();
	void playerPosFromCBA();
	void goingCBAFalse();

	void bossDefeated(bool yes);
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
	Text task3;
	Text task4;
	Font font;

	Text score1;
	Text score2;
	Text score3;

	HP hp;
	bool showHP;
	HealthCount healthCount;

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
	Sprite ghost14Sprite;
	Sprite ghost15Sprite;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
	IntRect ghostRect;

	Texture arrowTex;
	Sprite arrowSprite;
	float switchTimeArrow;
	Vector2u currentImageArrow;
	IntRect arrowRect;

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

	bool weapon1Show;
	bool weapon2Show;
	bool weapon3Show;

	Texture weapon1Texture;
	Sprite weapon1Sprite;
	Texture weapon2Texture;
	Sprite weapon2Sprite;
	Texture weapon3Texture;
	Sprite weapon3Sprite;

	bool goingHM2nd;
	bool goingRoom1;
	bool goingCBA;

	Clock clock5;
	bool start5;
	Clock clock6;
	bool start6;
	Clock clock7;
	bool start7;
	Clock clock8;
	bool start8;
	Clock clock9;
	bool start9;
	Clock clock10;
	bool start10;
	Clock clock11;
	bool start11;
	Clock clock12;
	bool start12;
	Clock clock13;
	bool start13;
	Clock clock14;
	bool start14;
	Clock clock15;
	bool start15;

	Clock c5;
	Clock c6;
	Clock c7;
	Clock c8;
	Clock c9;
	Clock c10;
	Clock c11;
	Clock c12;
	Clock c13;
	Clock c14;
	Clock c15;
	
	bool slowed5;
	bool slowed6;
	bool slowed7;
	bool slowed8;
	bool slowed9;
	bool slowed10;
	bool slowed11;
	bool slowed12;
	bool slowed13;
	bool slowed14;
	bool slowed15;
	float speed1;
	float speed2;
	float speed3;
	float speed4;
	float speed5;
	float speed6;
	float speed7;
	float speed8;
	float speed9;
	float speed10;
	float speed11;
	float speed12;
	float speed13;
	float speed14;
	float speed15;

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

	SoundBuffer ghostDeathBuffer;
	Sound ghostDeathSFX;
	SoundBuffer shootBuffer;
	Sound shootSFX;
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
	bool showGhost14;
	bool showGhost15;

	int ghost1Score;
	int ghost2Score;
	int ghost3Score;

	bool levelComplete1;
	bool levelComplete2;
	bool levelComplete3;

	bool startLevel2;
	bool startLevel3;

	bool showScores;
	bool bossDead;

	void disableGhosts();
	void showTask1();
	void showTask2();
	void showTask3();
	void showTask4();

	bool dialogue;
	void showDialogue();

	bool showCat;
	NPC npc;
	bool dialogueBoolCat;
	void catDialogueBox();

	bool task4Show;

	int health1;
	int health2;
	int health3;
	int health4;
	int health5;
	int health6;
	int health7;
	int health8;
	int health9;
	int health10;
	int health11;
	int health12;
	int health13;
	int health14;
	int health15;
};

