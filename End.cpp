#include "End.h"
#include "BlackFadeTransition.h"
#include <SFML/Graphics.hpp>

using namespace sf;

End::End(RenderWindow& window) : window(window), fadeTrans(window) {
	font.loadFromFile("C:\\Users\\kjiez\\OneDrive\\Desktop\\ehh\\font\\pixeboy-font\\Pixeboy-z8XGD.ttf");
	creditsText.setFont(font);
	membersText.setFont(font);
	thanks.setFont(font);
	burgerText.setFont(font);

	kwehText.setFont(font);
	desText.setFont(font);
	cjText.setFont(font);
	ameruText.setFont(font);
	kitText.setFont(font);

	bgTexture.loadFromFile("sprites\\background\\samplebg.jpg");

	bgScale = Vector2f(2.4f, 2.6f);
	
	blackFill.setFillColor(Color::Black);
	blackFill.setSize(Vector2f(window.getSize().x, window.getSize().y));

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

	totalTime = 0.0f;
	switchTime = 0.4f;

	initEnd();
}

End::~End() {

}

void End::initEnd() {
	bg.setTexture(bgTexture);
	creditsText.setString("BROUGHT TO YOU BY:");
	creditsText.setCharacterSize(100);
	creditsText.setPosition(300, 500);

	membersText.setString("LUTANG PEOPEL INC.");
	membersText.setCharacterSize(60);
	membersText.setPosition(420, 700);

	burgerText.setString("MEMBERS:");
	burgerText.setCharacterSize(120);
	burgerText.setPosition(450, 1500);

	kwehText.setString("hays salamat makatulog nako\n\n\t\t\t\t-kwenn");
	kwehText.setCharacterSize(50);
	kwehText.setPosition(150, 2000);

	desText.setString("Wihihihi thank you Lord\n\n\t\t\t\t-desiree");
	desText.setCharacterSize(50);
	desText.setPosition(150, 2500);

	ameruText.setString("all glory to God\n\n\t\t\t\t-amery");
	ameruText.setCharacterSize(50);
	ameruText.setPosition(150, 3000);

	kitText.setString("kudos to everyone\n\n\t\t\t\t-khyth");
	kitText.setCharacterSize(50);
	kitText.setPosition(150, 3500);

	cjText.setString("advanced rest in peace cj    : )");
	cjText.setCharacterSize(50);
	cjText.setPosition(150, 4000);

	kwehSprite.setPosition(900, 2000);
	desSprite.setPosition(900, 2500);
	cjSprite.setPosition(900, 4000);
	ameruSprite.setPosition(900, 3000);
	kitSprite.setPosition(900, 3500);

	thanks.setString("thanks for witnessing our cause of deaths");
	thanks.setCharacterSize(40);
	thanks.setPosition(180, 500);
	thanks.setFillColor(Color::Red);
}

void End::handleInput() {
	Event event;
	while (window.pollEvent(event)) {
		if (Keyboard::isKeyPressed(Keyboard::Escape) || Keyboard::isKeyPressed(Keyboard::Enter) || event.type == Event::Closed) {
			window.close();
		}
	}
}

void End::animupdate(float dt) {
	currentImage3.y = 0;
	currentImage4.y = 0;
	currentImage5.y = 0;
	currentImage6.y = 0;
	currentImage7.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage3.x++;
		currentImage4.x++;
		currentImage5.x++;
		currentImage6.x++;
		currentImage7.x++;

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

void End::update() {
	dt = clock.restart().asSeconds();

	creditsText.move(0, -2);
	membersText.move(0, -2);
	burgerText.move(0, -2);
	kwehText.move(0, -2);
	desText.move(0, -2);
	cjText.move(0, -2);
	ameruText.move(0, -2);
	kitText.move(0, -2);
	kwehSprite.move(0, -2);
	desSprite.move(0, -2);
	cjSprite.move(0, -2);
	ameruSprite.move(0, -2);
	kitSprite.move(0, -2);
}

void End::render() {
	window.clear();
	bg.setScale(bgScale);
	window.draw(bg);
	window.draw(thanks);
	window.draw(blackFill);
	window.draw(creditsText);
	window.draw(membersText);

	kwehSprite.setScale(6.0f, 6.0f);
	desSprite.setScale(6.0f, 6.0f);
	cjSprite.setScale(6.0f, 6.0f);
	ameruSprite.setScale(6.0f, 6.0f);
	kitSprite.setScale(6.0f, 6.0f);

	kwehSprite.setTextureRect(kwehRect);
	desSprite.setTextureRect(desRect);
	cjSprite.setTextureRect(cjRect);
	ameruSprite.setTextureRect(ameruRect);
	kitSprite.setTextureRect(kitRect);

	window.draw(burgerText);
	window.draw(kwehText);
	window.draw(desText);
	window.draw(ameruText);
	window.draw(kitText);
	window.draw(cjText);

	window.draw(kwehSprite);
	window.draw(desSprite);
	window.draw(ameruSprite);
	window.draw(kitSprite);
	window.draw(cjSprite);

	//window.display();
}