#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class BlackFadeTransition
{
public:
	BlackFadeTransition(RenderWindow& window);
	~BlackFadeTransition();

	void updateIn(float dt);
	void renderIn();
	bool isFadedIn() const;

	void updateOut(float dt);
	void renderOut();
	bool isFadedOut() const;

	void fadedInFalse();
	void fadedOutFalse();

private:
	RenderWindow& window;
	
	Texture fadeTexture;
	Sprite fade;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
	bool fadedIn;
	IntRect fadeRect;

	Sprite fade2;
	Vector2u currentImage2;
	float totalTime2;
	float switchTime2;
	bool fadedOut;
	IntRect fadeRect2;

	Clock clock;
};