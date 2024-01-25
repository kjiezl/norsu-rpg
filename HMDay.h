#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "Skylab.h"
#include "DialogueBox.h"

using namespace std;
using namespace sf;

class HMDay
{
public:
	HMDay(RenderWindow& window);
	~HMDay();

	void handleInput();
	void animUpdate(float dt);
	void update();
	void Camera();
	void render();

	bool gotoMainGate();
	void playerPosFromMainGate();
	void goingMainGateFalse();

	bool gotoHM2nd();
	void playerPosFromHM2nd();
	void goingHM2ndFalse();

	bool gotoCBA();
	void playerPosFromCBA();
	void goingCBAFalse();

	void goingHM(bool papersPlaced);

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

	bool goingMainGate;
	bool goingHM2nd;
	bool goingCBA;

	Texture ghostTex;
	Sprite ghost;
	float switchTime;
	float totalTime;
	Vector2u currentImage;
	IntRect ghostRect;
	Vector2f ghostPos;

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
	bool ghostMove;
	bool showDialogue;

	void dialogue();

	Text collectScraps;

	Texture item1Tex;
	Texture item2Tex;
	Texture item3Tex;

	Sprite match1;
	Sprite ice1;
	Sprite metal1;
	Sprite metal2;

	vector<Sprite> item1;
	vector<Sprite> item2;
	vector<Sprite> item3;

	Inventory inv;

	bool hide1;
	bool hide2;
	bool hide3;
	bool hide4;

	SoundBuffer itemBuffer;
	Sound itemSFX;
};

