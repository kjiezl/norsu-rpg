#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "DialogueBox.h"
#include "PlayerName.h"
#include "NPC.h"
#include "Inventory.h"

using namespace sf;
using namespace std;

class Rectangle {
public:
	RectangleShape shape;

	Rectangle(float x, float y, float width, float height, float transparency = 255.0f) {
		shape.setPosition(x, y);
		shape.setSize(sf::Vector2f(width, height));
		shape.setFillColor(sf::Color(0, 255, 0, static_cast<sf::Uint8>(transparency)));
	}
};

class Skylab
{
public:
	Skylab(RenderWindow& window, const string& pName);
	~Skylab();

	void handleInput();
	void update();
	void Camera();
	void render();
	void setPlayerName(const string& pName) {
		this->pName = pName;
	}

	void animUpdate(float dt);

	void playerPosFrom3rdCAS();
	void going3rdCASFalse();
	void goingSkylabRoomFalse();

	bool goto3rdCAS();
	bool gotoSkylabRoom();

	void isCJCollected(bool isCollected);
	void day2Start();

	bool papersComplete();

	void cjDialogue(bool papersPlaced);

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

	bool going3rdCAS;
	bool goingSkylabRoom;

	RectangleShape blackBG;

	Texture arrowTexture;
	Sprite arrowSprite;
	Vector2u currentImageArrow;
	float switchTimeArrow;
	IntRect arrowRect;

	Text enterDoorText;
	bool showEnterText;

	void initPlayer();
	void updateTextPos();
	void enterText();

	RectangleShape shape;
	bool isIntersecting(const FloatRect& rect1, const FloatRect& rect2);
	void handleCollision(const Rectangle& rect);
	FloatRect charBounds;
	FloatRect rectBounds;
	FloatRect intersection;
	vector<Rectangle> rectangles;

	NPC npc;
	bool day2;
	Text task2;
	Text task3;
	Text hwCountText;
	int hwCount;
	bool hwComplete;
	bool showTask3;
	bool showNPCs;
	bool showCJ;

	bool cjCollected;
	bool desCollected;
	bool kitCollected;
	bool ameruCollected;
	bool kwehCollected;

	bool dialogueBoolDes;
	bool dialogueBoolKweh;
	bool dialogueBoolKit;
	bool dialogueBoolAmeru;
	bool dialogueBoolCJ;

	void desDialogueBox();
	void kwehDialogueBox();
	void kitDialogueBox();
	void ameruDialogueBox();
	void cjDialogueBox();

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
	Sprite metal3;

	vector<Sprite> item1;
	vector<Sprite> item2;

	Inventory inv;

	bool hide1;
	bool hide2;
	bool hide3;
	bool hide4;
	bool hide5;

	SoundBuffer paper1Buffer;
	Sound paper1SFX;
	SoundBuffer paper2Buffer;
	Sound paper2SFX;
	SoundBuffer itemBuffer;
	Sound itemSFX;
};

