#include "Game.h"
using namespace std;


void Game::DrawHUD()
{
	//glViewport((GLint)0,(GLint)0,(GLint)stateInfo.windowWidth,(GLint)stateInfo.windowHeight);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100,100,-56.25,56.25,1,10000);
	//glOrtho(-50,50,-28.125,28.125,1,10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt((GLdouble)0,(GLdouble)0,(GLdouble)10,/*Location of camera*/ 
			(GLdouble)0,(GLdouble)0,(GLdouble)0,/*where camera is looking*/ 
			(GLdouble)0,(GLdouble)1,(GLdouble)0);
	for(int i = 0; i < (player->health/10) && i < 10; i++)
	{
		healthBlock_HUD[i]->draw();
	}
	
	if(player->powerups.size() > 0)
	{
		
		switch(powerups_init[currentID-1]->ID)
		{
		case GRAVITY_BOMB:
			gravityBomb_HUD->draw();
			break;
		case SPEED_UP:
			speedUp_HUD->draw();
			if(playerSpeedUp)
			{
				shieldTimeBar_HUD->scaleX = float(speedUpTime)/180.0;
				shieldTimeBar_HUD->draw();
			}
			break;
		case SLOW_DOWN:
			slowDown_HUD->draw();
			if(slowDown)
			{
				shieldTimeBar_HUD->scaleX = float(slowDownTime)/180.0;
				shieldTimeBar_HUD->draw();
			}
			break;
		case FREEZE_TIME:
			freezeTime_HUD->draw();
			if(freezeEnemies)
			{
				shieldTimeBar_HUD->scaleX = float(freezeTime)/120.0;
				shieldTimeBar_HUD->draw();
			}
			break;
		case SHIELD:
			shield_HUD->draw();
			if(player->shieldActive)
			{
				shieldTimeBar_HUD->scaleX = player->shield/500;
				shieldTimeBar_HUD->draw();
			}
			break;
		}
	}

	

	if(flamethrower)
	{
		fireBar_HUD->scaleX = player->flamethrowerFuel/100;
		fireDrop_HUD->draw();
		fireBar_HUD->draw();
	}else if(waterGun)
	{
		waterBar_HUD->scaleX = player->waterFuel/100;
		waterDrop_HUD->draw();
		waterBar_HUD->draw();
	}
	
	boostBar_HUD->scaleX = player->boostFuel/100;
	boostBar_HUD->draw();
	

	if(player->shieldActive)
	{
		shieldBar_HUD->scaleX = player->shield/500;
		shieldBar_HUD->draw();
	}
}


void Game::drawParticles()
{
	/*if(player->bullets.size() > 0)
	{
		for(int i = 0; i < player->bullets.size();i++)
		{
			player->bullets[i]->render();
		}
	}*/
	if(player->missiles.size() > 0)
	{
		for(int i = 0; i < player->missiles.size();i++)
		{
			player->missiles[i]->render();
		}
	}
	if(player->water.size() > 0)
	{
		for(int i = 0; i < player->water.size();i++)
		{
			player->water[i]->update(1);
		}
	}
	if(player->fire.size() > 0)
	{
		for(int i = 0; i < player->fire.size();i++)
		{
			player->fire[i]->update(1);
		}
	}
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	if(player->bullets.size() > 0)
	{
		for(int i = 0; i < player->bullets.size();i++)
		{
			player->bullets[i]->render();
		}
	}
	glPushMatrix();
	glLineWidth(15.f);
	glBegin(GL_LINES);
	if(trail.size())
	{
		for(int i = 0; i < trail.size(); i++)
		{
			trail[i].useRand = false;
			trail[i].draw(1.f);
		}
	}
	glEnd();
	glPopMatrix();
	glDepthMask(GL_FALSE);
	glPushMatrix();
	glPointSize(10.f * (30/camZ));
	glBegin(GL_POINTS);
	if(healthDrops.size())
	{
		for(int i = 0; i < healthDrops.size(); i++)
		{
			healthDrops[i].draw();
		}
	}
	if(explosions.size())
	{
		for(int i = 0; i < explosions.size(); i++)
		{
			explosions[i].draw(1);
		}
	}
	if(wall_explosions.size())
	{
		for(int i = 0; i < wall_explosions.size(); i++)
		{
			wall_explosions[i].draw(this->elapsedTime);
		}
	}
	if(player->fireP.size() > 0)
	{
		for(int i = 0; i < player->fireP.size();i++)
		{
			player->fireP[i]->draw(1);
		}
	}
	
	if(player->waterP.size() > 0)
	{
		for(int i = 0; i < player->waterP.size();i++)
		{
			player->waterP[i]->draw(1);
		}
	}
	glEnd();
	if(stateInfo.bossState != STATE_NO_BOSS)
	{
		glPointSize(10.f);
		glBegin(GL_POINTS);
		switch(stateInfo.bossState)
		{
		case 1:
			if(spaceBoss->phase >= PHASE1)
			{
				if (spaceBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<spaceBoss->particleBullet.size(); i++)
					{
						spaceBoss->particleBullet[i]->draw(1);
					}
				}
			}
			break;
		case 2:
			if(oceanBoss->phase >= PHASE1)
			{
				if (oceanBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<oceanBoss->particleBullet.size(); i++)
					{
						oceanBoss->particleBullet[i]->draw(1);
					}
				}
			}
			break;
		case 3:
			if(desertBoss->phase >= PHASE1)
			{
				if (desertBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<desertBoss->particleBullet.size(); i++)
					{
						desertBoss->particleBullet[i]->draw(1);
					}
				}
			}
			break;
		case 4:
			if(tropicalBoss->phase >= PHASE1)
			{
				if (tropicalBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<tropicalBoss->particleBullet.size(); i++)
					{
						tropicalBoss->particleBullet[i]->draw(1);
					}
				}
			}
			break;
		case 5:
			if(iceBoss->phase >= PHASE1)
			{
				if (iceBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<iceBoss->particleBullet.size(); i++)
					{
						iceBoss->particleBullet[i]->draw(1);
					}
				}
			}
			break;
		}
		glEnd();
	}
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1,1,1,1);
	glDepthMask(GL_TRUE);


}
