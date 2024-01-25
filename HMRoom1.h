#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "DialogueBox.h"
#include "BlackFadeTransition.h"
#include "PauseMenu.h"
#include "Skylab.h"

using namespace sf;

class HMRoom1
{
public:
	HMRoom1(RenderWindow& window);
	~HMRoom1();

	void handleInput();
	void update();
	void animUpdate(float dt);
	void Camera();
	void render();

	bool gotoHM();
	void playerPosFromHM();
	void goingHMFalse();

	bool bossDead();

	void setWeapon1();
	void setWeapon2();
	void setWeapon3();

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

	bool goingHM;

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

	Clock cooldown;
	RectangleShape projectile;
	bool projectileShot;
	Vector2f projectileDirection;
	float shakeTime;
	float shakeMagnitude;
	bool isShaking;
	Clock shakeClock;
	vector<RectangleShape> projectiles;

	Texture broomItemTexture;
	Sprite broomItemSprite;
	Vector2f broomToMouse;

	bool weapon1Show;
	bool weapon2Show;
	bool weapon3Show;

	Texture weapon1Texture;
	Sprite weapon1Sprite;
	Texture weapon2Texture;
	Sprite weapon2Sprite;
	Texture weapon3Texture;
	Sprite weapon3Sprite;

	SoundBuffer ghostDeathBuffer;
	Sound ghostDeathSFX;
	SoundBuffer shootBuffer;
	Sound shootSFX;

	bool bossDefeated;
	bool dialogue;
	void showDialogue();
};

