#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "PauseMenu.h"
#include "CircTrans.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "NPC.h"
#include "Skylab.h"
#include "Inventory.h"

using namespace sf;
using namespace std;

class Game
{
public:
	Game(RenderWindow& window, const string& pName);
	~Game();

	void handleInput();
	void update();
	void Camera();
	void render();
	void setPlayerName(const string& pName) {
		this -> pName = pName;
	}

	void animUpdate(float dt);
	void catUpdate(float dt);

	bool gotoSkylab();
	bool gotoMainGate();

	void playerPosFromSkylab();
	void goingSkylabFalse();

	void playerPosFromMainGate();
	void goingMainGateFalse();

	void day2Start();

	bool isCJCollected();

	void goingHM(bool papersPlaced);

private:
	RenderWindow& window;
	CircTrans circTrans;
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

	Texture animTexture;
	Sprite animSprite;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
	IntRect animRect;

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

	float xVeloGhost;
	float yVeloGhost;
	Vector2f ghostPos;

	Sprite topLeft;
	Sprite bottomLeft;
	Sprite topRight;
	Sprite bottomRight;
	Texture borderTexture;

	Texture vignetteTexture;
	Sprite vignette;
	Vector2f vignetteScale;

	RectangleShape borderShape;
	bool isChasing;

	DialogueBox dialogueBox;
	bool dialogueBoolCat;

	NPC npc;

	Clock cooldown;
	CircleShape projectile;
	bool projectileShot;
	Vector2f projectileDirection;
	Texture broomTexture;
	Sprite broomSprite;
	Vector2f broomToMouse;

	bool goingSkylab;
	bool goingMainGate;

	RectangleShape blackBG;

	Texture arrowTexture;
	Sprite arrowSprite;
	Vector2u currentImageArrow;
	float switchTime2;
	IntRect arrowRect;

	Sprite arrowSprite2;

	void initPlayer();
	void updateTextPos();
	void catDialogueBox();

	RectangleShape shape;
	bool isIntersecting(const FloatRect& rect1, const FloatRect& rect2);
	void handleCollision(const Rectangle& rect);
	FloatRect charBounds;
	FloatRect rectBounds;
	FloatRect intersection;
	vector<Rectangle> rectangles;

	bool day2;
	Text task2;
	bool dialogueBoolCJ;
	void cjDialogueBox();
	Text hwCountText;
	int hwCount;
	bool hwComplete;
	bool cjCollected;
	bool showCJ;
	bool showTask4;
	Text task4;

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

	SoundBuffer paperBuffer;
	Sound paperSFX;
	SoundBuffer itemBuffer;
	Sound itemSFX;
};