#include "CutScene2.h"
#include "DialogueBox.h"
#include "BlackFadeTransition.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

CutScene2::CutScene2(RenderWindow& window) : window(window), dialogueBox(window),
fadeTrans(window), s9Dialogue(false), s10Dialogue(false) {
	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");
	text.setFont(font);

	bgTexture0.loadFromFile("sprites\\cutscenes\\intro\\scene0.png");
	bgTexture1.loadFromFile("sprites\\cutscenes\\intro\\scene1.png");
	bgTexture2.loadFromFile("sprites\\cutscenes\\intro\\scene2.png");
	bgTexture3.loadFromFile("sprites\\cutscenes\\hm-scene.png");

	bgSprite0.setTexture(bgTexture0); // black bg
	bgSprite1.setTexture(bgTexture1);
	bgSprite2.setTexture(bgTexture2);
	bgSprite3.setTexture(bgTexture3);

	dt = 0.0f;
}

CutScene2::~CutScene2() {

}

void CutScene2::handleInput() {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}
	}

	dt = clock.restart().asSeconds();
}

//void CutScene2::scene0() {
//	window.clear();
//	window.setView(window.getDefaultView());
//	window.draw(bgSprite0);
//	text.setString("7:00AM");
//	text.setPosition(525, 300);
//	text.setCharacterSize(100);
//	text.setFillColor(Color::White);
//	window.draw(text);
//}

void CutScene2::scene9() {
	s9Dialogue = true;
	window.clear();
	window.setView(window.getDefaultView());
	bgSprite3.setScale(0.8f, 0.8f);
	bgSprite3.setPosition(300, -180);
	window.draw(bgSprite3);
	if (s9Dialogue) {
		scene9Dia();
	}
}

void CutScene2::scene9Dia() {
	dialogueBox.initDialogue("\n\tYou have been tasked to check the class works.");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		s9Dialogue = false;
		dialogueBox.isEnterPressed(true);
	}
}

void CutScene2::scene10() {
	s10Dialogue = true;
	window.clear();
	window.setView(window.getDefaultView());
	bgSprite0.setScale(1.3f, 1.3f);
	bgSprite0.setPosition(360, 20);
	window.draw(bgSprite0);
	if (s10Dialogue) {
		scene10Dia();
	}
}

void CutScene2::scene10Dia() {
	dialogueBox.initDialogue("\n\tYou shouldn't have done that.	           	                                                        				  ");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		s10Dialogue = false;
		dialogueBox.isEnterPressed(true);
	}
}