#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class CircleTransition
{
public:
	CircleTransition(RenderWindow& window);
	~CircleTransition();

	void update(float dt);
	void render();
	bool isInTransComplete() const;

private:
	RenderWindow& window;
	bool transComplete;
	Texture texture;
	Sprite circleTrans;
	Clock clock;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
	IntRect transRect;
};

