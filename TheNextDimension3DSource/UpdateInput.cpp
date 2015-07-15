#include "Game.h"
using namespace std;

bool buttonDown = false;
bool controlsButtonDown = false;
bool povhDown = false;
//used in menu navigation with controller
bool xbuttonDown = false;
bool circleButtonDown = false;
bool l2ButtonDown = false;

int oldKey = 0;


void Game::updateInput()
{
	
	if(stateInfo.keymap && (stateInfo.gameState == STATE_CONTROLS) && !sf::Joystick::isConnected(0))
	{
		bool finished = false;
		controlsMenu->actionKeys[controlsMenu->currentButton] = 99;

		for(int i = 0; i <(int)sf::Keyboard::KeyCount; i++)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)i))
			{
				for(int j = 0; j<controlsMenu->actionKeys.size(); j++)
				{
					if(controlsMenu->currentButton != controlsMenu->actionKeys[j] &&
						i == controlsMenu->actionKeys[j])
					{
						controlsMenu->actionKeys[controlsMenu->currentButton] = i;
						controlsMenu->actionKeys[j] = oldKey;
						stateInfo.keymap = false;
					}
				}
				controlsMenu->actionKeys[controlsMenu->currentButton] = i;
				updateActionKeys();
				stateInfo.keymap = false;
				controlsMenu->stopCollision = false;
			}
		}
	}
		input.LeftKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		input.RightKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		input.UpKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		input.DownKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);

		input.S_KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		input.W_KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		input.R_KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
		input.F_KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::F);
		input.P_KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::P);
		input.Y_KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Y);
		input.N_KeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::N);
		input.BackSlash_Down = sf::Keyboard::isKeyPressed(sf::Keyboard::BackSlash);
		input.SpaceBar_Down = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
		input.ReturnKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
		input.TabKeyDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Tab);
		input.tilde = sf::Keyboard::isKeyPressed(sf::Keyboard::Tilde);

		input.NUMKEY_1 = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
		input.NUMKEY_2 = sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
		input.NUMKEY_3 = sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
		
		input.LeftButtonDown  = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		input.MiddleButtonDown= sf::Mouse::isButtonPressed(sf::Mouse::Middle);
		input.RightButtonDown = sf::Mouse::isButtonPressed(sf::Mouse::Right);
		
		
		 /*glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
		 glGetDoublev( GL_PROJECTION_MATRIX, projection );
		 glGetIntegerv( GL_VIEWPORT, viewport );

		 winX = (float)input.MouseX;
		 winY = (float)viewport[3] - (float)input.MouseY;
		
		 glReadPixels( input.MouseX, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
		 gluUnProject( winX, winY, winZ, modelview, projection, viewport, &input.clickX, &input.clickY, &input.clickZ);*/

		 missile.orientation = bullet.orientation = player->orientation;

		// player->position.thisVector.z = 0;
		// player->position.X_Y_Z[2] = 0;
		 
		
		/*{
			mouseInput();
		}*/
		if (sf::Joystick::isConnected(0))
		{
			joystickInput();
		}
		else
		{
			
			 Vector temp = Vector(((float)input.MouseX)-800,(((float)input.MouseY)-450)*(-1),0);

			 temp.normalize();
		 
			 player->directionVec = Vector(1,0,0);
			 float angle = player->directionVec.angle(temp);
			 if(temp.thisVector.y < 0)
			 {
				 angle *= (-1.f);
			 }
			 player->orientation = Quaternion(angle,false,false,true);
			keyboardInput();
			mouseInput();
			//sf::Joystick::update();
		}
		
}
/*************************************************/
/* INPUT - keyboard/mouse functions below        */
/*************************************************/
/* keyboardInput()
	- tests whether a key is down
	-allows for multiple inputs
	-to add a new button go to _InputInfo struct in Game.h
*/

void Game::keyboardInput()
{
	
	if(input.ReturnKeyDown)
	{
		if(returnK == false)
		{
			returnK = true;
			if(stateInfo.gameState == STATE_MAINMENU)
			{
				stateInfo.gameState = STATE_CUTSCENE;
				stateInfo.subState = STATE_CUTSCENE1;
				introDialogue->play(player->position);
				/*if(stateInfo.gameState == STATE_CUTSCENE)
				{
					if(stateInfo.subState == STATE_CUTSCENE1)
					{
						stateInfo.gameState = STATE_LEVELSELECT;
						stateInfo.subState = STATE_HUB;
					}
				}*/
			}else if(stateInfo.gameState == STATE_CUTSCENE)
			{
				if(stateInfo.subState == STATE_CUTSCENE1 || stateInfo.subState == STATE_CUTSCENE3)
				{
					stateInfo.gameState = STATE_LEVELSELECT;
					stateInfo.subState = STATE_HUB;
					introDialogue->pause();
					hubMusic->play(player->position);
				}
			}else if(stateInfo.gameState == STATE_LEVELSELECT)
			{
				player->position = Vector(0,0,0);
			}
		}
	}else
	{
		returnK = false;
	}
	
	if(stateInfo.gameState == STATE_MENU)
	{
		if(input.Y_KeyDown)
		{
			stateInfo.gameState = STATE_GAMEPLAY;
			stateInfo.bossState = STATE_NO_BOSS;
			player->position = Vector(0,0,0);
			this->score = 0;
			score = 0;
			camZ = 70;
			loadLevel();
		}
		else if(input.N_KeyDown)
		{
			stateInfo.gameState = STATE_LEVELSELECT;
			stateInfo.subState = STATE_HUB;
			player->position = Vector(0,0,0);
			currentLevel = &levels[0];
			camZ = 70;
		}
	}

	else if(stateInfo.gameState == STATE_SCORING)
	{
		if(input.ReturnKeyDown)
		{
			stateInfo.gameState = STATE_LEVELSELECT;
			stateInfo.subState = STATE_HUB;
			score = 0;
			currentLevel = &levels[0];
		}
	}

	else if(stateInfo.gameState == STATE_LEVELSELECT)
	{
		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.up_key) || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.down_key)  || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.right_key) || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.left_key))
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.boost_key))
			{
				player->accelWeight = 0.6;
			}else
			{
				player->accelWeight = 0.2;
			}

			player->setVel(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.up_key),sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.down_key),sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.left_key),sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.right_key));
		}else
		{
			player->velocity = player->acceleration = Vector(0,0,0);
		}

		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.elevateup_key))
		{
			if(player->position.X_Y_Z[2] < 5)
			{
				player->position.X_Y_Z[2]++;
				player->position.thisVector.z = player->position.X_Y_Z[2];
			}
		}
		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.elevatedown_key))
		{
			if(player->position.X_Y_Z[2] > -5)
			{
				player->position.X_Y_Z[2]--;
				player->position.thisVector.z = player->position.X_Y_Z[2];
			}
		}

		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.camera_key))
		{
			if(!switched)
			{
				if(perspective<2)
				{
					perspective++;
				}
				else
				{
					perspective=0;
				}
				switched=true;
			}
		}
		else
		{
			switched=false;
		}

		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.pause_key))
		{
			stateInfo.gameState = STATE_PAUSED;
			stateInfo.menuState = STATE_HUB_PAUSE;
		}
	}

	else if(stateInfo.gameState == STATE_GAMEPLAY)
	{
		/*if(stateInfo.subState != STATE_LEVEL2)
		{*/
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.up_key) || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.down_key)  || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.right_key) || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.left_key))
			{
				if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.boost_key))
				{
					if(player->boostFuel > 0)
					{
						if(!playerSpeedUp)
						{
							player->accelWeight = 0.6;
						}else
						{
							player->accelWeight = 1.2;
						}
						player->boostFuel -= 0.33333333;
					}else
					{
						if(!playerSpeedUp)
						{
							player->accelWeight = 0.2;
						}else
						{
							player->accelWeight = 0.6;
						}
					}
				}else
				{
					if(player->boostFuel < 101)
					{
						player->boostFuel += 0.11111111;
						if(player->boostFuel > 100)
						{
							player->boostFuel = 100;
						}
					}
					if(!playerSpeedUp)
					{
						player->accelWeight = 0.2;
					}else
					{
						player->accelWeight = 0.6;
					}
				}

				player->setVel(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.up_key),sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.down_key),sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.left_key),sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.right_key));
			}else
			{
				player->velocity = player->acceleration = Vector(0,0,0);
				if(player->boostFuel < 101)
				{
					player->boostFuel += 0.11111111;
				}
			}
		/*}
		else
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.up_key) || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.down_key)  || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.right_key) || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.left_key))
			{
				if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.boost_key))
				{
					if(player->boostFuel > 0)
					{
						if(!playerSpeedUp)
						{
							player->accelWeight = 0.4;
						}else
						{
							player->accelWeight = 0.8;
						}
						player->boostFuel -= 0.22222222;
					}else
					{
						if(!playerSpeedUp)
						{
							player->accelWeight = 0.05;
						}else
						{
							player->accelWeight = 0.3;
						}
					}
				}else
				{
					if(player->boostFuel < 101)
					{
						player->boostFuel += 0.11111111;
						if(player->boostFuel > 100)
						{
							player->boostFuel = 100;
						}
					}
					if(!playerSpeedUp)
					{
						player->accelWeight = 0.05;
					}else
					{
						player->accelWeight = 0.3;
					}
				}

				player->setVel(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.up_key),sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.down_key),sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.left_key),sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.right_key));
			}else
			{
				player->velocity = player->acceleration = Vector(0,0,0);
				if(player->boostFuel < 101)
				{
					player->boostFuel += 0.11111111;
				}
			}
		}*/
	
		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.pause_key))
		{
			stateInfo.gameState = STATE_PAUSED;
			stateInfo.menuState = STATE_GAMEPLAY_PAUSE;
		}
		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.elevateup_key))
		{
			if(player->position.X_Y_Z[2] < 5)
			{
				player->position.X_Y_Z[2]++;
				player->position.thisVector.z = player->position.X_Y_Z[2];
			}
		}
		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.elevatedown_key))
		{
			if(player->position.X_Y_Z[2] > -5)
			{
				player->position.X_Y_Z[2]--;
				player->position.thisVector.z = player->position.X_Y_Z[2];
			}
		}

		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.camera_key))
		{
			if(!switched)
			{
				if(perspective<2)
				{
					perspective++;
				}
				else
				{
					perspective=0;
				}
				switched=true;
			}
		}
		else
		{
			switched=false;
		}

		/*if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.elevatedown_key))
		{
			if(!pressed)
			{
				stateInfo.gameState = STATE_PAUSED;
				pressed=true;
			}
		}
		else
		{
			pressed=false;
		}*/

		if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.switchpowerup_key))
		{
			if ((player->powerups.size() > 0) && !selected)
			{
				bool found = false;
				for (int i=0; i<player->powerups.size(); i++)
				{
					if (player->powerups[i] > currentID)
					{
						currentID = player->powerups[i];
						i = player->powerups.size();
						found = true;
						selected = true;
					}
				}
				if (!found)
				{
					currentID = player->powerups[0];
					selected = true;
				}
			}
		}
		else
		{
			selected = false;
		}

		if(stateInfo.subState == STATE_LEVEL3)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.missiles_key))
			{
				missiles = true;
				flamethrower = false;
				waterGun = false;
			}
		}
		if(stateInfo.subState == STATE_LEVEL4)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.missiles_key))
			{
				missiles = true;
				flamethrower = false;
				waterGun = false;
			}else if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.flamethrower_key))
			{
				missiles = false;
				flamethrower = true;
				waterGun = false;
			}
		}else if(stateInfo.subState == STATE_LEVEL5)
		{
			if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.missiles_key))
			{
				missiles = true;
				flamethrower = false;
				waterGun = false;
			}else if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.flamethrower_key))
			{
				missiles = false;
				flamethrower = true;
				waterGun = false;
			}else if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.watergun_key))
			{
				missiles = false;
				flamethrower = false;
				waterGun = true;
			}
		}
	}

	/*else if(stateInfo.gameState == STATE_PAUSED)
	{
		if(input.pause_key)
		{
			if(!pressed)
			{
				stateInfo.gameState = STATE_GAMEPLAY;
				pressed=true;
			}
		}
		else
		{
			pressed=false;
		}
	}*/
	if(input.tilde)
	{
		if(stateInfo.gameState == STATE_GAMEPLAY || stateInfo.gameState == STATE_LEVELSELECT)
		{
			if(!pushed)
			{
				//player->health = 100;
				Vector temp_d = player->directionVec;
				player->orientation.normalize();
				temp_d.multiplyVector(player->orientation);
				temp_d.multiplyVector(5);
				Vector temp_p = player->position;
				temp_p.addVector(temp_d);
				bool willCollide = false;
				if(stateInfo.subState >= STATE_HUB && stateInfo.subState < STATE_LEVEL6)
				{
					for(int i=0; i<4; i++)
					{
						if(checkIfWillCollide(player_collider, &level_border[i], temp_p))
						{
							willCollide = true;
						}
					}
				}
				switch (stateInfo.subState)
				{
				case STATE_LEVEL1:
					for(int i=0; i<6; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level1[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				case STATE_LEVEL2:
					for(int i=0; i<6; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level2[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				case STATE_LEVEL3:
					for(int i=0; i<8; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level3[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				case STATE_LEVEL5:
					for(int i=0; i<14; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level5[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				}
				if(!willCollide)
				{
					player->position = temp_p;
				}
				pushed = true;
			}
		}
	}
	else
	{
		pushed = false;
	}
}
/*
 * mouseClicked
 * - this function is called when the mouse is clicked and it handles the 
 *   input state managment
 */
void Game::mouseInput()
{
	 Vector temp = Vector(((float)input.MouseX)-800,(((float)input.MouseY)-450)*(-1),0);

	 //mouse hover for all menus
	if(stateInfo.gameState == STATE_MAINMENU)
	{	
			if(mainMenu->checkButtonCollision(input.MouseX, input.MouseY))
			{
				if(mainMenu->currentButton == 0)
				   newGame_Button->currentFrame = 1;

				else if(mainMenu->currentButton == 1)
					settings_Button->currentFrame = 1;

				else if(mainMenu->currentButton == 2)
					credits_Button->currentFrame = 1;

				else if(mainMenu->currentButton == 3)
					exit_Button->currentFrame = 1;
			}
			else if(!mainMenu->checkButtonCollision(input.MouseX, input.MouseY))
			{
				   newGame_Button->currentFrame = 0;
				   settings_Button->currentFrame = 0;
				   credits_Button->currentFrame = 0;
				   exit_Button->currentFrame = 0;
			}

   }

	else if(stateInfo.gameState == STATE_SETTINGS)
	{
		if(settingsMenu->checkButtonCollision(input.MouseX, input.MouseY))
		{
			//controls
			if(settingsMenu->currentButton == 1)
				controls_Button->currentFrame = 1;
			
			//how to play
			else if(settingsMenu->currentButton == 2)
				howtoplay_Button->currentFrame = 1;

			else if(settingsMenu->currentButton == 3)
				back_Button->currentFrame = 1;

		}
		else
		{
			controls_Button->currentFrame = 0;
			howtoplay_Button->currentFrame = 0;
			back_Button->currentFrame = 0;
		}
	}

	else if(stateInfo.gameState == STATE_CONTROLS)
	{
		if(controlsMenu->checkButtonCollision(input.MouseX, input.MouseY))
		{
			//camPos = Vector(player->position.X_Y_Z[0],player->position.X_Y_Z[1],70);
			if(controlsMenu->currentButton == 13)
			  back_Button->currentFrame = 1;
			
			else
			  back_Button->currentFrame = 0;
		}
		
	}

	else if(stateInfo.gameState == STATE_HOWTOPLAY)
	{
		if(howtoplayMenu->checkButtonCollision(input.MouseX, input.MouseY))
			back_Button->currentFrame = 1;
		else 
			back_Button->currentFrame = 0;
	}

	else if(stateInfo.gameState == STATE_PAUSED)
	{
		if(pauseMenu->checkButtonCollision(input.MouseX, input.MouseY))
		{
			if(pauseMenu->currentButton == 0)
				resume_Button->currentFrame = 1;
			
			else if(pauseMenu->currentButton == 1)
				settings_Button->currentFrame = 1;
			
			else if(pauseMenu->currentButton == 2)
				hub_Button->currentFrame = 1;
		}

		else
		{
			resume_Button->currentFrame = 0;
			settings_Button->currentFrame = 0;
			hub_Button->currentFrame = 0;
		}
	}

	else if(stateInfo.gameState == STATE_CREDITS)
	{
		if(creditsMenu->checkButtonCollision(input.MouseX, input.MouseY))
		{
			back_Button->currentFrame = 1;
		}

		else
			back_Button->currentFrame = 0;
	}

	//on mouse button click---------------------------------------------------------------
	if(input.LeftButtonDown && !sf::Joystick::isConnected(0)) 
	{
		cout<<"X: "<<input.MouseX<<
			"Y: "<<input.MouseY<<endl;

		//cout<< "Button ID: "<<
			//controlsMenu->currentButton<<endl;

		if(stateInfo.gameState == STATE_GAMEPLAY)
		{
			if(frameCount%4 == 0)
			{
				player->fireBullet(temp, bullet);
			}
		}

	
		else if(stateInfo.gameState == STATE_MAINMENU)
		{
			if(mainMenu->checkButtonCollision(input.MouseX, input.MouseY) && buttonDown == false)
			{
				menuClick->play(player->position);
				buttonDown = true;
				if(mainMenu->currentButton == 0)
				{
					this->stateInfo.gameState = STATE_CUTSCENE;
					this->stateInfo.subState = STATE_CUTSCENE1;
					introDialogue->play(player->position);
				}

				else if(mainMenu->currentButton == 1)
				{
					this->stateInfo.gameState = STATE_SETTINGS;
					stateInfo.menuState = STATE_MAIN_SETTINGS;
				}
				

				else if(mainMenu->currentButton == 2)
					this->stateInfo.gameState = STATE_CREDITS;

				else if(mainMenu->currentButton == 3)
					mainMenu->exitClick = true;
				
			}
		}

		else if(stateInfo.gameState == STATE_SETTINGS)
		{		
			if(settingsMenu->checkButtonCollision(input.MouseX, input.MouseY) && buttonDown == false)
			{
				menuClick->play(player->position);	
				buttonDown = true;
				if(settingsMenu->currentButton == 0)
				{
					//put in code to switch fullscreen off
					if(audio_Button->currentFrame == 0)
						audio_Button->currentFrame = 1;
					
					else if(audio_Button->currentFrame == 1)
						audio_Button->currentFrame = 0;
					
				}

				else if(settingsMenu->currentButton == 1)
				{
					stateInfo.gameState = STATE_CONTROLS;
					//controlsButtonDown = true;
				}

				else if(settingsMenu->currentButton == 2)
				{
					stateInfo.gameState = STATE_HOWTOPLAY;
				}

				//back button
				else if(settingsMenu->currentButton == 3)
				{
					if(stateInfo.menuState == STATE_MAIN_SETTINGS)
						stateInfo.gameState = STATE_MAINMENU;
					
					else if(stateInfo.menuState == STATE_PAUSE_SETTINGS)
						stateInfo.gameState = STATE_PAUSED;
				}
			}
		}

		else if(stateInfo.gameState == STATE_HOWTOPLAY)
		{
			if(howtoplayMenu->checkButtonCollision(input.MouseX, input.MouseY) && buttonDown == false)
			{
				menuClick->play(player->position);
				buttonDown = true;
			   stateInfo.gameState = STATE_SETTINGS;
			}
		}

		else if(stateInfo.gameState == STATE_CREDITS)
		{
			
			if(creditsMenu->checkButtonCollision(input.MouseX, input.MouseY) && buttonDown == false)
			{
				menuClick->play(player->position);
				buttonDown = true;
				stateInfo.gameState = STATE_MAINMENU;
			}
		}

		else if(stateInfo.gameState == STATE_PAUSED)
		{
			if(pauseMenu->checkButtonCollision(input.MouseX, input.MouseY) && buttonDown == false)
			{
				buttonDown = true;
				menuClick->play(player->position);
				if(stateInfo.subState != STATE_HUB)
				{
					if(pauseMenu->currentButton == 0)
						stateInfo.gameState = STATE_GAMEPLAY;

					else if(pauseMenu->currentButton == 1)
					{
						stateInfo.gameState = STATE_SETTINGS;
						stateInfo.menuState = STATE_PAUSE_SETTINGS;
					}

					else if(pauseMenu->currentButton == 2)
					{
						/*stateInfo.gameState = STATE_LEVELSELECT;
						stateInfo.subState = STATE_HUB;*/
						player->health = 0;
						this->exitLevel();
					}
				}

				else if(stateInfo.subState == STATE_HUB)
				{

					if(pauseMenu->currentButton == 0)
						stateInfo.gameState = STATE_LEVELSELECT;

					else if(pauseMenu->currentButton == 1)
					{
						stateInfo.gameState = STATE_SETTINGS;
						stateInfo.menuState = STATE_PAUSE_SETTINGS;
					}
				}
			}
		}

		else if(stateInfo.gameState == STATE_CONTROLS && !controlsButtonDown)
		{
				if(controlsMenu->currentButton == 13)
				{
					menuClick->play(player->position);
					stateInfo.gameState = STATE_SETTINGS;
				}

				else if(controlsMenu->currentButton == 14)
				{
					resetKeys();menuClick->play(player->position);
				}

				else if(controlsMenu->currentButton >= 0 && controlsMenu->currentButton < 13 
					    &&!stateInfo.keymap)
				{
					menuClick->play(player->position);
					 stateInfo.keymap = true;
					 controlsMenu->stopCollision = true;
					 oldKey = controlsMenu->actionKeys[controlsMenu->currentButton];
				}
			
		  }
		}
	

	else if(!input.LeftButtonDown)
	{
		buttonDown = false;
		controlsButtonDown = false;
	}

	if(!(sf::Joystick::isConnected(0)))
	{
		if(input.RightButtonDown)
		{
			if(stateInfo.gameState == STATE_GAMEPLAY && stateInfo.subState >= STATE_LEVEL3)
			{
				if(missiles)
				{
					if(!fired)
					{
						fired = true;
						player->fireMissiles(temp,missile);
						if(player->missiles.size() == 4)
						{
							player->missiles.erase(player->missiles.begin());
							player->missiles.erase(player->missiles.begin());
						}
					}
				}else if(waterGun)
				{
					player->sprayWater(temp,water);
					if(player->waterFuel > 0)
					{
						player->waterFuel -= 0.66666666666;
					}
					if(player->flamethrowerFuel < 101)
					{
						player->flamethrowerFuel += 0.055555555555;
					}
				}else if(flamethrower)
				{
					if(player->flamethrowerFuel > 0)
					{
						player->flamethrower(temp,fire);
						player->flamethrowerFuel -= 0.66666666666;
					}
					if(player->waterFuel < 101)
					{
						player->waterFuel += 0.1666666666666;
					}
				}
			}
		}else
		{
			fired = false;
			if(player->waterFuel < 101)
			{
				player->waterFuel += 0.3333333333333;
			}
			if(player->flamethrowerFuel < 101)
			{
				player->flamethrowerFuel += 0.11111111111;
			}
		}
		if(input.MiddleButtonDown || sf::Keyboard::isKeyPressed((sf::Keyboard::Key)input.usePowerup_key))
		{
			if(!middleClicked)
			{
				middleClicked = true;
				if(player->powerups.size() > 0)
				{
					int imin=0;
					int imax=player->powerups.size()-1;
					int imid=0;
					bool found = false;
					while (imax >= imin)
					{
						imid = floor((imin+imax)/2.0);
 
						if (player->powerups[imid] < currentID)
						{
							imin = imid + 1;
						}
						else if (player->powerups[imid] > currentID)
						{
							imax = imid - 1;
						}
						else
						{
							found = true;
							break;
						}
					}
					if (found)
					{
						player->powerups.erase(player->powerups.begin()+imid);
						switch(currentID)
						{
						case 1:
							if(player->bombs.size() == 0 && !gravityBomb)
							{
								player->bomb(temp,bomb);
							}
							break;
						case 2:
							player->shieldActive = true;
							player->shield = 500;
							break;
						case 3:
							/*if(freezeEnemies)
							{
								freezeTime = 120;
							}*/
							freezeEnemies = true;
							break;
						case 4:
							if(playerSpeedUp)
							{
								speedUpTime = 180;
							}
							playerSpeedUp = true;
							break;
						case 5:
							if(slowDown)
							{
								slowDownTime = 180;
								slowDown_num+=2;
								slowDownTime_begin->play(player->position);
							}else if(slowDown ==false)
							{
								slowDown = true;
								slowDownTime_begin->play(player->position);
							}

							if(enemies.size() > 0)
							{
								for(int i = 0; i <enemies.size();i++)
								{
									enemies[i]->max_speed /=2;
								}
							}
							break;
						}
					}
				
					if (player->powerups.size() > 0)
					{
						int imin2=0;
						int imax2=player->powerups.size()-1;
						int imid2=0;
						bool found2 = false;
						while (imax2 >= imin2)
						{
							imid2 = floor((imin2+imax2)/2.0);
 
							if (player->powerups[imid2] < currentID)
							{
								imin2 = imid2 + 1;
							}
							else if (player->powerups[imid2] > currentID)
							{
								imax2 = imid2 - 1;
							}
							else
							{
								found2 = true;
								break;
							}
						}
						if (!found2)
						{
							if (!selected)
							{
								bool found3 = false;
								for (int i=player->powerups.size()-1; i>-1; i--)
								{
									if (player->powerups[i] < currentID)
									{
										currentID = player->powerups[i];
										i = 0;
										found3 = true;
										selected = true;
									}
								}
								if (!found3)
								{
									currentID = player->powerups[player->powerups.size()-1];
									selected = true;
								}
							}
						}
					}
				}
			}
		}else
		{
			middleClicked = false;
		}
	}
}

void Game::updateActionKeys()
{
	input.up_key = controlsMenu->actionKeys[0];
	input.down_key = controlsMenu->actionKeys[1];
	input.left_key = controlsMenu->actionKeys[2];
	input.right_key = controlsMenu->actionKeys[3];
	input.boost_key = controlsMenu->actionKeys[4];
	input.usePowerup_key = controlsMenu->actionKeys[5];
	input.switchpowerup_key = controlsMenu->actionKeys[6];
	input.watergun_key = controlsMenu->actionKeys[7];
	input.flamethrower_key = controlsMenu->actionKeys[8];
	input.pause_key = controlsMenu->actionKeys[9];
	input.camera_key = controlsMenu->actionKeys[10];
	input.elevateup_key = controlsMenu->actionKeys[11];
	input.elevatedown_key = controlsMenu->actionKeys[12];
}

void Game::resetKeys()
{
	controlsMenu->actionKeys[0] = 22;
	controlsMenu->actionKeys[1] = 18;
	controlsMenu->actionKeys[2] = 0;
	controlsMenu->actionKeys[3] = 3;
	controlsMenu->actionKeys[4] = 57;
	controlsMenu->actionKeys[5] = 38;
	controlsMenu->actionKeys[6] = 60;
	controlsMenu->actionKeys[7] = 29;
	controlsMenu->actionKeys[8] = 28;
	controlsMenu->actionKeys[9] = 15;
	controlsMenu->actionKeys[10] = 53;
	controlsMenu->actionKeys[11] = 17;
	controlsMenu->actionKeys[12] = 5;

	updateActionKeys();
}

void Game::joystickInput()
{
	//if povx = 100, up on d-pad
	//if povy = 100, down on d-pad
	/*cout<<"Povh x: "<<sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
	cout<<"  Povh y: "<<sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY)<<endl;*/

	float povx = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
	float povy = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);

	unsigned int buttonCount = sf::Joystick::getButtonCount(0);
	int n;
		
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
	float z = sf::Joystick::getAxisPosition(0, sf::Joystick::Z);
	y*=(-1);
	//cout << x << " " << y << " " << z << endl;
	if(x < 10 && x > -10)
	{
		x = 0;
	}
	if(y < 10 && y > -10)
	{
		y = 0;
	}

	
	float r = sf::Joystick::getAxisPosition(0, sf::Joystick::R);
	float u = sf::Joystick::getAxisPosition(0, sf::Joystick::U);
	float v = sf::Joystick::getAxisPosition(0, sf::Joystick::V);
	//cout << r << " " << u << " " << v << endl;
	r*=(-1);
	if(r < 10 && r > -10)
	{
		r = 0;
	}
	if(u < 10 && u > -10)
	{
		u = 0;
	}

	//put all the other non-menu game states here
	if(stateInfo.gameState != STATE_GAMEPLAY && stateInfo.gameState != STATE_MENU && stateInfo.gameState != STATE_LEVELSELECT && 
		stateInfo.gameState != STATE_CUTSCENE)
	{
		//menu navigation---------------------------------------
		if(stateInfo.gameState == STATE_MAINMENU)
		{	
			if(povy == 100 && mainMenu->currentJoystickButton < mainMenu->buttons.size() && povhDown == false)
				{
					mainMenu->currentJoystickButton +=1;
					povhDown = true;
					menuClick->play(player->position);
			    }

			else if(povx == 100 && mainMenu->currentJoystickButton != 0 && povhDown == false)
			{
				mainMenu->currentJoystickButton -=1;
				povhDown = true;
				menuClick->play(player->position);
			}
	    }

		else if(stateInfo.gameState == STATE_SETTINGS)
		{
			if(povy == 100 && settingsMenu->currentJoystickButton < settingsMenu->buttons.size() && povhDown == false)
				{
					settingsMenu->currentJoystickButton +=1;
					povhDown = true;
					menuClick->play(player->position);
			    }

			else if(povx == 100 && settingsMenu->currentJoystickButton != 0 && povhDown == false)
			{
				settingsMenu->currentJoystickButton -=1;
				povhDown = true;
				menuClick->play(player->position);
			}	
		}

		else if(stateInfo.gameState == STATE_PAUSED)
		{
		   if(povy == 100 && pauseMenu->currentJoystickButton < pauseMenu->buttons.size() && povhDown == false)
				{
					pauseMenu->currentJoystickButton +=1;
					povhDown = true;
					menuClick->play(player->position);
			    }

			else if(povx == 100 && pauseMenu->currentJoystickButton != 0 && povhDown == false)
			{
				pauseMenu->currentJoystickButton -=1;
				povhDown = true;
				menuClick->play(player->position);
			}	
		}


		if(povy != 100 && povx != 100)
			povhDown = false;

		//button selection highlights-----------------------------
		if(stateInfo.gameState == STATE_MAINMENU)
		{	
					if(mainMenu->currentJoystickButton == 0)
					   newGame_Button->currentFrame = 1;
					else
					   newGame_Button->currentFrame = 0;

					if(mainMenu->currentJoystickButton == 1)
						settings_Button->currentFrame = 1;
					else
						settings_Button->currentFrame = 0;

					if(mainMenu->currentJoystickButton == 2)
						credits_Button->currentFrame = 1;
					else
						credits_Button->currentFrame = 0;

					if(mainMenu->currentJoystickButton == 3)
						exit_Button->currentFrame = 1;
					else
						exit_Button->currentFrame = 0;

	   }

		else if(stateInfo.gameState == STATE_SETTINGS)
		{
				if(settingsMenu->currentJoystickButton == 1)
					controls_Button->currentFrame = 1;
				else
					controls_Button->currentFrame = 0;
			
				if(settingsMenu->currentJoystickButton == 2)
					howtoplay_Button->currentFrame = 1;
				else
					howtoplay_Button->currentFrame = 0;

				if(settingsMenu->currentJoystickButton == 3)
					back_Button->currentFrame = 1;
				else
					back_Button->currentFrame = 0;
		}

		else if(stateInfo.gameState == STATE_CONTROLS)
		{
				  back_Button->currentFrame = 1;
		}

		else if(stateInfo.gameState == STATE_PAUSED)
		{
				if(pauseMenu->currentJoystickButton == 0)
					resume_Button->currentFrame = 1;
				else
					resume_Button->currentFrame = 0;
			
				if(pauseMenu->currentJoystickButton == 1)
					settings_Button->currentFrame = 1;
				else
					settings_Button->currentFrame = 0;
			
				if(pauseMenu->currentJoystickButton == 2)
					hub_Button->currentFrame = 1;
				else
					hub_Button->currentFrame = 0;
		}

		else if(stateInfo.gameState == STATE_CREDITS)
		{
				back_Button->currentFrame = 1;
		}

		else if(stateInfo.gameState == STATE_HOWTOPLAY)
		{
			back_Button->currentFrame = 1;
		}

		//menu state logic for joystick
		//if you press the selection (x) button
		if(sf::Joystick::isButtonPressed(0,0))
		{
			if(stateInfo.gameState == STATE_MAINMENU && !xbuttonDown)
			{
					xbuttonDown = true;
					menuClick->play(player->position);
					if(mainMenu->currentJoystickButton == 0)
					{
						this->stateInfo.gameState = STATE_CUTSCENE;
						this->stateInfo.subState = STATE_CUTSCENE1;
						introDialogue->play(player->position);
					}

					else if(mainMenu->currentJoystickButton == 1)
					{
						this->stateInfo.gameState = STATE_SETTINGS;
						stateInfo.menuState = STATE_MAIN_SETTINGS;
					}
				

					else if(mainMenu->currentJoystickButton == 2)
						this->stateInfo.gameState = STATE_CREDITS;

					else if(mainMenu->currentJoystickButton == 3)
						mainMenu->exitClick = true;			
			}

			else if(stateInfo.gameState == STATE_SETTINGS && !xbuttonDown)
			{
					xbuttonDown = true;
					menuClick->play(player->position);
					if(settingsMenu->currentJoystickButton == 0)
					{
						//put in code to switch audio off
						if(audio_Button->currentFrame == 0)
							audio_Button->currentFrame = 1;
					
						else if(audio_Button->currentFrame == 1)
							audio_Button->currentFrame = 0;
					
					}

					else if(settingsMenu->currentJoystickButton == 1)
					{
						stateInfo.gameState = STATE_CONTROLS;
						//controlsButtonDown = true;
					}

					else if(settingsMenu->currentJoystickButton == 2)
						stateInfo.gameState = STATE_HOWTOPLAY;

					//back button
					else if(settingsMenu->currentJoystickButton == 3)
					{
						if(stateInfo.menuState == STATE_MAIN_SETTINGS)
							stateInfo.gameState = STATE_MAINMENU;
					
						else if(stateInfo.menuState == STATE_PAUSE_SETTINGS)
							stateInfo.gameState = STATE_PAUSED;
					}
			}

			else if(stateInfo.gameState == STATE_CREDITS && !xbuttonDown)
			{
				menuClick->play(player->position);
					xbuttonDown = true;
					stateInfo.gameState = STATE_MAINMENU;
			}

			else if(stateInfo.gameState == STATE_CONTROLS && !xbuttonDown)
			{
				menuClick->play(player->position);
					xbuttonDown = true;
					stateInfo.gameState = STATE_SETTINGS;
			}

			else if(stateInfo.gameState == STATE_PAUSED && !xbuttonDown)
			{
				menuClick->play(player->position);
					xbuttonDown = true;

					if(stateInfo.subState != STATE_HUB)
					{
						if(pauseMenu->currentJoystickButton == 0)
							stateInfo.gameState = STATE_GAMEPLAY;

						else if(pauseMenu->currentJoystickButton == 1)
						{
							stateInfo.gameState = STATE_SETTINGS;
							stateInfo.menuState = STATE_PAUSE_SETTINGS;
						}

						//hub button, only during gameplay
						else if(pauseMenu->currentJoystickButton == 2)
						{
							/*stateInfo.gameState = STATE_LEVELSELECT;
							stateInfo.subState = STATE_HUB;*/
							if(!stateInfo.subState == STATE_HUB)
							{
							player->health = 0;
							this->exitLevel();
							}
						}
					}

					else if(stateInfo.subState == STATE_HUB)
					{
						if(pauseMenu->currentJoystickButton == 0)
							stateInfo.gameState = STATE_LEVELSELECT;

						else if(pauseMenu->currentJoystickButton == 1)
						{
							stateInfo.gameState = STATE_SETTINGS;
							stateInfo.menuState = STATE_PAUSE_SETTINGS;
						}
					}
			}

			else if(stateInfo.gameState == STATE_HOWTOPLAY && !xbuttonDown)
			{
				menuClick->play(player->position);
						xbuttonDown = true;
						stateInfo.gameState = STATE_SETTINGS;
			}
	}

	if(!sf::Joystick::isButtonPressed(0,0))
			xbuttonDown = false;
	}

	

	if(stateInfo.gameState == STATE_GAMEPLAY)
	{
		if( r != 0 || u != 0)
		{
			Vector temp = Vector(u,r,0);

			temp.normalize();

			player->directionVec = Vector(1,0,0);
			float angle = player->directionVec.angle(temp);
			if(temp.thisVector.y < 0)
			{
				angle *= (-1.f);
			}
			player->orientation = Quaternion(angle,false,false,true);
			missile.orientation = bullet.orientation = player->orientation;
			if(frameCount%4 == 0)
			{
				player->fireBullet(temp, bullet);
			}
			if(sf::Joystick::isButtonPressed(0,5))
			{
				if(stateInfo.gameState == STATE_GAMEPLAY && stateInfo.subState >= STATE_LEVEL3)
				{
					if(missiles)
					{
						if(!fired)
						{
							fired = true;
							player->fireMissiles(temp,missile);
							if(player->missiles.size() == 4)
							{
								player->missiles.erase(player->missiles.begin());
								player->missiles.erase(player->missiles.begin());
							}
						}/*else
						{
							fired = false;
						}*/
					}else if(waterGun)
					{
						player->sprayWater(temp,water);
						if(player->waterFuel > 0)
						{
							player->waterFuel -= 0.66666666666;
						}
						if(player->flamethrowerFuel < 101)
						{
							player->flamethrowerFuel += 0.055555555555;
						}
					}else if(flamethrower)
					{
						if(player->flamethrowerFuel > 0)
						{
							player->flamethrower(temp,fire);
							player->flamethrowerFuel -= 0.66666666666;
						}
						if(player->waterFuel < 101)
						{
							player->waterFuel += 0.1666666666666;
						}
					}
				}
			}else
			{
				fired = false;
				if(player->waterFuel < 101)
				{
					player->waterFuel += 0.3333333333333;
				}
				if(player->flamethrowerFuel < 101)
				{
					player->flamethrowerFuel += 0.11111111111;
				}
			}
		}else if((r == 0 && u == 0 ) && (x != 0 || y != 0))
		{
			Vector temp = Vector(x,y,0);

			temp.normalize();

			player->directionVec = Vector(1,0,0);
			float angle = player->directionVec.angle(temp);
			if(temp.thisVector.y < 0)
			{
				angle *= (-1.f);
			}
			player->orientation = Quaternion(angle,false,false,true);
		}
	}

	if(stateInfo.gameState == STATE_CUTSCENE || stateInfo.gameState == STATE_SCORING)
	{
			if(sf::Joystick::isButtonPressed(0,7) ^ sf::Joystick::isButtonPressed(0,1) ^ sf::Joystick::isButtonPressed(0,0))
			{
				if(!returnK)
				{
					returnK = true;
					/*if(stateInfo.gameState == STATE_MAINMENU)
					{
						stateInfo.gameState = STATE_CUTSCENE;
						stateInfo.subState = STATE_CUTSCENE1;
						if(stateInfo.gameState == STATE_CUTSCENE)
						{
							if(stateInfo.subState == STATE_CUTSCENE1)
							{
								stateInfo.gameState = STATE_LEVELSELECT;
								stateInfo.subState = STATE_HUB;
							}
						}
					}else */if(stateInfo.gameState == STATE_CUTSCENE)
					{
						if(stateInfo.subState == STATE_CUTSCENE1 || stateInfo.subState == STATE_CUTSCENE3)
						{
							stateInfo.gameState = STATE_LEVELSELECT;
							stateInfo.subState = STATE_HUB;
							introDialogue->pause();
							hubMusic->play(player->position);
						}
					}/*else if(stateInfo.gameState == STATE_LEVELSELECT)
					{
						if(sf::Joystick::isButtonPressed(0,9) && stateInfo.gameState!= STATE_GAMEPLAY)
						{
							player->position = Vector(0,0,0);
						}
					}*/else if(stateInfo.gameState == STATE_SCORING)
					{
						stateInfo.gameState = STATE_LEVELSELECT;
						stateInfo.subState = STATE_HUB;
					}
				}
			}else
			{
				returnK = false;
			}
	}
	
	if(stateInfo.gameState == STATE_MENU)
	{
		if(sf::Joystick::isButtonPressed(0,0))
		{
			stateInfo.gameState = STATE_GAMEPLAY;
			stateInfo.bossState = STATE_NO_BOSS;
			player->position = Vector(0,0,0);
			this->score = 0;
			score = 0;
			camZ = 70;
			loadLevel();
		}
		else if(sf::Joystick::isButtonPressed(0,1))
		{
			stateInfo.gameState = STATE_LEVELSELECT;
			stateInfo.subState = STATE_HUB;
			player->position = Vector(0,0,0);
			currentLevel = &levels[0];
			camZ = 70;
		}
	}
	else if(stateInfo.gameState == STATE_LEVELSELECT)
	{
		if(x != 0 || y != 0)
		{
			if(z < -1)
			{
				player->accelWeight = 0.2 + (0.4 * ( ( (-1)*z ) / 100 ));
			}else
			{
				player->accelWeight = 0.2;
			}
			Vector dirAcc = Vector(x,y,0);
			dirAcc.normalize();
			dirAcc.multiplyVector(player->accelWeight);
			player->setAcceleration(dirAcc);
			Vector temp = Vector(x,y,0);

			temp.normalize();

			player->directionVec = Vector(1,0,0);
			float angle = player->directionVec.angle(temp);
			if(temp.thisVector.y < 0)
			{
				angle *= (-1.f);
			}
			player->orientation = Quaternion(angle,false,false,true);
		}else
		{
			player->velocity = player->acceleration = Vector(0,0,0);
		}

		if(z>=80)
		{
			if(!l2ButtonDown)
			{
				//player->health = 100;
				player->directionVec = Vector(1,0,0);
				Vector temp_d = player->directionVec;
				//player->orientation.z = 0;
				player->orientation.normalize();
				temp_d.multiplyVector(player->orientation);
				temp_d.multiplyVector(5);
				//cout << player->directionVec.thisVector.x << " " << player->directionVec.thisVector.y << endl;
				Vector temp_p = player->position;
				temp_p.addVector(temp_d);
				bool willCollide = false;
				if(stateInfo.subState >= STATE_HUB && stateInfo.subState < STATE_LEVEL6)
				{
					for(int i=0; i<4; i++)
					{
						if(checkIfWillCollide(player_collider, &level_border[i], temp_p))
						{
							willCollide = true;
						}
					}
				}
				switch (stateInfo.subState)
				{
				case STATE_LEVEL1:
					for(int i=0; i<6; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level1[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				case STATE_LEVEL2:
					for(int i=0; i<6; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level2[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				case STATE_LEVEL3:
					for(int i=0; i<8; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level3[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				case STATE_LEVEL5:
					for(int i=0; i<14; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level5[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				}
				if(!willCollide)
				{
					player->position = temp_p;
				}
				l2ButtonDown = true;
			}
		}
		else
		{
			l2ButtonDown = false;
		}

		if(sf::Joystick::isButtonPressed(0,6))
		{
			if(!switched)
			{
				if(perspective<2)
				{
					perspective++;
				}
				else
				{
					perspective=0;
				}
				switched=true;
			}
		}
		else
		{
			switched=false;
		}
		if(sf::Joystick::isButtonPressed(0,7))
		{
			if(!pressed)
			{
				stateInfo.gameState = STATE_PAUSED;
				pressed=true;
			}
		}
		else
		{
			pressed=false;
		}
	}

	else if(stateInfo.gameState == STATE_GAMEPLAY)
	{
		if(x != 0 || y != 0)
		{
			/*if(stateInfo.subState != STATE_LEVEL2)
			{*/
			if(z < -1 && player->boostFuel > 0)
			{
				
				if(!playerSpeedUp)
				{
					player->accelWeight = 0.2 + (0.4 * ( ( (-1)*z ) / 100 ));
				}else
				{
					player->accelWeight = 0.6 + (0.6 * ( ( (-1)*z ) / 100 ));
				}
				player->boostFuel -= 0.33333333 * ( ( (-1)*z ) / 100 );
			}else
			{
				if(player->boostFuel < 101)
				{
					player->boostFuel += 0.11111111;
					if(player->boostFuel > 100)
					{
						player->boostFuel = 100 ;
					}
				}
				if(!playerSpeedUp)
				{
					player->accelWeight = 0.2;
				}else
				{
					player->accelWeight = 0.6; 
				}
			}
			/*}
			else
			{
				if(z < -1 && player->boostFuel > 0)
				{
				
					if(!playerSpeedUp)
					{
						player->accelWeight = 0.05 + (0.4 * ( ( (-1)*z ) / 100 ));
					}else
					{
						player->accelWeight = 0.3 + (0.6 * ( ( (-1)*z ) / 100 ));
					}
					player->boostFuel -= 0.22222222 * ( ( (-1)*z ) / 100 );
				}else
				{
					if(player->boostFuel < 101)
					{
						player->boostFuel += 0.11111111;
						if(player->boostFuel > 100)
						{
							player->boostFuel = 100 ;
						}
					}
					if(!playerSpeedUp)
					{
						player->accelWeight = 0.05;
					}else
					{
						player->accelWeight = 0.3; 
					}
				}
			}*/
			Vector dirAcc = Vector(x,y,0);
			dirAcc.normalize();
			dirAcc.multiplyVector(player->accelWeight);
			player->setAcceleration(dirAcc);
		}else
		{
			player->velocity = player->acceleration = Vector(0,0,0);
			if(player->boostFuel < 101)
			{
				player->boostFuel += 0.11111111;
			}
		}

		if(z>=80)
		{
			if(!l2ButtonDown)
			{
				//player->health = 100;
				player->directionVec = Vector(1,0,0);
				Vector temp_d = player->directionVec;
				//player->orientation.z = 0;
				player->orientation.normalize();
				temp_d.multiplyVector(player->orientation);
				temp_d.multiplyVector(5);
				//cout << player->directionVec.thisVector.x << " " << player->directionVec.thisVector.y << endl;
				Vector temp_p = player->position;
				temp_p.addVector(temp_d);
				bool willCollide = false;
				if(stateInfo.subState >= STATE_HUB && stateInfo.subState < STATE_LEVEL6)
				{
					for(int i=0; i<4; i++)
					{
						if(checkIfWillCollide(player_collider, &level_border[i], temp_p))
						{
							willCollide = true;
						}
					}
				}
				switch (stateInfo.subState)
				{
				case STATE_LEVEL1:
					for(int i=0; i<6; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level1[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				case STATE_LEVEL2:
					for(int i=0; i<6; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level2[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				case STATE_LEVEL3:
					for(int i=0; i<8; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level3[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				case STATE_LEVEL5:
					for(int i=0; i<14; i++)
					{
						if(checkIfWillCollide(player_collider, &walls_level5[i], temp_p))
						{
							willCollide = true;
						}
					}
					break;
				}
				if(!willCollide)
				{
					player->position = temp_p;
				}
				l2ButtonDown = true;
			}
		}
		else
		{
			l2ButtonDown = false;
		}

		if(sf::Joystick::isButtonPressed(0,6))
		{
			if(!switched)
			{
				if(perspective<2)
				{
					perspective++;
				}
				else
				{
					perspective=0;
				}
				switched=true;
			}
		}
		else
		{
			switched=false;
		}

		if(sf::Joystick::isButtonPressed(0,7))
		{
			if(!pressed)
			{
				stateInfo.gameState = STATE_PAUSED;
				pressed=true;
			}
		}
		else
		{
			pressed=false;
		}

		if(sf::Joystick::isButtonPressed(0,4))
		{
			if ((player->powerups.size() > 0) && !selected)
			{
				bool found = false;
				for (int i=0; i<player->powerups.size(); i++)
				{
					if (player->powerups[i] > currentID)
					{
						currentID = player->powerups[i];
						i = player->powerups.size();
						found = true;
						selected = true;
					}
				}
				if (!found)
				{
					currentID = player->powerups[0];
					selected = true;
				}
			}
		}
		else
		{
			selected = false;
		}

		if(stateInfo.subState == STATE_LEVEL3)
		{
			missiles = true;
			flamethrower = false;
			waterGun = false;
		}
		if(stateInfo.subState == STATE_LEVEL4)
		{
			if(sf::Joystick::isButtonPressed(0,3))
			{
				missiles = true;
				flamethrower = false;
				waterGun = false;
			}else if(sf::Joystick::isButtonPressed(0,2))
			{
				missiles = false;
				flamethrower = true;
				waterGun = false;
			}
		}else if(stateInfo.subState == STATE_LEVEL5)
		{
			if(sf::Joystick::isButtonPressed(0,3))
			{
				missiles = true;
				flamethrower = false;
				waterGun = false;
			}else if(sf::Joystick::isButtonPressed(0,2))
			{
				missiles = false;
				flamethrower = true;
				waterGun = false;
			}else if(sf::Joystick::isButtonPressed(0,1))
			{
				missiles = false;
				flamethrower = false;
				waterGun = true;
			}
		}
	}

	else if(stateInfo.gameState == STATE_PAUSED)
	{
		if(sf::Joystick::isButtonPressed(0,7))
		{
			if(!pressed)
			{
				stateInfo.gameState = STATE_GAMEPLAY;
				pressed=true;
			}
		}
		else
		{
			pressed=false;
		}
	}

	if((sf::Joystick::isButtonPressed(0,0) ^ sf::Joystick::isButtonPressed(0,9)) && stateInfo.gameState == STATE_GAMEPLAY)
	{
		if(!middleClicked)
		{
			middleClicked = true;
			if(player->powerups.size() > 0)
			{
				int imin=0;
				int imax=player->powerups.size()-1;
				int imid=0;
				bool found = false;
				while (imax >= imin)
				{
					imid = floor((imin+imax)/2.0);
 
					if (player->powerups[imid] < currentID)
					{
						imin = imid + 1;
					}
					else if (player->powerups[imid] > currentID)
					{
						imax = imid - 1;
					}
					else
					{
						found = true;
						break;
					}
				}
				if (found)
				{
					player->powerups.erase(player->powerups.begin()+imid);
					switch(currentID)
					{
					case 1:
						if(player->bombs.size() == 0 && !gravityBomb)
						{
							Vector temp = player->position;
							player->bomb(temp,bomb);
						}
						break;
					case 2:
						player->shieldActive = true;
						player->shield = 500;
						break;
					case 3:
						freezeEnemies = true;
						break;
					case 4:
						if(playerSpeedUp)
						{
							speedUpTime = 180;
						}
						playerSpeedUp = true;
						break;
					case 5:
						if(slowDown)
						{
							slowDownTime = 180;
							slowDown_num+=2;
							slowDownTime_begin->play(player->position);
						}else if(slowDown ==false)
						{
							slowDown = true;
							slowDownTime_begin->play(player->position);
						}

						if(enemies.size() > 0)
						{
							for(int i = 0; i <enemies.size();i++)
							{
								enemies[i]->max_speed /=2;
							}
						}
						break;
					}
				}
				
				if (player->powerups.size() > 0)
				{
					int imin2=0;
					int imax2=player->powerups.size()-1;
					int imid2=0;
					bool found2 = false;
					while (imax2 >= imin2)
					{
						imid2 = floor((imin2+imax2)/2.0);
 
						if (player->powerups[imid2] < currentID)
						{
							imin2 = imid2 + 1;
						}
						else if (player->powerups[imid2] > currentID)
						{
							imax2 = imid2 - 1;
						}
						else
						{
							found2 = true;
							break;
						}
					}
					if (!found2)
					{
						if (!selected)
						{
							bool found3 = false;
							for (int i=player->powerups.size()-1; i>-1; i--)
							{
								if (player->powerups[i] < currentID)
								{
									currentID = player->powerups[i];
									i = 0;
									found3 = true;
									selected = true;
								}
							}
							if (!found3)
							{
								currentID = player->powerups[player->powerups.size()-1];
								selected = true;
							}
						}
					}
				}
			}
		}
	}else
	{
		middleClicked = false;
	}
	if(stateInfo.gameState == STATE_GAMEPLAY || stateInfo.gameState == STATE_MENU || stateInfo.gameState == STATE_LEVELSELECT)
	{
		if(povx == 100)
		{
			if(camZ < 150)
			{
				camZ++;
			}
			float scale = 0.5 + ((camZ/300.0));
			for(int i = 0; i < powerups.size(); i++)
			{
				powerups[i]->setScale(scale,scale,scale);
			}
			for(int i = 0; i < 5; i++)
			{
				powerups_init[i]->setScale(scale,scale,scale);
			}
		}
		if(povy == 100)
		{
			if(camZ > 30)
			{
				camZ--;
			}
			float scale = 0.5 + ((camZ/300.0));
			for(int i = 0; i < powerups.size(); i++)
			{
				powerups[i]->setScale(scale,scale,scale);
			}
			for(int i = 0; i < 5; i++)
			{
				powerups_init[i]->setScale(scale,scale,scale);
			}
		}

	}
	//sf::Joystick::update();
}

/*
 * mouseMoved(x,y)
 * - this occurs only when the mouse is pressed down
 *   and the mouse has moved.  you are given the x,y locations
 *   in window coordinates (from the top left corner) and thus 
 *   must be converted to screen coordinates using the screen to window pixels ratio
 *   and the y must be flipped to make the bottom left corner the origin.
 */
void Game::mouseMoved(int x, int y)
{
	/* convert from window to screen pixel coordinates */

}

void Game::mouseHover(int x, int y)
{
	/* convert from window to screen pixel coordinates */

}