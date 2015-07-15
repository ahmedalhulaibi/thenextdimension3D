#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include "Shader.h"
#include "ShaderProgram.h"
#include "Matrix33.h"
#include "Quaternion.h"
#include "Vector.h"
#include "Explosion.h"
#include "Model.h"
#include "Box.h"
#include "Player.h"
#include "Powerup.h"
#include <OpenGL\glut.h>
#include "Sprite.h"
#include <IL\il.h>
#include <IL\ilu.h>
#include <IL\ilut.h>
#include "SFML\Window.hpp"
#include "EnemyBase.h"
#include "ParticlePoint.h"
#include "Boss.h"
#include <string>
#include <sstream>
#include "Tree.h"
#include "Asteroid.h"
#include "FrameBufferObj.h"
#include "menuPage.h"
#include "Spring.h"
#include "Spawner.h"
#include "Sound.h"
#include "SoundEngine.h"
#include "Listener.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* these are enumerated types (just names) of game states
   that the game can be in at any moment.  These help you
   manage the flow of the game.  Especially if you want 
   to do different updates (call different update functions)
   or have different behaviour for input (i.e. mouse and keyboard
   functions might have different behaviour in-game (STATE_GAMEPLAY)
   versus when in the Menu (STATE_MAINMENU)
*/
enum GAME_STATE{
	STATE_GAMEPLAY = 0,
	STATE_MAINMENU,
	STATE_MENU,
	STATE_PAUSED,
	STATE_CREDITS,
	STATE_CUTSCENE,
	STATE_LEVELSELECT,
	STATE_SCORING,
	STATE_CONTROLS,
	STATE_SETTINGS,
	STATE_HOWTOPLAY
};

enum SUB_STATE{
	STATE_HUB = 0,
	STATE_LEVEL1,
	STATE_LEVEL2,
	STATE_LEVEL3,
	STATE_LEVEL4,
	STATE_LEVEL5,
	STATE_LEVEL6,
	STATE_CUTSCENE1,
	STATE_CUTSCENE2,
	STATE_CUTSCENE3
};

enum BOSS_STATE{
	STATE_NO_BOSS = 0,
	STATE_BOSS1,
	STATE_BOSS2,
	STATE_BOSS3,
	STATE_BOSS4,
	STATE_BOSS5
};

enum SCREEN_STATE{
	STATE_KEYMAP,
	STATE_MAIN_SETTINGS,
	STATE_PAUSE_SETTINGS,
	STATE_HUB_PAUSE,
	STATE_GAMEPLAY_PAUSE
};


// input information related to mouse
// you could add keyboard info in here too if you need to know if a key is currently pressed down
typedef struct _InputInfo
{
	bool mouseDown; // is the mouse down?
	int button; // which mouse button
	GLdouble clickX,clickY, clickZ; // where the mouse was clicked
	float currentX,currentY;

	int missiles_key;
	int flamethrower_key;
	int watergun_key;
	int up_key;
	int down_key;
	int right_key;
	int left_key;
	int switchpowerup_key;
	int pause_key;
	int boost_key;
	int elevateup_key;
	int elevatedown_key;
	int camera_key;
	int usePowerup_key;
	//for keymapping
	int *selectedAction;

	bool NUMKEY_1;
	bool NUMKEY_2;
	bool NUMKEY_3;
	bool LeftKeyDown;
	bool RightKeyDown;
	bool UpKeyDown;
	bool DownKeyDown;
	bool W_KeyDown;
	bool A_KeyDown;
	bool S_KeyDown;
	bool D_KeyDown;
	bool R_KeyDown;
	bool F_KeyDown;
	bool P_KeyDown;
	bool Y_KeyDown;
	bool N_KeyDown;
	bool BackSlash_Down;
	bool SpaceBar_Down;
	bool ReturnKeyDown;
	bool TabKeyDown;
	bool tilde;

	bool LeftButtonDown;
	bool MiddleButtonDown;
	bool RightButtonDown;

	unsigned int MouseX;
	unsigned int MouseY;

}InputInfo;

// convenience structure to hold rgb values
typedef struct _RGBColor
{
	float red,green,blue;
}RGBColor;

// GameStateInfo
// this stores anything related to the state of the game
// i.e. what level are we on?, what is the score? etc.
typedef struct _GameStateInfo
{
	int gameState; // the game state, see enum's above
	int subState;  //sub-game state, used for levels and cutscenes
	int bossState;
	int menuState;
	int screenState;
	RGBColor bgClearColor; // the default clear color of the background

	// window width/height are the actual size of the window
	int windowWidth, windowHeight;
	
	// screen width/height are the apparent size of the window
	// i.e. you can have a 640x480 game screen stretched to 1280x1024
	// your calculations for actual pixel locations will depend on the ratio
	//   between screen and window width/height
	int screenWidth, screenHeight;

	int midScreenX, midScreenY;

	float aspect;
	bool keymap;
}GameStateInfo;

typedef struct {
    float x, y, z;    // position
    float s, t;       // texture
    float r, g, b, a; // color
} vertex_t;

struct healthDrop
{
	Vector desiredVel, acceleration, velocity, position;
	float mass;
	float max_speed;
	healthDrop(Vector &pos)
	{
		position = pos;
	}
	void seek(Vector &pos,float dT)
	{
		desiredVel = pos.subVector(position);
		desiredVel.normalize();
		desiredVel.multiplyVector(this->max_speed);
		desiredVel.subtractVector(velocity);
		desiredVel.multiplyVector(1/mass);
		this->acceleration = desiredVel;
		acceleration.multiplyVector(dT +0.7);
		this->velocity.addVector(acceleration);
		this->position.addVector(velocity);
	};
	void draw()
	{
		glColor4f(0,1,0.5,((float)rand()/(float)RAND_MAX)+0.000001);
		glVertex3f(position.X_Y_Z[0],position.X_Y_Z[1],position.X_Y_Z[2]);
		//glVertex3f(position.X_Y_Z[0]+0.1,position.X_Y_Z[1],position.X_Y_Z[2]);
		//glVertex3f(position.X_Y_Z[0]+0.1,position.X_Y_Z[1]+0.1,position.X_Y_Z[2]);
		//glVertex3f(position.X_Y_Z[0],position.X_Y_Z[1]+0.1,position.X_Y_Z[2]);
		//glVertex3f(position.X_Y_Z[0]-0.1,position.X_Y_Z[1]+0.1,position.X_Y_Z[2]);
		//glVertex3f(position.X_Y_Z[0]-0.1,position.X_Y_Z[1],position.X_Y_Z[2]);
		//glVertex3f(position.X_Y_Z[0]-0.1,position.X_Y_Z[1]-0.1,position.X_Y_Z[2]);
		//glVertex3f(position.X_Y_Z[0],position.X_Y_Z[1]-0.1,position.X_Y_Z[2]);
		//glVertex3f(position.X_Y_Z[0]+0.1,position.X_Y_Z[1]-0.1,position.X_Y_Z[2]);
	};
};

/* 
 * Game.h
 * This is the main Game class of the base sprite lib starter code
 * it handles input, game loop update, display
 */
class Game
{
public:
	/* initialization */
	Game();
	~Game(void);
	void initializeGame();
	void initEnemies();
	void initBosses();
	void initLevels();
	void initSprites();
	void initHUD();
	void initSounds();
	void initSpawners();
	void initPlayer();
	/* LOCATED IN initializeShaders.cpp*/
	void initBloomShader();
	void initToonShader();
	void initScrollingTexShader();
	void initNormalMappingShader();

	/* convenience functions */
	// screen size is the apparent size in pixels
	// i.e. this is what your game calculations should use
	void setScreenSize(int w, int h)
	{
		stateInfo.screenWidth = w;
		stateInfo.screenHeight = h;
		stateInfo.midScreenX = stateInfo.screenWidth/2;
		stateInfo.midScreenY = stateInfo.screenHeight/2;

	}
	// sets the screen-to-window pixel coordinates ratio
	void updateScreenRatio()
	{
		stateInfo.aspect = ((float)stateInfo.windowWidth/(float)stateInfo.windowHeight);
		/* these are only really used for the mouse function
		   to get actual screen pixel coordinates from the window coordinates */
	}

	// sets the window size in pixels for the window itself
	void setNewWindowSize(int width,int height)
	{
		stateInfo.windowWidth = width;
		stateInfo.windowHeight = height;
	}

	// add a sprite to the draw list
	// only sprites in the draw list will be drawn
	void addSpriteToDrawList();
	void removeSpriteFromDrawList();

	/* draw/rendering routines */
	void draw(); // called from the main

	void PreDraw(); // prior to drawing
	void DrawGame(); // actual drawing the frame
	void PostDraw(); // cleanup and prepare for next frame

	void DrawHUD();
	void drawParticles();
	void drawLevelWalls();
	
	void drawSprites(); // draw the sprite list
	void drawTestPrimitives(); // test function

	

	//reloading functions to reload sprites and inventory
	void Reload();
	void softReload();

	/* update routines, the game loop */
	void update(); // called from main frequently
	bool checkSphericalCollision(Model *, Model *);
	bool checkSphericalCollision(Model *, EnemyBase *);
	bool checkSphericalCollision(EnemyBase *, EnemyBase *);
	bool checkBoxCollision(Model *, Model *);
	bool checkIfWillCollide(Model *, Model *, Vector position);
	int checkBoxQuadrant(Model *, Model *);

	/* Check collisions */
	void checkPlayerCollision();
	void checkEnemyCollision();
	void checkBulletCollision();
	void checkPowerupCollision();
	void checkAsteroidCollision();
	void checkSpawnerCollision();
	void checkFire();
	void checkWater();
	void checkMissiles();
	void checkBullets();
	void checkBombs();
	void checkEnemies();
	void checkPlayer();
	void checkPowerups();
	void checkHealthDrops();
	void checkExplosions();
	void checkBossBullets();
	void checkAsteroids();
	void checkSpawners();
	void updateBosses();

	void spawnEnemies();

	/* input callback functions */
	void updateInput();
	void keyboardInput();
	void mouseInput();
	void joystickInput();
	void mouseMoved(int x, int y);
	void mouseHover(int x, int y);
	void defaultKeys();

	/* Handle level-specific information */
	void loadLevel();
	void reloadEnemies();
	void exitLevel();

	void quickSortPowerups();
	
	/*********************************/
	/* DATA */
	/*********************************/

	/* thing user presses before gameplay */

	/* game state info */
	GameStateInfo stateInfo;
	float elapsedTime;

	GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;

	/* individual sprites to manipulate by name, 
	their corresponding bounding boxes for collision,
	and positions of boxes and tokens to be used for loading positions from a text file*/
	//Player sprite and the player sprite's bounding box


	/* Audio objects */
	

	InputInfo input;
	
	bool isClicked;
	bool isAnimating;
	bool exitClick;

	/*SPRITES*/
	
	Sprite *testSprite;
	Sprite *water_overlay;

	menuPage *mainMenu;
	menuPage *settingsMenu;
	menuPage *creditsMenu;
	menuPage *pauseMenu;
	menuPage *controlsMenu;
	menuPage *controllerMenu;
	menuPage *howtoplayMenu;

	Sprite *newGame_Button;
	Sprite *settings_Button;
	Sprite *credits_Button;
	Sprite *exit_Button;
	Sprite *howtoplay_Button;

	//now fullscreen button
	Sprite *audio_Button;
	Sprite *controls_Button;
	Sprite *back_Button;

	Sprite *resume_Button;
	Sprite *hub_Button;

	Player *player;
	Vector player_lastPos;
	Player *player_collider;
	EnemyBase *enemy1_base;
	EnemyBase *enemy1_collider;
	EnemyBase *enemy2_base;
	EnemyBase *enemy2_collider;
	EnemyBase *enemy3_base;
	EnemyBase *enemy3_collider;
	EnemyBase *enemy4_base;
	EnemyBase *enemy4_collider;
	EnemyBase *enemy5_base;
	EnemyBase *enemy5_collider;

	Powerup* powerups_init[5];

	Boss *spaceBoss, *desertBoss, *oceanBoss, *tropicalBoss, *iceBoss, *lavaBoss;
	Boss *spaceBoss_collider, *desertBoss_collider, *oceanBoss_collider, *tropicalBoss_collider, *iceBoss_collider, *lavaBoss_collider;
	float totalTime;
	Asteroid *asteroid;
	vector <Asteroid*> asteroids;

	vector <EnemyBase*> enemies;
	vector <EnemyBase*> spheres;
	vector <Powerup*> powerups;
	vector <Powerup*> blackhole;
	vector <healthDrop> healthDrops;
	vector <Explosion> explosions;
	vector <Explosion> wall_explosions;
	vector <ParticlePoint> trail;
	Model *portals[5];
	Model *gravityBombPortal;
	Model bullet, fire, water, missile, bomb;
	Model *currentLevel;
	Model levels[6];
	Model *desert_Things, *ocean_Things, *tropical_Things;
	bool levelsCleared[5];
	int waves_num;
	int currentID;

	Tree t;

	Box border_box_vert, border_box_hori;
	Box box_vert, box_hori;
	Box level_border[4];
	Box walls_level1[6];
	Box box_verthori, box_horivert, box_vert2;
	Box walls_level2[6];
	Box box_vert3, box_vert4, box_hori2;
	Box walls_level3[8];
	Box box_hori3, box_hori4;
	Box walls_level5[14];
	Spawner spawner_level1, spawner_level2, spawner_level3, spawner_level4, spawner_level5;
	vector <Spawner*> spawners;

	Model main_menu;
	Model pause_screen;
	Model select_screen;

	bool missiles;
	bool flamethrower;
	bool waterGun;

	bool freezeEnemies;
	int freezeTime;

	bool playerSpeedUp;
	int speedUpTime;

	bool slowDown;
	int slowDownTime;
	int slowDown_num;

	bool gravityBomb;
	int gravityBombTime;

	vector <Vector*> cutscene1;
	float cutscene1_dt[4];
	int cutsceneIT;
	vector <Vector*> cutscene2;
	vector <Vector*> cutscene3;
	float speedControl_1[4];
	bool cuts3;

	bool returnK;
	

	//custom keymapping
	void updateActionKeys();
	void resetKeys();

	
float camX, camY, camZ;
Vector camPos;
int frameCount, frame, click, it, invi_frames,perspective;
bool startSLERP, invincible, fired, switched, middleClicked, pressed, selected, pushed;
char delay;
Spring camSpring;


	/************************************SHADER STUFF**********************************/	
	void loadImage(string filename, Texture &texture)
	{
			LoadTGA(&texture, (char *)filename.c_str());
		glGenTextures(1, &texture.texID);
		glBindTexture(GL_TEXTURE_2D, texture.texID);
		glTexImage2D(GL_TEXTURE_2D, 0, texture.bpp / 8, 
			texture.width, texture.height, 0,
			texture.type,GL_UNSIGNED_BYTE,texture.imageData);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
		if(texture.imageData)
		{
			free(texture.imageData);
		}
	};

	/*BLOOM SHADER STUFF*/
	FrameBufferObj *scenePass, *brightPass,*blurPass1, *blurPass2;
	Shader *brightPass_f, *passThroughTex_v,*composite_f,*gaussV_f, *gaussH_f;
	ShaderProgram *brightPass_Program,*composite_Program, *gaussV_Program, *gaussH_Program;
	int brightPass_uniform1;
	int composite_uniform1, composite_uniform2, composite_uniform_gamma;
	int gaussV_uniform1, gaussV_uniform2;
	int gaussH_uniform1, gaussH_uniform2;
	float gamma;

	/*TOON SHADER STUFF*/
	FrameBufferObj *toonPass;
	Shader *toon_v, *toon_f, *edges_f;
	ShaderProgram *toon_program,*edges_program;
	int toon_inImg_uniform, toon_inQmap_uniform,
				 edges_inCol_uniform,edges_inNorm_uniform,edges_inDepth_uniform,edges_pixSize_uniform;
	Texture ramp;

	/*SCROLLING TEXTURE*/
	Shader *scrollTexHor_f, *scrollTexHor2_f;
	ShaderProgram *scrollingTexHor_program, *scrollingTexHor2_program;
	int scrollHor_tex_uniform,scrollHor_time_uniform,scrollHor_speed_uniform;
	int scrollHor2_tex_uniform,	scrollHor2_time_uniform, scrollHor2_speed_uniform;

	/*NORMAL MAPPING*/
	Shader *objectNormalMap_v, *objectNormalMap_f;
	ShaderProgram *normalMapping_program;
	int diffuseMap_uniform, normalMap_uniform;
	Texture normalMap;

	/*---------------------------------------------------HUD------------------------------------------------*/
	Model boostBar;
	Model healthBar;
	Model shieldBar;
	Model fireFuelBar;
	Model waterFuelBar;
	int score;
	stringstream ss;
	string s;

	Sprite *gravityBomb_HUD;
	Sprite *shield_HUD;
	Sprite *freezeTime_HUD;
	Sprite *slowDown_HUD;
	Sprite *speedUp_HUD;

	Sprite *fireBar_HUD, *fireDrop_HUD;
	Sprite *healthBlock_HUD[10];
	Sprite *waterBar_HUD, *waterDrop_HUD;
	Sprite *shieldBar_HUD;
	Sprite *boostBar_HUD;
	Sprite *freezeTimeBar_HUD;
	Sprite *shieldTimeBar_HUD;
	Sprite *slowTimeBar_HUD;
	Sprite *speedTimeBar_HUD;

	Sprite *tropical_fog;



	/*********************************************SOUNDS****************************************/
	SoundEngine *soundSystem;
	Sound *introDialogue, *gameMusic, *menuClick, *hubMusic;
	Sound *finalBoss_dialogue;
	Sound *slowDownTime_begin;
	Sound *slowDownTime_end;
	Sound *powerup_pickUp;
	Vector zeroVector;
};
