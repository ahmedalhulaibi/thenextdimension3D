/*
	NOVEMBER 2ND, 2012, 8:55 PM
*/
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <windows.h>
#include "Game.h"
#include "Sprite.h"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"

#define _WIN32_WINNT 0x0500
#include <Windows.h>
#include <iostream>

using namespace std;
//physical window size
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900
//screen size
#define WINDOW_SCREEN_WIDTH 1600
#define WINDOW_SCREEN_HEIGHT 900
#define FRAMES_PER_SECOND 30
Game *theGame;
int screenMode = 1;

enum screenMode{
	STATE_WINDOWED,
	STATE_FULLSCREEN
};
// Create the main window	


sf::Text scoreText;
sf::Text win_or_lose;
sf::Text currentKey;

sf::Event Event;

sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "The Next Dimension", sf::Style::Default);

void initImageLibrary()
{
	glEnable(GL_TEXTURE_2D);
	ilInit();
	iluInit();
	ilutRenderer(ILUT_OPENGL);
}

void DisplayCallbackFunction(void)
{
	//theGame->draw();

	if(theGame->stateInfo.gameState == STATE_GAMEPLAY)
	{
		App.pushGLStates();
		stringstream ss;
		ss.clear();
		ss << theGame->score;
		string scoreString = "SCORE ";
		scoreString.append(ss.str());
		scoreText.setString(scoreString.c_str());
		scoreText.setPosition(650,0);
		App.draw(scoreText);
	}else if(theGame->stateInfo.gameState == STATE_SCORING)
	{
		App.pushGLStates();
		stringstream ss;
		ss.clear();
		ss << theGame->score;
		string scoreString = "SCORE ";
		scoreString.append(ss.str());
	//	scoreText.setString(scoreString.c_str());
		scoreText.setString(theGame->s.c_str());
		scoreText.setPosition(650,400);
		App.draw(scoreText);
	}else if(theGame->stateInfo.gameState == STATE_CONTROLS && !sf::Joystick::isConnected(0))
	{
		App.pushGLStates();
		//just handling drawing
		int numButtons = theGame->controlsMenu->actionKeys.size();

		for(int i = 0; i<numButtons; i++)
		{
			typedef map<string, int>::iterator it;
			for(it iterator = theGame->controlsMenu->keys.begin();
				iterator != theGame->controlsMenu->keys.end(); iterator++)
			{
				if(theGame->controlsMenu->actionKeys[i] ==
					iterator->second)
				{

					if(screenMode == STATE_WINDOWED)
					{
						string test = iterator->first;
					    currentKey.setString(test);
						currentKey.setPosition(theGame->controlsMenu->buttons[i].x + 390,
											  theGame->controlsMenu->buttons[i].y +5);
						currentKey.setCharacterSize(40);
						App.draw(currentKey);
					}

					else if(screenMode == STATE_FULLSCREEN)
					{
						string test = iterator->first;
					    currentKey.setString(test);
						currentKey.setPosition(theGame->controlsMenu->buttons[i].x + 390,
										  theGame->controlsMenu->buttons[i].y +32);
					currentKey.setCharacterSize(40);
					App.draw(currentKey);
					}
				}
			}
		}

		

		//draw as an offset from each button
		/*int buttons = theGame->controlsMenu->buttons.size() - 1;
		for(int i = 0; i<buttons; i++)
		{

		}*/
	}else if(theGame->stateInfo.gameState == STATE_MENU)
	{
		App.pushGLStates();
		string s = "CONTINUE TO NEXT DIMENSION?\n          Y for Yes  N for No";
		scoreText.setString(s.c_str());
		scoreText.setPosition(430,400);
		App.draw(scoreText);

	}
	App.display();
	if(theGame->stateInfo.gameState == STATE_GAMEPLAY || theGame->stateInfo.gameState == STATE_SCORING || theGame->stateInfo.gameState == STATE_CONTROLS ||theGame->stateInfo.gameState == STATE_MENU)
	{
		App.popGLStates();
	}
	
}

/* function WindowReshapeCallbackFunction()
 * Description: 
 *  - this is called whenever the window is resized 
 *  - and sets up the projection matrix properly
 *  - currently set up for an orthographic view (2D only)
 */
void WindowReshapeCallbackFunction(int w,int h)
{
	//gluOrtho2D(0,WINDOW_SCREEN_WIDTH,0,WINDOW_SCREEN_HEIGHT)
	theGame->setNewWindowSize(w,h);
	theGame->setScreenSize(WINDOW_SCREEN_WIDTH, WINDOW_SCREEN_HEIGHT);
	theGame->updateScreenRatio();
}

void SpecialKeyEvent()
{
	// Close window : exit
	
	if (Event.type == sf::Event::Closed)
		App.close();

            // Escape key : exit
	if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
		App.close();

	if(theGame->mainMenu->exitClick)
		App.close();

	if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::PageUp))
	{
		if(theGame->camZ < 150)
		{
			theGame->camZ++;
		}
		float scale = 0.5 + ((theGame->camZ/300.0));
		for(int i = 0; i < theGame->powerups.size(); i++)
		{
			theGame->powerups[i]->setScale(scale,scale,scale);
		}
		for(int i = 0; i < 5; i++)
		{
			theGame->powerups_init[i]->setScale(scale,scale,scale);
		}
	}
	if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::PageDown))
	{
		if(theGame->camZ > 30)
		{
			theGame->camZ--;
		}
		float scale = 0.5 + ((theGame->camZ/300.0));
		for(int i = 0; i < theGame->powerups.size(); i++)
		{
			theGame->powerups[i]->setScale(scale,scale,scale);
		}
		for(int i = 0; i < 5; i++)
		{
			theGame->powerups_init[i]->setScale(scale,scale,scale);
		}
	}
	
	// Resize event : adjust viewport
	if(Event.type == sf::Event::Resized)
	{
		WindowReshapeCallbackFunction(Event.size.width, Event.size.height);
	}
        
}

/*/////////////////////////////////////////////////////////
 Entry point of application

 \return Application exit code

/////////////////////////////////////////////////////////*/
int main(int argc, char **argv)
{
	//hiding console
	HWND hWnd = GetConsoleWindow();
	ShowWindow (hWnd, SW_HIDE);
	

	if(screenMode == STATE_WINDOWED)
		App.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "The Next Dimension", sf::Style::Default);

	else if(screenMode == STATE_FULLSCREEN)
		App.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "The Next Dimension", sf::Style::Fullscreen);

	glewInit();
	initImageLibrary();
	sf::Texture loadingScreen_texture;
	loadingScreen_texture.loadFromFile("images/Loading Screen/LoadingScreen.png");
	sf::Sprite loadingScreen(loadingScreen_texture);
	App.pushGLStates();
	App.draw(loadingScreen);
	App.display();
	App.popGLStates();
	/* init the game */
	theGame = new Game();
	theGame->setNewWindowSize(WINDOW_WIDTH,WINDOW_HEIGHT);
	theGame->setScreenSize(WINDOW_SCREEN_WIDTH,WINDOW_SCREEN_HEIGHT);
	theGame->updateScreenRatio();
	theGame->initializeGame();

	theGame->elapsedTime = theGame->totalTime = 0;

	App.setFramerateLimit(60);
	App.setVerticalSyncEnabled(true);
	sf::Font slider;
	sf::Font undercover;
	slider.loadFromFile("images/SLIDER.TTF");
	undercover.loadFromFile("images/UNDERCOV.TTF");
	scoreText.setFont(undercover);
	//scoreText.setCharacterSize(60);
	win_or_lose.setFont(slider);
	sf::Mouse Mouse;
	sf::Keyboard Keyboard;
	sf::Vector2i v;//used for mouse coords

    // Create a clock for measuring time elapsed
    sf::Clock Clock;

	//glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	int maxMotionFrames = 3;
	int accumMotionFrames = 0;
    // Start game loop
    while (App.isOpen())
    {
		while (App.pollEvent(Event))
        {
            SpecialKeyEvent();
        }

        // Set the active window before using OpenGL commands
        // It's useless here because active window is always the same,
        // but don't forget it if you use multiple windows or controls
		App.setActive();
		

        // Finally, display rendered frame on screen
		v = Mouse.getPosition(App);
		
		
		sf::Time time = Clock.getElapsedTime();
		theGame->elapsedTime = time.asSeconds();
		theGame->totalTime += time.asSeconds();
		//DisplayCallbackFunction();
		theGame->input.MouseX = v.x;
		theGame->input.MouseY = v.y;
		theGame->updateInput();
		theGame->update();
		Clock.restart();

		theGame->draw();
		theGame->gameMusic->update();
		theGame->hubMusic->update();
		FMOD_Channel_SetVolume(theGame->gameMusic->channel,0.25);
		FMOD_Channel_SetVolume(theGame->hubMusic->channel,0.5);
		//FMOD_Channel_SetVolume(theGame->player->shooting_sound->channel,0.2);
		theGame->player->shooting_sound->update();
		theGame->finalBoss_dialogue->update();
		if(theGame->stateInfo.bossState == STATE_NO_BOSS || theGame->stateInfo.gameState == STATE_LEVELSELECT)
		{
			theGame->finalBoss_dialogue->pause();
		}
		theGame->menuClick->update();
		theGame->slowDownTime_begin->update();
		theGame->slowDownTime_end->update();
		theGame->powerup_pickUp->update();

		theGame->soundSystem->update();
		if(theGame->player->accelWeight >= 0.5)
		{
			if(theGame->player->accelWeight > 1.1)
			{
				maxMotionFrames = (int)theGame->player->velocity.returnLength()+3;
			}else if(theGame->player->accelWeight > 0.5)
			{
				maxMotionFrames = (int)theGame->player->velocity.returnLength()+1;
			}
			if(accumMotionFrames == 0)
			{
				glAccum(GL_LOAD,1.0/maxMotionFrames);
			}else
			{
				glAccum(GL_ACCUM,1.0/maxMotionFrames);
			}

			accumMotionFrames++;

			if(accumMotionFrames >= maxMotionFrames)
			{
				accumMotionFrames = 0;
				glAccum(GL_RETURN, 1.0);
				DisplayCallbackFunction();
				glClearAccum(0,0,0,1);
				glClear(GL_ACCUM_BUFFER_BIT);
			}
		}else 
		{
			//if(accumMotionFrames /*>= maxMotionFrames*/)
			//{
			//	accumMotionFrames = 0;
			//	glAccum(GL_RETURN, 1.0);
			//	DisplayCallbackFunction();
			//	/*glClearAccum(0,0,0,1);
			//	glClear(GL_ACCUM_BUFFER_BIT);*/
			//}else
			{
				accumMotionFrames = 0;
				glClearAccum(0,0,0,1);
				glClear(GL_ACCUM_BUFFER_BIT);
				DisplayCallbackFunction();
			}
		}
    }

	//screenMode = theGame->stateInfo.screenState;
    return EXIT_SUCCESS;
}