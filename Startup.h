#pragma once
#include "BlackFadeTransition.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Startup
{
public:
	Startup(RenderWindow& window);
	~Startup();

	void handleInput();
	void update();
	void animUpdate(float dt);
	void render();

	bool startComplete();

private:
	RenderWindow& window;
	RectangleShape whiteBG;
	
	Texture logoTexture;
	Sprite logoSprite;
	Texture logo1Texture;
	Sprite logo1Sprite;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
	IntRect logoRect;
	bool animComplete;
	bool logoComplete;
	bool startCount;
	bool startLogo;

	Sound logoBGM;
	SoundBuffer logoBuffer;

	Clock clock;
};

