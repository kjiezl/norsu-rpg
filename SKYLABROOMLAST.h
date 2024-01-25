#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "NPC.h"
#include "PlayerName.h"
#include "Skylab.h"

using namespace sf;

class SKYLABROOMLAST
{
public:
	SKYLABROOMLAST(RenderWindow& window);
	~SKYLABROOMLAST();

	void handleInput();
	void update();
	void Camera();
	void render();

	void animUpdate(float dt);
	void npcUpdate(float dt);

	bool gotoCredits();

private:
	RenderWindow& window;
	BlackFadeTransition fadeTrans;
	Sprite playerSprite;
	Texture playerTexture;
	Sprite bgSprite;
	Texture bgTexture;
	Vector2f roomScale;
	Vector2f playerScale;
	View camera;
	float zoom;
	Text quitText;
	Text pauseText;
	Font font;
	PauseMenu pauseMenu;
	bool gamePaused;

	float totalTime;

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

	NPC npc;

	RectangleShape blackBG;

	bool dialogueBoolKweh;
	bool dialogueBoolDes;
	bool dialogueBoolCJ;
	bool dialogueBoolAmeru;
	bool dialogueBoolKit;

	void initPlayer();
	void updateTextPos();

	void kwehDialogueBox();
	void desDialogueBox();
	void cjDialogueBox();
	void ameruDialogueBox();
	void kitDialogueBox();

	RectangleShape shape;
	bool isIntersecting(const FloatRect& rect1, const FloatRect& rect2);
	void handleCollision(const Rectangle& rect);
	FloatRect charBounds;
	FloatRect rectBounds;
	FloatRect intersection;
	vector<Rectangle> rectangles;

	bool startCredits;

	bool dialogue;

	void showDialogue();
};

