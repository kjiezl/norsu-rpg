#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DialogueBox.h"
#include "BlackFadeTransition.h"
#include "PauseMenu.h"
#include "Skylab.h"
#include "Inventory.h"

using namespace sf;

class CBARoomDay
{
public:
	CBARoomDay(RenderWindow& window);
	~CBARoomDay();

	void handleInput();
	void update();
	void animUpdate(float dt);
	void Camera();
	void render();

	bool gotoCBA();
	void playerPosFromCBA();
	void goingCBAFalse();

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

	bool showTask4;
};

