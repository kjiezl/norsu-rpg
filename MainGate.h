#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "CircTrans.h"
#include "PauseMenu.h"
#include "Skylab.h"
#include "Inventory.h"

using namespace sf;
using namespace std;

class MainGate
{
public:
	MainGate(RenderWindow& window, const string& pName);
	~MainGate();

	void handleInput();
	void update();
	void animUpdate(float dt);
	void Camera();
	void render();
	void setPlayerName(const string& pName) {
		this->pName = pName;
	}

	bool goto3rdCAS();
	void playerPosFrom3rdCAS();
	void going3rdCASFalse();

	void day2Start();

	void show4(bool papersPlaced);

	bool gotoHM();
	void playerPosFromHM();
	void goingHMFalse();

	bool gotoCBA();
	void playerPosFromCBA();
	void goingCBAFalse();

private:
	RenderWindow& window;
	CircTrans circTrans;
	string pName;
	Texture playerTexture;
	Sprite playerSprite;
	Texture bgTexture1;
	Sprite bgSprite1;
	Texture bgTexture2;
	Sprite bgSprite2;

	Texture arrowTexture;
	Sprite arrowSprite;
	Sprite arrowSprite1;
	Sprite arrowSprite2;
	float switchTime;
	float totalTime;
	Vector2u currentImage;
	IntRect arrowRect;

	Text quitText;
	Text pauseText;
	Text task1;
	Font font;
	Text playerName;
	PauseMenu pauseMenu;
	bool gamePaused;
	RectangleShape blackBG;

	bool dPressed;
	bool aPressed;

	Clock clock;
	float dt;

	FloatRect playerBounds;

	View camera;
	float zoom;
	float dampingFactor;

	Vector2f mousePos;
	Vector2f playerToMouse;
	Vector2f targetCenter;
	Vector2f currentCenter;
	Vector2f newCenter;

	bool going3rdCAS;
	bool goingHM;
	bool goingCBA;

	Texture rectTexture;
	Sprite rectSprite;

	Texture wasdTexture;
	Sprite wasdSprite;
	Vector2u currentImageWASD;
	float switchTimeWASD;
	IntRect wasdRect;

	void initPlayer();
	void updateTextPos();

	RectangleShape shape;
	bool isIntersecting(const FloatRect& rect1, const FloatRect& rect2);
	void handleCollision(const Rectangle& rect);
	FloatRect charBounds;
	FloatRect rectBounds;
	FloatRect intersection;
	vector<Rectangle> rectangles;

	bool day2;
	Text task2;
	bool showTask4;
	Text task4;

	Inventory inv;
	Text collectScraps;
};

