#include "Game.h"
using namespace std;

bool Game::checkSphericalCollision(Model *sprite1, Model *sprite2)
{
	Vector distance = sprite1->position - sprite2->position;

	float squareDistance = distance.thisVector.x * distance.thisVector.x + distance.thisVector.y * distance.thisVector.y /*+ distance.thisVector.z * distance.thisVector.z*/;

	float squareMinDistance = (sprite1->radii[0] + sprite2->radii[0]) * (sprite1->radii[0] + sprite2->radii[0]) + (sprite1->radii[1] + sprite2->radii[1]) * (sprite1->radii[1] + sprite2->radii[1]) /*+ (sprite1->radii[2] + sprite2->radii[2]) * (sprite1->radii[2] + sprite2->radii[2])*/;

	/*float squareDistanceY = (distance.thisVector.y * distance.thisVector.y);

	float squareMinDistanceY = (sprite1->radii[1] + sprite2->radii[1]) * (sprite1->radii[1] + sprite2->radii[1]);

	float squareDistanceZ = (distance.thisVector.z * distance.thisVector.z);

	float squareMinDistanceZ = (sprite1->radii[2] + sprite2->radii[2]) * (sprite1->radii[2] + sprite2->radii[2]);*/

	if (squareDistance <= squareMinDistance)
	{
		/*if (squareDistanceY <= squareMinDistanceY)
		{
			if (squareDistanceZ <= squareMinDistanceZ)
			{
				return true;
			}
		}*/
		return true;
	}

	return false;
}

bool Game::checkSphericalCollision(Model *sprite1, EnemyBase *sprite2)
{
	Vector distance = sprite1->position - sprite2->position;

	float squareDistance = distance.thisVector.x * distance.thisVector.x + distance.thisVector.y * distance.thisVector.y /*+ distance.thisVector.z * distance.thisVector.z*/;

	float squareMinDistance = (sprite1->radii[0] + sprite2->radii[0]) * (sprite1->radii[0] + sprite2->radii[0]) + (sprite1->radii[1] + sprite2->radii[1]) * (sprite1->radii[1] + sprite2->radii[1]) /*+ (sprite1->radii[2] + sprite2->radii[2]) * (sprite1->radii[2] + sprite2->radii[2])*/;

	/*float squareDistanceY = (distance.thisVector.y * distance.thisVector.y);

	float squareMinDistanceY = (sprite1->radii[1] + sprite2->radii[1]) * (sprite1->radii[1] + sprite2->radii[1]);

	float squareDistanceZ = (distance.thisVector.z * distance.thisVector.z);

	float squareMinDistanceZ = (sprite1->radii[2] + sprite2->radii[2]) * (sprite1->radii[2] + sprite2->radii[2]);*/

	if (squareDistance <= squareMinDistance)
	{
		/*if (squareDistanceY <= squareMinDistanceY)
		{
			if (squareDistanceZ <= squareMinDistanceZ)
			{
				return true;
			}
		}*/
		return true;
	}

	return false;
}

bool Game::checkSphericalCollision(EnemyBase *sprite1, EnemyBase *sprite2)
{
	Vector distance = sprite1->position - sprite2->position;

	float squareDistance = distance.thisVector.x * distance.thisVector.x + distance.thisVector.y * distance.thisVector.y /*+ distance.thisVector.z * distance.thisVector.z*/;

	float squareMinDistance = (sprite1->radii[0] + sprite2->radii[0]) * (sprite1->radii[0] + sprite2->radii[0]) + (sprite1->radii[1] + sprite2->radii[1]) * (sprite1->radii[1] + sprite2->radii[1]) /*+ (sprite1->radii[2] + sprite2->radii[2]) * (sprite1->radii[2] + sprite2->radii[2])*/;

	/*float squareDistanceY = (distance.thisVector.y * distance.thisVector.y);

	float squareMinDistanceY = (sprite1->radii[1] + sprite2->radii[1]) * (sprite1->radii[1] + sprite2->radii[1]);

	float squareDistanceZ = (distance.thisVector.z * distance.thisVector.z);

	float squareMinDistanceZ = (sprite1->radii[2] + sprite2->radii[2]) * (sprite1->radii[2] + sprite2->radii[2]);*/

	if (squareDistance <= squareMinDistance)
	{
		/*if (squareDistanceY <= squareMinDistanceY)
		{
			if (squareDistanceZ <= squareMinDistanceZ)
			{
				return true;
			}
		}*/
		return true;
	}

	return false;
}

bool Game::checkBoxCollision(Model *sprite1, Model *sprite2)
{
	if ((sprite1->position.thisVector.x + sprite1->radii[0]) > (sprite2->position.thisVector.x - sprite2->radii[0]))
	{
		if ((sprite1->position.thisVector.x - sprite1->radii[0]) < (sprite2->position.thisVector.x + sprite2->radii[0]))
		{
			if ((sprite1->position.thisVector.y + sprite1->radii[1]) > (sprite2->position.thisVector.y - sprite2->radii[1]))
			{
				if ((sprite1->position.thisVector.y - sprite1->radii[1]) < (sprite2->position.thisVector.y + sprite2->radii[1]))
				{
						wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,30.0));
						wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.2,0.2,0.2),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,30.0));
						wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,30.0));
						//wall_explosions.push_back( Explosion(120,false,true,false,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,1));
						//wall_explosions.push_back( Explosion(120,true,false,false,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,1));
					if(wall_explosions.size() > 20)
					{
						wall_explosions.erase(wall_explosions.begin() + 1);
						wall_explosions.erase(wall_explosions.begin() + 1);
						wall_explosions.erase(wall_explosions.begin() + 1);
					}
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool Game::checkIfWillCollide(Model *sprite1, Model *sprite2, Vector position)
{
	if ((position.thisVector.x + sprite1->radii[0]) > (sprite2->position.thisVector.x - sprite2->radii[0]))
	{
		if ((position.thisVector.x - sprite1->radii[0]) < (sprite2->position.thisVector.x + sprite2->radii[0]))
		{
			if ((position.thisVector.y + sprite1->radii[1]) > (sprite2->position.thisVector.y - sprite2->radii[1]))
			{
				if ((position.thisVector.y - sprite1->radii[1]) < (sprite2->position.thisVector.y + sprite2->radii[1]))
				{
					//	wall_explosions.push_back( Explosion(120,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,30.0));
					//	wall_explosions.push_back( Explosion(120,false,false,true,Vector(0.2,0.2,0.2),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,30.0));
					//	wall_explosions.push_back( Explosion(120,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,30.0));
					//	//wall_explosions.push_back( Explosion(120,false,true,false,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,1));
					//	//wall_explosions.push_back( Explosion(120,true,false,false,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(sprite1->position),1,0.9,0,1,1,1));
					//if(wall_explosions.size() > 20)
					//{
					//	wall_explosions.erase(wall_explosions.begin() + 1);
					//	wall_explosions.erase(wall_explosions.begin() + 1);
					//	wall_explosions.erase(wall_explosions.begin() + 1);
					//}
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

int Game::checkBoxQuadrant(Model *sprite1, Model *sprite2)
{
	if (sprite1->position.thisVector.x > sprite2->position.thisVector.x)
	{
		if (sprite1->position.thisVector.y > sprite2->position.thisVector.y)
		{
			return 0;
		}
		else if (sprite1->position.thisVector.y < sprite2->position.thisVector.y)
		{
			return 1;
		}
	}
	else if (sprite1->position.thisVector.x < sprite2->position.thisVector.x)
	{
		if (sprite1->position.thisVector.y > sprite2->position.thisVector.y)
		{
			return 2;
		}
		else if (sprite1->position.thisVector.y < sprite2->position.thisVector.y)
		{
			return 3;
		}
	}
}

void Game::checkPlayerCollision()
{
	if(enemies.size() > 0)
	{
		for(int k = 0; k<enemies.size(); k++)
		{
			if(player->health>0)
			{
				
				{
					Vector temp = player->position.subVector(enemies[k]->position);
					if(abs(temp.thisVector.x)<50 && abs(temp.thisVector.y)<30)
					{
						if(this->checkSphericalCollision(player_collider, spheres[k]))
						{
							enemies[k]->position = enemies[k]->prevPos;
							enemies[k]->state = REPEL;
							enemies[k]->substate = REPEL_PLAYER;
							if(player->shieldActive)
							{
								player->shield-=10;
								if(player->shield <=0)
								{
									if (!invincible)
									{
										player->shieldActive = false;
										player->shield = 500;
										invincible=true;
									}
								}
							}else
							{
								if (!invincible)
								{
									player->health-=10;
									invincible=true;
								}
							}
							cout << "Hit!" << endl;
						}
					}
				}
			}
		}
	}
	if(stateInfo.bossState != STATE_NO_BOSS)
	{
		switch(stateInfo.bossState)
		{
		case 1:
			if(spaceBoss->Bullets.size() > 0)
			{
				for(int k = 0; k<spaceBoss->Bullets.size(); k++)
				{
					Vector temp = player->position.subVector(spaceBoss->Bullets[k]->position);
					if(abs(temp.thisVector.x)<50 && abs(temp.thisVector.y)<30)
					{
						if(spaceBoss->particleBullet[k]->lifetime >= 0)
						{
							if(this->checkSphericalCollision(player_collider, spaceBoss->Bullets[k]))
							{
								if(player->shieldActive)
								{
									player->shield-=2;
									if(player->shield <=0)
									{
										player->shieldActive = false;
										player->shield = 500;
										invincible=true;
									}
								}else
								{
									player->health-=1;
									invincible=true;
								}
							}
						}
					}
				}
			}
			if(spaceBoss->deltaT >= 1)
			{
				if(this->checkSphericalCollision(player,spaceBoss_collider))
				{
					if(player->shieldActive)
					{
						player->shield-=2;
						if(player->shield <=0)
						{
							player->shieldActive = false;
							player->shield = 500;
							invincible=true;
						}
					}else
					{
						player->health-=1;
						invincible=true;
					}
				}
			}
			break;
		case 2:
			if(oceanBoss->Bullets.size() > 0)
			{
				for(int k = 0; k<oceanBoss->Bullets.size(); k++)
				{
					Vector temp = player->position.subVector(oceanBoss->Bullets[k]->position);
					if(abs(temp.thisVector.x)<50 && abs(temp.thisVector.y)<30)
					{
						if(oceanBoss->particleBullet[k]->lifetime >= 0)
						{
							if(this->checkSphericalCollision(player_collider, oceanBoss->Bullets[k]))
							{
								if(player->shieldActive)
								{
									player->shield-=2;
									if(player->shield <=0)
									{
										player->shieldActive = false;
										player->shield = 500;
										invincible=true;
									}
								}else
								{
									player->health-=1;
									invincible=true;
								}
							}
						}
					}
				}
			}
			if(oceanBoss->deltaT >= 1)
			{
				if(this->checkSphericalCollision(player,oceanBoss_collider))
				{
					if(player->shieldActive)
					{
						player->shield-=2;
						if(player->shield <=0)
						{
							player->shieldActive = false;
							player->shield = 500;
							invincible=true;
						}
					}else
					{
						player->health-=1;
						invincible=true;
					}
				}
			}
			break;
		case 3:
			if(desertBoss->Bullets.size() > 0)
			{
				for(int k = 0; k<desertBoss->Bullets.size(); k++)
				{
					Vector temp = player->position.subVector(desertBoss->Bullets[k]->position);
					if(abs(temp.thisVector.x)<50 && abs(temp.thisVector.y)<30)
					{
						if(desertBoss->particleBullet[k]->lifetime >= 0)
						{
							if(this->checkSphericalCollision(player_collider, desertBoss->Bullets[k]))
							{
								if(player->shieldActive)
								{
									player->shield-=2;
									if(player->shield <=0)
									{
										player->shieldActive = false;
										player->shield = 500;
										invincible=true;
									}
								}else
								{
									player->health-=1;
									invincible=true;
								}
							}
						}
					}
				}
			}
			if(desertBoss->deltaT >= 1)
			{
				if(this->checkSphericalCollision(player,desertBoss_collider))
				{
					if(player->shieldActive)
					{
						player->shield-=2;
						if(player->shield <=0)
						{
							player->shieldActive = false;
							player->shield = 500;
							invincible=true;
						}
					}else
					{
						player->health-=1;
						invincible=true;
					}
				}
			}
			break;
		case 4:
			if(tropicalBoss->Bullets.size() > 0)
			{
				for(int k = 0; k<tropicalBoss->Bullets.size(); k++)
				{
					Vector temp = player->position.subVector(tropicalBoss->Bullets[k]->position);
					if(abs(temp.thisVector.x)<50 && abs(temp.thisVector.y)<30)
					{
						if(tropicalBoss->particleBullet[k]->lifetime >= 0)
						{
							if(this->checkSphericalCollision(player_collider, tropicalBoss->Bullets[k]))
							{
								if(player->shieldActive)
								{
									player->shield-=2;
									if(player->shield <=0)
									{
										player->shieldActive = false;
										player->shield = 500;
										invincible=true;
									}
								}else
								{
									player->health-=1;
									invincible=true;
								}
							}
						}
					}
				}
			}
			if(tropicalBoss->deltaT >= 1)
			{
				if(this->checkSphericalCollision(player,tropicalBoss_collider))
				{
					if(player->shieldActive)
					{
						player->shield-=2;
						if(player->shield <=0)
						{
							player->shieldActive = false;
							player->shield = 500;
							invincible=true;
						}
					}else
					{
						player->health-=1;
						invincible=true;
					}
				}
			}
			break;
		case 5:
			if(iceBoss->Bullets.size() > 0)
			{
				for(int k = 0; k<iceBoss->Bullets.size(); k++)
				{
					Vector temp = player->position.subVector(iceBoss->Bullets[k]->position);
					if(abs(temp.thisVector.x)<50 && abs(temp.thisVector.y)<30)
					{
						if(iceBoss->particleBullet[k]->lifetime >= 0)
						{
							if(this->checkSphericalCollision(player_collider, iceBoss->Bullets[k]))
							{
								if(player->shieldActive)
								{
									player->shield-=2;
									if(player->shield <=0)
									{
										player->shieldActive = false;
										player->shield = 500;
										invincible=true;
									}
								}else
								{
									player->health-=1;
									invincible=true;
								}
							}
						}
					}
				}
			}
			if(iceBoss->deltaT >= 1)
			{
				if(this->checkSphericalCollision(player,iceBoss_collider))
				{
					if(player->shieldActive)
					{
						player->shield-=2;
						if(player->shield <=0)
						{
							player->shieldActive = false;
							player->shield = 500;
							invincible=true;
						}
					}else
					{
						player->health-=1;
						invincible=true;
					}
				}
			}
			break;
		}
	}
	if(asteroids.size() > 0)
	{
		for(int i = 0; i<asteroids.size(); i++)
		{
			if(player->health>0)
			{
				if (!invincible)
				{
					Vector temp = player->position.subVector(asteroids[i]->position);
					if(abs(temp.thisVector.x)<50 && abs(temp.thisVector.y)<30)
					{
						if(this->checkSphericalCollision(player_collider, asteroids[i]))
						{
							if(player->shieldActive)
							{
								player->shield-=10;
								if(player->shield <=0)
								{
									player->shieldActive = false;
									player->shield = 500;
									invincible=true;
								}
							}else
							{
								player->health-=5;
								invincible=true;
							}
							cout << "Hit!" << endl;
							asteroids[i]->collided = true;
						}
					}
				}
			}
		}
	}
}

void Game::checkEnemyCollision()
{
	for (int i=0; i<enemies.size(); i++)
	{
		for (int k=0; k<enemies.size(); k++)
		{
			if(i!=k)
			{
				Vector temp = enemies[i]->position.subVector(enemies[k]->position);
				if(abs(temp.thisVector.x)<10 && abs(temp.thisVector.y)<10)
				{
					if(this->checkSphericalCollision(spheres[i], spheres[k]))
					{
						enemies[k]->state = REPEL;
						enemies[k]->substate = REPEL_ENEMY;
						enemies[k]->setSeekTarget(enemies[i]);
					}
				}
			}
		}
	}
	if(player->health < 0)
	{
		player->health = 100;
		exitLevel();
	}
}

void Game::checkBulletCollision()
{
	for(int k = 0; k<enemies.size(); k++)
	{
		if (enemies[k]->health > 0)
		{
			if(player->health > 0)
			{
				for (int b=0; b<player->bullets.size(); b++)
				{
					if(player->bullets[b]->lifetime > 0)
					{
     					if(this->checkSphericalCollision(player->bullets[b], spheres[k]))
						{
							enemies[k]->health--;
							player->bullets[b]->lifetime=0;
							score+=2;
							cout << "Kill!" << endl;
						}
					}
				}
				for (int b=0; b<player->fire.size(); b++)
				{
					if(player->fire[b]->lifetime > 0)
					{
     					if(this->checkSphericalCollision(player->fire[b], spheres[k]))
						{
							enemies[k]->health-=0.2;
							score+=5;
							player->fire[b]->lifetime=0;
							cout << "Kill!" << endl;
						}
					}
				}
				for (int b=0; b<player->water.size(); b++)
				{
					if(player->water[b]->lifetime > 0)
					{
     					if(this->checkSphericalCollision(player->water[b], spheres[k]))
						{
							enemies[k]->health-=0.2;
							score+=5;
							player->water[b]->lifetime=0;
							cout << "Kill!" << endl;
						}
					}
				}
				for (int b=0; b<player->missiles.size(); b++)
				{
					if(player->missiles[b]->lifetime > 0)
					{
     					if(this->checkSphericalCollision(player->missiles[b], spheres[k]))
						{
							enemies[k]->health--;
							score+=1;
							cout << "Kill!" << endl;
						}
					}
				}
				if(gravityBomb)
				{
					if(this->checkSphericalCollision(gravityBombPortal, spheres[k]))
					{
						enemies[k]->health = 0;
						score++;
						cout << "Kill!" << endl;
					}
				}
			}
		}
	}
	if (asteroids.size() > 0)
	{
		for (int i = 0; i<asteroids.size(); i++)
		{
			if(player->health > 0)
			{
				for (int b=0; b<player->bullets.size(); b++)
				{
					if(player->bullets[b]->lifetime > 0)
					{
     					if(this->checkSphericalCollision(player->bullets[b], asteroids[i]))
						{
							asteroids[i]->collided = true;
							score+=1;
							player->bullets[b]->lifetime=0;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->bullets[b]->position),1,0.9,0,1,1,15.0));

						}
					}
				}
			}
		}
	}
	if(stateInfo.bossState > 0)
	{
		switch(stateInfo.bossState)
		{
		case 1:
			if(spaceBoss->deltaT >= 1)
			{
				for (int b=0; b<player->bullets.size(); b++)
				{
					if(player->bullets[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->bullets[b], spaceBoss_collider))
						{
							spaceBoss->health--;
							player->bullets[b]->lifetime=0;
							score+=20;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->bullets[b]->position),1,0.9,0,1,1,120.0));
							
						}
					}
				}
				for (int b=0; b<player->fire.size(); b++)
				{
					if(player->fire[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->fire[b], spaceBoss_collider))
						{
							spaceBoss->health-=0.2;
							score+=2;
							player->fire[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->fire[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->water.size(); b++)
				{
					if(player->water[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->water[b], spaceBoss_collider))
						{
							spaceBoss->health-=0.2;
							score+=2;
							player->water[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->water[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->missiles.size(); b++)
				{
					if(player->missiles[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->missiles[b], spaceBoss_collider))
						{
							spaceBoss->health--;
							score+=2;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->missiles[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
			}
			break;
		case 2:
			if(oceanBoss->deltaT >= 1)
			{
				for (int b=0; b<player->bullets.size(); b++)
				{
					if(player->bullets[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->bullets[b], oceanBoss_collider))
						{
							oceanBoss->health--;
							player->bullets[b]->lifetime=0;
							score+=20;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->bullets[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->fire.size(); b++)
				{
					if(player->fire[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->fire[b], oceanBoss_collider))
						{
							oceanBoss->health-=0.2;
							score+=2;
							player->fire[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->fire[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->water.size(); b++)
				{
					if(player->water[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->water[b], oceanBoss_collider))
						{
							oceanBoss->health-=0.2;
							score+=2;
							player->water[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->water[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->missiles.size(); b++)
				{
					if(player->missiles[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->missiles[b], oceanBoss_collider))
						{
							oceanBoss->health--;
							score+=2;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->missiles[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
			}
			break;
		case 3:
			if(desertBoss->deltaT >= 1)
			{
				for (int b=0; b<player->bullets.size(); b++)
				{
					if(player->bullets[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->bullets[b], desertBoss_collider))
						{
							desertBoss->health--;
							player->bullets[b]->lifetime=0;
							score+=20;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->bullets[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->fire.size(); b++)
				{
					if(player->fire[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->fire[b], desertBoss_collider))
						{
							desertBoss->health-=0.2;
							score+=2;
							player->fire[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->fire[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->water.size(); b++)
				{
					if(player->water[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->water[b], desertBoss_collider))
						{
							desertBoss->health-=0.2;
							score+=2;
							player->water[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->water[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->missiles.size(); b++)
				{
					if(player->missiles[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->missiles[b], desertBoss_collider))
						{
							desertBoss->health--;
							score+=2;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->missiles[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
			}
			break;
		case 4:
			if(tropicalBoss->deltaT >= 1)
			{
				for (int b=0; b<player->bullets.size(); b++)
				{
					if(player->bullets[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->bullets[b], tropicalBoss_collider))
						{
							tropicalBoss->health--;
							player->bullets[b]->lifetime=0;
							score+=20;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->bullets[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->fire.size(); b++)
				{
					if(player->fire[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->fire[b], tropicalBoss_collider))
						{
							tropicalBoss->health-=0.2;
							score+=2;
							player->fire[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->fire[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->water.size(); b++)
				{
					if(player->water[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->water[b], tropicalBoss_collider))
						{
							tropicalBoss->health-=0.2;
							score+=2;
							player->water[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->water[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->missiles.size(); b++)
				{
					if(player->missiles[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->missiles[b], tropicalBoss_collider))
						{
							tropicalBoss->health--;
							score+=2;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->missiles[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
			}
			break;
		case 5:
			if(iceBoss->deltaT >= 1)
			{
				for (int b=0; b<player->bullets.size(); b++)
				{
					if(player->bullets[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->bullets[b], iceBoss_collider))
						{
							iceBoss->health--;
							player->bullets[b]->lifetime=0;
							score+=20;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->bullets[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->fire.size(); b++)
				{
					if(player->fire[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->fire[b], iceBoss_collider))
						{
							iceBoss->health-=0.2;
							score+=2;
							player->fire[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->fire[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->water.size(); b++)
				{
					if(player->water[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->water[b], iceBoss_collider))
						{
							iceBoss->health-=0.2;
							score+=2;
							player->water[b]->lifetime=0;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->water[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
				for (int b=0; b<player->missiles.size(); b++)
				{
					if(player->missiles[b]->lifetime >0)
					{
     					if(this->checkSphericalCollision(player->missiles[b], iceBoss_collider))
						{
							iceBoss->health--;
							score+=2;
							cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->missiles[b]->position),1,0.9,0,1,1,120.0));

						}
					}
				}
			}
			break;
		}
	}
}

void Game::checkPowerupCollision()
{
	for (int i=0; i<powerups.size(); i++)
	{
		if(powerups[i]->alive)
		{
			if(player->health > 0)
			{
				if(this->checkSphericalCollision(player_collider, powerups[i]))
				{
					player->powerups.push_back(powerups[i]->ID);
					currentID = player->powerups.back();
					quickSortPowerups();
					powerups[i]->alive = false;
					this->powerup_pickUp->play(Vector(0,0,0));
				}
			}
		}
	}
}

void Game::checkAsteroidCollision()
{
	for (int j=0; j<asteroids.size(); j++)
	{
		for (int k=0; k<asteroids.size(); k++)
		{
			if(j!=k)
			{
				if(!asteroids[j]->collided && !asteroids[k]->collided)
				{
					Vector temp = asteroids[j]->position.subVector(asteroids[k]->position);
					if(abs(temp.thisVector.x)<10 && abs(temp.thisVector.y)<10)
					{
						if(this->checkSphericalCollision(asteroids[j], asteroids[k]))
						{
							asteroids[j]->collided = true;
							asteroids[k]->collided = true;
						}
					}
				}
			}
		}
	}
	if (enemies.size() > 0)
	{
		for(int k = 0; k<enemies.size(); k++)
		{
			for(int a = 0; a<asteroids.size(); a++)
			{
				if(!asteroids[a]->collided)
				{
     				if(this->checkSphericalCollision(asteroids[a], spheres[k]))
					{
						enemies[k]->health--;
						asteroids[a]->collided = true;
					}
				}
			}
		}
	}
}

void Game::checkSpawnerCollision()
{
	for (int i=0; i<spawners.size(); i++)
	{
		if(spawners[i]->health > 0)
		{
			for (int b=0; b<player->bullets.size(); b++)
			{
				if(player->bullets[b]->lifetime >0)
				{
     				if(this->checkSphericalCollision(player->bullets[b], spawners[i]))
					{
						spawners[i]->health--;
						player->bullets[b]->lifetime=0;
						score+=2;
						cout << "Kill!" << endl;
						wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->bullets[b]->position),1,0.9,0,1,1,30.0));

					}
				}
			}
			for (int b=0; b<player->fire.size(); b++)
			{
				if(player->fire[b]->lifetime >0)
				{
     				if(this->checkSphericalCollision(player->fire[b], spawners[i]))
					{
						spawners[i]->health-=0.2;
						player->fire[b]->lifetime=0;
						score+=1;
						cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->fire[b]->position),1,0.9,0,1,1,30.0));

					}
				}
			}
			for (int b=0; b<player->water.size(); b++)
			{
				if(player->water[b]->lifetime >0)
				{
     				if(this->checkSphericalCollision(player->water[b], spawners[i]))
					{
						spawners[i]->health-=0.2;
						player->water[b]->lifetime=0;
						score+=1;
						cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->water[b]->position),1,0.9,0,1,1,30.0));
					}
				}
			}
			for (int b=0; b<player->missiles.size(); b++)
			{
				if(player->missiles[b]->lifetime >0)
				{
     				if(this->checkSphericalCollision(player->missiles[b], spawners[i]))
					{
						spawners[i]->health--;
						score+=1;
						cout << "Kill!" << endl;
							wall_explosions.push_back( Explosion(90,false,false,true,Vector(0.1,0.1,0.1),Vector(0,0,0),Vector(player->missiles[b]->position),1,0.9,0,1,1,30.0));

					}
				}
			}
		}
	}
}