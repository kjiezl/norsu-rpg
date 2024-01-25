#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LoadingScreen
{
public:
	LoadingScreen(RenderWindow& window);
	~LoadingScreen();

	void initLoadingScreen();
	void update(float dt);
	void render();

	bool loadingComplete() const;

	void clockRestart();

	void loadCompleteFalse();

private:
	RenderWindow& window;
	Texture blackTexture;
	Sprite black;
	RectangleShape blackbg;
	Texture charTexture;
	Sprite charSprite;
	float totalTime;
	float switchTime;
	Vector2u currentImage;
	bool loadComplete;
	IntRect charRect;
	Clock clock;

	Texture charbwTexture;
	Sprite char2;
	Sprite char3;
};

