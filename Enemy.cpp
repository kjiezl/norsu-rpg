#include "Enemy.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Enemy::Enemy(Texture& texture, Vector2f position) : enemySprite(texture) {
	enemySprite.setPosition(position);
}