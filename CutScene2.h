#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "DialogueBox.h"
#include "BlackFadeTransition.h"

using namespace sf;
using namespace std;

class CutScene2
{
public:
	CutScene2(RenderWindow& window);
	~CutScene2();

	void handleInput();
	void scene9();
	void scene10();

private:
	RenderWindow& window;
	DialogueBox dialogueBox;
	BlackFadeTransition fadeTrans;
	Texture bgTexture0, bgTexture1, bgTexture2, bgTexture3;
	Sprite bgSprite0, bgSprite1, bgSprite2, bgSprite3;
	Font font;
	Text text;

	Clock clock;
	float dt;

	bool s9Dialogue;
	bool s10Dialogue;

	void scene9Dia();
	void scene10Dia();
};

