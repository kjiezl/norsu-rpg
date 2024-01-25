#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "Skylab.h"
#include "DialogueBox.h"
#include "HealthCount.h"
#include "Inventory.h"

using namespace std;

class CBADay
{
public:
	CBADay(RenderWindow& window);
	~CBADay();

	void handleInput();
	void animUpdate(float dt);
	void update();
	void Camera();
	void render();

	bool gotoHM();
	void playerPosFromHM();
	void goingHMFalse();

	bool gotoRoom();
	void playerPosFromRoom();
	void goingRoomFalse();

	bool gotoMainGate();
	void playerPosFromMainGate();
	void goingMainGateFalse();

	bool gotoCourt();
	void playerPosFromCourt();
	void goingCourtFalse();

	void show4(bool papersPlaced);

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
	Text task2;
	Text task4;
	Font font;

	PauseMenu pauseMenu;
	bool gamePaused;

	float totalTime;

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

	bool goingHM;
	bool goingRoom;
	bool goingMainGate;
	bool goingCourt;

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

	bool showTask4;

	Text collectScraps;

	Texture item1Tex;
	Texture item2Tex;
	Texture item3Tex;

	Sprite match1;
	Sprite ice1;
	Sprite ice2;
	Sprite metal1;
	Sprite metal2;
	Sprite metal3;

	vector<Sprite> item1;
	vector<Sprite> item2;
	vector<Sprite> item3;

	Inventory inv;

	bool hide1;
	bool hide2;
	bool hide3;
	bool hide4;
	bool hide5;
	bool hide6;

	SoundBuffer itemBuffer;
	Sound itemSFX;
};

