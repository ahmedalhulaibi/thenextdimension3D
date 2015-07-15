#include "Game.h"
using namespace std;
void Game::defaultKeys()
{
	input.missiles_key = int(sf::Keyboard::Num1);
	input.flamethrower_key = int(sf::Keyboard::Num2);
	input.watergun_key = int(sf::Keyboard::Num3);
	input.up_key = int(sf::Keyboard::W);
	input.down_key = int(sf::Keyboard::S);
	input.right_key = int(sf::Keyboard::D);
	input.left_key = int(sf::Keyboard::A);
	input.usePowerup_key = int(sf::Keyboard::LShift);
	input.switchpowerup_key = int(sf::Keyboard::Tab);
	input.pause_key = int(sf::Keyboard::P);
	input.boost_key = int(sf::Keyboard::Space);
	input.elevateup_key = int(sf::Keyboard::R);
	input.elevatedown_key = int(sf::Keyboard::F);
	input.camera_key = int(sf::Keyboard::BackSlash);
	stateInfo.keymap = false;
}

void Game::initHUD()
{
	/*water_overlay = new Sprite("images/waterFilter_v2.png", 3200, 1800);
	water_overlay->setPosition(-1600,-900,0);
	water_overlay->setNumberOfAnimations(1);
	water_overlay->setSpriteFrameSize(3200, 1800);
	water_overlay->addSpriteAnimFrame(0,0,0);
	water_overlay->currentFrame = 0;*/

	gravityBomb_HUD = new Sprite("images/HUD/HUD_GravityBomb.png",112,112);
	gravityBomb_HUD->setNumberOfAnimations(1);
	gravityBomb_HUD->setSpriteFrameSize(112,112);
	gravityBomb_HUD->setPosition(-56.25,-750,0);
	gravityBomb_HUD->addSpriteAnimFrame(0,0,0);
	gravityBomb_HUD->setCurrentAnimation(0);
	gravityBomb_HUD->currentFrame = 0;

	shield_HUD= new Sprite("images/HUD/HUD_Powerup_Shield.png",112,112);
	shield_HUD->setNumberOfAnimations(1);
	shield_HUD->setSpriteFrameSize(112,112);
	shield_HUD->setPosition(-56.25,-750,0);
	shield_HUD->addSpriteAnimFrame(0,0,0);
	shield_HUD->setCurrentAnimation(0);
	shield_HUD->currentFrame = 0;

	freezeTime_HUD= new Sprite("images/HUD/HUD_FreezeTime.png",112,112);
	freezeTime_HUD->setNumberOfAnimations(1);
	freezeTime_HUD->setSpriteFrameSize(112,112);
	freezeTime_HUD->setPosition(-56.25,-750,0);
	freezeTime_HUD->addSpriteAnimFrame(0,0,0);
	freezeTime_HUD->setCurrentAnimation(0);
	freezeTime_HUD->currentFrame = 0;

	slowDown_HUD= new Sprite("images/HUD/HUD_SlowDown.png",112,112);
	slowDown_HUD->setNumberOfAnimations(1);
	slowDown_HUD->setSpriteFrameSize(112,112);
	slowDown_HUD->setPosition(-56.25,-750,0);
	slowDown_HUD->addSpriteAnimFrame(0,0,0);
	slowDown_HUD->setCurrentAnimation(0);
	slowDown_HUD->currentFrame = 0;

	speedUp_HUD= new Sprite("images/HUD/HUD_SpeedUP.png",112,112);
	speedUp_HUD->setNumberOfAnimations(1);
	speedUp_HUD->setSpriteFrameSize(112,112);
	speedUp_HUD->setPosition(-56.25,-750,0);
	speedUp_HUD->addSpriteAnimFrame(0,0,0);
	speedUp_HUD->setCurrentAnimation(0);
	speedUp_HUD->currentFrame = 0;
	
	fireBar_HUD= new Sprite("images/HUD/HUD_FireBar.png",197,38);
	fireBar_HUD->setNumberOfAnimations(1);
	fireBar_HUD->setSpriteFrameSize(197,38);
	fireBar_HUD->setPosition(-1370,-750,0);
	fireBar_HUD->addSpriteAnimFrame(0,0,0);
	fireBar_HUD->setCurrentAnimation(0);
	fireBar_HUD->currentFrame = 0;

	fireDrop_HUD= new Sprite("images/HUD/HUD_FireDrop.png",58,79);
	fireDrop_HUD->setNumberOfAnimations(1);
	fireDrop_HUD->setSpriteFrameSize(58,79);
	fireDrop_HUD->setPosition(-1427,-750,1);
	fireDrop_HUD->addSpriteAnimFrame(0,0,0);
	fireDrop_HUD->setCurrentAnimation(0);
	fireDrop_HUD->currentFrame = 0;

	for(int i = 0; i < 10; i++)
	{
		healthBlock_HUD[i]= new Sprite("images/HUD/HUD_HealthBlock.png",38,44);
		healthBlock_HUD[i]->setNumberOfAnimations(1);
		healthBlock_HUD[i]->setSpriteFrameSize(38,44);
		healthBlock_HUD[i]->setPosition(900+(i*38),-750,0);
		healthBlock_HUD[i]->addSpriteAnimFrame(0,0,0);
		healthBlock_HUD[i]->setCurrentAnimation(0);
		healthBlock_HUD[i]->currentFrame = 0;
	}
	
	waterBar_HUD= new Sprite("images/HUD/HUD_WaterBar.png",197,38);
	waterBar_HUD->setNumberOfAnimations(1);
	waterBar_HUD->setSpriteFrameSize(197,38);
	waterBar_HUD->setPosition(-1370,-750,0);
	waterBar_HUD->addSpriteAnimFrame(0,0,0);
	waterBar_HUD->setCurrentAnimation(0);
	waterBar_HUD->currentFrame = 0;
	
	waterDrop_HUD= new Sprite("images/HUD/HUD_WaterDrop.png",58,79);
	waterDrop_HUD->setNumberOfAnimations(1);
	waterDrop_HUD->setSpriteFrameSize(58,79);
	waterDrop_HUD->setPosition(-1427,-750,1);
	waterDrop_HUD->addSpriteAnimFrame(0,0,0);
	waterDrop_HUD->setCurrentAnimation(0);
	waterDrop_HUD->currentFrame = 0;
	
	shieldBar_HUD= new Sprite("images/HUD/HUD_ShieldBarHealth.png",380,28);
	shieldBar_HUD->setNumberOfAnimations(1);
	shieldBar_HUD->setSpriteFrameSize(380,28);
	shieldBar_HUD->setPosition(895,-705,1);
	shieldBar_HUD->addSpriteAnimFrame(0,0,0);
	shieldBar_HUD->setCurrentAnimation(0);
	shieldBar_HUD->currentFrame = 0;

	shieldTimeBar_HUD = new Sprite("images/HUD/HUD_ShieldBar.png",165,20);
	shieldTimeBar_HUD->setNumberOfAnimations(1);
	shieldTimeBar_HUD->setSpriteFrameSize(165,20);
	shieldTimeBar_HUD->setPosition(-82.5,-770,0);
	shieldTimeBar_HUD->addSpriteAnimFrame(0,0,0);
	shieldTimeBar_HUD->setCurrentAnimation(0);
	shieldTimeBar_HUD->currentFrame = 0;

	boostBar_HUD= new Sprite("images/HUD/HUD_BoostBar.png",197,28);
	boostBar_HUD->setNumberOfAnimations(1);
	boostBar_HUD->setSpriteFrameSize(197,28);
	boostBar_HUD->setPosition(-1370,-720,1);
	boostBar_HUD->addSpriteAnimFrame(0,0,0);
	boostBar_HUD->setCurrentAnimation(0);
	boostBar_HUD->currentFrame = 0;

	freezeTimeBar_HUD = new Sprite(*shieldTimeBar_HUD);
	freezeTimeBar_HUD->setNumberOfAnimations(1);
	freezeTimeBar_HUD->setSpriteFrameSize(165,20);
	freezeTimeBar_HUD->setPosition(-82.5,-770,0);
	freezeTimeBar_HUD->addSpriteAnimFrame(0,0,0);
	freezeTimeBar_HUD->setCurrentAnimation(0);
	freezeTimeBar_HUD->currentFrame = 0;

	slowTimeBar_HUD = new Sprite(*shieldTimeBar_HUD);
	slowTimeBar_HUD->setNumberOfAnimations(1);
	slowTimeBar_HUD->setSpriteFrameSize(165,20);
	slowTimeBar_HUD->setPosition(-82.5,-770,0);
	slowTimeBar_HUD->addSpriteAnimFrame(0,0,0);
	slowTimeBar_HUD->setCurrentAnimation(0);
	slowTimeBar_HUD->currentFrame = 0;

	speedTimeBar_HUD = new Sprite(*shieldTimeBar_HUD);
	speedTimeBar_HUD->setNumberOfAnimations(1);
	speedTimeBar_HUD->setSpriteFrameSize(165,20);
	speedTimeBar_HUD->setPosition(-82.5,-770,0);
	speedTimeBar_HUD->addSpriteAnimFrame(0,0,0);
	speedTimeBar_HUD->setCurrentAnimation(0);
	speedTimeBar_HUD->currentFrame = 0;
}

void Game::initEnemies()
{
	EnemyBase::initializeEnemyModels();
	EnemyBase::loadTexture();
	/*enemy1_base = new EnemyBase("Obj/Enemies/EnemyShip1/EnemyShip1.obj");
	enemy1_base->loadTexture("Obj/Enemies/EnemyShip1/EnemyShip1Texture.tga");
	enemy1_collider = new EnemyBase("Obj/Enemies/EnemyShip1/EnemyShip1_Hull.obj");*/
	/*enemy1_base->ID = ENEMY_SPACE;
	enemy1_collider->ID = ENEMY_SPACE;*/

	enemy1_base = new EnemyBase(ENEMY_SPACE);
	enemy1_collider = new EnemyBase(ENEMY_SPACE);
	enemy1_collider->loadCollisionDimensions(6);//special case
	enemy1_collider->setScale(0.2,0.2,0.2);
	enemy1_base->max_speed = 0.7;
	enemy1_base->health = 5;

	/*enemy2_base = new EnemyBase("Obj/Enemies/EnemyShip3/EnemyShip3.obj");
	enemy2_base->loadTexture("Obj/Enemies/EnemyShip3/Enemy_Model_3_BadUV_polySurfaceShape14.tga");*/
	enemy2_base = new EnemyBase(ENEMY_OCEAN);
	enemy2_base->max_speed = 0.7;
	enemy2_base->health = 6;
	enemy2_collider = new EnemyBase(*enemy1_collider);
	enemy2_base->ID = ENEMY_OCEAN;
	//enemy2_collider->ID = ENEMY_DESERT;

	/*enemy3_base = new EnemyBase("Obj/Enemies/EnemyShip2/EnemyShip2.obj");
	enemy3_base->loadTexture("Obj/Enemies/EnemyShip2/Enemy_Model_2_BadUV_2_polySurfaceShape11.tga");*/
	enemy3_base = new EnemyBase(ENEMY_DESERT);
	enemy3_collider = new EnemyBase(*enemy1_collider);
	enemy3_base->max_speed = 0.75;
	enemy3_base->health = 8;
	enemy3_base->ID = ENEMY_DESERT;
	//enemy3_collider->ID = ENEMY_OCEAN;

	//enemy4_base = new EnemyBase("Obj/Enemies/EnemyShip4/EnemyShip4.obj");
	//enemy4_base->loadTexture("Obj/Enemies/EnemyShip4/Enemy_Model_4_BadUV_polySurfaceShape8.tga");
	enemy4_base = new EnemyBase(ENEMY_TROPICAL);
	enemy4_collider = new EnemyBase(*enemy1_collider);
	enemy4_base->max_speed = 0.75;
	enemy4_base->health = 10;
	//enemy4_base->ID = ENEMY_TROPICAL;
	//enemy4_collider->ID = ENEMY_TROPICAL;

	/*enemy5_base = new EnemyBase("Obj/Enemies/EnemyShip5/EnemyShip5.obj");
	enemy5_base->loadTexture("Obj/Enemies/EnemyShip5/Enemy_Model_5_BadUV_polySurfaceShape8.tga");*/
	enemy5_base = new EnemyBase(ENEMY_ICE);
	enemy5_collider = new EnemyBase(ENEMY_ICE);
	enemy5_collider->loadCollisionDimensions(5);//special case
	enemy5_collider->setScale(0.2,0.2,0.2);
	enemy5_base->max_speed = 1.0;
	enemy5_base->health = 16;
	/*enemy5_base->ID = ENEMY_ICE;
	enemy5_collider->ID = ENEMY_ICE;*/
}

void Game::initBosses()
{
	spaceBoss = new Boss("Obj/Enemies/EnemyShip1/EnemyShip1.obj",400);
	spaceBoss->loadTexture("Obj/Enemies/EnemyShip1/EnemyShip1Texture.tga");
	spaceBoss->target1 = new Model("Obj/Enemies/EnemyShip1/EnemyShip1.obj");
	spaceBoss->target2 = new Model("Obj/Enemies/Boss1/SpaceBoss.obj");
	spaceBoss->setScale(0.25,0.25,0.25);
	spaceBoss->mass = 50;
	spaceBoss->max_speed = 0.5;
	spaceBoss->setSeekTarget(player);
	spaceBoss->ID = ENEMY_SPACE;
	spaceBoss_collider = new Boss("Obj/Enemies/EnemyShip1/EnemyShip1_Hull.obj",400);
	spaceBoss_collider->target1 = new Model("Obj/Enemies/EnemyShip1/EnemyShip1_Hull.obj");
	spaceBoss_collider->target1->setScale(0.11,0.11,0.11);
	spaceBoss_collider->target2 = new Model("Obj/Enemies/Boss1/SpaceBoss_Hull.obj");
	spaceBoss_collider->setScale(1.75,1.75,1.75);
	spaceBoss_collider->position = spaceBoss->position;

	oceanBoss = new Boss("Obj/Enemies/EnemyShip3/EnemyShip3.obj",600);
	oceanBoss->loadTexture("Obj/Enemies/EnemyShip3/Enemy_Model_3_BadUV_polySurfaceShape14.tga");
	oceanBoss->target1 = new Model("Obj/Enemies/EnemyShip3/EnemyShip3.obj");
	oceanBoss->target2 = new Model("Obj/Enemies/Boss3/OceanBoss.obj");
	oceanBoss->setScale(0.25,0.25,0.25);
	oceanBoss->mass = 50;
	oceanBoss->max_speed = 0.55;
	oceanBoss->setSeekTarget(player);
	oceanBoss->ID = ENEMY_OCEAN;
	oceanBoss_collider = new Boss(*spaceBoss_collider);

	desertBoss = new Boss("Obj/Enemies/EnemyShip2/EnemyShip2.obj",800);
	desertBoss->loadTexture("Obj/Enemies/EnemyShip2/Enemy_Model_2_BadUV_2_polySurfaceShape11.tga");
	desertBoss->target1 = new Model("Obj/Enemies/EnemyShip2/EnemyShip2.obj");
	desertBoss->target2 = new Model("Obj/Enemies/Boss2/DesertBoss.obj");
	desertBoss->setScale(0.25,0.25,0.25);
	desertBoss->mass = 50;
	desertBoss->max_speed = 0.6;
	desertBoss->setSeekTarget(player);
	desertBoss->ID = ENEMY_DESERT;
	desertBoss_collider = new Boss(*spaceBoss_collider);

	tropicalBoss = new Boss("Obj/Enemies/EnemyShip4/EnemyShip4.obj",1000);
	tropicalBoss->loadTexture("Obj/Enemies/EnemyShip4/Enemy_Model_4_BadUV_polySurfaceShape8.tga");
	tropicalBoss->target1 = new Model("Obj/Enemies/EnemyShip4/EnemyShip4.obj");
	tropicalBoss->target2 = new Model("Obj/Enemies/Boss4/TropicalBoss.obj");
	tropicalBoss->setScale(0.25,0.25,0.25);
	tropicalBoss->mass = 50;
	tropicalBoss->max_speed = 0.65;
	tropicalBoss->setSeekTarget(player);
	tropicalBoss->ID = ENEMY_TROPICAL;
	tropicalBoss_collider = new Boss(*spaceBoss_collider);

	iceBoss = new Boss("Obj/Enemies/EnemyShip5/EnemyShip5.obj",1500);
	iceBoss->loadTexture("Obj/Enemies/EnemyShip5/Enemy_Model_5_BadUV_polySurfaceShape8.tga");
	iceBoss->target1 = new Model("Obj/Enemies/EnemyShip5/EnemyShip5.obj");
	iceBoss->target2 = new Model("Obj/Enemies/Boss5/IceBoss.obj");
	iceBoss->setScale(0.25,0.25,0.25);
	iceBoss->mass = 50;
	iceBoss->max_speed = 0.7;
	iceBoss->setSeekTarget(player);
	iceBoss->ID = ENEMY_ICE;
	iceBoss_collider = new Boss("Obj/Enemies/EnemyShip5/EnemyShip5_Hull.obj",1500);
	iceBoss_collider->target1 = new Model("Obj/Enemies/EnemyShip5/EnemyShip5_Hull.obj");
	iceBoss_collider->target1->setScale(0.11,0.11,0.11);
	iceBoss_collider->target2 = new Model("Obj/Enemies/Boss5/IceBoss_Hull.obj");
	iceBoss_collider->setScale(1.75,1.75,1.75);
	iceBoss_collider->position = iceBoss->position;

}

void Game::initLevels()
{
	levelsCleared[0] = true;
	levelsCleared[1] = true;
	for(int i = 0; i<5; i++)
	{
		levelsCleared[i] = true;
	}

	border_box_vert = Box("Obj/Box.obj", false);
	border_box_vert.setScale(12,30,1);
	border_box_vert.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");
	border_box_hori = Box("Obj/Box.obj", true);
	border_box_hori.setScale(12,36,1);
	border_box_hori.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");

	level_border[0] = Box(border_box_vert);
	level_border[0].position = Vector(-177.1, 0, 0);
	level_border[1] = Box(border_box_vert);
	level_border[1].position = Vector(177.1, 0, 0);
	level_border[2] = Box(border_box_hori);
	level_border[2].position = Vector(0, -180.3, 0);
	level_border[3] = Box(border_box_hori);
	level_border[3].position = Vector(0, 180.3, 0);

	box_vert = Box("Obj/Box.obj", false);
	box_vert.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");
	box_vert.setScale(2,2,1);
	box_hori = Box("Obj/Box.obj", true);
	box_hori.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");
	box_hori.setScale(2,8,1);

	walls_level1[0] = Box(box_vert);
	walls_level1[0].position = Vector(40.3, 33.2, 0);
	walls_level1[1] = Box(box_hori);
	walls_level1[1].position = Vector(0, 47, 0);
	walls_level1[2] = Box(box_vert);
	walls_level1[2].position = Vector(-40.3, 33.2, 0);
	walls_level1[3] = Box(box_vert);
	walls_level1[3].position = Vector(40.3, -33.2, 0);
	walls_level1[4] = Box(box_hori);
	walls_level1[4].position = Vector(0, -47, 0);
	walls_level1[5] = Box(box_vert);
	walls_level1[5].position = Vector(-40.3, -33.2, 0);

	box_verthori = Box("Obj/Box.obj", false);
	box_verthori.setScale(2,1.5,1);
	box_verthori.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");
	box_horivert = Box("Obj/Box.obj", true);
	box_horivert.setScale(2,2,1);
	box_horivert.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");
	box_vert2 = Box("Obj/Box.obj", false);
	box_vert2.setScale(2.5,5,1);
	box_vert2.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");

	walls_level2[0] = Box(box_horivert);
	walls_level2[0].position = Vector(-102.9, -48.9, 0);
	walls_level2[1] = Box(box_verthori);
	walls_level2[1].position = Vector(-95, -60, 0);
	walls_level2[2] = Box(box_vert2);
	walls_level2[2].position = Vector(-35, 30, 0);
	walls_level2[3] = Box(box_vert2);
	walls_level2[3].position = Vector(35, -30, 0);
	walls_level2[4] = Box(box_verthori);
	walls_level2[4].position = Vector(95, 65, 0);
	walls_level2[5] = Box(box_horivert);
	walls_level2[5].position = Vector(102.9, 53.9, 0);

	box_vert3 = Box("Obj/Box.obj", false);
	box_vert3.setScale(3,3,1);
	box_vert3.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");
	box_vert4 = Box("Obj/Box.obj", false);
	box_vert4.setScale(2,4,1);
	box_vert4.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");
	box_hori2 = Box("Obj/Box.obj", true);
	box_hori2.setScale(1.5,3,1);
	box_hori2.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");

	walls_level3[0] = Box(box_vert3);
	walls_level3[0].position = Vector(-25, 50, 0);
	walls_level3[1] = Box(box_vert3);
	walls_level3[1].position = Vector(25, 50, 0);
	walls_level3[2] = Box(box_vert4);
	walls_level3[2].position = Vector(-100, 0, 0);
	walls_level3[3] = Box(box_vert4);
	walls_level3[3].position = Vector(100, 0, 0);
	walls_level3[4] = Box(box_vert3);
	walls_level3[4].position = Vector(-25, -50, 0);
	walls_level3[5] = Box(box_vert3);
	walls_level3[5].position = Vector(25, -50, 0);
	walls_level3[6] = Box(box_hori2);
	walls_level3[6].position = Vector(0, 25, 0);
	walls_level3[7] = Box(box_hori2);
	walls_level3[7].position = Vector(0, -25, 0);

	box_hori3 = Box("Obj/Box.obj", true);
	box_hori3.setScale(2,6,1);
	box_hori3.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");
	box_hori4 = Box("Obj/Box.obj", true);
	box_hori4.setScale(2,4,1);
	box_hori4.loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");

	walls_level5[0] = Box(box_verthori);
	walls_level5[0].position = Vector(-45, 0, 0);
	walls_level5[1] = Box(box_verthori);
	walls_level5[1].position = Vector(45, -0, 0);
	walls_level5[2] = Box(box_horivert);
	walls_level5[2].position = Vector(-52.9, 11.1, 0);
	walls_level5[3] = Box(box_horivert);
	walls_level5[3].position = Vector(52.9, -11.1, 0);
	walls_level5[4] = Box(box_hori3);
	walls_level5[4].position = Vector(-74.4, -11.1, 0);
	walls_level5[5] = Box(box_hori3);
	walls_level5[5].position = Vector(74.4, 11.1, 0);
	walls_level5[6] = Box(box_vert);
	walls_level5[6].position = Vector(-115, 123.2, 0);
	walls_level5[7] = Box(box_vert);
	walls_level5[7].position = Vector(115, 123.2, 0);
	walls_level5[8] = Box(box_vert);
	walls_level5[8].position = Vector(-115, -123.2, 0);
	walls_level5[9] = Box(box_vert);
	walls_level5[9].position = Vector(115, -123.2, 0);
	walls_level5[10] = Box(box_hori4);
	walls_level5[10].position = Vector(-115, 107, 0);
	walls_level5[11] = Box(box_hori4);
	walls_level5[11].position = Vector(115, 107, 0);
	walls_level5[12] = Box(box_hori4);
	walls_level5[12].position = Vector(-115, -107, 0);
	walls_level5[13] = Box(box_hori4);
	walls_level5[13].position = Vector(115, -107, 0);

	//LEVEL HUB
	levels[0] = Model("Obj/SPHERE.obj");
	//levels[0].loadTexture("Obj/Levels/Level1/Level1v3_Electric_Rainbow.tga");
	levels[0].loadTexture("Obj/Levels/ScrollingTexture/HUB_Background2x.tga");
	//levels[0].position.subtractVector(Vector(0,0,0));
	//levels[0].orientation = Quaternion(1.57079633,true,false,false);
	levels[0].setScale(50,50,50);

	//SPACE LEVEL
	levels[1] = Model("Obj/SPHERE.obj");
	levels[1].loadTexture("Obj/Levels/ScrollingTexture/HUB_Background_22x.tga");
	//levels[1].position.subtractVector(Vector(0,0,60));
	//levels[1].orientation = Quaternion(1.57079633,true,false,false);
	levels[1].setScale(50,50,50);

	levels[2] = Model("Obj/Levels/OceanLevel/Ocean.obj");
	levels[2].loadTexture("Obj/Levels/OceanLevel/Ocean.tga");
	levels[2].position.subtractVector(Vector(0,0,1500));
	levels[2].setScale(1.5,1.5,1.5);

	ocean_Things = new Model("Obj/Levels/OceanLevel/OceanThings.obj");
	ocean_Things->loadTexture("Obj/Levels/OceanLevel/OceanThings.tga");
	ocean_Things->position.subtractVector(Vector(0,0,1500));
	ocean_Things->setScale(1.33,1.33,1.33);

	levels[3] = Model("Obj/Levels/DesertLevel/desertLevel.obj");
	levels[3].loadTexture("Obj/Levels/DesertLevel/desert.tga");
	levels[3].position.subtractVector(Vector(0,0,600));
	levels[3].setScale(2.5,2.5,2.5);

	desert_Things = new Model("Obj/Levels/DesertLevel/desertthings.obj");
	desert_Things->loadTexture("Obj/Levels/DesertLevel/desertthings.tga");
	desert_Things->position.subtractVector(Vector(0,0,600));
	desert_Things->setScale(2.5,2.5,2.5);

	levels[4] = Model("Obj/Levels/TropicalLevel/tropical.obj");
	levels[4].loadTexture("Obj/Levels/TropicalLevel/Tropical.tga");
	levels[4].position.subtractVector(Vector(0,0,600));
	levels[4].setScale(4,4,4);

	tropical_Things = new Model("Obj/Levels/TropicalLevel/TropicalThings.obj");
	tropical_Things->loadTexture("Obj/Levels/TropicalLevel/TropicalThings.tga");
	tropical_Things->position.subtractVector(Vector(0,0,150));
	tropical_Things->setScale(2.5,2.5,2.5);


	levels[5] = Model("Obj/Levels/Level1/glacierLow.obj");
	//levels[5] = Model("Obj/SPHERE.obj");
	levels[5].loadTexture("Obj/Levels/Level1/Level1v7.tga");
	//levels[5].loadTexture("Obj/Levels/Level1/Level1v3_Electric_Rainbow.tga");
	levels[5].position.subtractVector(Vector(0,0,600));
	levels[5].setScale(4,4,4);


	currentLevel = &levels[0];

	tropical_fog = new Sprite("images/Fog/Fog.png",3996,1800);
	tropical_fog->setPosition(-3000,-1500,0);
	tropical_fog->setNumberOfAnimations(1);
	tropical_fog->setSpriteFrameSize(3996,1800);
	tropical_fog->addSpriteAnimFrame(0,0,0);
	tropical_fog->scaleX =  1.4f;
	tropical_fog->scaleY = 2.8f;
	tropical_fog->scaleZ = 1.66667f;
	/*tropical_fog = new Sprite("images/Fog/Fog2.png",1998,1126);
	tropical_fog->setPosition(-1500,0,0);
	tropical_fog->setNumberOfAnimations(1);
	tropical_fog->setSpriteFrameSize(1998,1126);
	tropical_fog->addSpriteAnimFrame(0,0,0);
	tropical_fog->scaleX = tropical_fog->scaleY = tropical_fog->scaleZ = 2.f;*/
	/*tropical_fog = new Sprite("images/Fog/Fog3.png",1600,900);
	tropical_fog->setPosition(-1500,0,0);
	tropical_fog->setNumberOfAnimations(1);
	tropical_fog->setSpriteFrameSize(1600,900);
	tropical_fog->addSpriteAnimFrame(0,0,0);
	tropical_fog->scaleX = tropical_fog->scaleY = tropical_fog->scaleZ = 2.f;*/
}

void Game::initSprites()
{
	//------------------------------------MENU SPRITE LOADING-------------------------------------------
	//--------------------------------------------------------------------------------------------------
	mainMenu = new menuPage("images/main_menu.png", 1600, 900);
	mainMenu->setPosition(-800,-450,0);
	mainMenu->setNumberOfAnimations(1);
	mainMenu->setSpriteFrameSize(1600, 900);
	mainMenu->addSpriteAnimFrame(0,0,0);

	//button collision boxes
	mainMenu->createButton(585, 255, 425, 88);
	mainMenu->createButton(585, 383, 425, 88);
	mainMenu->createButton(585, 511, 425, 88);
	mainMenu->createButton(585, 639, 425, 88);

	newGame_Button = new Sprite("images/NewGame_Button.png", 850, 88);
	newGame_Button->setPosition(-212.5,100,10);
	newGame_Button->setNumberOfAnimations(1);
	newGame_Button->setSpriteFrameSize(425, 88);
	newGame_Button->addSpriteAnimFrame(0,0,0);
	newGame_Button->addSpriteAnimFrame(0,425,88);

	settings_Button = new Sprite("images/settings_Button.png", 850, 88);
	settings_Button->setPosition(-212.5,-28,10);
	settings_Button->setNumberOfAnimations(1);
	settings_Button->setSpriteFrameSize(425, 88);
	settings_Button->addSpriteAnimFrame(0,0,0);
	settings_Button->addSpriteAnimFrame(0,425,88);

	credits_Button = new Sprite("images/credits_Button.png", 850, 88);
	credits_Button->setPosition(-212.5,-156,10);
	credits_Button->setNumberOfAnimations(1);
	credits_Button->setSpriteFrameSize(425, 88);
	credits_Button->addSpriteAnimFrame(0,0,0);
	credits_Button->addSpriteAnimFrame(0,425,88);
	
	exit_Button = new Sprite("images/exit_Button.png", 850, 88);
	exit_Button->setPosition(-212.5,-284,10);
	exit_Button->setNumberOfAnimations(1);
	exit_Button->setSpriteFrameSize(425, 88);
	exit_Button->addSpriteAnimFrame(0,0,0);
	exit_Button->addSpriteAnimFrame(0,425,88);

	//-----------------------Settings Menu----------------------------------------------------------
	settingsMenu = new menuPage("images/settings_menu.png", 1600, 900);
	settingsMenu->setPosition(-800,-450,0);
	settingsMenu->setNumberOfAnimations(1);
	settingsMenu->setSpriteFrameSize(1600, 900);
	settingsMenu->addSpriteAnimFrame(0,0,0);

	audio_Button = new Sprite("images/fullscreen_Button.png", 850, 88);
	audio_Button->setPosition(-212.5,100,10);
	audio_Button->setNumberOfAnimations(1);
	audio_Button->setSpriteFrameSize(425, 88);
	audio_Button->addSpriteAnimFrame(0,0,0);
	audio_Button->addSpriteAnimFrame(0,425,88);
	audio_Button->currentFrame = 1;

	controls_Button = new Sprite("images/controls_Button.png", 850, 88);
	controls_Button->setPosition(-212.5,-28,10);
	controls_Button->setNumberOfAnimations(1);
	controls_Button->setSpriteFrameSize(425, 88);
	controls_Button->addSpriteAnimFrame(0,0,0);
	controls_Button->addSpriteAnimFrame(0,425,88);

	howtoplay_Button = new Sprite("images/howtoplay_Button.png", 850, 88);
	howtoplay_Button->setPosition(-212.5,-156,10);
	howtoplay_Button->setNumberOfAnimations(1);
	howtoplay_Button->setSpriteFrameSize(425, 88);
	howtoplay_Button->addSpriteAnimFrame(0,0,0);
	howtoplay_Button->addSpriteAnimFrame(0,425,88);

	back_Button = new Sprite("images/back_Button.png", 850, 88);
	back_Button->setPosition(-212.5,-284,10);
	back_Button->setNumberOfAnimations(1);
	back_Button->setSpriteFrameSize(425, 88);
	back_Button->addSpriteAnimFrame(0,0,0);
	back_Button->addSpriteAnimFrame(0,425,88);

	settingsMenu->createButton(585, 255, 425, 88);
	settingsMenu->createButton(585, 383, 425, 88);
	settingsMenu->createButton(585, 511, 425, 88);
	settingsMenu->createButton(585, 639, 425, 88);

	//----------------------------------------Credits Screen------------------------------------------
	creditsMenu = new menuPage("images/Credits_Screen.png", 1600, 900);
	creditsMenu->setPosition(-800,-450,0);
	creditsMenu->setNumberOfAnimations(1);
	creditsMenu->setSpriteFrameSize(1600, 900);
	creditsMenu->addSpriteAnimFrame(0,0,0);

	//using previously initialised back button
	creditsMenu->createButton(585, 620, 425, 88);


	//----------------------------------------Controls Menu-------------------------------------------
	controlsMenu = new menuPage("images/controls_menu.png", 1600, 900);
	controlsMenu->setPosition(-800,-450,0);
	controlsMenu->setNumberOfAnimations(1);
	controlsMenu->setSpriteFrameSize(1600, 900);
	controlsMenu->addSpriteAnimFrame(0,0,0);
	controlsMenu->initKeys();

	//-------------Controller Only Sprite-------------------------------------------------------------
	controllerMenu = new menuPage("images/controller_menu.png", 1600, 900);
	controllerMenu->setPosition(-800,-450,0);
	controllerMenu->setNumberOfAnimations(1);
	controllerMenu->setSpriteFrameSize(1600, 900);
	controllerMenu->addSpriteAnimFrame(0,0,0);
	controllerMenu->initKeys();
	

	//rest of the buttons (collision boxes)
	//note: order of init is important
	controlsMenu->createButton(110, 160, 305, 63);
	controlsMenu->createButton(110, 260, 305, 63);
	controlsMenu->createButton(110, 360, 305, 63);
	controlsMenu->createButton(110, 450, 305, 63);
	controlsMenu->createButton(110, 550, 305, 63);
	controlsMenu->createButton(110, 645, 305, 63);
	controlsMenu->createButton(110, 745, 305, 63);
	controlsMenu->createButton(812, 160, 305, 63);
	controlsMenu->createButton(812, 260, 305, 63);
	controlsMenu->createButton(812, 360, 305, 63);
	controlsMenu->createButton(812, 450, 305, 63);
	controlsMenu->createButton(812, 550, 305, 63);
	controlsMenu->createButton(812, 645, 305, 63);
	//back button
	controlsMenu->createButton(1185, 730, 425, 88);
	//reset button
	controlsMenu->createButton(812, 745, 305, 63);
	
	//setting up action keys
	controlsMenu->actionKeys.push_back(input.up_key);
	controlsMenu->actionKeys.push_back(input.down_key);
	controlsMenu->actionKeys.push_back(input.left_key);
	controlsMenu->actionKeys.push_back(input.right_key);
	controlsMenu->actionKeys.push_back(input.boost_key);
	controlsMenu->actionKeys.push_back(input.usePowerup_key);
	controlsMenu->actionKeys.push_back(input.switchpowerup_key);
	controlsMenu->actionKeys.push_back(input.watergun_key);
	controlsMenu->actionKeys.push_back(input.flamethrower_key);
	controlsMenu->actionKeys.push_back(input.pause_key);
	controlsMenu->actionKeys.push_back(input.camera_key);
	controlsMenu->actionKeys.push_back(input.elevateup_key);
	controlsMenu->actionKeys.push_back(input.elevatedown_key);
	//-----------------------------------------Pause Menu---------------------------------------------
	pauseMenu = new menuPage("images/pause_menu.png", 1600, 900);
	pauseMenu->setPosition(-800,-450,0);
	pauseMenu->setNumberOfAnimations(1);
	pauseMenu->setSpriteFrameSize(1600, 900);
	pauseMenu->addSpriteAnimFrame(0,0,0);

	resume_Button = new Sprite("images/resume_Button.png", 850, 88);
	resume_Button->setPosition(-212.5,100,10);
	resume_Button->setNumberOfAnimations(1);
	resume_Button->setSpriteFrameSize(425, 88);
	resume_Button->addSpriteAnimFrame(0,0,0);
	resume_Button->addSpriteAnimFrame(0,425,88);

	hub_Button = new Sprite("images/hub_Button.png", 850, 88);
	hub_Button->setPosition(-212.5,-156,10);
	hub_Button->setNumberOfAnimations(1);
	hub_Button->setSpriteFrameSize(425, 88);
	hub_Button->addSpriteAnimFrame(0,0,0);
	hub_Button->addSpriteAnimFrame(0,425,88);

	pauseMenu->createButton(585, 255, 425, 88);
	pauseMenu->createButton(585, 383, 425, 88);
	pauseMenu->createButton(585, 511, 425, 88);

	//----------------------------------------How To Play Menu-------------------------------------
	howtoplayMenu = new menuPage("images/howtoplay_menu.png", 1600, 900);
	howtoplayMenu->setPosition(-800,-450,0);
	howtoplayMenu->setNumberOfAnimations(1);
	howtoplayMenu->setSpriteFrameSize(1600, 900);
	howtoplayMenu->addSpriteAnimFrame(0,0,0);

	//back button
	howtoplayMenu->createButton(1088, 130, 425, 88);
}

void Game::initSpawners()
{
	spawner_level1 = Spawner("Obj/Spawner/Spawner1.obj", STATE_LEVEL1);
	spawner_level1.loadTexture("Obj/Spawner/SpawnerTex.tga");
	//spawner_level1.setScale(2,1,2);
	spawner_level2 = Spawner("Obj/Spawner/Spawner1.obj", STATE_LEVEL2);
//	spawner_level2.setScale(2,1,2);
	spawner_level3 = Spawner("Obj/Spawner/Spawner1.obj", STATE_LEVEL3);
//	spawner_level3.setScale(2,1,2);
	spawner_level4 = Spawner("Obj/Spawner/Spawner1.obj", STATE_LEVEL4);
//	spawner_level4.setScale(2,1,2);
	spawner_level5 = Spawner("Obj/Spawner/Spawner1.obj", STATE_LEVEL5);
//	spawner_level5.setScale(2,1,2);
	spawner_level2.modelTexture = spawner_level3.modelTexture = spawner_level4.modelTexture = spawner_level5.modelTexture = spawner_level1.modelTexture;

	spawner_level1.orientation = spawner_level2.orientation = spawner_level3.orientation = spawner_level4.orientation = spawner_level5.orientation = Quaternion(-0.785398163,false,false,true);

	string filename = "Obj/Spawner/Spawner";
	string obj = ".obj";
	for(int i = 0; i < 12; i++)
	{
		string fn = filename;
		stringstream num;
		num << i+1;
		fn.append(num.str());
		fn.append(obj);
		Spawner::morphTargets[i] = new Model(fn);
	}
}

void Game::initPlayer()
{
	//player = new Player("Obj/PlayerShip/SpaceShipKey1.obj");
	player = new Player("Obj/PlayerShip/test_7.obj");
	player->loadTexture("Obj/PlayerShip/SpaceShipTextureRed.tga");
	//player->morphTargets[0] =new Model(*player);
	//player->morphTargets[1] =new Model("Obj/PlayerShip/SpaceShipKey2.obj");
	//player->morphTargets[2] =new Model(*player);
	//player->morphTargets[3] =new Model("Obj/PlayerShip/SpaceShipKey3.obj");

	string filename = "Obj/PlayerShip/test_";
	string obj = ".obj";
	for(int i = 0; i < 8; i++)
	{
		string fn = filename;
		stringstream num;
		num << i+8;
		fn.append(num.str());
		fn.append(obj);
		player->morphTargets[i] = new Model(fn);
	}
	for(int i = 8; i < 15; i++)
	{
		string fn = filename;
		stringstream num;
		num << i-8;
		fn.append(num.str());
		fn.append(obj);
		player->morphTargets[i] = new Model(fn);
	}

	player_collider = new Player("Obj/PlayerShip/ShipHull.obj");
	player_collider->setScale(3,3,3);
	player->position = Vector(0,0,0);
	player_lastPos = Vector(0,0,0);

	camPos = Vector(player->position.X_Y_Z[0],player->position.X_Y_Z[1],player->position.X_Y_Z[2]+camZ);
	camSpring = Spring(10,0.1,Vector(player->position),Vector(camPos));
}

void Game::initSounds()
{
	zeroVector = Vector(0,0,0);
	soundSystem = new SoundEngine();
	player->shooting_sound = new Sound("sounds/Game Sounds/Pew_Pew.wav",SOUND,player->position,zeroVector,soundSystem->system,soundSystem->result);
	player->shooting_sound->setChannelMode(FMOD_2D);
	player->shooting_sound->setSoundMode(FMOD_2D);
		player->listenerRight = Vector(1,0,0);
			player->listenerUp = Vector(0,1,0);
			player->listenerDir = Vector(0,0,-1);
			player->listener = new Listener(player->position,player->velocity,player->listenerUp,player->listenerRight,player->listenerDir,soundSystem->system,soundSystem->result);

	introDialogue = new Sound("sounds/Game Sounds/Game Intro Dialogue.wav",SOUND,player->position,zeroVector);
	introDialogue->setChannelMode(FMOD_2D);
	introDialogue->setSoundMode(FMOD_2D);


	hubMusic = new Sound("sounds/Background_Music.wav",STREAM,player->position,zeroVector);
	hubMusic->setChannelMode(FMOD_2D);
	hubMusic->setSoundMode(FMOD_2D);
	FMOD_Channel_SetVolume(hubMusic->channel,0.2);
	hubMusic->setSoundMode(FMOD_LOOP_NORMAL);

	gameMusic = new Sound("sounds/Game Sounds/rutgermuller__electrohouse-cheesy.wav",STREAM,player->position,zeroVector);
	gameMusic->setChannelMode(FMOD_2D);
	gameMusic->setSoundMode(FMOD_2D);
	FMOD_Channel_SetVolume(gameMusic->channel,0.2);
	gameMusic->pause();
	gameMusic->setSoundMode(FMOD_LOOP_NORMAL);

	menuClick = new Sound("sounds/Game Sounds/Menu_Click.wav",SOUND,player->position,zeroVector);
	menuClick->setChannelMode(FMOD_2D);
	menuClick->setSoundMode(FMOD_2D);

	slowDownTime_begin = new Sound("sounds/Game Sounds/Slow Down.wav",SOUND,player->position,zeroVector);
	slowDownTime_begin->setChannelMode(FMOD_2D);
	slowDownTime_begin->setSoundMode(FMOD_2D);
	slowDownTime_end = new Sound("sounds/Game Sounds/Resume Time.wav",SOUND,player->position,zeroVector);
	slowDownTime_end->setChannelMode(FMOD_2D);
	slowDownTime_end->setSoundMode(FMOD_2D);

	spawner_level1.spawnerSound = new Sound("sounds/Game Sounds/Piston.wav",STREAM,spawner_level1.position,spawner_level1.velocity);
	spawner_level1.spawnerSound->setChannelMode(FMOD_3D_INVERSEROLLOFF);
	spawner_level1.spawnerSound->setSoundMode(FMOD_3D_INVERSEROLLOFF);
	spawner_level1.spawnerSound->setSoundMode(FMOD_LOOP_NORMAL);
	spawner_level1.spawnerSound->set3DMinMaxDist(1.f,1000.f);
	FMOD_Channel_SetVolume(spawner_level1.spawnerSound->channel,1.0);
	spawner_level2.spawnerSound = new Sound(*spawner_level1.spawnerSound);
	spawner_level3.spawnerSound = new Sound(*spawner_level1.spawnerSound);
	spawner_level4.spawnerSound = new Sound(*spawner_level1.spawnerSound);
	spawner_level5.spawnerSound = new Sound(*spawner_level1.spawnerSound);


	finalBoss_dialogue = new Sound("sounds/Game Sounds/Final Boss Music (FULL).mp3",SOUND,player->position,zeroVector);

	finalBoss_dialogue->setChannelMode(FMOD_2D);
	finalBoss_dialogue->setSoundMode(FMOD_2D);




	enemy1_base->explode = new Sound("sounds/Game Sounds/Blast_1.wav",SOUND,zeroVector,zeroVector);
	enemy1_base->explode->setChannelMode(FMOD_3D_LINEARROLLOFF);
	enemy1_base->explode->setSoundMode(FMOD_3D_LINEARROLLOFF);
	enemy1_base->explode->set3DMinMaxDist(0.001f,100.f);
	enemy2_base->explode = new Sound(*enemy1_base->explode);
	enemy3_base->explode = new Sound(*enemy1_base->explode);
	enemy4_base->explode = new Sound(*enemy1_base->explode);
	enemy5_base->explode = new Sound(*enemy1_base->explode);

	this->powerup_pickUp = new Sound("sounds/Dive.wav",SOUND,zeroVector,zeroVector);
}
/* 
 * initializeGame()
 * - this function is called in the constructor to initialize everything related
 *   to the game, i..e loading sprites etc.
 * - MUST be called prior to any drawing/updating (you should add in checks to ensure this occurs in the right order)
 */
void Game::initializeGame()
{
	initBloomShader();
	initToonShader();
	initScrollingTexShader();
	initNormalMappingShader();
	initEnemies();
	initLevels();
	initHUD();
	initSpawners();
	defaultKeys();
	initSprites();

	camX = 0;
	camY = 0;
	camZ = 70;
	frameCount = 0;
	score = 0;
	frame = 0;
	click = 0;
	it = 0;
	startSLERP = false;
	invi_frames = 30;
	invincible = false;
	fired = false;
	perspective = 0;
	switched = false;
	middleClicked = false;
	pressed = false;
	selected = false;
	delay;
	cuts3 = false;
	cutsceneIT = 0;
	cutscene1.push_back( new Vector(0,50,30));
	cutscene1.push_back( new Vector(0,50,30));
	cutscene1.push_back( new Vector(50,0,30));
	cutscene1.push_back( new Vector(0,-50,30));
	cutscene1.push_back( new Vector(-50,0,30));
	cutscene1.push_back( new Vector(0,50,30));
	cutscene1.push_back( new Vector(0,50,30));
	Vector temp;
	speedControl_1[0] = temp.speedControl_SLERP(*cutscene1[0],*cutscene1[1],*cutscene1[2],*cutscene1[3]);
	cutscene1_dt[0] = speedControl_1[0]/300;
	speedControl_1[1] = temp.speedControl_SLERP(*cutscene1[1],*cutscene1[2],*cutscene1[3],*cutscene1[4]);
	cutscene1_dt[1] = speedControl_1[1]/300;
	speedControl_1[2] = temp.speedControl_SLERP(*cutscene1[2],*cutscene1[3],*cutscene1[4],*cutscene1[5]);
	cutscene1_dt[2] = speedControl_1[2]/300;
	speedControl_1[3] = temp.speedControl_SLERP(*cutscene1[3],*cutscene1[4],*cutscene1[5],*cutscene1[6]);
	cutscene1_dt[3] = speedControl_1[3]/300;

	freezeEnemies = false;
	freezeTime = 180;
	
	playerSpeedUp = false;
	speedUpTime = 180;

	slowDown = false;
	slowDownTime = 180;
	slowDown_num = 2;

	gravityBomb = false;
	gravityBombTime = 360;

	stateInfo.bossState = STATE_NO_BOSS;

	initPlayer();
	initBosses();

	powerups_init[0] = new Powerup("Obj/Powerups/GravityBomb/GravBomb.obj");
	powerups_init[0]->loadTexture("Obj/Powerups/GravityBomb/Gravity_Bomb_polySurfaceShape1.tga");
	powerups_init[0]->ID = GRAVITY_BOMB;
	powerups_init[0]->setScale(0.5,0.5,0.5);

	powerups_init[1] = new Powerup("Obj/Powerups/Shield/Shield.obj");
	powerups_init[1]->loadTexture("Obj/Powerups/Shield/Shield_polySurfaceShape1.tga");
	powerups_init[1]->ID = SHIELD;
	powerups_init[1]->setScale(0.5,0.5,0.5);

	powerups_init[2] = new Powerup("Obj/Powerups/FreezeTime/FreezeTime.obj");
	powerups_init[2]->loadTexture("Obj/Powerups/FreezeTime/Freeze_Time - 2_polySurfaceShape1.tga");
	powerups_init[2]->ID = FREEZE_TIME;
	powerups_init[2]->setScale(0.5,0.5,0.5);

	powerups_init[3] = new Powerup("Obj/Powerups/SpeedUp/SpeedUp.obj");
	powerups_init[3]->loadTexture("Obj/Powerups/SpeedUp/Speed_Up_polySurfaceShape1.tga");
	powerups_init[3]->ID = SPEED_UP;
	powerups_init[3]->setScale(0.5,0.5,0.5);

	powerups_init[4] = new Powerup("Obj/Powerups/SlowDown/SlowDown.obj");
	powerups_init[4]->loadTexture("Obj/Powerups/SlowDown/Slow_Down_polySurfaceShape1.tga");
	powerups_init[4]->ID = SLOW_DOWN;
	powerups_init[4]->setScale(0.5,0.5,0.5);


	asteroid = new Asteroid("Obj/Asteroid_new.obj");
	asteroid->loadTexture("Obj/AsteroidTexture.tga");
	asteroid->loadNormalMap("images/Asteroid_ObjectMap.tga");
	/*asteroid->scaleFactor[0] *= 5;
	asteroid->scaleFactor[1] *= 5;
	asteroid->scaleFactor[2] *= 5;*/

	bullet =  Model("Obj/PlayerShip/Projectile/Bullet/Bullet.obj");
	bullet.loadTexture("Obj/PlayerShip/Projectile/Bullet/BulletTexture.tga");
	//bullet.loadTexture("Obj/Levels/Level1/Level1v7.tga");
	bullet.setScale(2,2,2);

	fire = Model("Obj/PlayerShip/Projectile/Fire/FireParticle.obj");
	fire.loadTexture("Obj/PlayerShip/Projectile/Fire/Fire_Particle.tga");

	water = Model("Obj/PlayerShip/Projectile/Water/WaterParticle.obj");
	water.loadTexture("Obj/PlayerShip/Projectile/Water/Water_Particle.tga");

	missile = Model("Obj/PlayerShip/Projectile/Missile/Missile.obj");
	missile.loadTexture("Obj/PlayerShip/Projectile/Missile/MissileTexture.tga");
	missile.setScale(0.5,0.5,0.5);

	bomb = Model("Obj/PlayerShip/Projectile/Bomb/Bomb.obj");
	bomb.loadTexture("Obj/PlayerShip/Projectile/Bomb/bomb_polySurfaceShape6.tga");
	bomb.setScale(0.2,0.2,0.2);

	testSprite = new Sprite("images/LaserOrb.png", 144,144);
	testSprite->setPosition(0,0,0);
	testSprite->setNumberOfAnimations(1);
	testSprite->setSpriteFrameSize(144,144);
	testSprite->addSpriteAnimFrame(0,0,0);
	testSprite->setCurrentAnimation(0);
	testSprite->currentFrame = 0;



	//---------------------------------------------Objects----------------------------------------
	//--------------------------------------------------------------------------------------------
	
	stateInfo.subState = STATE_HUB;
	portals[0] = new Model("Obj/Portals/Portal1/Portal1.obj");
	portals[0]->loadTexture("Obj/Portals/Portal1/Portal1Texture.tga");
	portals[0]->scaleFactor[0] *=5;
	portals[0]->scaleFactor[1] *=5;
	portals[0]->scaleFactor[2] *=5;

	portals[1] = new Model("Obj/Portals/Portal2/Portal2.obj");
	portals[1]->loadTexture("Obj/Portals/Portal2/Portal2Texture.tga");
	portals[1]->scaleFactor[0] *=5;
	portals[1]->scaleFactor[1] *=5;
	portals[1]->scaleFactor[2] *=5;

	portals[2] = new Model("Obj/Portals/Portal3/Portal3.obj");
	portals[2]->loadTexture("Obj/Portals/Portal3/Portal3Texture.tga");
	portals[2]->scaleFactor[0] *=5;
	portals[2]->scaleFactor[1] *=5;
	portals[2]->scaleFactor[2] *=5;

	portals[3] = new Model("Obj/Portals/Portal4/Portal4.obj");
	portals[3]->loadTexture("Obj/Portals/Portal4/Portal4Texture.tga");
	portals[3]->scaleFactor[0] *=5;
	portals[3]->scaleFactor[1] *=5;
	portals[3]->scaleFactor[2] *=5;

	portals[4] = new Model("Obj/Portals/Portal5/Portal5.obj");
	portals[4]->loadTexture("Obj/Portals/Portal5/Portal5Texture.tga");
	portals[4]->scaleFactor[0] *=5;
	portals[4]->scaleFactor[1] *=5;
	portals[4]->scaleFactor[2] *=5;

	gravityBombPortal = new Model("Obj/Portals/Portal5/Portal5.obj");
	gravityBombPortal->loadTexture("Obj/Portals/Portal5/gravityBombTexture.tga");
	gravityBombPortal->scaleFactor[0] *=5;
	gravityBombPortal->scaleFactor[1] *=5;
	gravityBombPortal->scaleFactor[2] *=5;

	/*main_menu = Model("Obj/Menus/MainMenu/Main_Menu.obj");
	main_menu.position = player->position;
	main_menu.setScale(6.45,6.45,6.45);
	pause_screen = Model(main_menu);
	select_screen = Model(main_menu);
	main_menu.loadTexture("Obj/Menus/MainMenu/Plain_MainMenu_pPlaneShape2.tga");
	pause_screen.loadTexture("Obj/Menus/PauseScreen/Plain_PauseScreen_pPlaneShape1.tga");
	select_screen.loadTexture("Obj/Menus/LevelSelect/LevelSelect_YN.tga");*/

	boostBar = Model("Obj/HUD/HealthBar.obj");
	boostBar.loadTexture("Obj/HUD/boostBar.tga");

	healthBar = Model("Obj/HUD/HealthBar.obj");
	healthBar.loadTexture("Obj/HUD/healthBar.tga");

	shieldBar = Model("Obj/HUD/HealthBar.obj");
	shieldBar.loadTexture("Obj/HUD/shieldBar.tga");

	fireFuelBar = Model("Obj/HUD/HealthBar.obj");
	fireFuelBar.loadTexture("Obj/HUD/fireBar.tga");

	waterFuelBar = Model("Obj/HUD/HealthBar.obj");
	waterFuelBar.loadTexture("Obj/HUD/waterBar.tga");

	this->flamethrower = false;
	this->waterGun = false;
	this->missiles = true;

	for(int i = 0; i<5; i++)
	{
		t.insert(powerups_init[i]->ID);
	}

	spaceBoss->shoot(bullet);

	srand ( time(NULL) );

	glEnable(GL_POLYGON_SMOOTH | GL_POINT_SMOOTH);
	glShadeModel (GL_SMOOTH);

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 100.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_position2[] = { -1.0, -10.0, 1.0, 0.0 };
   
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable ( GL_COLOR_MATERIAL ) ;
	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D); // turn on texturing
	
	glEnable(GL_DEPTH_TEST);
	glClearColor((GLclampf)stateInfo.bgClearColor.red, 
				(GLclampf)stateInfo.bgClearColor.green, 
				 (GLclampf)stateInfo.bgClearColor.blue, 0);
	
	/*glClearDepth(1.f);
	glClearColor(0, 0, 0, 0.7f);*/

	/*glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);*/

	/*glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);*/
 //Level 1 SoundTrack
	initSounds();
}