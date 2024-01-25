#pragma once
#include "PauseMenu.h"
#include "Inventory.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class Crafting
{
public:
	Crafting(RenderWindow& window);
	~Crafting();

	void handleInput();
	void update();

	void render();

	void showSecondSet(bool yes);

	bool weapon1Chosen();
	bool weapon2Chosen();
	bool weapon3Chosen();

	bool weapon4Chosen();
	bool weapon5Chosen();
	bool weapon6Chosen();

	bool doneChoosing();
	bool doneChoosing2();

private:
	RenderWindow& window;
	PauseMenu pauseMenu;
	Inventory inv;

	Font font;
	Text craftText;
	Text weapon1Text;
	Text weapon2Text;
	Text weapon3Text;
	Text weapon4Text;
	Text weapon5Text;
	Text weapon6Text;

	Texture weapon1Tex;
	Texture weapon2Tex;
	Texture weapon3Tex;
	Texture weapon4Tex;
	Texture weapon5Tex;
	Texture weapon6Tex;

	Sprite weapon1;
	Sprite weapon2;
	Sprite weapon3;
	Sprite weapon4;
	Sprite weapon5;
	Sprite weapon6;

	Texture craftWinTex1;
	Texture craftWinTex2;
	Sprite craftWin1;
	Sprite craftWin2;

	RectangleShape blackBG;
	RectangleShape box1;
	RectangleShape box2;
	RectangleShape box3;

	bool showSecond;

	bool showBox1;
	bool showBox2;
	bool showBox3;

	bool weapon1Clicked;
	bool weapon2Clicked;
	bool weapon3Clicked;
	bool weapon4Clicked;
	bool weapon5Clicked;
	bool weapon6Clicked;
	bool playerChosen;
	bool playerChosen2;

	void init();
};

