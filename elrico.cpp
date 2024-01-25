#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Game.h"
#include "Menu.h"
#include "End.h"
#include "PlayerName.h"
#include "PauseMenu.h"
#include "BlackFadeTransition.h"
#include "CircleTransition.h"
#include "CircTrans.h"
#include "LoadingScreen.h"
#include "Skylab.h"
#include "SkylabRoom.h"
#include "SkylabRoomNight.h"
#include "CutScene.h"
#include "CutScene2.h"
#include "MainGate.h"
#include "SkylabNight.h"
#include "Startup.h"
#include "CAS3Night.h"
#include "MainGateNight.h"
#include "HMDay.h"
#include "HMNight.h"
#include "HM2nd.h"
#include "HM2ndNight.h"
#include "HMRoom2.h"
#include "HMRoom2Night.h"
#include "HMRoom1.h"
#include "NPC.h"
#include "CBA.h"
#include "CBADay.h"
#include "CBARoom.h"
#include "CBARoomDay.h"
#include "OpenCourt.h"
#include "BossFight.h"
#include "SKYLABROOMLAST.h"
#include "Crafting.h"
#include "Inventory.h"
#include "HP.h"


using namespace sf;

int main() {
	RenderWindow window(VideoMode(1280, 720), "yuh");
	window.setFramerateLimit(60);

	SoundBuffer doorBuffer;
	Sound doorSFX;
	doorBuffer.loadFromFile("sprites\\sfx\\door.ogg");
	doorSFX.setBuffer(doorBuffer);
	SoundBuffer alarmBuffer;
	Sound alarmSFX;
	alarmBuffer.loadFromFile("sprites\\sfx\\alarm.ogg");
	alarmSFX.setBuffer(alarmBuffer);
	SoundBuffer dfBuffer;
	Sound dfSFX;
	dfBuffer.loadFromFile("sprites\\sfx\\darkfigure.ogg");
	dfSFX.setBuffer(dfBuffer);
	SoundBuffer bgmBuffer;
	Sound bgm;
	bgmBuffer.loadFromFile("sprites\\bgm\\ghostmusic.flac");
	bgm.setBuffer(bgmBuffer);
	SoundBuffer bgm2Buffer;
	Sound bgm2;
	bgm2Buffer.loadFromFile("sprites\\bgm\\ghost2.flac");
	bgm2.setBuffer(bgm2Buffer);
	SoundBuffer orbBuffer;
	Sound orbSFX;
	orbBuffer.loadFromFile("sprites\\sfx\\orb.ogg");
	orbSFX.setBuffer(orbBuffer);
	SoundBuffer ghostBuffer;
	Sound ghostSFX;
	ghostBuffer.loadFromFile("sprites\\sfx\\ghost-sound4.ogg");
	ghostSFX.setBuffer(ghostBuffer);
	SoundBuffer bossBuffer;
	Sound bossBGM;
	bossBuffer.loadFromFile("sprites\\bgm\\boss1.flac");
	bossBGM.setBuffer(bossBuffer);
	SoundBuffer equipBuffer;
	Sound equipSFX;
	equipBuffer.loadFromFile("sprites\\sfx\\equip.ogg");
	equipSFX.setBuffer(equipBuffer);

	Music logoBGM;
	Music menuBGM;
	Music nightBGM;
	Music endBGM;
	Music endBGM2;
	Music dayBGM;
	logoBGM.openFromFile("sprites\\bgm\\logo2.flac");
	menuBGM.openFromFile("sprites\\bgm\\menu.flac");
	nightBGM.openFromFile("sprites\\bgm\\night.flac");
	endBGM.openFromFile("sprites\\bgm\\end1.flac");
	endBGM2.openFromFile("sprites\\bgm\\end2.flac");
	dayBGM.openFromFile("sprites\\bgm\\day1.flac");

	Menu menu(window);
	End end(window);
	PlayerName playerName(window);
	string pName = playerName.getPlayerName();
	Game game(window, pName);
	PauseMenu pauseMenu(window);
	BlackFadeTransition fadeTrans(window);
	CircleTransition circleTrans(window);
	CircTrans circTrans(window);
	LoadingScreen loadScreen(window);
	Skylab skylab(window, pName);
	SkylabRoom skylabRoom(window, pName);
	CutScene cutScene(window);
	CutScene2 cutScene2(window);
	MainGate mainGate(window, pName);
	SkylabRoomNight skylabRoomNight(window, pName);
	SkylabNight skylabNight(window, pName);
	Startup startup(window);
	CAS3Night cas3Night(window, pName);
	MainGateNight mainGateNight(window, pName);
	HMDay hmDay(window);
	HMNight hmNight(window);
	HM2nd hm2ND(window);
	HM2ndNight hm2NDNight(window);
	HMRoom2 hmRoom2(window);
	HMRoom2Night hmRoom2Night(window);
	HMRoom1 hmRoom1(window);
	NPC npc(window);
	CBA cba(window);
	CBADay cbaDay(window);
	CBARoom cbaRoom(window);
	CBARoomDay cbaRoomDay(window);
	OpenCourt openCourt(window);
	BossFight bossFight(window);
	SKYLABROOMLAST skylabRoomLast(window);
	Crafting crafting(window);
	Inventory inv(window);
	HP hp(window, 100.0);

	enum gameState{STARTUP, MENU, INTROSCENE, PLAYER, MAINGATE, CAS3RD, SKYLAB, 
		SKYLABROOM, SKYLABROOMSCENE, SKYLABROOMNIGHT, SKYLABNIGHT, CAS3RDNIGHT, 
		MAINGATENIGHT, LASTSCENE1, PAUSED, EXIT, HMDAY, HM2ND, SCENE8, HMROOM2, SCENE9,
		HMROOM2NIGHT, HM2NDNIGHT, HMNIGHT, HMROOM1, CBA, CBAROOM, SCENE10, BOSSFIGHT, 
		LASTSCENE2, CBADAY, CBAROOMDAY, CRAFTING, OPENCOURT};
	enum sceneState { SCENE00, SCENE0, SCENE1, SCENE2 };
	enum sceneState1 { SCENE03, SCENE3 };
	enum sceneState2 { SCENE4, SCENE5, SCENE6, SCENE7 };
	sceneState currentScene = sceneState::SCENE00;
	sceneState1 currentScene1 = sceneState1::SCENE03;
	sceneState2 currentScene2 = sceneState2::SCENE4;
	bool seqComplete;
	bool seqComplete1;
	bool seqComplete2 = false;
	
	gameState currentState = gameState::STARTUP;
	gameState previousState = gameState::MENU;

	Clock clock;
	float dt = 0.0f;

	while (window.isOpen()) {
		dt = clock.restart().asSeconds();

		switch (currentState) {
		case gameState::STARTUP:
			logoBGM.pause();
			logoBGM.play();
			startup.handleInput();
			startup.update();
			startup.animUpdate(dt);
			startup.render();
			if (!fadeTrans.isFadedOut()) {
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();

			if (startup.startComplete()) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				fadeTrans.fadedOutFalse();
				currentState = MENU;
			}

			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				currentState = MENU;
			}
			break;

		case gameState::MENU:
			//std::cout << "in menu\n";
			menuBGM.pause();
			menuBGM.play();
			menuBGM.setLoop(true);
			menuBGM.setVolume(50);
			menu.handleInput();
			menu.update(dt);
			menu.update2(dt);
			menu.render();
			if (!fadeTrans.isFadedOut()) {
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (menu.startButtonPressed()) {
				menuBGM.stop();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				fadeTrans.fadedOutFalse();
				currentState = gameState::INTROSCENE;
			}
			break;

		case gameState::PLAYER:
			//std::cout << "in player profile\n";
			playerName.handleInput();
			playerName.update();
			playerName.render();
			fadeTrans.fadedInFalse();

			if (playerName.getEnter()) {
				menuBGM.stop();
				game.setPlayerName(playerName.getPlayerName());
				while (!fadeTrans.isFadedIn()) {
					window.setView(window.getDefaultView());
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				fadeTrans.fadedOutFalse();

				loadScreen.clockRestart();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					window.setView(window.getDefaultView());
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					window.setView(window.getDefaultView());
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				currentState = gameState::INTROSCENE;
			}

			break;

		case gameState::INTROSCENE:
			seqComplete = false;

			switch (currentScene) {
				case SCENE00:
					cutScene.handleInput();
					cutScene.scene00();
					if (!fadeTrans.isFadedOut()) {
						fadeTrans.updateOut(dt);
						fadeTrans.renderOut();
					}
					window.display();
					fadeTrans.fadedInFalse();

					if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						while (!fadeTrans.isFadedIn()) {
							fadeTrans.updateIn(dt);
							fadeTrans.renderIn();
							window.display();
						}
						fadeTrans.fadedOutFalse();
						currentScene = sceneState::SCENE0;
						seqComplete = false;
					}

					break;
				
				case SCENE0:
					alarmSFX.pause();
					alarmSFX.play();
					cutScene.handleInput();
					cutScene.scene0();
					if (!fadeTrans.isFadedOut()) {
						fadeTrans.updateOut(dt);
						fadeTrans.renderOut();
					}
					window.display();
					fadeTrans.fadedInFalse();

					if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						alarmSFX.stop();
						while (!fadeTrans.isFadedIn()) {
							fadeTrans.updateIn(dt);
							fadeTrans.renderIn();
							window.display();
						}
						dayBGM.pause();
						dayBGM.play();
						dayBGM.setLoop(true);
						fadeTrans.fadedOutFalse();
						currentScene = sceneState::SCENE1;
						seqComplete = false;
					}
					break;

				case SCENE1:
					cutScene.handleInput();
					cutScene.scene1();
					if (!fadeTrans.isFadedOut()) {
						fadeTrans.updateOut(dt);
						fadeTrans.renderOut();
					}
					window.display();
					fadeTrans.fadedInFalse();

					if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						while (!fadeTrans.isFadedIn()) {
							fadeTrans.updateIn(dt);
							fadeTrans.renderIn();
							window.display();
						}
						fadeTrans.fadedOutFalse();
						currentScene = sceneState::SCENE2;
						seqComplete = false;
					}
					break;

				case SCENE2:
					cutScene.handleInput();
					cutScene.scene2();
					if (!fadeTrans.isFadedOut()) {
						fadeTrans.updateOut(dt);
						fadeTrans.renderOut();
					}
					window.display();
					fadeTrans.fadedInFalse();

					if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						while (!fadeTrans.isFadedIn()) {
							window.setView(window.getDefaultView());
							fadeTrans.updateIn(dt);
							fadeTrans.renderIn();
							window.display();
						}
						fadeTrans.fadedOutFalse();

						loadScreen.clockRestart();
						loadScreen.loadCompleteFalse();
						fadeTrans.fadedInFalse();

						while (!loadScreen.loadingComplete()) {
							window.setView(window.getDefaultView());
							loadScreen.initLoadingScreen();
							loadScreen.update(dt);
							loadScreen.render();
							window.display();
						}

						while (!fadeTrans.isFadedIn()) {
							window.setView(window.getDefaultView());
							fadeTrans.updateIn(dt);
							fadeTrans.renderIn();
							window.display();
						}
						seqComplete = true;
					}
					break;
			}

			if (seqComplete) {
				currentState = gameState::MAINGATE;
			}
			break;
			
		case gameState::MAINGATE:
			mainGate.handleInput();
			mainGate.update();
			mainGate.animUpdate(dt);
			mainGate.Camera();
			mainGate.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::MAINGATE;
			}

			if (mainGate.goto3rdCAS()) {
				game.playerPosFromMainGate();
				game.goingMainGateFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				endBGM.stop();
				dayBGM.pause();
				dayBGM.play();
				dayBGM.setLoop(true);
				currentState = gameState::CAS3RD;
			}

			if (mainGate.gotoHM()) {
				hmDay.playerPosFromMainGate();
				hmDay.goingMainGateFalse();
				hmDay.goingCBAFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HMDAY;
			}

			if (mainGate.gotoCBA()) {
				cbaDay.playerPosFromMainGate();
				cbaDay.goingMainGateFalse();
				cbaDay.goingHMFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::CBADAY;
			}

			if (skylabRoom.papersPlaced()) {
				mainGate.show4(true);
			}

			break;

		case gameState::CAS3RD:
			//std::cout << "in game\n";
			game.handleInput();
			game.update();
			game.animUpdate(dt);
			game.catUpdate(dt);
			game.Camera();
			game.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				} 

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::CAS3RD;
			}

			if (game.gotoSkylab()) {
				skylab.playerPosFrom3rdCAS();
				skylab.going3rdCASFalse();
				fadeTrans.fadedOutFalse();
				playerName.setSkylab();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::SKYLAB;
			}

			if (game.gotoMainGate()) {
				mainGate.playerPosFrom3rdCAS();
				mainGate.going3rdCASFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::MAINGATE;
			}

			if (skylabRoom.papersPlaced()) {
				game.goingHM(true);
			}

			break;

		case gameState::SKYLAB:
			//std::cout << "in game\n";
			skylab.handleInput();
			skylab.update();
			skylab.animUpdate(dt);
			skylab.Camera();
			skylab.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			if (game.isCJCollected()) {
				skylab.isCJCollected(true);
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::SKYLAB;
			}

			if (skylab.goto3rdCAS()) {
				fadeTrans.fadedOutFalse();
				game.playerPosFromSkylab();
				game.goingSkylabFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::CAS3RD;
			}

			if (skylab.gotoSkylabRoom()) {
				fadeTrans.fadedOutFalse();
				doorSFX.play();
				skylabRoom.goingSkylabFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::SKYLABROOM;
			}

			if (skylabRoom.papersPlaced()) {
				skylab.cjDialogue(true);
			}

			break;

		case gameState::SKYLABROOM:
			//std::cout << "in game\n";
			skylabRoom.handleInput();
			skylabRoom.update();
			skylabRoom.animUpdate(dt);
			skylabRoom.npcUpdate(dt);
			skylabRoom.Camera();
			skylabRoom.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			if (skylab.papersComplete()) {
				skylabRoom.papersComplete(true);
			}
			else {
				skylabRoom.papersComplete(false);
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::SKYLABROOM;
			}

			if (skylabRoom.gotoSkylab()) {
				fadeTrans.fadedOutFalse();
				doorSFX.play();
				skylab.goingSkylabRoomFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::SKYLAB;
			}

			if (skylabRoom.startScene()) {
				dayBGM.stop();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = SKYLABROOMSCENE;
			}

			break;

		case gameState::SKYLABROOMSCENE:
			seqComplete1 = false;

			switch (currentScene1) {
			case SCENE03:
				cutScene.handleInput();
				cutScene.scene03();
				if (!fadeTrans.isFadedOut()) {
					fadeTrans.updateOut(dt);
					fadeTrans.renderOut();
				}
				window.display();
				fadeTrans.fadedInFalse();

				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					fadeTrans.fadedOutFalse();
					currentScene1 = sceneState1::SCENE3;
					seqComplete1 = false;
				}
				break;

			case SCENE3:
				nightBGM.pause();
				nightBGM.play();
				cutScene.handleInput();
				cutScene.scene3();
				if (!fadeTrans.isFadedOut()) {
					fadeTrans.updateOut(dt);
					fadeTrans.renderOut();
				}
				window.display();
				fadeTrans.fadedInFalse();

				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					fadeTrans.fadedOutFalse();
					skylabRoomNight.goingSkylabFalse();
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					fadeTrans.fadedOutFalse();
					seqComplete1 = true;
				}
				break;
			}

			if (seqComplete1) {
				currentState = gameState::SKYLABROOMNIGHT;
			}
			break;

		case gameState::SKYLABROOMNIGHT:
			skylabRoomNight.handleInput();
			skylabRoomNight.update();
			skylabRoomNight.animUpdate(dt);
			skylabRoomNight.Camera();
			skylabRoomNight.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (skylabRoomNight.gameStart()) {
				skylabNight.startSpawn();
			}

			if (!skylabRoomNight.nightBGMFalse()) {
				nightBGM.stop();
			}

			if (skylabRoomNight.startBGM()) {
				bgm.pause();
				bgm.play();
				bgm.setLoop(true);
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::SKYLABROOMNIGHT;
			}

			if (skylabRoomNight.gotoSkylab()) {
				fadeTrans.fadedOutFalse();
				doorSFX.play();
				skylabNight.goingSkylabRoomFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::SKYLABNIGHT;
			}
			break;

		case gameState::SKYLABNIGHT:
			skylabNight.handleInput();
			skylabNight.update();
			skylabNight.animUpdate(dt);
			skylabNight.Camera();
			skylabNight.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (skylabNight.changeTextRoom()) {
				skylabRoomNight.goHomeFalse();
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::SKYLABNIGHT;
			}

			if (skylabNight.goto3rdCAS()) {
				fadeTrans.fadedOutFalse();
				cas3Night.playerPosFromSkylab();
				cas3Night.goingSkylabFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::CAS3RDNIGHT;
			}

			if (skylabNight.gotoSkylabRoom()) {
				fadeTrans.fadedOutFalse();
				doorSFX.play();
				skylabRoomNight.goingSkylabFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::SKYLABROOMNIGHT;
			}
			break;

		case gameState::CAS3RDNIGHT:
			cas3Night.handleInput();
			cas3Night.update();
			cas3Night.animUpdate(dt);
			cas3Night.Camera();
			cas3Night.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (cas3Night.stopBGM()) {
				bgm.stop();
			}

			if (hp.noHP()) {
				cas3Night.restart();
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::CAS3RDNIGHT;
			}

			if (cas3Night.gotoSkylab()) {
				skylabNight.playerPosFrom3rdCAS();
				skylabNight.going3rdCASFalse();
				fadeTrans.fadedOutFalse();
				playerName.setSkylab();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::SKYLABNIGHT;
			}

			if (cas3Night.gotoMainGate()) {
				mainGateNight.playerPosFrom3rdCAS();
				mainGateNight.going3rdCASFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				dfSFX.pause();
				dfSFX.play();
				currentState = gameState::MAINGATENIGHT;
			}
			break;

		case gameState::MAINGATENIGHT:
			mainGateNight.handleInput();
			mainGateNight.update();
			mainGateNight.animUpdate(dt);
			mainGateNight.Camera();
			mainGateNight.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::MAINGATENIGHT;
			}

			if (mainGateNight.goto3rdCAS()) {
				cas3Night.playerPosFromMainGate();
				cas3Night.goingMainGateFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::CAS3RDNIGHT;
			}

			if (mainGateNight.sceneComplete()) {
				/*alarmSFX.pause();
				alarmSFX.play();*/
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::LASTSCENE1;
			}
			break;

		case gameState::LASTSCENE1:
			seqComplete2 = false;

			switch (currentScene2) {

			case SCENE4:
				cutScene.handleInput();
				cutScene.scene4();
				if (!fadeTrans.isFadedOut()) {
					fadeTrans.updateOut(dt);
					fadeTrans.renderOut();
				}
				window.display();
				fadeTrans.fadedInFalse();

				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					fadeTrans.fadedOutFalse();
					currentScene2 = sceneState2::SCENE5;
					seqComplete2 = false;
				}
				break;

			case SCENE5:
				cutScene.handleInput();
				cutScene.scene5();
				if (!fadeTrans.isFadedOut()) {
					fadeTrans.updateOut(dt);
					fadeTrans.renderOut();
				}
				window.display();
				fadeTrans.fadedInFalse();

				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					fadeTrans.fadedOutFalse();
					currentScene2 = sceneState2::SCENE6;
					seqComplete2 = false;
				}
				break;

			case SCENE6:
				endBGM.pause();
				endBGM.play();
				cutScene.handleInput();
				cutScene.scene6();
				if (!fadeTrans.isFadedOut()) {
					fadeTrans.updateOut(dt);
					fadeTrans.renderOut();
				}
				window.display();
				fadeTrans.fadedInFalse();

				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					while (!fadeTrans.isFadedIn()) {
						window.setView(window.getDefaultView());
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					fadeTrans.fadedOutFalse();
					currentScene2 = sceneState2::SCENE7;
					seqComplete2 = false;
				}
				break;

			case SCENE7:
				cutScene.handleInput();
				cutScene.scene7();
				if (!fadeTrans.isFadedOut()) {
					fadeTrans.updateOut(dt);
					fadeTrans.renderOut();
				}
				window.display();
				fadeTrans.fadedInFalse();

				if (Keyboard::isKeyPressed(Keyboard::Enter)) {
					while (!fadeTrans.isFadedIn()) {
						window.setView(window.getDefaultView());
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					fadeTrans.fadedOutFalse();
					seqComplete2 = true;
				}
				break;
			}

			if (seqComplete2) {
				window.clear();
				mainGate.day2Start();
				game.day2Start();
				npc.day2Start();
				skylab.day2Start();
				skylabRoom.day2Start();
				npc.day2Start();
				currentState = gameState::MAINGATE;
			}
			break;

			case gameState::CBADAY:
				cbaDay.handleInput();
				cbaDay.update();
				cbaDay.animUpdate(dt);
				cbaDay.Camera();
				cbaDay.render();
				if (!fadeTrans.isFadedOut()) {
					window.setView(window.getDefaultView());
					fadeTrans.updateOut(dt);
					fadeTrans.renderOut();
				}
				window.display();
				fadeTrans.fadedInFalse();

				if (skylabRoom.papersPlaced()) {
					cbaDay.show4(true);
				}

				if (Keyboard::isKeyPressed(Keyboard::Q)) {
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}

					loadScreen.clockRestart();
					loadScreen.loadCompleteFalse();
					fadeTrans.fadedOutFalse();
					fadeTrans.fadedInFalse();

					while (!loadScreen.loadingComplete()) {
						loadScreen.initLoadingScreen();
						loadScreen.update(dt);
						loadScreen.render();
						window.display();
					}
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::EXIT;
				}

				if (Keyboard::isKeyPressed(Keyboard::P)) {
					currentState = gameState::PAUSED;
					previousState = gameState::CBADAY;
				}

				if (cbaDay.gotoHM()) {
					hmDay.playerPosFromCBA();
					hmDay.goingCBAFalse();
					hmDay.goingMainGateFalse();
					fadeTrans.fadedOutFalse();
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::HMDAY;
				}

				if (cbaDay.gotoRoom()) {
					doorSFX.play();
					cbaRoomDay.playerPosFromCBA();
					cbaRoomDay.goingCBAFalse();
					fadeTrans.fadedOutFalse();
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::CBAROOMDAY;
				}

				if (cbaDay.gotoMainGate()) {
					mainGate.playerPosFromCBA();
					mainGate.goingCBAFalse();
					mainGate.goingHMFalse();
					fadeTrans.fadedOutFalse();
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::MAINGATE;
				}

				if (cbaDay.gotoCourt()) {
					openCourt.playerPosFromCBA();
					openCourt.goingCBAFalse();
					fadeTrans.fadedOutFalse();
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::OPENCOURT;
				}

				break;

			case gameState::CBAROOMDAY:
				cbaRoomDay.handleInput();
				cbaRoomDay.update();
				cbaRoomDay.animUpdate(dt);
				cbaRoomDay.Camera();
				cbaRoomDay.render();
				if (!fadeTrans.isFadedOut()) {
					window.setView(window.getDefaultView());
					fadeTrans.updateOut(dt);
					fadeTrans.renderOut();
				}
				window.display();
				fadeTrans.fadedInFalse();

				if (skylabRoom.papersPlaced()) {
					cbaDay.show4(true);
				}

				if (Keyboard::isKeyPressed(Keyboard::Q)) {
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}

					loadScreen.clockRestart();
					loadScreen.loadCompleteFalse();
					fadeTrans.fadedOutFalse();
					fadeTrans.fadedInFalse();

					while (!loadScreen.loadingComplete()) {
						loadScreen.initLoadingScreen();
						loadScreen.update(dt);
						loadScreen.render();
						window.display();
					}
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::EXIT;
				}

				if (Keyboard::isKeyPressed(Keyboard::P)) {
					currentState = gameState::PAUSED;
					previousState = gameState::CBAROOMDAY;
				}

				if (cbaRoomDay.gotoCBA()) {
					doorSFX.play();
					cbaDay.playerPosFromRoom();
					cbaDay.goingRoomFalse();
					fadeTrans.fadedOutFalse();
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::CBADAY;
				}

				break;

			case gameState::OPENCOURT:
				openCourt.handleInput();
				openCourt.update();
				openCourt.animUpdate(dt);
				openCourt.Camera();
				openCourt.render();
				if (!fadeTrans.isFadedOut()) {
					window.setView(window.getDefaultView());
					fadeTrans.updateOut(dt);
					fadeTrans.renderOut();
				}
				window.display();
				fadeTrans.fadedInFalse();

				if (skylabRoom.papersPlaced()) {
					openCourt.show4(true);
				}

				if (Keyboard::isKeyPressed(Keyboard::Q)) {
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}

					loadScreen.clockRestart();
					loadScreen.loadCompleteFalse();
					fadeTrans.fadedOutFalse();
					fadeTrans.fadedInFalse();

					while (!loadScreen.loadingComplete()) {
						loadScreen.initLoadingScreen();
						loadScreen.update(dt);
						loadScreen.render();
						window.display();
					}
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::EXIT;
				}

				if (Keyboard::isKeyPressed(Keyboard::P)) {
					currentState = gameState::PAUSED;
					previousState = gameState::OPENCOURT;
				}

				if (openCourt.gotoCBA()) {
					cbaDay.playerPosFromCourt();
					cbaDay.goingCourtFalse();
					fadeTrans.fadedOutFalse();
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::CBADAY;
				}

				/*if (cbaDay.gotoMainGate()) {
					mainGate.playerPosFromCBA();
					mainGate.goingCBAFalse();
					mainGate.goingHMFalse();
					fadeTrans.fadedOutFalse();
					while (!fadeTrans.isFadedIn()) {
						fadeTrans.updateIn(dt);
						fadeTrans.renderIn();
						window.display();
					}
					currentState = gameState::MAINGATE;
				}*/

				break;

		case gameState::HMDAY:
			hmDay.handleInput();
			hmDay.update();
			hmDay.animUpdate(dt);
			hmDay.Camera();
			hmDay.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::HMDAY;
			}

			if (hmDay.gotoMainGate()) {
				mainGate.playerPosFromHM();
				mainGate.goingHMFalse();
				mainGate.goingCBAFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::MAINGATE;
			}

			if (hmDay.gotoHM2nd()) {
				hm2ND.playerPosFromHM();
				hm2ND.goingHMFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HM2ND;
			}

			if (hmDay.gotoCBA()) {
				cbaDay.playerPosFromHM();
				cbaDay.goingHMFalse();
				cbaDay.goingMainGateFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::CBADAY;
			}

			if (skylabRoom.papersPlaced()) {
				hmDay.goingHM(true);
			}

			break;

		case gameState::HM2ND:
			hm2ND.handleInput();
			hm2ND.update();
			hm2ND.animUpdate(dt);
			hm2ND.Camera();
			hm2ND.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::HM2ND;
			}

			if (hm2ND.gotoHM()) {
				hmDay.playerPosFromHM2nd();
				hmDay.goingHM2ndFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HMDAY;
			}

			if (hm2ND.gotoHMRoom2()) {
				doorSFX.play();
				hmRoom2.playerPosFromHM2nd();
				hmRoom2.goingHM2ndFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HMROOM2;
			}

			if (skylabRoom.papersPlaced()) {
				hm2ND.show4(true);
			}

			if (hm2ND.showBlackScene()) {
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::SCENE8;
			}

			break;

		case gameState::SCENE8:
			dayBGM.stop();
			cutScene.animUpdate(dt);
			cutScene.handleInput();
			cutScene.scene8();
			if (!fadeTrans.isFadedOut()) {
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				dayBGM.pause();
				dayBGM.play();
				dayBGM.setLoop(true);
				dayBGM.setVolume(70);
				fadeTrans.fadedOutFalse();
				hm2ND.showBlackFalse();
				currentState = gameState::HM2ND;
			}
			break;

		case gameState::HMROOM2:
			hmRoom2.handleInput();
			hmRoom2.update();
			hmRoom2.animUpdate(dt);
			hmRoom2.Camera();
			hmRoom2.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::HMROOM2;
			}

			if (hmRoom2.gotoHM2nd()) {
				doorSFX.play();
				hm2ND.playerPosFromHMRoom2();
				hm2ND.goingHMRoom2False();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HM2ND;
			}

			if (skylabRoom.papersPlaced()) {
				hmRoom2.show4(true);
			}

			if (hmRoom2.startCutScene()) {
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::SCENE9;
			}

			break;

		case gameState::SCENE9:
			dayBGM.stop();
			cutScene2.handleInput();
			cutScene2.scene9();
			if (!fadeTrans.isFadedOut()) {
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				nightBGM.pause();
				nightBGM.play();
				currentState = gameState::HMROOM2NIGHT;
			}
			break;

		case gameState::HMROOM2NIGHT:
			hmRoom2Night.handleInput();
			hmRoom2Night.update();
			hmRoom2Night.animUpdate(dt);
			hmRoom2Night.Camera();
			hmRoom2Night.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::HMROOM2NIGHT;
			}

			/*if (hmRoom2Night.gotoHM2nd()) {
				doorSFX.play();
				hm2NDNight.playerPosFromHMRoom2();
				hm2NDNight.goingHMRoom2False();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				nightBGM.stop();
				bgm2.pause();
				bgm2.play();
				bgm2.setVolume(40);
				currentState = gameState::HM2NDNIGHT;
			}*/

			if (hmRoom2Night.gotoHM2nd()) {
				doorSFX.play();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::CRAFTING;
			}

			break;

		case gameState::HM2NDNIGHT:
			hm2NDNight.handleInput();
			hm2NDNight.update();
			hm2NDNight.animUpdate(dt);
			hm2NDNight.Camera();
			hm2NDNight.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (crafting.weapon1Chosen()) {
				hm2NDNight.setWeapon1();
			}
			if (crafting.weapon2Chosen()) {
				hm2NDNight.setWeapon2();
			}
			if (crafting.weapon3Chosen()) {
				hm2NDNight.setWeapon3();
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::HM2NDNIGHT;
			}

			if (hm2NDNight.gotoHM()) {
				hmNight.playerPosFromHM2nd();
				hmNight.goingHM2ndFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HMNIGHT;
			}

			if (hm2NDNight.gotoHMRoom2()) {
				doorSFX.play();
				hmRoom2Night.playerPosFromHM2nd();
				hmRoom2Night.goingHM2ndFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HMROOM2NIGHT;
			}

			break;

		case gameState::HMNIGHT:
			hmNight.handleInput();
			hmNight.update();
			hmNight.animUpdate(dt);
			hmNight.Camera();
			hmNight.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (hmNight.stopBGM()) {
				bgm2.stop();
			}

			if (hp.noHP()) {
				hmNight.restart();
			}

			if (crafting.weapon1Chosen()) {
				hmNight.setWeapon1();
			}
			if (crafting.weapon2Chosen()) {
				hmNight.setWeapon2();
			}
			if (crafting.weapon3Chosen()) {
				hmNight.setWeapon3();
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::HMNIGHT;
			}

			if (hmNight.gotoHM2nd()) {
				hm2NDNight.playerPosFromHM();
				hm2NDNight.goingHMFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HM2NDNIGHT;
			}

			if (hmNight.gotoRoom1()) {
				doorSFX.play();
				hmRoom1.playerPosFromHM();
				hmRoom1.goingHMFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				ghostSFX.pause();
				ghostSFX.play();
				currentState = gameState::HMROOM1;
			}

			if (hmRoom1.bossDead()) {
				hmNight.bossDefeated(true);
				bgm.stop();
			}

			/*if (hmNight.gotoCBA()) {
				cba.playerPosFromHM();
				cba.goingHMFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				bossBGM.pause();
				bossBGM.play();
				currentState = gameState::CBA;
			}*/

			if (hmNight.gotoCBA()) {
				crafting.showSecondSet(true);
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::CRAFTING;
			}

			break;

		case gameState::HMROOM1:
			hmRoom1.handleInput();
			hmRoom1.update();
			hmRoom1.animUpdate(dt);
			hmRoom1.Camera();
			hmRoom1.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (crafting.weapon1Chosen()) {
				hmRoom1.setWeapon1();
			}
			if (crafting.weapon2Chosen()) {
				hmRoom1.setWeapon2();
			}
			if (crafting.weapon3Chosen()) {
				hmRoom1.setWeapon3();
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::HMROOM1;
			}

			if (hmRoom1.gotoHM()) {
				doorSFX.play();
				hmNight.playerPosFromRoom1();
				hmNight.goingRoom1False();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HMNIGHT;
			}

			break;

		case gameState::CBA:
			cba.handleInput();
			cba.update();
			cba.animUpdate(dt);
			cba.Camera();
			cba.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (cba.bossDead()) {
				bossBGM.stop();
			}

			if (crafting.weapon4Chosen()) {
				cba.setWeapon1();
			}
			if (crafting.weapon5Chosen()) {
				cba.setWeapon2();
			}
			if (crafting.weapon6Chosen()) {
				cba.setWeapon3();
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::CBA;
			}

			if (cba.gotoHM()) {
				hmNight.playerPosFromCBA();
				hmNight.goingCBAFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::HMNIGHT;
			}

			if (cba.gotoRoom()) {
				doorSFX.play();
				cbaRoom.playerPosFromCBA();
				cbaRoom.goingCBAFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				orbSFX.pause();
				orbSFX.play();
				currentState = gameState::CBAROOM;
			}

			break;

		case gameState::CBAROOM:
			cbaRoom.handleInput();
			cbaRoom.update();
			cbaRoom.animUpdate(dt);
			cbaRoom.Camera();
			cbaRoom.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::CBAROOM;
			}

			if (cbaRoom.gotoCBA()) {
				doorSFX.play();
				cba.playerPosFromRoom();
				cba.goingRoomFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::CBA;
			}

			if (cbaRoom.startScene()) {
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				orbSFX.stop();
				currentState = gameState::SCENE10;
			}

			break;

		case gameState::SCENE10:
			cutScene2.handleInput();
			cutScene2.scene10();
			if (!fadeTrans.isFadedOut()) {
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Enter)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				bossBGM.pause();
				bossBGM.play();
				bossBGM.setLoop(true);
				currentState = gameState::BOSSFIGHT;
			}

			break;

		case gameState::BOSSFIGHT:
			bossFight.handleInput();
			bossFight.update();
			bossFight.animUpdate(dt);
			bossFight.Camera();
			bossFight.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (bossFight.stopBGM()) {
				bossBGM.stop();
			}

			if (crafting.weapon4Chosen()) {
				bossFight.setWeapon1();
			}
			if (crafting.weapon5Chosen()) {
				bossFight.setWeapon2();
			}
			if (crafting.weapon6Chosen()) {
				bossFight.setWeapon3();
			}

			if (hp.noHP()) {
				bossFight.restart();
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::BOSSFIGHT;
			}

			if (bossFight.sceneComplete()) {
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				nightBGM.pause();
				nightBGM.play();
				currentState = gameState::LASTSCENE2;
			}

			break;

		case gameState::LASTSCENE2:
			//std::cout << "in game\n";
			skylabRoomLast.handleInput();
			skylabRoomLast.update();
			skylabRoomLast.animUpdate(dt);
			skylabRoomLast.npcUpdate(dt);
			skylabRoomLast.Camera();
			skylabRoomLast.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::LASTSCENE2;
			}

			// credits
			if (skylabRoomLast.gotoCredits()) {
				fadeTrans.fadedOutFalse();
				nightBGM.stop();
				doorSFX.play();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				endBGM2.pause();
				endBGM2.play();
				currentState = gameState::EXIT;
			}

			break;

		case gameState::CRAFTING:
			crafting.handleInput();
			crafting.update();
			crafting.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();

			if (crafting.weapon1Chosen()) {
				inv.weapon1Crafted();
			}
			if (crafting.weapon2Chosen()) {
				inv.weapon2Crafted();
			}
			if (crafting.weapon3Chosen()) {
				inv.weapon3Crafted();
			}

			if (crafting.weapon4Chosen()) {
				inv.weapon4Crafted();
			}
			if (crafting.weapon5Chosen()) {
				inv.weapon5Crafted();
			}
			if (crafting.weapon6Chosen()) {
				inv.weapon6Crafted();
			}

			if (Keyboard::isKeyPressed(Keyboard::Q)) {
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				loadScreen.clockRestart();
				loadScreen.loadCompleteFalse();
				fadeTrans.fadedOutFalse();
				fadeTrans.fadedInFalse();

				while (!loadScreen.loadingComplete()) {
					loadScreen.initLoadingScreen();
					loadScreen.update(dt);
					loadScreen.render();
					window.display();
				}

				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}

				currentState = gameState::EXIT;
			}

			if (Keyboard::isKeyPressed(Keyboard::P)) {
				currentState = gameState::PAUSED;
				previousState = gameState::CRAFTING;
			}

			if (crafting.doneChoosing()) {
				equipSFX.pause();
				equipSFX.play();
				hm2NDNight.playerPosFromHMRoom2();
				hm2NDNight.goingHMRoom2False();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				nightBGM.stop();
				bgm2.pause();
				bgm2.play();
				bgm2.setVolume(40);
				bgm2.setLoop(true);
				currentState = gameState::HM2NDNIGHT;
			}

			if (crafting.doneChoosing2()) {
				equipSFX.pause();
				equipSFX.play();
				cba.playerPosFromHM();
				cba.goingHMFalse();
				fadeTrans.fadedOutFalse();
				while (!fadeTrans.isFadedIn()) {
					fadeTrans.updateIn(dt);
					fadeTrans.renderIn();
					window.display();
				}
				bossBGM.pause();
				bossBGM.play();
				bossBGM.setLoop(true);
				currentState = gameState::CBA;
			}

			break;

		case gameState::PAUSED:
			pauseMenu.handleInput();
			pauseMenu.update();
			pauseMenu.render();

			if (pauseMenu.resumeButtonPressed()) {
				currentState = previousState;
			}
			else if (pauseMenu.quitGameButtonPressed()) {
				window.close();
			}
			break;

		case gameState::EXIT:
			std::cout << "in end screen\n";
			end.handleInput();
			end.update();
			end.animupdate(dt);
			end.render();
			if (!fadeTrans.isFadedOut()) {
				window.setView(window.getDefaultView());
				fadeTrans.updateOut(dt);
				fadeTrans.renderOut();
			}
			window.display();
			fadeTrans.fadedInFalse();
			break;
		}
	}
	return 0;
}