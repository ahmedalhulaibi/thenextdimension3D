#include "Game.h"
using namespace std;


/* update()
  - this function is essentially the game loop
    it gets called often and as such you
	don't actually need a "loop" to define the game
	it happens behind the scenes
  - think of this function as one iteration of the game loop
  - if you need to update physics calculations, sprite animation info,
    or sound etc, it goes in here
*/
void Game::update()
{	

	if(this->stateInfo.gameState == STATE_GAMEPLAY)
	{
		//cout << player->acceleration.thisVector.x << " " << player->acceleration.thisVector.y << endl;

		if (stateInfo.subState >= STATE_LEVEL1 && stateInfo.subState < STATE_LEVEL6)
		{
			int random = rand()%stateInfo.subState+1;
			if(random == 1)
			{
				for(int s=0; s<spawners.size(); s++)
				{
					if(spawners[s]->health>0)
					{
						if(spawners[s]->update(enemies.size()))
						{
							enemies.push_back(new EnemyBase(*enemy1_base));
							enemies.back()->position = spawners[s]->position;
							enemies.back()->setSeekTarget(player);
							spheres.push_back(new EnemyBase(*enemy1_collider));
							spheres.back()->position = enemies.back()->position;
							enemies.back()->state = SEEK;
							enemies.back()->substate = SEEK_PLAYER;
						}
					}
				}
			}
			else if(random == 2)
			{
				for(int s=0; s<spawners.size(); s++)
				{
					if(spawners[s]->health>0)
					{
						if(spawners[s]->update(enemies.size()))
						{
							enemies.push_back(new EnemyBase(*enemy2_base));
							enemies.back()->position = spawners[s]->position;
							enemies.back()->setSeekTarget(player);
							spheres.push_back(new EnemyBase(*enemy2_collider));
							spheres.back()->position = enemies.back()->position;
							enemies.back()->state = SEEK;
							enemies.back()->substate = SEEK_PLAYER;
						}
					}
				}
			}
			else if(random == 3)
			{
				for(int s=0; s<spawners.size(); s++)
				{
					if(spawners[s]->health>0)
					{
						if(spawners[s]->update(enemies.size()))
						{
							enemies.push_back(new EnemyBase(*enemy3_base));
							enemies.back()->position = spawners[s]->position;
							enemies.back()->setSeekTarget(player);
							spheres.push_back(new EnemyBase(*enemy3_collider));
							spheres.back()->position = enemies.back()->position;
							enemies.back()->state = SEEK;
							enemies.back()->substate = SEEK_PLAYER;
						}
					}
				}
			}
			else if(random == 4)
			{
				for(int s=0; s<spawners.size(); s++)
				{
					if(spawners[s]->health>0)
					{
						if(spawners[s]->update(enemies.size()))
						{
							enemies.push_back(new EnemyBase(*enemy4_base));
							enemies.back()->position = spawners[s]->position;
							enemies.back()->setSeekTarget(player);
							spheres.push_back(new EnemyBase(*enemy4_collider));
							spheres.back()->position = enemies.back()->position;
							enemies.back()->state = SEEK;
							enemies.back()->substate = SEEK_PLAYER;
						}
					}
				}
			}
			else
			{
				for(int s=0; s<spawners.size(); s++)
				{
					if(spawners[s]->health>0)
					{
						if(spawners[s]->update(enemies.size()))
						{
							enemies.push_back(new EnemyBase(*enemy5_base));
							enemies.back()->position = spawners[s]->position;
							enemies.back()->setSeekTarget(player);
							spheres.push_back(new EnemyBase(*enemy5_collider));
							spheres.back()->position = enemies.back()->position;
							enemies.back()->state = SEEK;
							enemies.back()->substate = SEEK_PLAYER;
						}
					}
				}
			}

			for(int i=0; i<4; i++)
			{
				Vector temp = player->position.subVector(level_border[i].position);
				if(abs(temp.thisVector.x)<450 && abs(temp.thisVector.y)<450)
				{
					if(checkBoxCollision(player_collider, &level_border[i])/* && !pushed*/)
					{
						Vector temp_f;
						switch(checkBoxQuadrant(player_collider, &level_border[i]))
						{
						case 0:
							temp_f = Vector(500,500,0);
							break;
						case 1:
							temp_f = Vector(500,-500,0);
							break;
						case 2:
							temp_f = Vector(-500,500,0);
							break;
						case 3:
							temp_f = Vector(-500,-500,0);
							break;
						}
						player->acceleration.addVector(temp_f);
						//player->acceleration.multiplyVector(-30);
						/*pushed = true;*/
					}
					/*else if(pushed)
					{
						pushed = false;
					}*/
					if(player->bullets.size() > 0)
					{
						for(int j=0; j<player->bullets.size(); j++)
						{
							if(player->bullets[j]->lifetime > 0)
							{
								if(checkBoxCollision(player->bullets[j], &level_border[i]))
								{
									player->bullets[j]->lifetime = 0;
								}
							}
						}
					}
				}
			}
		}
		if (stateInfo.bossState == STATE_NO_BOSS)
		{
			if (stateInfo.subState == STATE_LEVEL1)
			{
				//cout << player->position.thisVector.x << " " << player->position.thisVector.y << endl;
				for(int i=0; i<6; i++)
				{
					Vector temp = player->position.subVector(walls_level1[i].position);
					if(abs(temp.thisVector.x)<100 && abs(temp.thisVector.y)<100)
					{
						if(checkBoxCollision(player_collider, &walls_level1[i])/* && !pushed*/)
						{
							Vector temp_f;
							switch(checkBoxQuadrant(player_collider, &walls_level1[i]))
							{
							case 0:
								temp_f = Vector(1000,1000,0);
								break;
							case 1:
								temp_f = Vector(1000,-1000,0);
								break;
							case 2:
								temp_f = Vector(-1000,1000,0);
								break;
							case 3:
								temp_f = Vector(-1000,-1000,0);
								break;
							}
							player->acceleration.addVector(temp_f);
							//player->acceleration.multiplyVector(-30);
							/*pushed = true;*/
						}
						/*else if(pushed)
						{
							pushed = false;
						}*/
						if(player->bullets.size() > 0)
						{
							for(int j=0; j<player->bullets.size(); j++)
							{
								if(player->bullets[j]->lifetime > 0)
								{
									if(checkBoxCollision(player->bullets[j], &walls_level1[i]))
									{
										player->bullets[j]->lifetime = 0;
									}
								}
							}
						}
					}
				}
			}
			else if (stateInfo.subState == STATE_LEVEL2)
			{
				for(int i=0; i<6; i++)
				{
					Vector temp = player->position.subVector(walls_level2[i].position);
					if(abs(temp.thisVector.x)<100 && abs(temp.thisVector.y)<100)
					{
						if(checkBoxCollision(player_collider, &walls_level2[i])/* && !pushed*/)
						{
							Vector temp_f;
							switch(checkBoxQuadrant(player_collider, &walls_level2[i]))
							{
							case 0:
								temp_f = Vector(1000,1000,0);
								break;
							case 1:
								temp_f = Vector(1000,-1000,0);
								break;
							case 2:
								temp_f = Vector(-1000,1000,0);
								break;
							case 3:
								temp_f = Vector(-1000,-1000,0);
								break;
							}
							player->acceleration.addVector(temp_f);
							//player->acceleration.multiplyVector(-30);
							/*pushed = true;*/
						}
						/*else if(pushed)
						{
							pushed = false;
						}*/
						if(player->bullets.size() > 0)
						{
							for(int j=0; j<player->bullets.size(); j++)
							{
								if(player->bullets[j]->lifetime > 0)
								{
									if(checkBoxCollision(player->bullets[j], &walls_level2[i]))
									{
										player->bullets[j]->lifetime = 0;
									}
								}
							}
						}
					}
				}
			}
			else if (stateInfo.subState == STATE_LEVEL3)
			{
				for(int i=0; i<8; i++)
				{
					Vector temp = player->position.subVector(walls_level3[i].position);
					if(abs(temp.thisVector.x)<100 && abs(temp.thisVector.y)<100)
					{
						if(checkBoxCollision(player_collider, &walls_level3[i])/* && !pushed*/)
						{
							Vector temp_f;
							switch(checkBoxQuadrant(player_collider, &walls_level3[i]))
							{
							case 0:
								temp_f = Vector(1000,1000,0);
								break;
							case 1:
								temp_f = Vector(1000,-1000,0);
								break;
							case 2:
								temp_f = Vector(-1000,1000,0);
								break;
							case 3:
								temp_f = Vector(-1000,-1000,0);
								break;
							}
							player->acceleration.addVector(temp_f);
							//player->acceleration.multiplyVector(-30);
							/*pushed = true;*/
						}
						/*else if(pushed)
						{
							pushed = false;
						}*/
						if(player->bullets.size() > 0)
						{
							for(int j=0; j<player->bullets.size(); j++)
							{
								if(player->bullets[j]->lifetime > 0)
								{
									if(checkBoxCollision(player->bullets[j], &walls_level3[i]))
									{
										player->bullets[j]->lifetime = 0;
									}
								}
							}
						}
					}
				}
			}
			else if (stateInfo.subState == STATE_LEVEL5)
			{
				for(int i=0; i<14; i++)
				{
					Vector temp = player->position.subVector(walls_level5[i].position);
					if(abs(temp.thisVector.x)<100 && abs(temp.thisVector.y)<100)
					{
						if(checkBoxCollision(player_collider, &walls_level5[i])/* && !pushed*/)
						{
							Vector temp_f;
							switch(checkBoxQuadrant(player_collider, &walls_level5[i]))
							{
							case 0:
								temp_f = Vector(1000,1000,0);
								break;
							case 1:
								temp_f = Vector(1000,-1000,0);
								break;
							case 2:
								temp_f = Vector(-1000,1000,0);
								break;
							case 3:
								temp_f = Vector(-1000,-1000,0);
								break;
							}
							player->acceleration.addVector(temp_f);
							//player->acceleration.multiplyVector(-30);
							/*pushed = true;*/
						}
						/*else if(pushed)
						{
							pushed = false;
						}*/
						if(player->bullets.size() > 0)
						{
							for(int j=0; j<player->bullets.size(); j++)
							{
								if(player->bullets[j]->lifetime > 0)
								{
									if(checkBoxCollision(player->bullets[j], &walls_level5[i]))
									{
										player->bullets[j]->lifetime = 0;
									}
								}
							}
						}
					}
				}
			}
		}
		if(player->health <= 0)
		{
			exitLevel();
		}
		trail.push_back(ParticlePoint(0,0.5,1.0,1.0,1,Vector(player_lastPos),Vector(0,0,0),Vector(0,0,0),30,60));
		player_lastPos = player->position;
		trail.push_back(ParticlePoint(0,0.5,1.0,1.0,1,Vector(player_lastPos),Vector(0,0,0),Vector(0,0,0),30,60));
		player->update(this->elapsedTime);
		player_collider->position = player->position;
		player_collider->orientation = player->orientation;
		pause_screen.position = player->position;
		//if(!(player_lastPos == player->position))
		//{
			camPos = Vector(player_lastPos.X_Y_Z[0],player_lastPos.X_Y_Z[1],player->position.X_Y_Z[2]+camZ);
		//}
		camPos.addVector(camSpring.update(Vector(player->position),Vector(camPos)));
		if(asteroids.size() > 0)
		{
			for (int i = 0; i<asteroids.size(); i++)
			{
				asteroids[i]->update(0.2);
			}
			checkAsteroidCollision();
		}

		if(stateInfo.bossState == STATE_NO_BOSS)
		{
			if(freezeEnemies)
			{
				this->freezeTime--;
				if(freezeTime<=0)
				{
					freezeEnemies = false;
					freezeTime = 180;
				}
			}else
			{
				if(enemies.size() > 0)
				{
					for(int i = 0; i<enemies.size(); i++)
					{
						enemies[i]->update(this->elapsedTime);
						spheres[i]->position = enemies[i]->position;
						spheres[i]->orientation = enemies[i]->orientation;
					}
				}
			}

			if(slowDown)
			{
				slowDownTime--;
				if(slowDownTime <= 0)
				{
					if(enemies.size() >0)
					{
						for(int i = 0; i<enemies.size(); i++)
						{
							enemies[i]->max_speed*=slowDown_num;
						}
					}
					slowDownTime=180;
					slowDown = false;
					slowDown_num = 2;
					slowDownTime_end->play(player->position);
				}
			
			}
			if(gravityBomb)
			{
				gravityBombTime--;
				if(gravityBombTime <= 0)
				{
					gravityBombTime = 360;
					gravityBomb = false;
				}
			}
			if(playerSpeedUp)
			{
				speedUpTime--;
				if(speedUpTime<=0)
				{
					speedUpTime = 180;
					playerSpeedUp = false;
				}
			}
			if(healthDrops.size())
			{
				for(int i = 0; i < healthDrops.size(); i++)
				{
					healthDrops[i].seek(player->position,this->elapsedTime);
				}
			}
			checkEnemyCollision();
		}else if(stateInfo.bossState != STATE_NO_BOSS)
		{

			if(healthDrops.size())
			{
				for(int i = 0; i < healthDrops.size(); i++)
				{
					healthDrops[i].seek(player->position,this->elapsedTime);
				}
			}
			this->updateBosses();
		}
		checkPlayerCollision();
		checkBulletCollision();
		checkPowerupCollision();
		checkSpawnerCollision();
		/*checkHealthDrops();
		checkExplosions();*/

		if(invincible)
		{
			if (invi_frames>0)
			{
				invi_frames--;
			}
			else
			{
				invincible=false;
				invi_frames=30;
			}
		}
		
			switch(stateInfo.subState)
			{
			case STATE_LEVEL1:
				if(spawners.size() <= 0)
				{
					if(stateInfo.bossState == STATE_NO_BOSS)
					{
						finalBoss_dialogue->play(player->position);
					}
					enemies.clear();
					stateInfo.bossState = STATE_BOSS1;
					gameMusic->pause();
					
				}
				if(frameCount%600 == 0 && spawners.size()>0)
				{
					/*if(enemies.size() < 2)
						reloadEnemies();*/
				}
				break;
			case STATE_LEVEL2:
				if(spawners.size() <= 0)
				{
					
					if(stateInfo.bossState == STATE_NO_BOSS)
					{
						finalBoss_dialogue->play(player->position);
					}
					enemies.clear();
					stateInfo.bossState = STATE_BOSS2;
					gameMusic->pause();
				}
				if(frameCount%600 == 0 && spawners.size()>0)
				{
					/*if(enemies.size() < 4)
						reloadEnemies();*/
				}
				break;
			case STATE_LEVEL3:
				if(spawners.size() <= 0)
				{
					
					if(stateInfo.bossState == STATE_NO_BOSS)
					{
						finalBoss_dialogue->play(player->position);
					}
					enemies.clear();
					stateInfo.bossState = STATE_BOSS3;
					
					gameMusic->pause();
				}
				if(frameCount%600 == 0 && spawners.size()>0)
				{
					/*if(enemies.size() < 6)
						reloadEnemies();*/
				}
				break;
			case STATE_LEVEL4:
				if(spawners.size() <= 0)
				{
					
					if(stateInfo.bossState == STATE_NO_BOSS)
					{
						finalBoss_dialogue->play(player->position);
					}
					enemies.clear();
					stateInfo.bossState = STATE_BOSS4;
					gameMusic->pause();
					

				}
				if(frameCount%1200 == 0 && spawners.size()>0)
				{
					/*if(enemies.size() < 8)
						reloadEnemies();*/
				}
				break;
			case STATE_LEVEL5:
				if(spawners.size() <= 0)
				{
					
					if(stateInfo.bossState == STATE_NO_BOSS)
					{
						finalBoss_dialogue->play(player->position);
					}
					enemies.clear();
					stateInfo.bossState = STATE_BOSS5;
					
					gameMusic->pause();
				}
				if(frameCount%1200 == 0 && spawners.size()>0)
				{
					/*if(enemies.size() < 10)
					{
						reloadEnemies();
					}*/
				}
				break;
			}

		frameCount++;
	}

	else if (stateInfo.gameState == STATE_LEVELSELECT)
	{
		FMOD_BOOL isPlaying;
		FMOD_Channel_GetPaused(introDialogue->channel,&isPlaying);
		if(isPlaying)
		{
			FMOD_Channel_GetPaused(hubMusic->channel,&isPlaying);
			if(isPlaying)
			{
				hubMusic->play(player->position);
			}
		}
		//cout << player->acceleration.thisVector.x << " " << player->acceleration.thisVector.y << endl;		
		for(int j=0; j<4; j++)
		{
			Vector temp = player->position.subVector(level_border[j].position);
			if(abs(temp.thisVector.x)<450 && abs(temp.thisVector.y)<450)
			{
				if(checkBoxCollision(player_collider, &level_border[j])/* && !pushed*/)
				{
					Vector temp_f;
					switch(checkBoxQuadrant(player_collider, &level_border[j]))
					{
					case 0:
						temp_f = Vector(1000,1000,0);
						break;
					case 1:
						temp_f = Vector(1000,-1000,0);
						break;
					case 2:
						temp_f = Vector(-1000,1000,0);
						break;
					case 3:
						temp_f = Vector(-1000,-1000,0);
						break;
					}
					player->acceleration.addVector(temp_f);
					//player->acceleration.multiplyVector(-30);
					/*pushed = true;*/
				}
				/*else if(pushed)
				{
					pushed = false;
				}*/
			}
		}
		trail.push_back(ParticlePoint(0,0.5,1.0,1.0,1,Vector(player_lastPos),Vector(0,0,0),Vector(0,0,0),30,60));
		player_lastPos = player->position;
		trail.push_back(ParticlePoint(0,0.5,1.0,1.0,1,Vector(player_lastPos),Vector(0,0,0),Vector(0,0,0),30,60));
		player->update(this->elapsedTime);
		player_collider->position = player->position;
		player_collider->orientation = player->orientation;
		select_screen.position = player->position;
		//camSpring->update();
		//camPos = Vector(player->position.X_Y_Z[0],player->position.X_Y_Z[1],player->position.X_Y_Z[2]+camZ);
		//if(!(player_lastPos == player->position))
		//{
			camPos = Vector(player_lastPos.X_Y_Z[0],player_lastPos.X_Y_Z[1],player->position.X_Y_Z[2]+camZ);
		//}
		camPos.addVector(camSpring.update(Vector(player->position),Vector(camPos)));
		portals[0]->position = Vector(40,-30,0);
		portals[1]->position = Vector(-40,-30,0);
		portals[2]->position = Vector(75,10,0);
		portals[3]->position = Vector(-75,10,0);
		portals[4]->position = Vector(0,35,0);

		if(this->checkSphericalCollision(player_collider, portals[0]))
		{
			camPos = player->position = Vector(0,0,0);
			camZ = 200;
			stateInfo.gameState = STATE_MENU;
			stateInfo.subState = 1;
			currentLevel = &levels[1];
			stateInfo.bossState = STATE_NO_BOSS;
		}

		for (int i = 1; i<5; i++)
		{
			if(levelsCleared[i-1])
			{
				if(this->checkSphericalCollision(player_collider, portals[i]))
				{
					camPos = player->position = Vector(0,0,0);
					camZ = 200;
					stateInfo.gameState = STATE_MENU;
					stateInfo.subState = i+1;
					currentLevel = &levels[i+1];
					stateInfo.bossState = STATE_NO_BOSS;
				}
			}
		}
	}
	
}