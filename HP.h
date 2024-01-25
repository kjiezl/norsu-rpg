#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

class HP
{
public:
	HP(RenderWindow& window, float maxHealth);
	~HP();

	void update();
	void render();

	void setHealth(float max);

	void damage(float hit);
	void resetHealth();
	bool noHP();

private:
	RenderWindow& window;

	Texture barTex;
	Texture fillTex;

	Sprite barSprite;
	Sprite fillSprite;

	bool dead;

	float maxHealth;
	float currentHealth;

	void init();
};

