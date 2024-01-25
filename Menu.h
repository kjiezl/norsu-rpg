#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Menu
{
public:
	Menu(RenderWindow& window);
	~Menu();

	void handleInput();
	void update(float dt);
	void update2(float dt);
	void render();
	bool startButtonPressed() const;

private:
	RenderWindow& window;
	Font font;
	Text buttonText;
	Text button1Text;
	Texture button;
	Texture button1;
	Sprite startButton;
	Sprite exitButton;
	int selectedButton;
	bool startPressed;
	Texture bgTexture;
	Sprite bg;
	Vector2f bgScale;
	Vector2f startScale;

	//Texture titleTex;
	//Sprite title;

	Vector2u currentImage;
	float totalTime;
	float switchTime;
	Clock clock;
	IntRect bgRect;

	Texture petalsTexture;
	Sprite petals;
	float switchTime2;
	float totalTime2;
	Vector2u currentImage2;
	IntRect petalsRect;

	SoundBuffer menuBuffer;
	Sound menuBGM;

	void initButtons();
	void moveUp();
	void moveDown();
	void updateButtonState();
};

