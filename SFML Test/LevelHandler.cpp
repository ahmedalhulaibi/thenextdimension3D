#include "Game.h"
using namespace std;

void Game::loadLevel()
{
	hubMusic->pause();
	gameMusic->play(player->position);
	if (stateInfo.subState == STATE_LEVEL1)
	{
		float x2 = 0;
		float y2 = 0;
		for(int j = 0; j<30; j++)
		{
			x2 = rand()%300 - 150;
			y2 = rand()%300 - 150;
			asteroids.push_back(new Asteroid(*asteroid));
			asteroids[j]->position = Vector(x2, y2, 0);
			asteroids[j]->direct();
		}

		spawners.push_back(new Spawner(spawner_level1));
		spawners.back()->position = Vector(-100, -75, 0);
		spawners.push_back(new Spawner(spawner_level1));
		spawners.back()->position = Vector(-100, 75, 0);
		spawners.push_back(new Spawner(spawner_level1));
		spawners.back()->position = Vector(100, -75, 0);
		spawners.push_back(new Spawner(spawner_level1));
		spawners.back()->position = Vector(100, 75, 0);
	}

	else if (stateInfo.subState == STATE_LEVEL2)
	{
		/*for(int i = 0; i<10; i++)
		{
			enemies[i]->max_speed = 0.5;
		}
		for(int i = 10; i<30; i++)
		{
			enemies[i]->max_speed = 0.6;
		}*/
		spawners.push_back(new Spawner(spawner_level2));
		spawners.back()->position = Vector(-105, -60, 0);
		spawners.push_back(new Spawner(spawner_level2));
		spawners.back()->position = Vector(-100, 70, 0);
		spawners.push_back(new Spawner(spawner_level2));
		spawners.back()->position = Vector(100, -65, 0);
		spawners.push_back(new Spawner(spawner_level2));
		spawners.back()->position = Vector(105, 65, 0);
	}

	if (stateInfo.subState == STATE_LEVEL3)
	{
		spawners.push_back(new Spawner(spawner_level3));
		spawners.back()->position = Vector(-110, 0, 0);
		spawners.push_back(new Spawner(spawner_level3));
		spawners.back()->position = Vector(110, 0, 0);
		spawners.push_back(new Spawner(spawner_level3));
		spawners.back()->position = Vector(0, -60, 0);
		spawners.push_back(new Spawner(spawner_level3));
		spawners.back()->position = Vector(0, 60, 0);
	}

	if (stateInfo.subState == STATE_LEVEL4)
	{
		int rand_x[4];
		int rand_y[4];
		for(int r=0; r<4; r++)
		{
			rand_x[r] = rand()%250 - 125;
			rand_y[r] = rand()%250 - 125;
		}

		spawners.push_back(new Spawner(spawner_level4));
		spawners.back()->position = Vector(rand_x[0], rand_y[0], 0);
		spawners.push_back(new Spawner(spawner_level4));
		spawners.back()->position = Vector(rand_x[1], rand_y[1], 0);
		spawners.push_back(new Spawner(spawner_level4));
		spawners.back()->position = Vector(rand_x[2], rand_y[2], 0);
		spawners.push_back(new Spawner(spawner_level4));
		spawners.back()->position = Vector(rand_x[3], rand_y[3], 0);

		for(int s=0; s<spawners.size(); s++)
		{
			spawners[s]->radii[0] *= 9.0;
			spawners[s]->radii[1] *= 9.0;
			spawners[s]->radii[2] *= 9.0;
		}
		for(int i=0; i<spawners.size(); i++)
		{
			for(int j=0; j<spawners.size(); j++)
			{
				if(i != j)
				{
					while(checkBoxCollision(spawners[i], spawners[j]))
					{
						rand_x[i] = rand()%250 - 125;
						rand_y[i] = rand()%250 - 125;
						spawners[i]->position = Vector(rand_x[i], rand_y[i], 0);
					}
				}
			}
		}
		for(int p=0; p<spawners.size(); p++)
		{
			spawners[p]->radii[0] /= 9.0;
			spawners[p]->radii[1] /= 9.0;
			spawners[p]->radii[2] /= 9.0;
	}
	}

	if (stateInfo.subState == STATE_LEVEL5)
	{
		spawners.push_back(new Spawner(spawner_level5));
		spawners.back()->position = Vector(-55, -0, 0);
		spawners.push_back(new Spawner(spawner_level5));
		spawners.back()->position = Vector(55, 0, 0);
		spawners.push_back(new Spawner(spawner_level5));
		spawners.back()->position = Vector(-125, -123, 0);
		spawners.push_back(new Spawner(spawner_level5));
		spawners.back()->position = Vector(-125, 123, 0);
		spawners.push_back(new Spawner(spawner_level5));
		spawners.back()->position = Vector(125, -123, 0);
		spawners.push_back(new Spawner(spawner_level5));
		spawners.back()->position = Vector(125, 123, 0);
	}
	for(unsigned int i = 0; i < spawners.size(); i++)
	{
		spawners[i]->spawnerSound->play(spawners[i]->position);
	FMOD_Channel_SetVolume(spawners[i]->spawnerSound->channel,1.0);
	}
	float rand_s = rand()%spawners.size();
	Vector temp_pos = spawners[rand_s]->position;
	//enemies.clear();
	if (stateInfo.subState == STATE_LEVEL1)
	{
		for(int i = 0; i<10; i++)
		{
			enemies.push_back(new EnemyBase(*enemy1_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy1_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	if (stateInfo.subState == STATE_LEVEL2)
	{
		float x = 100;
		float y = 100;
		for(int i = 0; i<15; i++)
		{
			enemies.push_back(new EnemyBase(*enemy2_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy2_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	if (stateInfo.subState == STATE_LEVEL3)
	{
		float x = 100;
		float y = 100;
		for(int i = 0; i<20; i++)
		{
			enemies.push_back(new EnemyBase(*enemy3_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy3_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	if (stateInfo.subState == STATE_LEVEL4)
	{
		float x = 100;
		float y = 100;
		for(int i = 0; i<20; i++)
		{
			enemies.push_back(new EnemyBase(*enemy4_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy4_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	if (stateInfo.subState == STATE_LEVEL5)
	{
		float x = 100;
		float y = 100;
		int it = enemies.size()-1;
		for(int i = 0; i<15; i++)
		{
			enemies.push_back(new EnemyBase(*enemy5_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy5_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	for(int i = 0; i<enemies.size(); i++)
	{
		float x = rand()%100 + 1;
		float y = rand()%100 + 1;

		enemies[i]->setSeekTarget(Vector(x,y,0));
	}
}

void Game::reloadEnemies()
{
	enemies.clear();
	float rand_s = rand()%spawners.size();
	Vector temp_pos = spawners[rand_s]->position;
	if (stateInfo.subState >= STATE_LEVEL1)
	{
		for(int i = 0; i<10; i++)
		{
			enemies.push_back(new EnemyBase(*enemy1_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy1_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	if (stateInfo.subState >= STATE_LEVEL2)
	{
		float x = 100;
		float y = 100;
		for(int i = 10; i<30; i++)
		{
			enemies.push_back(new EnemyBase(*enemy2_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy2_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	if (stateInfo.subState >= STATE_LEVEL3)
	{
		float x = 100;
		float y = 100;
		for(int i = 30; i<50; i++)
		{
			enemies.push_back(new EnemyBase(*enemy3_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy3_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	if (stateInfo.subState >= STATE_LEVEL4)
	{
		float x = 100;
		float y = 100;
		for(int i = 50; i<70; i++)
		{
			enemies.push_back(new EnemyBase(*enemy4_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy4_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	if (stateInfo.subState >= STATE_LEVEL5)
	{
		float x = 100;
		float y = 100;
		int it = enemies.size()-1;
		for(int i = 70; i<90; i++)
		{
			enemies.push_back(new EnemyBase(*enemy5_base));
			enemies[i]->position = temp_pos;
			enemies[i]->setSeekTarget(player);
			spheres.push_back(new EnemyBase(*enemy5_collider));
			spheres[i]->position = enemies[i]->position;
			enemies[i]->state = SEEK;
			enemies[i]->substate = SEEK_POINT;
		}
	}

	for(int i = 0; i<enemies.size(); i++)
	{
		float x = rand()%100 + 1;
		float y = rand()%100 + 1;

		enemies[i]->setSeekTarget(Vector(x,y,0));
	}
}

void Game::exitLevel()
{
	//PostDraw();
	asteroids.clear();
	enemies.clear();
	healthDrops.clear();
	explosions.clear();
	wall_explosions.clear();
	for(unsigned int i = 0; i < spawners.size(); i++)
	{
		spawners[i]->spawnerSound->pause();
	}
	spawners.clear();
	powerups.clear();
	spaceBoss->health = spaceBoss->fullHealth;
	spaceBoss->phase = PHASE1;
	desertBoss->health = desertBoss->fullHealth;
	desertBoss->phase = PHASE1;
	oceanBoss->health = oceanBoss->fullHealth;
	oceanBoss->phase = PHASE1;
	tropicalBoss->health = tropicalBoss->fullHealth;
	tropicalBoss->phase = PHASE1;
	iceBoss->health = iceBoss->fullHealth;
	iceBoss->phase = PHASE1;
	spaceBoss->deltaT = desertBoss->deltaT = oceanBoss->deltaT = tropicalBoss->deltaT = iceBoss->deltaT = 0;
	gameMusic->pause();
	hubMusic->play(player->position);
	finalBoss_dialogue->pause();

	if(player->health > 0)
	{
		s = "DIMENSION SAVED\n";
		if (!levelsCleared[stateInfo.subState-1])
		{
			levelsCleared[stateInfo.subState-1] = true;
		}
	}
	if(player->health <= 0)
	{
		s = "  YOU FAILED TO\nCLEAR THE LEVEL\nYOU SAD LITTLE\nTHINGY\n";
	}

	waves_num = 0;
	this->stateInfo.gameState = STATE_SCORING;
	this->stateInfo.bossState = STATE_NO_BOSS;
	player->position = Vector(0,0,0);
	player->health = 100;
	camPos = Vector(player->position.X_Y_Z[0],player->position.X_Y_Z[1],player->position.X_Y_Z[2]+camZ);

	ss.str("");
	ss << score;
	s.append("SCORE: ");
	s.append(ss.str());
	//score = 0;
	currentLevel = &levels[0];
}