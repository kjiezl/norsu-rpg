#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "PlayerName.h"
#include "SkylabNight.h"
#include "Skylab.h"

using namespace sf;
using namespace std;

class SkylabRoomNight
{
public:
	SkylabRoomNight(RenderWindow& window, const string& pName);
	~SkylabRoomNight();

	void handleInput();
	void update();
	void Camera();
	void render();
	void setPlayerName(const string& pName) {
		this->pName = pName;
	}

	void animUpdate(float dt);

	void goingSkylabFalse();
	bool gotoSkylab();

	void goHomeFalse();

	bool gameStart();

	bool nightBGMFalse();

	bool startBGM();

private:
	RenderWindow& window;
	DialogueBox dialogueBox;
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

	bool goingSkylab;

	RectangleShape blackBG;

	Text exitDoorText;
	bool showExitText;

	Texture arrowTexture;
	Sprite arrowSprite;
	Vector2u currentImageArrow;
	float switchTimeArrow;
	IntRect arrowRect;
	float totalTime;

	bool showGoHome;
	bool showPhoneTask;
	bool showPhone;
	bool showBroom;
	bool animBroom;
	bool showGhost1;
	bool showGhost2;

	bool broomPicked;

	Texture phoneTexture;
	Sprite phoneSprite;
	Texture broomTexture;
	Sprite broomSprite;

	Texture broomAnimTexture;
	Sprite broomAnimSprite;
	Vector2u currentImageBroom;
	float switchTimeBroom;
	IntRect broomRect;

	Texture ghost1Texture;
	Sprite ghost1Sprite;
	Sprite ghost2Sprite;
	Vector2u currentImageGhost1;
	float switchTimeGhost1;
	IntRect ghost1Rect;

	Texture broomItemTexture;
	Sprite broomItemSprite;
	Vector2f broomToMouse;

	Text pickupItemText;
	bool showPickupText;

	Text tutorText;
	bool showTutorText;

	RectangleShape ghost2Border;
	bool isChasing;

	bool dialogue;
	bool dialogue2;

	void goHome();
	void phoneTask();
	void showTutor();

	void initPlayer();
	void updateTextPos();
	void exitText();
	void itemText();
	void showDialogueBox();
	void showDialogue2();

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
	Clock switchClock;
	//bool enemySpawned;
	//vector<Sprite> enemies;
	vector<RectangleShape> projectiles;
	//bool spawnEnemies;
	//void updateEnemies();

	bool nightBGM;

	SoundBuffer windBuffer;
	Sound windSFX;
	SoundBuffer ghostDeathBuffer;
	Sound ghostDeathSFX;
	SoundBuffer shootBuffer;
	Sound shootSFX;
	SoundBuffer pickupBuffer;
	Sound pickupSFX;

	Texture lightsaberTexture;
	Texture glockTexture;
	Texture nerfTexture;
	Texture pewpewTexture;
	vector<Texture> items;
	int itemIndex;
	void switchItem();
};



