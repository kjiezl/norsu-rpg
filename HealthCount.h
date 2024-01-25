#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class HealthCount
{
public:
	HealthCount(RenderWindow& window);
	~HealthCount();

	void showHealth(Vector2f ghostPos, int count);
	void showHealthBoss(Vector2f ghostPos, int count);
	void showHealthBoss2(Vector2f ghostPos, int count);
	void disableCount();
	void render();

private:
	RenderWindow& window;

	Font font;
	Text healthText;
	bool showText;

	void init();
};

