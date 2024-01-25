#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class CircTrans
{
public:
	CircTrans(RenderWindow& window);
	~CircTrans();

	void update(float dt);
	void render();
	bool isOutTransComplete() const;

private:
	RenderWindow& window;
	bool transComplete;
	Texture texture;
	Sprite circleTrans;
	Vector2u currentImage;
	float totalTime;
	float switchTime;
	IntRect transRect;
};