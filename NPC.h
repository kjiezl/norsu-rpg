#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class NPC
{
public:
	NPC(RenderWindow& window);
	~NPC();

	void initNPC();
	void catUpdate(float dt);
	void animUpdate(float dt2);
	void update();
	void render();

	Vector2f catPos();
	Vector2f catPos2();
	Vector2f blehPos();
	Vector2f kwehPos();
	Vector2f desPos();
	Vector2f cjPos();
	Vector2f ameruPos();
	Vector2f kitPos();

	Vector2f kwehPos3();
	Vector2f desPos3();
	Vector2f cjPos3();
	Vector2f ameruPos3();
	Vector2f kitPos3();

	void renderKweh();
	void renderDes();
	void renderCJ();
	void renderAmeru();
	void renderKit();

	void renderKweh3();
	void renderDes3();
	void renderCJ3();
	void renderAmeru3();
	void renderKit3();

	void renderCat();

	void showArrowCat();
	void showArrowBleh();
	void showArrowKweh();
	void showArrowDes();
	void showArrowCJ();
	void showArrowAmeru();
	void showArrowKit();

	void showArrowKweh3();
	void showArrowDes3();
	void showArrowCJ3();
	void showArrowAmeru3();
	void showArrowKit3();
	
	void day2Start();

private:
	RenderWindow& window;
	Texture arrowTexture;

	Sprite arrowCat;
	Sprite arrowBleh;
	Sprite arrowKweh;
	Sprite arrowDes;
	Sprite arrowCJ;
	Sprite arrowAmeru;
	Sprite arrowKit;

	Texture catTexture;
	Sprite catSprite;
	Sprite catSprite2;
	Vector2u currentImage;
	float totalTime;
	float totalTime2;
	float switchTime;
	float switchTime2;
	IntRect catRect;

	Texture blehTexture;
	Sprite blehSprite;
	Vector2u currentImage2;
	IntRect blehRect;

	Texture kwehTexture;
	Sprite kwehSprite;
	Sprite kwehSprite2;
	Sprite kwehSprite3;
	Vector2u currentImage3;
	IntRect kwehRect;

	Texture desTexture;
	Sprite desSprite;
	Sprite desSprite2;
	Sprite desSprite3;
	Vector2u currentImage4;
	IntRect desRect;

	Texture cjTexture;
	Sprite cjSprite;
	Sprite cjSprite2;
	Sprite cjSprite3;
	Vector2u currentImage5;
	IntRect cjRect;

	Texture ameruTexture;
	Sprite ameruSprite;
	Sprite ameruSprite2;
	Sprite ameruSprite3;
	Vector2u currentImage6;
	IntRect ameruRect;

	Texture kitTexture;
	Sprite kitSprite;
	Sprite kitSprite2;
	Sprite kitSprite3;
	Vector2u currentImage7;
	IntRect kitRect;

	bool day2;
};

