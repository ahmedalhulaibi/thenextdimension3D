#include "Game.h"
using namespace std;

void Game::updateBosses()
{
	if(stateInfo.bossState != STATE_NO_BOSS)
	{
		switch(stateInfo.bossState)
		{
		case 1:
			if(spaceBoss->health <= 0)
			{
				stateInfo.bossState = STATE_NO_BOSS;
				spaceBoss->health = spaceBoss->fullHealth;
				exitLevel();
			}
			if(spaceBoss->deltaT >= 1)
			{
				gameMusic->pause();
				FMOD_BOOL isPaused;
				FMOD_Channel_GetPaused(finalBoss_dialogue->channel,&isPaused);
				if(isPaused)
				{
					//bossTrack->play();
				}
			}
			if(spaceBoss->deltaT < 1)
			{
				spaceBoss->morph();
				spaceBoss_collider->morph();
			}else if(spaceBoss->phase >= PHASE1)
			{
				if (spaceBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<spaceBoss->particleBullet.size(); i++)
					{
						spaceBoss->particleBullet[i]->update(1);
						spaceBoss->Bullets[i]->position = spaceBoss->particleBullet[i]->position;
					}
				}
				if(!(frameCount%60))
				{
					spaceBoss->shootParticle(bullet);
				}
				spaceBoss->update();
				spaceBoss_collider->position = spaceBoss->position;
				spaceBoss_collider->orientation = spaceBoss->orientation;
			}
			/*spaceBoss->position.X_Y_Z[0] = player->position.X_Y_Z[0] - 30;
			spaceBoss->position.thisVector.x = spaceBoss->position.X_Y_Z[0];*/
			break;
		case 2:
			if(oceanBoss->health <= 0)
			{
				stateInfo.bossState = STATE_NO_BOSS;
				oceanBoss->health = oceanBoss->fullHealth;
				exitLevel();
			}
			if(oceanBoss->deltaT >= 1)
			{
				gameMusic->pause();
				FMOD_BOOL isPaused;
				FMOD_Channel_GetPaused(finalBoss_dialogue->channel,&isPaused);
				if(isPaused)
				{
					//bossTrack->play();
				}
			}
			if(oceanBoss->deltaT < 1)
			{
				oceanBoss->morph();
				oceanBoss_collider->morph();
			}else if(oceanBoss->phase >= PHASE1)
			{
				if (oceanBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<oceanBoss->particleBullet.size(); i++)
					{
						oceanBoss->particleBullet[i]->update(1);
						oceanBoss->Bullets[i]->position = oceanBoss->particleBullet[i]->position;
					}
				}
				if(oceanBoss->phase == 1)
				{
					if(frameCount%90 == 0)
					{
						oceanBoss->shootParticle(bullet);
					}
				}else
				{
					if(frameCount%180 == 0)
					{
						oceanBoss->shootParticle(bullet);
					}
				}
				oceanBoss->update();
				oceanBoss_collider->position = oceanBoss->position;
				oceanBoss_collider->orientation = oceanBoss->orientation;
			}
			/*oceanBoss->position.X_Y_Z[0] = player->position.X_Y_Z[0] - 30;
			oceanBoss->position.thisVector.x = oceanBoss->position.X_Y_Z[0];*/
			break;
		case 3:
			if(desertBoss->health <= 0)
			{
				stateInfo.bossState = STATE_NO_BOSS;
				desertBoss->health = desertBoss->fullHealth;
				exitLevel();
			}
			if(desertBoss->deltaT >= 1)
			{
				gameMusic->pause();
				FMOD_BOOL isPaused;
				FMOD_Channel_GetPaused(finalBoss_dialogue->channel,&isPaused);
				if(isPaused)
				{
					//bossTrack->play();
				}
			}
			if(desertBoss->deltaT < 1)
			{
				desertBoss->morph();
				desertBoss_collider->morph();
			}else if(desertBoss->phase >= PHASE1)
			{
				if (desertBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<desertBoss->particleBullet.size(); i++)
					{
						desertBoss->particleBullet[i]->update(1);
						desertBoss->Bullets[i]->position = desertBoss->particleBullet[i]->position;
					}
				}
				if(desertBoss->phase == 1)
				{
					if(frameCount%60 == 0)
					{
						desertBoss->shootParticle(bullet);
					}
				}else
				{
					if(frameCount%120 == 0)
					{
						desertBoss->shootParticle(bullet);
					}
				}
				desertBoss->update();
				desertBoss_collider->position = desertBoss->position;
				desertBoss_collider->orientation = desertBoss->orientation;
			}
			/*desertBoss->position.X_Y_Z[0] = player->position.X_Y_Z[0] - 30;
			desertBoss->position.thisVector.x = desertBoss->position.X_Y_Z[0];*/
			break;
		case 4:
			if(tropicalBoss->health <= 0)
			{
				stateInfo.bossState = STATE_NO_BOSS;
				tropicalBoss->health = tropicalBoss->fullHealth;
				exitLevel();
			}
			if(tropicalBoss->deltaT >= 1)
			{
				gameMusic->pause();
				FMOD_BOOL isPaused;
				FMOD_Channel_GetPaused(finalBoss_dialogue->channel,&isPaused);
				if(isPaused)
				{
				//	bossTrack->play();
				}
			}
			if(tropicalBoss->deltaT < 1)
			{
				tropicalBoss->morph();
				tropicalBoss_collider->morph();
			}else if(tropicalBoss->phase >= PHASE1)
			{
				if (tropicalBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<tropicalBoss->particleBullet.size(); i++)
					{
						tropicalBoss->particleBullet[i]->update(1);
						tropicalBoss->Bullets[i]->position = tropicalBoss->particleBullet[i]->position;
					}
				}
				if(tropicalBoss->phase == 1)
				{
					if(frameCount%30 == 0)
					{
						tropicalBoss->shootParticle(bullet);
					}
				}else
				{
					if(frameCount%90 == 0)
					{
						tropicalBoss->shootParticle(bullet);
					}
				}
				tropicalBoss->update();
				tropicalBoss_collider->position = tropicalBoss->position;
				tropicalBoss_collider->orientation = tropicalBoss->orientation;
			}
			/*tropicalBoss->position.X_Y_Z[0] = player->position.X_Y_Z[0] - 30;
			tropicalBoss->position.thisVector.x = tropicalBoss->position.X_Y_Z[0];*/
			break;
		case 5:
			if(iceBoss->health <= 0)
			{
				cutsceneIT = 0;
				iceBoss->health = iceBoss->fullHealth;
				stateInfo.bossState = STATE_NO_BOSS;
				stateInfo.gameState = STATE_CUTSCENE;
				stateInfo.subState = STATE_CUTSCENE3;
			}
			if(iceBoss->deltaT >= 1)
			{
				gameMusic->pause();
				FMOD_BOOL isPaused;
				FMOD_Channel_GetPaused(finalBoss_dialogue->channel,&isPaused);
				if(isPaused)
				{
					//bossTrack->play();
				}
			}
			if(iceBoss->deltaT == 1 && cuts3 == false)
			{
				stateInfo.gameState = STATE_CUTSCENE;
				stateInfo.subState = STATE_CUTSCENE2;
			}else if(iceBoss->deltaT < 1)
			{
				iceBoss->morph();
				iceBoss_collider->morph();
			}else if(iceBoss->phase >= PHASE1)
			{
				if (iceBoss->particleBullet.size() > 0)
				{
					for (int i=0; i<iceBoss->particleBullet.size(); i++)
					{
						iceBoss->particleBullet[i]->update(1);
						iceBoss->Bullets[i]->position = iceBoss->particleBullet[i]->position;
					}
				}
				if(frameCount%5 == 0)
				{
					iceBoss->shootParticle(bullet);
				}
				iceBoss->update();
				iceBoss_collider->position = iceBoss->position;
				iceBoss_collider->orientation = iceBoss->orientation;
			}
			/*iceBoss->position.X_Y_Z[0] = player->position.X_Y_Z[0] - 30;
			iceBoss->position.thisVector.x = iceBoss->position.X_Y_Z[0];*/
			break;
		}
	}
}