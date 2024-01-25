#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DialogueBox.h"
#include "BlackFadeTransition.h"
#include "PauseMenu.h"
#include "Skylab.h"

using namespace sf;

class CBARoom
{
public:
	CBARoom(RenderWindow& window);
	~CBARoom();

	void handleInput();
	void update();
	void animUpdate(float dt);
	void Camera();
	void render();

	bool gotoCBA();
	void playerPosFromCBA();
	void goingCBAFalse();

	bool startScene();

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

	bool goingCBA;

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

	Texture orbTex;
	Sprite orbSprite;
	float totalTime;
	float switchTime;
	Vector2u currentImage;
	IntRect orbRect;

	bool startCutScene;
};

