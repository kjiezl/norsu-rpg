#include "CutScene.h"
#include "DialogueBox.h"
#include "BlackFadeTransition.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace sf;
using namespace std;

CutScene::CutScene(RenderWindow& window) : window(window), dialogueBox(window), 
fadeTrans(window), s1Dialogue(false), s2Dialogue(false), s03Dialogue(false), 
s4Dialogue(false), s5Dialogue(false), s6Dialogue(false), s8Dialogue(false) {
	font.loadFromFile("fonts\\pixeboy-font\\Pixeboy-z8XGD.ttf");
	text.setFont(font);

	bgTexture0.loadFromFile("sprites\\cutscenes\\intro\\scene0.png");
	bgTexture1.loadFromFile("sprites\\cutscenes\\intro\\scene1.png");
	bgTexture2.loadFromFile("sprites\\cutscenes\\intro\\scene2.png");
	skylabroomTex.loadFromFile("sprites\\cutscenes\\skylabroom1.png");
	
	bgSprite0.setTexture(bgTexture0);
	bgSprite1.setTexture(bgTexture1);
	bgSprite2.setTexture(bgTexture2);
	skylabroomSprite.setTexture(skylabroomTex);

	ghostTex.loadFromFile("sprites\\enemies\\ghost1.1.png");
	ghost.setTexture(ghostTex);
	playerTex.loadFromFile("sprites\\characters\\1 (1).png");
	playerSprite.setTexture(playerTex);

	totalTime = 0.0f;
	switchTime = 0.3f;
	currentImage.x = 0;
	ghostRect.width = ghostTex.getSize().x / 3;
	ghostRect.height = ghostTex.getSize().y / 1;

	dt = 0.0f;

	playerSprite.setPosition(500, 300);
	ghost.setPosition(700, 300);
}

CutScene::~CutScene() {

}

void CutScene::handleInput() {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || event.type == Event::Closed) {
			window.close();
		}
	}

	dt = clock.restart().asSeconds();
}

void CutScene::scene00() {
	window.clear();
	window.setView(window.getDefaultView());
	window.draw(bgSprite0);
	text.setString("DAY 1");
	text.setPosition(525, 300);
	text.setCharacterSize(100);
	text.setFillColor(Color::White);
	window.draw(text);
}

void CutScene::scene0() {
	window.clear();
	window.setView(window.getDefaultView());
	window.draw(bgSprite0);
	text.setString("7:00AM");
	text.setPosition(525, 300);
	text.setCharacterSize(100);
	text.setFillColor(Color::White);
	window.draw(text);
}

void CutScene::scene1() {
	s1Dialogue = true;
	window.clear();
	window.setView(window.getDefaultView());
	bgSprite1.setScale(1.3f, 1.3f);
	bgSprite1.setPosition(360, 20);
	window.draw(bgSprite1);
	if (s1Dialogue) {
		scene1Dia();
	}
}

void CutScene::scene1Dia() {
	dialogueBox.initDialogue("[MONDAY]\n\t7:06AM");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		s1Dialogue = false;
		dialogueBox.isEnterPressed(true);
	}
}

void CutScene::scene2() {
	s2Dialogue = true;
	window.clear();
	window.setView(window.getDefaultView());
	bgSprite2.setScale(1.3f, 1.3f);
	bgSprite2.setPosition(360, 20);
	window.draw(bgSprite2);
	if (s2Dialogue) {
		scene2Dia();
	}
}

void CutScene::scene2Dia() {
	dialogueBox.initDialogue("\n\t. . .                    ");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		s2Dialogue = false;
		dialogueBox.isEnterPressed(true);
	}
}

void CutScene::scene03() {
	s03Dialogue = true;
	window.clear();
	window.setView(window.getDefaultView());
	skylabroomSprite.setScale(0.9f, 0.9f);
	skylabroomSprite.setPosition(250, -170);
	window.draw(skylabroomSprite);
	if (s03Dialogue) {
		scene03Dia();
	}
}

void CutScene::scene03Dia() {
	dialogueBox.initDialogue("\n\tYou have been tasked to collect the class works tomorrow.");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		s03Dialogue = false;
		dialogueBox.isEnterPressed(true);
	}
}

void CutScene::scene3() {
	window.clear();
	window.setView(window.getDefaultView());
	window.draw(bgSprite0);
	text.setString("MANY HOURS LATER");
	text.setPosition(300, 300);
	text.setCharacterSize(100);
	text.setFillColor(Color::White);
	window.draw(text);
}

void CutScene::scene4() {
	s4Dialogue = true;
	window.clear();
	window.setView(window.getDefaultView());
	bgSprite1.setScale(1.3f, 1.3f);
	bgSprite1.setPosition(360, 20);
	window.draw(bgSprite1);
	if (s4Dialogue) {
		scene4Dia();
	}
}

void CutScene::scene4Dia() {
	dialogueBox.initDialogue("\n\t. . .                                                                          ");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		s4Dialogue = false;
		dialogueBox.isEnterPressed(true);
	}
}

void CutScene::scene5() {
	s5Dialogue = true;
	window.clear();
	window.setView(window.getDefaultView());
	bgSprite1.setScale(1.3f, 1.3f);
	bgSprite1.setPosition(360, 20);
	window.draw(bgSprite1);
	if (s5Dialogue) {
		scene5Dia();
	}
}

void CutScene::scene5Dia() {
	dialogueBox.initDialogue("\n\t. . . .                                                                                        ");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		s5Dialogue = false;
		dialogueBox.isEnterPressed(true);
	}
}

void CutScene::scene6() {
	s6Dialogue = true;
	window.clear();
	window.setView(window.getDefaultView());
	bgSprite1.setScale(1.3f, 1.3f);
	bgSprite1.setPosition(360, 20);
	window.draw(bgSprite1);
	if (s6Dialogue) {
		scene6Dia();
	}
}

void CutScene::scene6Dia() {
	dialogueBox.initDialogue("\n\t ... was it just a dream?                                                                                       ");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		s6Dialogue = false;
		dialogueBox.isEnterPressed(true);
	}
}

void CutScene::scene7() {
	window.clear();
	window.setView(window.getDefaultView());
	window.draw(bgSprite0);
	text.setString("DAY 2");
	text.setPosition(525, 300);
	text.setCharacterSize(100);
	text.setFillColor(Color::White);
	window.draw(text);
}

void CutScene::scene8() {
	s8Dialogue = true;
	window.clear();
	window.setView(window.getDefaultView());
	window.draw(bgSprite0);
	ghost.setTextureRect(ghostRect);
	ghost.setScale(4.0f, 4.0f);
	playerSprite.setScale(4.0f, 4.0f);
	window.draw(ghost);
	window.draw(playerSprite);

	if (s8Dialogue) {
		scene8Dia();
	}
}

void CutScene::scene8Dia() {
	dialogueBox.initDialogue("\tGhost:\n\t\tYou shouldn't be here.                                                                                       ");
	dialogueBox.update();
	dialogueBox.render();

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		s8Dialogue = false;
		dialogueBox.isEnterPressed(true);
	}
}

void CutScene::animUpdate(float dt) {
	currentImage.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= 3) {
			currentImage.x = 0;
		}
	}

	ghostRect.left = currentImage.x * ghostRect.width;
	ghostRect.top = currentImage.y * ghostRect.height;
}