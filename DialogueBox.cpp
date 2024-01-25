#include "DialogueBox.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;
using namespace std;

DialogueBox::DialogueBox(RenderWindow& window) : window(window), displayIndex(0), typeSpeed(0.1f), textComplete(false), enterPressed(false) {
	boxTexture.loadFromFile("sprites\\ui\\dialoguebox.png");
	font.loadFromFile("fonts\\minecraft\\Minecraft.ttf");
	text.setFont(font);
	text.setFillColor(Color::White);
	text.setCharacterSize(30);
	boxSprite.setTexture(boxTexture);
	boxSprite.setScale(Vector2f(1.5f, 0.3f));
	blipBuffer.loadFromFile("sprites\\sfx\\dialogue.ogg");
	blipSFX.setBuffer(blipBuffer);
}

DialogueBox::~DialogueBox() {

}

void DialogueBox::initDialogue(const string& textString) {
	textComplete = false;
	enterPressed = false;
	boxSprite.setPosition(Vector2f(-200, 550));
	fullText = textString;
	text.setPosition(Vector2f(boxSprite.getPosition().x + 250, boxSprite.getPosition().y + 50));
}

void DialogueBox::update() {
	textComplete = false;
	float elapsedTime = elapsedTypingTime.getElapsedTime().asSeconds();
	bool isEnterPressed = Keyboard::isKeyPressed(Keyboard::Enter);

	if (elapsedTime >= typeSpeed && displayIndex <= fullText.getSize() && !textComplete) {
		text.setString(fullText.substring(0, displayIndex));
		displayIndex++;
		blipSFX.pause();
		blipSFX.play();
	}
	else {
		blipSFX.stop();
	}

	if (isEnterPressed) {
		text.setString(fullText);
		textComplete = true;
	}
}

void DialogueBox::reset() {
	textComplete = false;
	text.setString("");
	displayIndex = 0;
}

bool DialogueBox::farFromPlayer(bool playerFar){
	if (playerFar) {
		blipSFX.stop();
		textComplete = true;
		text.setString("");
		displayIndex = 0;
	}

	return isTextComplete();
}

void DialogueBox::render() {
	window.draw(boxSprite);
	window.draw(text);
}

bool DialogueBox::isTextComplete() const{
	return textComplete;
}

void DialogueBox::isEnterPressed(bool enterIsPressed) {
	if (enterIsPressed) {
		reset();
	}
}