#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "DialogueBox.h"
#include "BlackFadeTransition.h"

using namespace sf;
using namespace std;

class CutScene
{
public:
	CutScene(RenderWindow& window);
	~CutScene();

	void handleInput();
	void scene00();
	void scene0();
	void scene1();
	void scene2();

	void scene03();
	void scene3();

	void scene4();
	void scene5();
	void scene6();
	void scene7();

	void scene8();
	void animUpdate(float dt);
	
private:
	RenderWindow& window;
	DialogueBox dialogueBox;
	BlackFadeTransition fadeTrans;
	Texture bgTexture0, bgTexture1, bgTexture2, skylabroomTex;
	Sprite bgSprite0, bgSprite1, bgSprite2, skylabroomSprite;
	Font font;
	Text text;

	Clock clock;
	float dt;

	bool s1Dialogue;
	bool s2Dialogue;
	bool s03Dialogue;
	bool s4Dialogue;
	bool s5Dialogue;
	bool s6Dialogue;
	bool s8Dialogue;

	void scene1Dia();
	void scene2Dia();
	void scene03Dia();
	void scene4Dia();
	void scene5Dia();
	void scene6Dia();
	void scene8Dia();

	Texture playerTex;
	Sprite playerSprite;
	Texture ghostTex;
	Sprite ghost;

	float totalTime;
	float switchTime;
	Vector2u currentImage;
	IntRect ghostRect;
};

