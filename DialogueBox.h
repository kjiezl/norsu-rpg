#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

class DialogueBox
{
public:
	DialogueBox(RenderWindow& window);
	~DialogueBox();

	void initDialogue(const string& textString);
	void update();
	void render();

	bool isTextComplete() const;
	void isEnterPressed(bool enterIsPressed);

	bool farFromPlayer(bool playerFar);

	void reset();

private:
	RenderWindow& window;
	Texture boxTexture;
	Sprite boxSprite;
	String textString;
	Text text;
	Font font;

	String fullText;
	Clock clock;
	size_t displayIndex;
	float typeSpeed;
	Clock elapsedTypingTime;

	bool enterPressed;
	bool textComplete;

	SoundBuffer blipBuffer;
	Sound blipSFX;
};