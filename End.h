#pragma once
#include "BlackFadeTransition.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class End
{
public:
	End(RenderWindow& window);
	~End();

	void initEnd();
	void handleInput();
	void animupdate(float dt);
	void update();
	void render();

private:
	RenderWindow& window;
	Sprite bg;
	Texture bgTexture;
	Font font;
	Text creditsText;
	Text membersText;
	Text burgerText;
	Text thanks;
	Vector2f bgScale;

	Text kwehText;
	Text desText;
	Text cjText;
	Text ameruText;
	Text kitText;

	BlackFadeTransition fadeTrans;
	Clock clock;
	float dt;

	RectangleShape blackFill;

	float totalTime;
	float switchTime;

	Texture kwehTexture;
	Sprite kwehSprite;
	Sprite kwehSprite2;
	Sprite kwehSprite3;
	Vector2u currentImage3;
	IntRect kwehRect;

	Texture desTexture;
	Sprite desSprite;
	Sprite desSprite2;
	Sprite desSprite3;
	Vector2u currentImage4;
	IntRect desRect;

	Texture cjTexture;
	Sprite cjSprite;
	Sprite cjSprite2;
	Sprite cjSprite3;
	Vector2u currentImage5;
	IntRect cjRect;

	Texture ameruTexture;
	Sprite ameruSprite;
	Sprite ameruSprite2;
	Sprite ameruSprite3;
	Vector2u currentImage6;
	IntRect ameruRect;

	Texture kitTexture;
	Sprite kitSprite;
	Sprite kitSprite2;
	Sprite kitSprite3;
	Vector2u currentImage7;
	IntRect kitRect;
};

