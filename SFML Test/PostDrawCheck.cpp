#include "Game.h"
using namespace std;

void Game::checkBullets()
{
	if(player->bullets.size() > 0)
	{
		for(int i = player->bullets.size() - 1; i > -1;i--)
		{
			if(player->bullets[i]->position.X_Y_Z[0] > player->position.X_Y_Z[0]+500 || player->bullets[i]->position.X_Y_Z[0] < player->position.X_Y_Z[0]-500)
			{
				player->bullets[i]->lifetime = 0;
			}
			else if(player->bullets[i]->position.X_Y_Z[1] > player->position.X_Y_Z[1]+300 || player->bullets[i]->position.X_Y_Z[1] < player->position.X_Y_Z[1]-300)
			{
				player->bullets[i]->lifetime = 0;
			}
		}
		for(int i = player->bullets.size() - 1; i > -1;i--)
		{
			if(player->bullets[i]->lifetime <= 0)
			{
				player->bullets.erase(player->bullets.begin() + i);
			}
		}
	}
}

void Game::checkMissiles()
{
	if(player->missiles.size() > 0)
	{
		for(int i = player->missiles.size() - 1; i > -1;i--)
		{
			if(player->missiles[i]->position.X_Y_Z[0] > player->position.X_Y_Z[0]+50 || player->missiles[i]->position.X_Y_Z[0] < player->position.X_Y_Z[0]-50)
			{
				player->missiles[i]->lifetime = 0;
			}else if(player->missiles[i]->position.X_Y_Z[1] > player->position.X_Y_Z[1]+30 || player->missiles[i]->position.X_Y_Z[1] < player->position.X_Y_Z[1]-30)
			{
				player->missiles[i]->lifetime = 0;
			}
		}
		for(int i = player->missiles.size() - 1; i > -1;i--)
		{
			if(player->missiles[i]->lifetime <= 0)
			{
				player->missiles.erase(player->missiles.begin() + i);
			}
		}
	}
}

void Game::checkFire()
{
	if(player->fire.size() > 0)
	{
		for(int i = player->fire.size() - 1; i > -1;i--)
		{
			if(player->fire[i]->position.X_Y_Z[0] > player->position.X_Y_Z[0]+50 || player->fire[i]->position.X_Y_Z[0] < player->position.X_Y_Z[0]-50)
			{
				player->fire[i]->lifetime = 0;
			}else if(player->fire[i]->position.X_Y_Z[1] > player->position.X_Y_Z[1]+30 || player->fire[i]->position.X_Y_Z[1] < player->position.X_Y_Z[1]-30)
			{
				player->fire[i]->lifetime = 0;
			}
		}
		for(int i = player->fire.size() - 1; i > -1;i--)
		{
			if(player->fire[i]->lifetime <= 0)
			{
				player->fire.erase(player->fire.begin() + i);
			}
		}
	}
	if(player->fireP.size() > 0)
	{
		for(int i = player->fireP.size() - 1; i > -1;i--)
		{
			if(player->fireP[i]->lifetime <= 0)
			{
				player->fireP.erase(player->fireP.begin() + i);
			}
		}
	}
}

void Game::checkWater()
{
	if(player->water.size() > 0)
	{
		for(int i = player->water.size() - 1; i > -1;i--)
		{
			if(player->water[i]->position.X_Y_Z[0] > player->position.X_Y_Z[0]+50 || player->water[i]->position.X_Y_Z[0] < player->position.X_Y_Z[0]-50)
			{
				player->water[i]->lifetime = 0;
			}else if(player->water[i]->position.X_Y_Z[1] > player->position.X_Y_Z[1]+30 || player->water[i]->position.X_Y_Z[1] < player->position.X_Y_Z[1]-30)
			{
				player->water[i]->lifetime = 0;
			}
		}
		for(int i = player->water.size() - 1; i > -1;i--)
		{
			if(player->water[i]->lifetime <= 0)
			{
				player->water.erase(player->water.begin() + i);
			}
		}
	}
	if(player->waterP.size() > 0)
	{
		for(int i = player->waterP.size() - 1; i > -1;i--)
		{
			if(player->waterP[i]->lifetime <= 0)
			{
				player->waterP.erase(player->waterP.begin() + i);
			}
		}
	}
}

void Game::checkBombs()
{
	if(player->bombs.size() > 0)
	{
		if(player->bombs[0]->lifetime <=0)
		{
			gravityBombPortal->position = player->bombs[0]->position;
			gravityBomb = true;
			player->bombs.erase(player->bombs.begin());
		}
	}
}

void Game::checkEnemies()
{
	for(int i = 0; i <enemies.size(); i++)
	{
		//CHANGE THIS SHIT
		enemies[i]->position.thisVector.z = player->position.thisVector.z;
		enemies[i]->position.X_Y_Z[2] = player->position.X_Y_Z[2];
		spheres[i]->position = enemies[i]->position;
	}
	for(int i = enemies.size() - 1; i > -1;i--)
	{
		if(enemies[i]->health <= 0)
		{
		
			int appear = rand()%100+1;
			if (appear%20 == 0)
			{
				int id = rand()%5+1;
				for(int k=0; k<5; k++)
				{
					if(powerups_init[k]->ID == id)
					{
						powerups.push_back(new Powerup(*powerups_init[k]));
						powerups.back()->position = enemies[i]->position;
					}
				}
			}
			healthDrops.push_back(healthDrop(enemies[i]->position.addVec(Vector(0,0,rand()%6))));
			for(int offset = 1; offset < 20; offset++)
			{
				healthDrops.push_back( healthDrop(enemies[i]->position.addVec(Vector(offset,0,rand()%6))) );
				healthDrops.push_back( healthDrop(enemies[i]->position.addVec(Vector(offset,offset,rand()%6))) );
				healthDrops.push_back( healthDrop(enemies[i]->position.addVec(Vector(0,offset,rand()%6))) );
				healthDrops.push_back( healthDrop(enemies[i]->position.addVec(Vector(-offset,offset,rand()%6))) );
				healthDrops.push_back( healthDrop(enemies[i]->position.addVec(Vector(-offset,0,rand()%6))) );
				healthDrops.push_back( healthDrop(enemies[i]->position.addVec(Vector(-offset,-offset,rand()%6))) );
				healthDrops.push_back( healthDrop(enemies[i]->position.addVec(Vector(0,-offset,rand()%6))) );
			}
			if(explosions.size() < 10)
			{
				float rgb[3] = {(float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX,(float)rand()/(float)RAND_MAX};
				explosions.push_back ( Explosion(100,true,false,false,Vector(0,0.4,0),Vector(0,0,0),enemies[i]->position,rgb[0],rgb[1],rgb[2],1.0,5,30.0));
				explosions.push_back ( Explosion(100,false,true,false,Vector(0.4,0,0),Vector(0,0,0),enemies[i]->position,rgb[0],rgb[1],rgb[2],1.0,5,30.0));
				explosions.push_back ( Explosion(100,false,false,true,Vector(0,0.4,0),Vector(0,0,0),enemies[i]->position,rgb[0],rgb[1],rgb[2],1.0,5,30.0));
			}
			enemies[i]->explode->play(enemies[i]->position);
			enemies.erase(enemies.begin() + i);
			spheres.erase(spheres.begin() + i);
			//This is where we put enemies EnemyDeath Sound
			//sounds->playEnemyDeath();
		
		}else if(enemies[i]->position.X_Y_Z[0] > 2000 || enemies[i]->position.X_Y_Z[0] < -2000 || enemies[i]->position.X_Y_Z[1] > 2000 || enemies[i]->position.X_Y_Z[1] < -2000)
		{
			enemies[i]->explode->play(enemies[i]->position);
			enemies.erase(enemies.begin() + i);
			spheres.erase(spheres.begin() + i);
		}
	}
	if(!gravityBomb)
	{
		if(frameCount % 2 == 0)
		{
			for(int i = 0; i<enemies.size(); i++)
			{
				if(enemies[i]->state != SEEK && enemies[i]->substate != SEEK_PLAYER)
				{
					enemies[i]->state = SEEK;
					enemies[i]->substate = SEEK_PLAYER;
				}else if(enemies[i]->state == SEEK && enemies[i]->substate != SEEK_PLAYER)
				{
					enemies[i]->state = SEEK;
					enemies[i]->substate = SEEK_PLAYER;
				}
			}
		}
	}else
	{
		if(frameCount % 2 == 0)
		{
			for(int i = 0; i<enemies.size(); i++)
			{
				if(enemies[i]->state != SEEK || enemies[i]->substate != SEEK_POINT)
				{
					enemies[i]->setSeekTarget(gravityBombPortal->position);
					enemies[i]->state = SEEK;
					enemies[i]->substate = SEEK_POINT;
				}
			}
		}
	}
	if(!freezeEnemies)
	{
		for(int i = 0; i <enemies.size(); i++)
		{
			Vector temp = player->position.subVector(enemies[i]->position);
			temp.normalize();
			enemies[i]->directionVec = Vector(1,0,0);
			float angle = enemies[i]->directionVec.angle(temp);
			if(temp.X_Y_Z[1] < 0)
			 {
				 angle = angle * (-1.f);
			 }
			 enemies[i]->orientation = Quaternion(angle,false,false,true);
		}
	}
}

void Game::checkPlayer()
{
	if(player->position.thisVector.x >= 170)
	{
		player->position = Vector(0,0,0);
	}
	else if(player->position.thisVector.x < -170)
	{
		player->position = Vector(0,0,0);
	}
	if(player->position.thisVector.y > 170)
	{
		player->position = Vector(0,0,0);
	}
	else if(player->position.thisVector.y < -170)
	{
		player->position = Vector(0,0,0);
	}
	if(trail.size())
	{
		for(int i = trail.size() - 1; i > -1;i--)
		{
			if(trail[i].lifetime <= 0)
			{
				cout << " ";
				trail.erase(trail.begin() + i);
			}
		}

	}
}

void Game::checkPowerups()
{
	if (powerups.size() > 0)
	{
		for(int k = 0; k < powerups.size(); k++)
		{
			for(int i=0; i<powerups.size(); i++)
			{
				if(i != k)
				{
					if(!powerups[i]->alive && !powerups[k]->alive)
					{
						if(this->checkSphericalCollision(powerups[i],powerups[k]))
						{
							powerups[i]->position.addVector(Vector(2,2,0));
						}
					}
				}
			}
		}
		for(int i=powerups.size()-1; i>-1; i--)
		{
			if (!powerups[i]->alive)
			{
				powerups.erase(powerups.begin()+i);
			}
		}
	}
}

void Game::checkHealthDrops()
{
	if(healthDrops.size() > 0)
	{
		for(int i = healthDrops.size() - 1; i > -1 ; i--)
		{
			if((healthDrops[i].position.X_Y_Z[0]  > player->position.X_Y_Z[0] - 1) && (healthDrops[i].position.X_Y_Z[0]  < player->position.X_Y_Z[0] + 1))
			{
				if((healthDrops[i].position.X_Y_Z[1]  > player->position.X_Y_Z[1] - 1) && (healthDrops[i].position.X_Y_Z[1]  < player->position.X_Y_Z[1] + 1))
				{
					healthDrops.erase(healthDrops.begin() + i);
					if(player->health < 100)
					{
						player->health+= 0.015;
					}else if(player->health >= 100)
					{
						this->score++;
					}
				}
			}
		}
	}
	if(healthDrops.size() > 0)
	{
		for(int i = 0; i < healthDrops.size(); i++)
		{
			healthDrops[i].mass = 10;
			healthDrops[i].max_speed = 4;
		}
	}
}

//#pragma optimize( "", off )
void Game::checkExplosions()
{
	if(explosions.size() > 0)
	{
		for(int i = explosions.size() - 1; i > -1; i --)
		{
			if(explosions[i].dead)
			{
				for(unsigned int n = 0; n < explosions[i].p.size(); n++)
				{
 					healthDrops.push_back(healthDrop(explosions[i].p[n]->position));
				}
				explosions.erase(explosions.begin() + i);
			}

		}
	}
	if(wall_explosions.size())
	{
		for(int i = wall_explosions.size() - 1; i > -1 ; i--)
		{
			if(wall_explosions[i].dead)
			{
				wall_explosions.erase(wall_explosions.begin() + i);
			}
		}
	}
	if(healthDrops.size() > 0)
	{
		for(int i = 0; i < healthDrops.size(); i++)
		{
			healthDrops[i].mass = 10;
			healthDrops[i].max_speed = 4;
		}
	}
}

//#pragma optimize( "", on )

void Game::checkBossBullets()
{
	if(spaceBoss->particleBullet.size() > 0)
	{
		for(int i = spaceBoss->particleBullet.size() - 1; i > 0; i++)
		{
			if(spaceBoss->particleBullet[i]->lifetime <=0 || stateInfo.bossState == STATE_NO_BOSS)
			{
				cout << " ";
				spaceBoss->particleBullet.erase(spaceBoss->particleBullet.begin()+i);
				spaceBoss->Bullets.erase(spaceBoss->Bullets.begin()+i);
			}
		}
	}
	if(oceanBoss->particleBullet.size() > 0)
	{
		for(int i = oceanBoss->particleBullet.size() - 1; i > 0; i++)
		{
			if(oceanBoss->particleBullet[i]->lifetime <=0 || stateInfo.bossState == STATE_NO_BOSS)
			{
				cout << " ";
				oceanBoss->particleBullet.erase(oceanBoss->particleBullet.begin()+i);
				oceanBoss->Bullets.erase(oceanBoss->Bullets.begin()+i);
			}
		}
	}
	if(desertBoss->particleBullet.size() > 0)
	{
		for(int i = desertBoss->particleBullet.size() - 1; i > 0; i++)
		{
			if(desertBoss->particleBullet[i]->lifetime <=0 || stateInfo.bossState == STATE_NO_BOSS)
			{
				cout << " ";
				desertBoss->particleBullet.erase(desertBoss->particleBullet.begin()+i);
				desertBoss->Bullets.erase(desertBoss->Bullets.begin()+i);
			}
		}
	}
	if(tropicalBoss->particleBullet.size() > 0)
	{
		for(int i = tropicalBoss->particleBullet.size() - 1; i > 0; i++)
		{
			if(tropicalBoss->particleBullet[i]->lifetime <=0 || stateInfo.bossState == STATE_NO_BOSS)
			{
				cout << " ";
				tropicalBoss->particleBullet.erase(tropicalBoss->particleBullet.begin()+i);
				tropicalBoss->Bullets.erase(tropicalBoss->Bullets.begin()+i);
			}
		}
	}
	if(iceBoss->particleBullet.size() > 0)
	{
		for(int i = iceBoss->particleBullet.size() - 1; i > 0; i++)
		{
			if(iceBoss->particleBullet[i]->lifetime <=0 || stateInfo.bossState == STATE_NO_BOSS)
			{
				cout << " ";
				iceBoss->particleBullet.erase(iceBoss->particleBullet.begin()+i);
				iceBoss->Bullets.erase(iceBoss->Bullets.begin()+i);
			}
		}
	}
}

void Game::checkAsteroids()
{
	if (asteroids.size() > 0)
	{
		for (int i = asteroids.size()-1; i > -1; i--)
		{
			if(asteroids[i]->position.thisVector.x >= 150 || asteroids[i]->position.thisVector.x <= -150)
			{
				cout << " ";
				asteroids[i]->velocity.thisVector.x*=-1;
				asteroids[i]->velocity.X_Y_Z[0]*=-1;
			}
			if(asteroids[i]->position.thisVector.y >= 150 || asteroids[i]->position.thisVector.y <= -150)
			{
				cout << " ";
				asteroids[i]->velocity.thisVector.y*=-1;
				asteroids[i]->velocity.X_Y_Z[1]*=-1;
			}
			if (asteroids[i]->collided)
			{
				cout << " ";
				int appear = rand()%100+1;
				if (appear%20 == 0)
				{
					int id = rand()%5 + 1;
					for(int k=0; k<5; k++)
					{
						if(powerups_init[k]->ID == id)
						{
							powerups.push_back(new Powerup(*powerups_init[k]));
							powerups.back()->position = asteroids[i]->position;
						}
					}
				}
				asteroids.erase(asteroids.begin()+i);
			}
		}
	}
}

void Game::checkSpawners()
{
	for(int i=0; i<spawners.size(); i++)
	{
		if(spawners[i]->health <= 0)
		{
			cout << " ";
			spawners[i]->spawnerSound->pause();
			spawners.erase(spawners.begin()+i);
			score+=400;
		}
	}
}