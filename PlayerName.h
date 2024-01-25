#pragma once
#include "BlackFadeTransition.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class PlayerName
{
public:
	PlayerName(RenderWindow& window);
	~PlayerName();

	void handleInput();
	void update();
	void render();
	bool getEnter() const;

	const string& getPlayerName() const;

	void setSkylab();
	void setSkylabRoom();

private:
	RenderWindow& window;
	Texture bgTexture;
	Texture nameInputTexture;
	Sprite bg;
	Sprite nameInput;
	Text elricoText;
	Font font;
	Vector2f bgScale;
	Vector2f nameScale;
	string playerName;
	bool showElrico;
	Text playerNameText;
	bool nameEntered;

	View camera;

	BlackFadeTransition fadeTrans;
	Clock clock;
	float dt;

	void initPlayer();
};

