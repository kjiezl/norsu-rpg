#include "NPC.h"
#include <SFML/Graphics.hpp>

using namespace sf;

NPC::NPC(RenderWindow& window) : window(window), day2(false) {

	arrowTexture.loadFromFile("sprites\\ui\\dialogue-arrow.png");
	arrowKweh.setTexture(arrowTexture);
	arrowDes.setTexture(arrowTexture);
	arrowCJ.setTexture(arrowTexture);
	arrowAmeru.setTexture(arrowTexture);
	arrowKit.setTexture(arrowTexture);
	arrowCat.setTexture(arrowTexture);
	arrowBleh.setTexture(arrowTexture);

	catTexture.loadFromFile("sprites\\characters\\cat1.png");
	catSprite.setTexture(catTexture);
	catSprite2.setTexture(catTexture);
	catRect.width = catTexture.getSize().x / 8;
	catRect.height = catTexture.getSize().y / 1;
	totalTime = 0.0f;
	totalTime2 = 0.0f;
	switchTime = 0.4f;
	switchTime2 = 0.4f;
	currentImage.x = 0;

	blehTexture.loadFromFile("sprites\\characters\\dance2.png");
	blehSprite.setTexture(blehTexture);
	blehRect.width = blehTexture.getSize().x / 8;
	blehRect.height = blehTexture.getSize().x / 8;
	currentImage2.x = 0;

	kwehTexture.loadFromFile("sprites\\characters\\kweh1.png");
	kwehSprite.setTexture(kwehTexture);
	kwehSprite2.setTexture(kwehTexture);
	kwehSprite3.setTexture(kwehTexture);
	kwehRect.width = kwehTexture.getSize().x / 8;
	kwehRect.height = kwehTexture.getSize().y / 2;
	currentImage3.x = 0;

	desTexture.loadFromFile("sprites\\characters\\desu.png");
	desSprite.setTexture(desTexture);
	desSprite2.setTexture(desTexture);
	desSprite3.setTexture(desTexture);
	desRect.width = desTexture.getSize().x / 8;
	desRect.height = desTexture.getSize().y / 2;
	currentImage4.x = 0;

	cjTexture.loadFromFile("sprites\\characters\\sijeh.png");
	cjSprite.setTexture(cjTexture);
	cjSprite2.setTexture(cjTexture);
	cjSprite3.setTexture(cjTexture);
	cjRect.width = cjTexture.getSize().x / 6;
	cjRect.height = cjTexture.getSize().y / 2;
	currentImage5.x = 0;

	ameruTexture.loadFromFile("sprites\\characters\\ameru.png");
	ameruSprite.setTexture(ameruTexture);
	ameruSprite2.setTexture(ameruTexture);
	ameruSprite3.setTexture(ameruTexture);
	ameruRect.width = ameruTexture.getSize().x / 8;
	ameruRect.height = ameruTexture.getSize().y / 2;
	currentImage6.x = 0;

	kitTexture.loadFromFile("sprites\\characters\\kit.png");
	kitSprite.setTexture(kitTexture);
	kitSprite2.setTexture(kitTexture);
	kitSprite3.setTexture(kitTexture);
	kitRect.width = kitTexture.getSize().x / 8;
	kitRect.height = kitTexture.getSize().y / 2;
	currentImage7.x = 0;

	initNPC();
}

NPC::~NPC() {

}

void NPC::day2Start() {
	day2 = true;
}

void NPC::initNPC() {
	catSprite.setPosition(1200, 150);
	catSprite.setScale(Vector2f(1.75f, 1.75f));

	blehSprite.setPosition(900, 150);

	kwehSprite.setPosition(700, 465);
	kwehSprite.setScale(Vector2f(1.75f, 1.75f));

	desSprite.setPosition(540, 460);
	desSprite.setScale(Vector2f(1.75f, 1.75f));

	cjSprite.setPosition(475, 215);
	cjSprite.setScale(Vector2f(1.75f, 1.75f));

	ameruSprite.setPosition(755, 250);
	ameruSprite.setScale(Vector2f(1.75f, 1.75f));

	kitSprite.setPosition(380, 463);
	kitSprite.setScale(Vector2f(1.75f, 1.75f));

	// DAY 2 POS
	catSprite2.setPosition(735, 250);
	catSprite2.setScale(Vector2f(1.75f, 1.75f));

	cjSprite2.setPosition(500, 170);
	cjSprite2.setScale(Vector2f(1.75f, 1.75f));

	kwehSprite2.setPosition(3325, 85);
	kwehSprite2.setScale(Vector2f(1.75f, 1.75f));

	desSprite2.setPosition(500, 170);
	desSprite2.setScale(Vector2f(1.75f, 1.75f));

	ameruSprite2.setPosition(285, 170);
	ameruSprite2.setScale(Vector2f(1.75f, 1.75f));

	kitSprite2.setPosition(1730, 320);
	kitSprite2.setScale(Vector2f(1.75f, 1.75f));

	// last scene
	cjSprite3.setPosition(430, 215);
	cjSprite3.setScale(Vector2f(1.75f, 1.75f));

	kwehSprite3.setPosition(600, 240);
	kwehSprite3.setScale(Vector2f(1.75f, 1.75f));

	desSprite3.setPosition(500, 250);
	desSprite3.setScale(Vector2f(1.75f, 1.75f));

	ameruSprite3.setPosition(755, 320);
	ameruSprite3.setScale(Vector2f(1.75f, 1.75f));

	kitSprite3.setPosition(745, 460);
	kitSprite3.setScale(Vector2f(1.75f, 1.75f));
}

void NPC::catUpdate(float dt) {
	currentImage.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= 8) {
			currentImage.x = 0;
		}
	}

	catRect.left = currentImage.x * catRect.width;
	catRect.top = currentImage.y * catRect.height;
}

void NPC::animUpdate(float dt2) {
	currentImage2.y = 5;
	currentImage3.y = 0;
	currentImage4.y = 1;
	currentImage5.y = 0;
	currentImage6.y = 0;
	currentImage7.y = 0;
	totalTime2 += dt2;

	if (totalTime2 >= switchTime2) {
		totalTime2 -= switchTime2;
		currentImage2.x++;
		currentImage3.x++;
		currentImage4.x++;
		currentImage5.x++;
		currentImage6.x++;
		currentImage7.x++;

		if (currentImage2.x >= 8) {
			currentImage2.x = 0;
		}

		if (currentImage3.x >= 8) {
			currentImage3.x = 0;
		}

		if (currentImage4.x >= 8) {
			currentImage4.x = 0;
		}

		if (currentImage5.x >= 6) {
			currentImage5.x = 0;
		}

		if (currentImage6.x >= 8) {
			currentImage6.x = 0;

		}

		if (currentImage7.x >= 8) {
			currentImage7.x = 0;

		}

		blehRect.left = currentImage2.x * blehRect.width;
		blehRect.top = currentImage2.y * blehRect.height;
		kwehRect.left = currentImage3.x * kwehRect.width;
		kwehRect.top = currentImage3.y * kwehRect.height;
		desRect.left = currentImage4.x * desRect.width;
		desRect.top = currentImage4.y * desRect.height;
		cjRect.left = currentImage5.x * cjRect.width;
		cjRect.top = currentImage5.y * cjRect.height;
		ameruRect.left = currentImage6.x * ameruRect.width;
		ameruRect.top = currentImage6.y * ameruRect.height;
		kitRect.left = currentImage7.x * kitRect.width;
		kitRect.top = currentImage7.y * kitRect.height;
	}
}

void NPC::update() {
	
}

void NPC::render() {
	catSprite.setTextureRect(catRect);
	catSprite2.setTextureRect(catRect);
	if (!day2) {
		window.draw(catSprite);
	}
	else {
		window.draw(catSprite2);
	}
	blehSprite.setTextureRect(blehRect);
	//window.draw(blehSprite);
}

void NPC::renderCat() {
	catSprite2.setTextureRect(catRect);
	window.draw(catSprite2);
}

void NPC::renderKweh() {
	kwehSprite.setTextureRect(kwehRect);
	kwehSprite2.setTextureRect(kwehRect);
	if (!day2) {
		window.draw(kwehSprite);
	}
	else {
		window.draw(kwehSprite2);
	}
}

void NPC::renderDes() {
	desSprite.setTextureRect(desRect);
	desSprite2.setTextureRect(desRect);
	if (!day2) {
		window.draw(desSprite);
	}
	else {
		window.draw(desSprite2);
	}
}

void NPC::renderCJ() {
	cjSprite.setTextureRect(cjRect);
	cjSprite2.setTextureRect(cjRect);
	if (!day2) {
		window.draw(cjSprite);
	}
	else {
		window.draw(cjSprite2);
	}
}

void NPC::renderAmeru() {
	ameruSprite.setTextureRect(ameruRect);
	ameruSprite2.setTextureRect(ameruRect);
	if (!day2) {
		window.draw(ameruSprite);
	}
	else {
		window.draw(ameruSprite2);
	}
}

void NPC::renderKit() {
	kitSprite.setTextureRect(kitRect);
	kitSprite2.setTextureRect(kitRect);
	if (!day2) {
		window.draw(kitSprite);
	}
	else {
		window.draw(kitSprite2);
	}
}

void NPC::renderKweh3() {
	kwehSprite3.setTextureRect(kwehRect);
	window.draw(kwehSprite3);
}

void NPC::renderDes3() {
	desSprite3.setTextureRect(desRect);
	window.draw(desSprite3);
}

void NPC::renderCJ3() {\
	cjSprite3.setTextureRect(cjRect);
	window.draw(cjSprite3);
}

void NPC::renderAmeru3() {
	ameruSprite3.setTextureRect(ameruRect);
	window.draw(ameruSprite3);
}

void NPC::renderKit3() {
	kitSprite3.setTextureRect(kitRect);
	window.draw(kitSprite3);
}

Vector2f NPC::catPos() {
	return Vector2f(catSprite.getPosition().x + 25, catSprite.getPosition().y + 10);
}

Vector2f NPC::catPos2() {
	return Vector2f(catSprite2.getPosition().x + 25, catSprite2.getPosition().y + 10);
}

Vector2f NPC::blehPos() {
	return Vector2f(blehSprite.getPosition().x + 70, blehSprite.getPosition().y + 30);
}

Vector2f NPC::kwehPos() {
	if (!day2) {
		return Vector2f(kwehSprite.getPosition().x + 25, kwehSprite.getPosition().y + 25);
	}
	else {
		return Vector2f(kwehSprite2.getPosition().x + 25, kwehSprite2.getPosition().y + 25);
	}
}

Vector2f NPC::desPos() {
	if (!day2) {
		return Vector2f(desSprite.getPosition().x + 25, desSprite.getPosition().y + 25);
	}
	else {
		return Vector2f(desSprite2.getPosition().x + 25, desSprite2.getPosition().y + 25);
	}
}

Vector2f NPC::cjPos() {
	if (!day2) {
		return Vector2f(cjSprite.getPosition().x + 25, cjSprite.getPosition().y + 25);
	}
	else {
		return Vector2f(cjSprite2.getPosition().x + 25, cjSprite2.getPosition().y + 25);
	}
}

Vector2f NPC::ameruPos() {
	if (!day2) {
		return Vector2f(ameruSprite.getPosition().x + 25, ameruSprite.getPosition().y + 25);
	}
	else {
		return Vector2f(ameruSprite2.getPosition().x + 25, ameruSprite2.getPosition().y + 25);
	}
}

Vector2f NPC::kitPos() {
	if (!day2) {
		return Vector2f(kitSprite.getPosition().x + 25, kitSprite.getPosition().y + 25);
	}
	else {
		return Vector2f(kitSprite2.getPosition().x + 25, kitSprite2.getPosition().y + 25);
	}
}

Vector2f NPC::kwehPos3() {
	return Vector2f(kwehSprite3.getPosition().x + 25, kwehSprite3.getPosition().y + 25);
}

Vector2f NPC::desPos3() {
	return Vector2f(desSprite3.getPosition().x + 25, desSprite3.getPosition().y + 25);
}

Vector2f NPC::cjPos3() {
	return Vector2f(cjSprite3.getPosition().x + 25, cjSprite3.getPosition().y + 25);
}

Vector2f NPC::ameruPos3() {
	return Vector2f(ameruSprite3.getPosition().x + 25, ameruSprite3.getPosition().y + 25);
}

Vector2f NPC::kitPos3() {
	return Vector2f(kitSprite3.getPosition().x + 25, kitSprite3.getPosition().y + 25);
}

void NPC::showArrowCat() {
	arrowCat.setPosition(catSprite.getPosition().x + 23, catSprite.getPosition().y + 17);
	arrowCat.setScale(1.0f, 1.0f);
	window.draw(arrowCat);
}

void NPC::showArrowBleh() {
	arrowBleh.setPosition(blehSprite.getPosition().x + 63, blehSprite.getPosition().y + 5);
	arrowBleh.setScale(1.0f, 1.0f);
	window.draw(arrowBleh);
}

void NPC::showArrowKweh() {
	if (!day2) {
		arrowKweh.setPosition(kwehSprite.getPosition().x + 20, kwehSprite.getPosition().y - 15);
	}
	else {
		arrowKweh.setPosition(kwehSprite2.getPosition().x + 20, kwehSprite2.getPosition().y - 15);
	}
	arrowKweh.setScale(1.0f, 1.0f);
	window.draw(arrowKweh);
}

void NPC::showArrowDes() {
	if (!day2) {
		arrowDes.setPosition(desSprite.getPosition().x + 20, desSprite.getPosition().y - 13);
	}
	else {
		arrowDes.setPosition(desSprite2.getPosition().x + 20, desSprite2.getPosition().y - 13);
	}
	arrowDes.setScale(1.0f, 1.0f);
	window.draw(arrowDes);
}

void NPC::showArrowCJ() {
	if (!day2) {
		arrowCJ.setPosition(cjSprite.getPosition().x + 20, cjSprite.getPosition().y - 13);
	}
	else {
		arrowCJ.setPosition(cjSprite2.getPosition().x + 20, cjSprite2.getPosition().y - 13);
	}
	arrowCJ.setScale(1.0f, 1.0f);
	window.draw(arrowCJ);
}

void NPC::showArrowAmeru() {
	if (!day2) {
		arrowAmeru.setPosition(ameruSprite.getPosition().x + 20, ameruSprite.getPosition().y - 13);
	}
	else {
		arrowAmeru.setPosition(ameruSprite2.getPosition().x + 20, ameruSprite2.getPosition().y - 13);
	}
	arrowCJ.setScale(1.0f, 1.0f);
	window.draw(arrowAmeru);
}

void NPC::showArrowKit() {
	if (!day2) {
		arrowKit.setPosition(kitSprite.getPosition().x + 20, kitSprite.getPosition().y - 13);
	}
	else {
		arrowKit.setPosition(kitSprite2.getPosition().x + 20, kitSprite2.getPosition().y - 13);
	}
	arrowKit.setScale(1.0f, 1.0f);
	window.draw(arrowKit);
}

void NPC::showArrowKweh3() {
	arrowKweh.setPosition(kwehSprite3.getPosition().x + 20, kwehSprite3.getPosition().y - 15);
	arrowKweh.setScale(1.0f, 1.0f);
	window.draw(arrowKweh);
}

void NPC::showArrowDes3() {
	arrowDes.setPosition(desSprite3.getPosition().x + 20, desSprite3.getPosition().y - 13);
	arrowDes.setScale(1.0f, 1.0f);
	window.draw(arrowDes);
}

void NPC::showArrowCJ3() {
	arrowCJ.setPosition(cjSprite3.getPosition().x + 20, cjSprite3.getPosition().y - 13);
	arrowCJ.setScale(1.0f, 1.0f);
	window.draw(arrowCJ);
}

void NPC::showArrowAmeru3() {
	arrowAmeru.setPosition(ameruSprite3.getPosition().x + 20, ameruSprite3.getPosition().y - 13);
	arrowCJ.setScale(1.0f, 1.0f);
	window.draw(arrowAmeru);
}

void NPC::showArrowKit3() {
	arrowKit.setPosition(kitSprite3.getPosition().x + 20, kitSprite3.getPosition().y - 13);
	arrowKit.setScale(1.0f, 1.0f);
	window.draw(arrowKit);
}