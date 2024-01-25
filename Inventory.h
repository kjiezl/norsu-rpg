#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

class Inventory
{
public:
	Inventory(RenderWindow& window);
	~Inventory();

	void addItem1();
	void addItem2();
	void addItem3();

	void updateTextPos();

	void render();

	int item1Total();
	int item2Total();
	int item3Total();

	void weapon1Crafted();
	void weapon2Crafted();
	void weapon3Crafted();

	void weapon4Crafted();
	void weapon5Crafted();
	void weapon6Crafted();

	static int item1Count;
	static int item2Count;
	static int item3Count;

	float calcuDistance(Vector2f v1, Vector2f v2);

private:
	RenderWindow& window;

	Texture item1Tex;
	Texture item2Tex;
	Texture item3Tex;

	Sprite item1;
	Sprite item2;
	Sprite item3;

	Font font;
	Text item1Text;
	Text item2Text;
	Text item3Text;

	bool crafted1;
	bool crafted2;
	bool crafted3;

	bool crafted4;
	bool crafted5;
	bool crafted6;

	void init();
};

