#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "NPC.h"
#include "PlayerName.h"
#include "Skylab.h"
#include "Inventory.h"

using namespace sf;
using namespace std;

class SkylabRoom
{
public:
	SkylabRoom(RenderWindow& window, const string& pName);
	~SkylabRoom();

	void handleInput();
	void update();
	void Camera();
	void render();
	void setPlayerName(const string& pName) {
		this->pName = pName;
	}

	void animUpdate(float dt);
	void npcUpdate(float dt);

	void goingSkylabFalse();

	bool gotoSkylab();

	bool startScene();

	void day2Start();
	void papersComplete(bool areComplete);

	bool papersPlaced();

private:
	RenderWindow& window;
	BlackFadeTransition fadeTrans;
	string pName;
	Sprite elrico;
	Texture texture;
	Sprite room;
	Texture roomTexture;
	Vector2f roomScale;
	Vector2f playerScale;
	View camera;
	float zoom;
	Text quitText;
	Text pauseText;
	Text task1;
	Font font;
	Text playerName;
	PauseMenu pauseMenu;
	bool gamePaused;
	RectangleShape nightTint;

	PlayerName playerNameClass;

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

	bool goingSkylab;

	RectangleShape blackBG;

	Text exitDoorText;
	bool showExitText;

	Texture arrowTexture;
	Sprite arrowSprite;
	Sprite arrowSprite2;
	Vector2u currentImageArrow;
	float switchTimeArrow;
	IntRect arrowRect;

	bool startCutScene;

	bool dialogueBoolKweh;
	bool dialogueBoolDes;
	bool dialogueBoolCJ;
	bool dialogueBoolAmeru;
	bool dialogueBoolKit;

	void initPlayer();
	void updateTextPos();
	void exitText();

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

	bool day2;
	Text task2;
	Text task3;
	bool showTask4;
	Text task4;
	Texture paperTex;
	Sprite paperStack;
	bool completePapers;
	bool showPaper;

	Inventory inv;

	SoundBuffer paperPlacedBuffer;
	Sound paperPlacedSFX;
};

