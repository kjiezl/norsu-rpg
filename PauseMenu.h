#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PauseMenu
{
public:
	PauseMenu(RenderWindow& window);
	~PauseMenu();
	void handleInput();
	void update();
	void render();

	bool resumeButtonPressed() const;
	bool quitGameButtonPressed() const;

private:
	RenderWindow& window;
	Font font;
	Text resumeText;
	Text quitGameText;
	Text gamePausedText;
	RectangleShape overlay;

	bool resumed;
	bool quitGame;
	int selectedButton;
	bool resumePressed;
	bool quitGamePressed;

	void initPauseMenu();
	void moveUp();
	void moveDown();
	void updateButtonState();
};

