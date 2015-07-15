#include "Game.h"
#include <ctime>
#include <vector>
#include <Windows.h>

float camX = 0;
float camY = 0;
float camZ = 45;
int frameCount = 0;
int frame = 0;
int click = 0;
int it = 0;
bool startSLERP = false;
int invi_frames = 20;
bool invincible = false;
bool fired = false;
int perspective = 0;
bool switched = false;
bool middleClicked = false;
bool pressed = false;
bool selected = false;
bool pushed = false;
char delay;
/* constructor */
Game::Game()
{
	/* green background */
	stateInfo.bgClearColor.red = 0;
	stateInfo.bgClearColor.green = 0;
	stateInfo.bgClearColor.blue = 0;
	/* init state */
	stateInfo.gameState = STATE_MAINMENU;
	stateInfo.menuState = STATE_MAIN_SETTINGS;
	//renderingTimer = new Timer("RENDER");
	//updateTimer = new Timer("UPDATE");
}

/* destructor */
Game::~Game(void)
{
	/* deallocate memory and clean up here if needed */
}



/* draw()
 * - this gets called automatically about 30 times per second
 * - this function just draws the sprites 
 */
void Game::draw()
{
	bool bloom = false;
	/* pre-draw - setup the rendering */
	PreDraw();
	/*toonPass->bindAsFBO();
	const unsigned int buffs[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, buffs);
	PreDraw();*/

	if(stateInfo.gameState == STATE_GAMEPLAY || stateInfo.gameState == STATE_CUTSCENE || stateInfo.gameState == STATE_LEVELSELECT || stateInfo.gameState == STATE_SCORING || stateInfo.gameState == STATE_MENU)//when false this won't render to fbo
	{
		bloom = true;
		scenePass->bindAsFBO();//bind to render to fbo
		PreDraw();
	}

	/* draw - actually render to the screen */
	/*toon_program->useProgram();
	glUniform1i(toon_inQmap_uniform,1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D,ramp.texID);

			glUniform1i(toon_inImg_uniform,0);
			glActiveTexture(GL_TEXTURE0);
		DrawGame();
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, 0);

	FrameBufferObj::unbindFBO();
	ShaderProgram::unbindShaders();

	edges_program->useProgram();
		glUniform1i(edges_inCol_uniform,0);
		glActiveTexture(GL_TEXTURE0);
		toonPass->bindAsColorTexture(0);

		glUniform1i(edges_inNorm_uniform,1);
		glActiveTexture(GL_TEXTURE1);
		toonPass->bindAsColorTexture(1);

		glUniform1i(edges_inDepth_uniform,2);
		glActiveTexture(GL_TEXTURE2);
		toonPass->bindAsDepthTexture();

		glUniform2f(edges_pixSize_uniform,
			1.0f/(float)stateInfo.windowWidth,
			1.0f/(float)stateInfo.windowHeight);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1, -1, -1.0f);
			glTexCoord2f(1.0f, 0.0f);	glVertex3f( 1, -1, -1.0f);
			glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1,  1, -1.0f);
			glTexCoord2f(1.0f, 1.0f);	glVertex3f( 1,  1, -1.0f);
		glEnd();

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);*/

	DrawGame();

	if(bloom && (stateInfo.gameState == STATE_GAMEPLAY || stateInfo.gameState == STATE_CUTSCENE || stateInfo.gameState == STATE_LEVELSELECT || stateInfo.gameState == STATE_SCORING || stateInfo.gameState == STATE_MENU)){
		FrameBufferObj::unbindFBO();
		ShaderProgram::unbindShaders();

		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);

		brightPass->bindAsFBO();
		glViewport((GLint)0,(GLint)0,(GLint)stateInfo.windowWidth/4,(GLint)stateInfo.windowHeight/4);
		glClear(GL_COLOR_BUFFER_BIT);
		brightPass_Program->useProgram();
		brightPass_uniform1 = brightPass_Program->getUniformVarLoc("image");
		glUniform1i(brightPass_uniform1,0);
		//glPushMatrix();
		scenePass->drawFBO(true,false);
		//glPopMatrix();
		FrameBufferObj::unbindFBO();
		ShaderProgram::unbindShaders();


		blurPass1->bindAsFBO();
		glViewport((GLint)0,(GLint)0,(GLint)stateInfo.windowWidth/4,(GLint)stateInfo.windowHeight/4);
		glClear(GL_COLOR_BUFFER_BIT);
		gaussV_Program->useProgram();
			glUniform1i(gaussV_uniform1, 0);//scene texture
			glUniform1f(gaussV_uniform2,
				1.0/( (float)stateInfo.windowWidth/4 ) );
			brightPass->drawFBO(true,false);
		FrameBufferObj::unbindFBO();
		ShaderProgram::unbindShaders();

		blurPass2->bindAsFBO();
		glViewport((GLint)0,(GLint)0,(GLint)stateInfo.windowWidth/4,(GLint)stateInfo.windowHeight/4);
		glClear(GL_COLOR_BUFFER_BIT);
		gaussH_Program->useProgram();
			glUniform1i(gaussH_uniform1, 0);//scene texture
			glUniform1f(gaussH_uniform2,
				1.0/( (float)stateInfo.windowWidth/4 ) );
			blurPass1->drawFBO(true,false);
		FrameBufferObj::unbindFBO();
		ShaderProgram::unbindShaders();

		glViewport((GLint)0,(GLint)0,(GLint)stateInfo.windowWidth,(GLint)stateInfo.windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//brightPass->drawFBO(true,false);

		composite_Program->useProgram();
		this->gamma = 0.5 + (0.5 * (player->health/100));
		if(player->shieldActive)
		{
			this->gamma = 1.0;
		}
		glUniform1f(composite_uniform_gamma,this->gamma);
		glActiveTexture(GL_TEXTURE0);
		scenePass->bindAsColorTexture(0);
		glUniform1i(composite_uniform1,0);
		glActiveTexture(GL_TEXTURE1);
		blurPass2->bindAsColorTexture(0);
		glUniform1i(composite_uniform2,1);
		glViewport((GLint)0,(GLint)0,(GLint)stateInfo.windowWidth,(GLint)stateInfo.windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBegin(GL_TRIANGLE_STRIP);
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1, -1, -1.0f);
			glTexCoord2f(1.0f, 0.0f);	glVertex3f( 1, -1, -1.0f);
			glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1,  1, -1.0f);
			glTexCoord2f(1.0f, 1.0f);	glVertex3f( 1,  1, -1.0f);
		glEnd();
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D,0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,0);
	}
	
	FrameBufferObj::unbindFBO();
	ShaderProgram::unbindShaders();
	/* post-draw - after rendering, setup the next frame */
	glEnable(GL_LIGHTING);
	PostDraw();

}

/*
 * Pre-Draw() is for setting up things that need to happen in order to draw
 *    the game, i.e. sorting, splitting things into appropriate lists etc.
 */
void Game::PreDraw()
{
	/* clear the screen */
	glViewport((GLint)0,(GLint)0,(GLint)stateInfo.windowWidth,(GLint)stateInfo.windowHeight);
		glClearColor((GLclampf)stateInfo.bgClearColor.red,
				(GLclampf)stateInfo.bgClearColor.green,
				 (GLclampf)stateInfo.bgClearColor.blue, 0);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.f, (GLfloat)stateInfo.aspect, 1.f, 10000.f);
		//glOrtho(0,1600,0,900,1.f,100000.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity(); // clear out the transformation matrix
	
		glEnable(GL_TEXTURE_2D); // turn on texturing
		glEnable(GL_DEPTH_TEST);
	// if we update our timer it will tell us the elapsed time since the previous 
	// frame that we rendered
	//renderingTimer->tick();
	if(stateInfo.gameState == STATE_CUTSCENE)
	{
		if(stateInfo.subState == STATE_CUTSCENE1 || stateInfo.subState == STATE_CUTSCENE3)
		{
			camPos.SLERP(*cutscene1[cutsceneIT],*cutscene1[cutsceneIT+1],*cutscene1[cutsceneIT+2],*cutscene1[cutsceneIT+3], cutscene1_dt[cutsceneIT]);
			camPos.addVector(player->position);
			cutscene1_dt[cutsceneIT] += speedControl_1[cutsceneIT]/(speedControl_1[cutsceneIT]*600);
			if(cutscene1_dt[cutsceneIT] > 1)
			{
				cutscene1_dt[cutsceneIT] = speedControl_1[cutsceneIT]/(speedControl_1[cutsceneIT]*600);
				cutsceneIT++;
			}
			if(cutsceneIT == 4)
			{
				cutsceneIT = 0;
				if(stateInfo.subState == STATE_CUTSCENE3)
				{
					exitLevel();
				}else
				{
					stateInfo.gameState = STATE_LEVELSELECT;
					camPos = Vector(player->position.X_Y_Z[0],player->position.X_Y_Z[1],player->position.X_Y_Z[2]+camZ);
					/*delete camSpring;
					camSpring = new Spring(3.0,2.0,player->position,camPos);*/
				}
			}
			gluLookAt((GLdouble)camPos.X_Y_Z[0],(GLdouble)camPos.X_Y_Z[1],(GLdouble)camPos.X_Y_Z[2],//Location of camera
			(GLdouble)player->position.X_Y_Z[0],(GLdouble)player->position.X_Y_Z[1],(GLdouble)player->position.X_Y_Z[2],//where camera is looking
			(GLdouble)0,(GLdouble)0,(GLdouble)1);//last triplet determines up vector of camera
		}
		else if(stateInfo.subState == STATE_CUTSCENE2)
		{
			camPos.SLERP(*cutscene1[cutsceneIT],*cutscene1[cutsceneIT+1],*cutscene1[cutsceneIT+2],*cutscene1[cutsceneIT+3], cutscene1_dt[cutsceneIT]);
			camPos.addVector(iceBoss->position);
			cutscene1_dt[cutsceneIT] += speedControl_1[cutsceneIT]/(speedControl_1[cutsceneIT]*180);
			if(cutscene1_dt[cutsceneIT] > 1)
			{
				cutscene1_dt[cutsceneIT] = speedControl_1[cutsceneIT]/(speedControl_1[cutsceneIT]*180);
				cutsceneIT++;
			}
			if(cutsceneIT == 4)
			{
				cuts3 = true;
				cutsceneIT = 0;
				stateInfo.gameState = STATE_GAMEPLAY;
				stateInfo.subState = STATE_LEVEL5;
				stateInfo.bossState = STATE_BOSS5;
			}
			gluLookAt((GLdouble)camPos.X_Y_Z[0],(GLdouble)camPos.X_Y_Z[1],(GLdouble)camPos.X_Y_Z[2],//Location of camera 
			(GLdouble)iceBoss->position.X_Y_Z[0],(GLdouble)iceBoss->position.X_Y_Z[1],(GLdouble)iceBoss->position.X_Y_Z[2],//where camera is looking
			(GLdouble)0,(GLdouble)0,(GLdouble)1);//last triplet determines up vector of camera
		}
	}else if(stateInfo.gameState == STATE_CONTROLS || stateInfo.gameState == STATE_SETTINGS || stateInfo.gameState == STATE_PAUSED || stateInfo.gameState == STATE_MAINMENU || stateInfo.gameState == STATE_HOWTOPLAY)
	{
		gluLookAt((GLdouble)camPos.X_Y_Z[0],(GLdouble)camPos.X_Y_Z[1],(GLdouble)0+(GLdouble)70,/*Location of camera*/ 
		(GLdouble)player->position.X_Y_Z[0]/*camPos.X_Y_Z[0],(GLdouble)*/,player->position.X_Y_Z[1]/*camPos.X_Y_Z[1]*/,(GLdouble)0,/*where camera is looking*/ 
		(GLdouble)0,(GLdouble)1,(GLdouble)0);
	}else if (perspective==0)
	{
	gluLookAt((GLdouble)camPos.X_Y_Z[0],(GLdouble)camPos.X_Y_Z[1],(GLdouble)player->position.X_Y_Z[2]+(GLdouble)camZ,/*Location of camera*/ 
		(GLdouble)player->position.X_Y_Z[0]/*camPos.X_Y_Z[0]*/,(GLdouble)player->position.X_Y_Z[1]/*camPos.X_Y_Z[1]*/,(GLdouble)player->position.X_Y_Z[2],/*where camera is looking*/ 
		(GLdouble)0,(GLdouble)1,(GLdouble)0);//last triplet determines up vector of camera
	}
	else if (perspective==1)
	{
		gluLookAt((GLdouble)camPos.X_Y_Z[0],(GLdouble)camPos.X_Y_Z[1]-12.5,(GLdouble)player->position.X_Y_Z[2]+(GLdouble)camZ,/*Location of camera*/ 
			(GLdouble)player->position.X_Y_Z[0],(GLdouble)player->position.X_Y_Z[1],(GLdouble)player->position.X_Y_Z[2],/*where camera is looking*/ 
			(GLdouble)0,(GLdouble)1,(GLdouble)0);//last triplet determines up vector of camera
	}
	else if (perspective==2)
	{
		gluLookAt((GLdouble)camPos.X_Y_Z[0],(GLdouble)camPos.X_Y_Z[1]-25,(GLdouble)player->position.X_Y_Z[2]+(GLdouble)camZ,/*Location of camera*/ 
			(GLdouble)player->position.X_Y_Z[0],(GLdouble)player->position.X_Y_Z[1],(GLdouble)player->position.X_Y_Z[2],/*where camera is looking*/ 
			(GLdouble)0,(GLdouble)1,(GLdouble)0);//last triplet determines up vector of camera
	}
}

/* 
 * DrawGame()
 *  - this is the actual drawing of the current frame of the game.
 */
void Game::DrawGame()
{	

	if (stateInfo.gameState == STATE_MAINMENU)
	{
		//main_menu.render();
		//glDisable(GL_LIGHTING);
		/*glDisable(GL_DEPTH_TEST);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glViewport(0,0,1600,900);
		gluOrtho2D(0,1600,0,900);*/
		//glOrtho(0, 1600, 0, 900, 1.f, 1000.f);
		//gluLookAt(0,0,200,0,0,0,0,1,0);

		/*glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();*/

		/*mainMenu->scale = 3.0f;
		mainMenu->setPosition(0,0,0);*/
		mainMenu->draw();
		newGame_Button->draw(); 
		settings_Button->draw();
		credits_Button->draw();
		exit_Button->draw();
		//testSprite->draw();	
	}

	else if(stateInfo.gameState == STATE_SETTINGS)
	{
		//translate to screen space
		glTranslatef(player->position.thisVector.x, 
			player->position.thisVector.y,
			/*player->position.thisVector.z*/0);

		settingsMenu->draw();
		audio_Button->draw();
		controls_Button->draw();
		howtoplay_Button->draw();

		back_Button->setPosition(-212.5, -284, 10);
		back_Button->draw();
	}

	else if(stateInfo.gameState == STATE_CREDITS)
	{
		creditsMenu->draw();
		back_Button->draw();
	}

	else if(stateInfo.gameState == STATE_CONTROLS)
	{
		//to screen space!
		glTranslatef(player->position.thisVector.x, 
			player->position.thisVector.y,
			/*player->position.thisVector.z*/0);

		if(sf::Joystick::isConnected(0))
			controllerMenu->draw();
		else
		{
		controlsMenu->draw();
		back_Button->setPosition(380, -385, 10);
		back_Button->draw();
		}
	}

	else if(stateInfo.gameState == STATE_PAUSED)
	{
		//to screen space
		glTranslatef(player->position.thisVector.x, 
			player->position.thisVector.y,
			/*player->position.thisVector.z*/0);

		if(stateInfo.subState == STATE_HUB)
		{
			pauseMenu->draw();
			resume_Button->draw();
			settings_Button->draw();
		}
		else
		{
			pauseMenu->draw();
			resume_Button->draw();
			settings_Button->draw();
			hub_Button->draw();
		}
	 }

	else if(stateInfo.gameState == STATE_HOWTOPLAY)
	{
		glTranslatef(player->position.thisVector.x, 
			player->position.thisVector.y, 0);

		howtoplayMenu->draw();

		back_Button->setPosition(300, 180, 10);
		back_Button->draw();
	}


	else if (stateInfo.gameState == STATE_GAMEPLAY || stateInfo.gameState == STATE_SCORING || stateInfo.gameState == STATE_MENU)
	{
		if (stateInfo.subState >= STATE_LEVEL1 && stateInfo.subState < STATE_LEVEL6)
		{
			for (int i=0; i<4; i++)
			{
				level_border[i].render();
			}
			for (int j=0; j<spawners.size(); j++)
			{
				if(spawners[j]->health > 0)
				{
					
					if(stateInfo.subState == STATE_LEVEL4)
					{
						spawners[j]->position.thisVector.z = spawners[j]->position.X_Y_Z[2] = -10;
					}
					if(!(stateInfo.subState == STATE_LEVEL4 && stateInfo.gameState == STATE_MENU))
					{
						spawners[j]->render();
					}
				}
			}
			
		}
		if (stateInfo.bossState == STATE_NO_BOSS)
		{
			scrollingTexHor_program->useProgram();
			glUniform1i(scrollHor_tex_uniform,0);
			glUniform1f(scrollHor_time_uniform,this->totalTime);
			glUniform1f(scrollHor_speed_uniform,10);
			if (stateInfo.subState == STATE_LEVEL1)
			{
				for (int i=0; i<6; i++)
				{
					walls_level1[i].render();
				}
			}
			else if (stateInfo.subState == STATE_LEVEL2)
			{
				for (int i=0; i<6; i++)
				{
					walls_level2[i].render();
				}
			}
			else if (stateInfo.subState == STATE_LEVEL3)
			{
				for (int i=0; i<8; i++)
				{
					walls_level3[i].render();
				}
			}
			else if (stateInfo.subState == STATE_LEVEL5)
			{
				for (int i=0; i<14; i++)
				{
					walls_level5[i].render();
				}
			}
			ShaderProgram::unbindShaders();
		}

		if(stateInfo.bossState != STATE_NO_BOSS)
		{
			switch(stateInfo.bossState)
			{
			case 1:
				spaceBoss->render();
				//spaceBoss_collider->render();
				break;
			case 2:
				oceanBoss->render();
				//oceanBoss_collider->render();
				break;
			case 3:
				desertBoss->render();
				break;
			case 4:
				tropicalBoss->render();
				break;
			case 5:
				iceBoss->render();
				break;
			}
			/*spaceBoss->render();
			if(spaceBoss->phase == PHASE1)
			{
				if (spaceBoss->bullets.size() > 0)
				{
					for (int i=0; i<spaceBoss->bullets.size(); i++)
					{
						spaceBoss->bullets[i]->render();
					}
				}
				if (spaceBoss->bullets2.size() > 0)
				{
					for (int i=0; i<spaceBoss->bullets2.size(); i++)
					{
						spaceBoss->bullets2[i]->render();
					}
				}
			}*/
		}
		if(stateInfo.subState == STATE_LEVEL1)
		{
			scrollingTexHor_program->useProgram();
			glUniform1i(scrollHor_tex_uniform,0);
			glUniform1f(scrollHor_time_uniform,this->totalTime);
			glUniform1f(scrollHor_speed_uniform,10);
		}/*else if(stateInfo.subState == STATE_LEVEL2)
		{
			ocean_Things->render();
		}else if(stateInfo.subState == STATE_LEVEL3)
		{
			desert_Things->render();
		}else if(stateInfo.subState == STATE_LEVEL4)
		{
			tropical_Things->render();
		}*/
			currentLevel->render();
		if(stateInfo.subState == STATE_LEVEL1)
		{
			ShaderProgram::unbindShaders();
		}

	glDisable(GL_LIGHTING);
	if (asteroids.size() > 0)
	{
		normalMapping_program->useProgram();
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(diffuseMap_uniform, 0);
		//glBindTexture(GL_TEXTURE_2D, asteroid_tex.texID);
		glActiveTexture(GL_TEXTURE1);
		glUniform1i(normalMap.texID, 1);
		glActiveTexture(GL_TEXTURE0);
		for(int i = 0; i<asteroids.size(); i++)
		{
			//glUniform3f(pos_uniform, asteroids[i]->position.thisVector.x, asteroids[i]->position.thisVector.y, asteroids[i]->position.thisVector.z);
			//glBindTexture(GL_TEXTURE_2D, normalMap.texID);

			asteroids[i]->rendra();
		}
		ShaderProgram::unbindShaders();
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glEnable(GL_LIGHTING);

	if (powerups.size() > 0)
	{
		for (int i=0; i<powerups.size(); i++)
		{
			powerups[i]->render();
		}
	}


	if (player->health > 0)
	{
		if (invincible)
		{
			if (frameCount%2==0)
			{
				player->render();
			}
		}
		else
		{
			player->render();
		}
	}

	for(int i = 0; i<enemies.size(); i++)
	{
			enemies[i]->render();
	}

	///*if(player->bullets.size() > 0)
	//{
	//	for(int i = 0; i < player->bullets.size();i++)
	//	{
	//		player->bullets[i]->render();
	//	}
	//}*/
	//if(player->missiles.size() > 0)
	//{
	//	for(int i = 0; i < player->missiles.size();i++)
	//	{
	//		player->missiles[i]->render();
	//	}
	//}
	//if(player->water.size() > 0)
	//{
	//	for(int i = 0; i < player->water.size();i++)
	//	{
	//		player->water[i]->update();
	//	}
	//}
	//if(player->fire.size() > 0)
	//{
	//	for(int i = 0; i < player->fire.size();i++)
	//	{
	//		player->fire[i]->update();
	//	}
	//}
	//
	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_LIGHTING);
	//if(player->bullets.size() > 0)
	//{
	//	for(int i = 0; i < player->bullets.size();i++)
	//	{
	//		player->bullets[i]->render();
	//	}
	//}
	//glDepthMask(GL_FALSE);
	//glPushMatrix();
	//glPointSize(5.f);
	//glBegin(GL_POINTS);
	//if(healthDrops.size())
	//{
	//	for(int i = 0; i < healthDrops.size(); i++)
	//	{
	//		healthDrops[i].draw();
	//	}
	//}
	//if(player->fireP.size() > 0)
	//{
	//	for(int i = 0; i < player->fireP.size();i++)
	//	{
	//		player->fireP[i]->draw();
	//	}
	//}
	//
	//if(player->waterP.size() > 0)
	//{
	//	for(int i = 0; i < player->waterP.size();i++)
	//	{
	//		player->waterP[i]->draw();
	//	}
	//}
	//glEnd();
	//if(stateInfo.bossState != STATE_NO_BOSS)
	//{
	//	glPointSize(10.f);
	//	glBegin(GL_POINTS);
	//	switch(stateInfo.bossState)
	//	{
	//	case 1:
	//		if(spaceBoss->phase >= PHASE1)
	//		{
	//			if (spaceBoss->particleBullet.size() > 0)
	//			{
	//				for (int i=0; i<spaceBoss->particleBullet.size(); i++)
	//				{
	//					spaceBoss->particleBullet[i]->draw();
	//				}
	//			}
	//		}
	//		break;
	//	case 2:
	//		if(oceanBoss->phase >= PHASE1)
	//		{
	//			if (oceanBoss->particleBullet.size() > 0)
	//			{
	//				for (int i=0; i<oceanBoss->particleBullet.size(); i++)
	//				{
	//					oceanBoss->particleBullet[i]->draw();
	//				}
	//			}
	//		}
	//		break;
	//	case 3:
	//		if(desertBoss->phase >= PHASE1)
	//		{
	//			if (desertBoss->particleBullet.size() > 0)
	//			{
	//				for (int i=0; i<desertBoss->particleBullet.size(); i++)
	//				{
	//					desertBoss->particleBullet[i]->draw();
	//				}
	//			}
	//		}
	//		break;
	//	case 4:
	//		if(tropicalBoss->phase >= PHASE1)
	//		{
	//			if (tropicalBoss->particleBullet.size() > 0)
	//			{
	//				for (int i=0; i<tropicalBoss->particleBullet.size(); i++)
	//				{
	//					tropicalBoss->particleBullet[i]->draw();
	//				}
	//			}
	//		}
	//		break;
	//	case 5:
	//		if(iceBoss->phase >= PHASE1)
	//		{
	//			if (iceBoss->particleBullet.size() > 0)
	//			{
	//				for (int i=0; i<iceBoss->particleBullet.size(); i++)
	//				{
	//					iceBoss->particleBullet[i]->draw();
	//				}
	//			}
	//		}
	//		break;
	//	}
	//	glEnd();
	//}
	//glPopMatrix();
	//glEnable(GL_LIGHTING);
	//glEnable(GL_TEXTURE_2D);
	//glColor4f(1,1,1,1);
	//glDepthMask(GL_TRUE);
	drawParticles();

	if(player->bombs.size() > 0)
	{
		for(int i = 0; i < player->bombs.size();i++)
		{
			player->bombs[i]->render();
		}
	}

	if(gravityBomb)
	{
		gravityBombPortal->setOrientation(Quaternion((float)frameCount,false,false,true));
		gravityBombPortal->render();
	}
	if(stateInfo.subState == STATE_LEVEL4 && stateInfo.bossState == STATE_NO_BOSS)
	{
		ShaderProgram::unbindShaders();
		scrollingTexHor2_program->useProgram();
		glUniform1i(scrollHor2_tex_uniform,0);
		glUniform1f(scrollHor2_time_uniform,this->totalTime);
		glUniform1f(scrollHor2_speed_uniform,10);
		tropical_fog->setPosition(-2900,-2490,0);
		tropical_fog->draw();
		/*tropical_fog->setPosition(-1500,0,0);
		tropical_fog->draw();
		tropical_fog->setPosition(-3000,0,0);
		tropical_fog->draw();
		tropical_fog->setPosition(0,-1500,0);
		tropical_fog->draw();*/
		ShaderProgram::unbindShaders();
	}
	//DrawWaterEffect();
	DrawHUD();
	}

	else if (stateInfo.gameState == STATE_LEVELSELECT)
	{
		
		for (int i=0; i<4; i++)
		{
			level_border[i].render();
		}
		player->render();
		scrollingTexHor_program->useProgram();
		glUniform1i(scrollHor_tex_uniform,0);
		glUniform1f(scrollHor_time_uniform,this->totalTime);
		glUniform1f(scrollHor_speed_uniform,10);

		currentLevel->render();
		ShaderProgram::unbindShaders();
		portals[0]->render();
		for(int i = 1; i<5; i++)
		{
			if(levelsCleared[i-1])
			{
				portals[i]->render();
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
				trail[i].draw(1);
			}
		}
		glEnd();
		glPopMatrix();
	}

	else if(stateInfo.gameState == STATE_CUTSCENE)
	{
		if(stateInfo.subState == STATE_CUTSCENE1)
		{
		player->render();
		scrollingTexHor_program->useProgram();
		glUniform1i(scrollHor_tex_uniform,0);
		glUniform1f(scrollHor_time_uniform,this->totalTime);
		glUniform1f(scrollHor_speed_uniform,10);
		currentLevel->render();
		ShaderProgram::unbindShaders();
		}

		else if(stateInfo.subState == STATE_CUTSCENE2)
		{
			iceBoss->render();
			currentLevel->render();
		}

		else if(stateInfo.subState == STATE_CUTSCENE3)
		{

			player->render();
			currentLevel->render();
		}
	}
	
	glColor4f(1,1,1,1);
	
		  
	/*glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	//glDisable(GL_LIGHTING);
	
	
	/*glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);*/
}

/*
 * PostDraw()
 *  - in here you should clean up and set up things for the next frame
 *  - i.e. once I've used my assets, I can change them to set up things for
 *    the next frame, usually just memory management or setting up game state 
 *    boolean values etc.  
 */
void Game::PostDraw()
{
	FrameBufferObj::unbindFBO();
	ShaderProgram::unbindShaders();
	if (this->stateInfo.gameState == STATE_SCORING)
	{
		//glutSwapBuffers();
	}

	else if (this->stateInfo.gameState == STATE_GAMEPLAY)
	{
		this->checkBullets();
		this->checkMissiles();
		this->checkFire();
		this->checkWater();
		this->checkEnemies();
		this->checkPlayer();
		this->checkBombs();
		this->checkPowerups();
		this->checkSpawners();
		this->checkHealthDrops();
		this->checkExplosions();
		if (this->stateInfo.subState == STATE_LEVEL1)
		{
			this->checkAsteroids();
		}
	}
	else if (this->stateInfo.gameState == STATE_LEVELSELECT)
	{
		this->checkPlayer();
	}
	/*FrameBufferObj::unbindFBO();
	ShaderProgram::unbindShaders();*/
}

/* drawSprites()
 * - THIS IS WHERE MENU
 */
void Game::drawSprites()
{
	
}


/*Reload()
This is used for when a player loses all their lives
It returns to the main menu and resets all inventory
It also redraws the tokens and the destructible boxes*/
void Game::Reload()
{
}

/*softReload()
This is used for when a player loses all their lives
It resets the player's position inventory except for lives
It also redraws the tokens and the destructible boxes*/
void Game::softReload()
{
	
}

/* 
 * addSpriteToDrawList()
 * - this function simply pushes the sprite to the end of the list
 */
void Game::addSpriteToDrawList()
{
}

/*Removes the sprite from the draw list*/
void Game::removeSpriteFromDrawList()
{
}


void Game::quickSortPowerups()
{
	if(player->powerups.size() > 1)
	{
		int pivot;
		int temp = player->powerups[0];
		player->powerups[0] = player->powerups[floor((player->powerups.size()-1)/2.0)];
		player->powerups[floor((player->powerups.size()-1)/2.0)] = temp;
		pivot = player->powerups[0];
		int s_i = 0;

		for(int i=1; i<player->powerups.size(); i++)
		{
			if(player->powerups[i] < pivot)
			{
				if(s_i < player->powerups.size() && i < player->powerups.size())
				{
					s_i++;
				int temp2 = player->powerups[s_i];
				player->powerups[s_i] = player->powerups[i];
				player->powerups[i] = temp2;
					//s_i++;
				}
			}
		int temp3 = player->powerups[0];
		player->powerups[0] = player->powerups[s_i];
		player->powerups[s_i] = temp3;

		for (int i=0; i<(s_i-1); i++)
		{
			for (int j=(i+1); j<s_i; j++)
			{
				if(player->powerups[j] < player->powerups[i])
				{
					int temp4 = player->powerups[j];
						player->powerups[j] = player->powerups[i];
					player->powerups[i] = temp4;
					}
				}
			}
		}
		for (int i=(s_i+1); i<(player->powerups.size()-1); i++)
		{
			for (int j=(i+1); j<player->powerups.size(); j++)
			{
				if(j < player->powerups.size() && i < player->powerups.size())
				{
					if(player->powerups[j] < player->powerups[i])
					{
					int temp5 = player->powerups[j];
						player->powerups[j] = player->powerups[i];
					player->powerups[i] = temp5;
					}
				}
			}
		}
	}
}