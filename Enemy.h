#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Enemy
{
public:
	Enemy(Texture& texture, Vector2f position);
	~Enemy();

	void update(float dt);
	void render();

private:
	Sprite enemySprite;
};

