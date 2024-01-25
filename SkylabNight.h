#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "PlayerName.h"
#include "Skylab.h"
#include "NPC.h"
#include "SkylabRoomNight.h"

using namespace sf;
using namespace std;

class SkylabNight
{
public:
	SkylabNight(RenderWindow& window, const string& pName);
	~SkylabNight();

	void handleInput();
	void update();
	void Camera();
	void render();
	void setPlayerName(const string& pName) {
		this->pName = pName;
	}

	void animUpdate(float dt);

	void playerPosFrom3rdCAS();
	void going3rdCASFalse();
	void goingSkylabRoomFalse();

	bool goto3rdCAS();
	bool gotoSkylabRoom();

	bool changeTextRoom();
	void startSpawn();

private:
	RenderWindow& window;
	BlackFadeTransition fadeTrans;
	//SkylabRoomNight skylabRoomNight;
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
	Font font;
	Text playerName;
	PauseMenu pauseMenu;
	bool gamePaused;

	PlayerName playerNameClass;

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

	bool going3rdCAS;
	bool goingSkylabRoom;

	RectangleShape blackBG;

	Texture arrowTexture;
	Sprite arrowSprite;
	Vector2u currentImageArrow;
	float switchTimeArrow;
	IntRect arrowRect;
	float totalTime;

	Text enterDoorText;
	bool showEnterText;

	void initPlayer();
	void updateTextPos();
	void enterText();

	bool showGoHome;
	bool phoneTask;
	bool dialogue;
	void showDialogueBox();
	void showPhoneTask();
	Text phoneText;
	bool blockStairs;

	bool broomPicked;
	Texture broomItemTexture;
	Sprite broomItemSprite;
	Vector2f broomToMouse;

	Texture ghost1Texture;
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

	RectangleShape borderGhost;
	RectangleShape borderGhost2;
	RectangleShape borderGhost3;
	bool isChasing;
	bool isChasing2;
	bool isChasing3;

	RectangleShape shape;
	bool isIntersecting(const FloatRect& rect1, const FloatRect& rect2);
	void handleCollision(const Rectangle& rect);
	FloatRect charBounds;
	FloatRect rectBounds;
	FloatRect intersection;
	vector<Rectangle> rectangles;

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

	SoundBuffer ghostDeathBuffer;
	Sound ghostDeathSFX;
	SoundBuffer shootBuffer;
	Sound shootSFX;
};

