#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include "BlackFadeTransition.h"
#include "PauseMenu.h"
#include "Skylab.h"

using namespace sf;
using namespace std;

class MainGateNight
{
public:
	MainGateNight(RenderWindow& window, const string& pName);
	~MainGateNight();

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

	bool sceneComplete();

private:
	RenderWindow& window;
	BlackFadeTransition fadeTrans;
	string pName;
	Texture playerTexture;
	Sprite playerSprite;
	Texture bgTexture1;
	Sprite bgSprite1;
	Texture bgTexture2;
	Sprite bgSprite2;

	Texture dfTexture;
	Sprite dfSprite;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
	IntRect dfRect;

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

	Texture rectTexture;
	Sprite rectSprite;

	void initPlayer();
	void updateTextPos();

	RectangleShape shape;
	bool isIntersecting(const FloatRect& rect1, const FloatRect& rect2);
	void handleCollision(const Rectangle& rect);
	FloatRect charBounds;
	FloatRect rectBounds;
	FloatRect intersection;
	vector<Rectangle> rectangles;

	float shakeMagnitude;
	bool isShaking;

	Clock countdown;
	bool fadeOut;
};

