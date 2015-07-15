#include "Game.h"

void Game::initBloomShader()
{
	brightPass_f = new Shader(FRAG,"Shaders/brightPass_f.glsl");
	passThroughTex_v = new Shader(VERT,"Shaders/passThroughTex_v.glsl");
	brightPass_Program = new ShaderProgram();
	//brightPass_Program->attachShader(passThroughTex_v);
	brightPass_Program->attachShader(brightPass_f);
	brightPass_Program->link();
	brightPass_uniform1 = brightPass_Program->getUniformVarLoc("image");


	gaussV_f = new Shader(FRAG,"Shaders/gaussianBlur1D_V_f.glsl");
	gaussV_Program = new ShaderProgram();
	gaussV_Program->attachShader(gaussV_f);
	//gaussV_Program->attachShader(passThroughTex_v);
	gaussV_Program->link();
	gaussV_uniform1 = gaussV_Program->getUniformVarLoc("scene");
	gaussV_uniform2 = gaussV_Program->getUniformVarLoc("pixelSize");

	gaussH_f = new Shader(FRAG,"Shaders/gaussianBlur1D_H_f.glsl");
	gaussH_Program = new ShaderProgram();
	gaussH_Program->attachShader(gaussH_f);
//	gaussV_Program->attachShader(passThroughTex_v);
	gaussH_Program->link();
	gaussH_uniform1 = gaussH_Program->getUniformVarLoc("scene");
	gaussH_uniform2 = gaussH_Program->getUniformVarLoc("pixelSize");


	composite_f = new Shader(FRAG,"Shaders/screen_f.glsl");
	composite_Program = new ShaderProgram();
	composite_Program->attachShader(composite_f);
	//composite_Program->attachShader(passThroughTex_v);
	composite_Program->link();
	composite_uniform1 = composite_Program->getUniformVarLoc("scene");
	composite_uniform2 = composite_Program->getUniformVarLoc("bloom");
	composite_uniform_gamma = composite_Program->getUniformVarLoc("gam");
	this->gamma = 1.0;


	scenePass = new FrameBufferObj(1,true,
								  stateInfo.windowWidth,stateInfo.windowHeight,
								  true,false);

	brightPass = new FrameBufferObj(1,false,
									stateInfo.windowWidth/4,stateInfo.windowHeight/4,
									true,false);
	

	blurPass1 = new FrameBufferObj(1,false,
								  stateInfo.windowWidth/4,stateInfo.windowHeight/4,
								  true,false);

	blurPass2 = new FrameBufferObj(1,false,
								  stateInfo.windowWidth/4,stateInfo.windowHeight/4,
								  true,false);
}

void Game::initToonShader()
{
	toonPass = new FrameBufferObj(2,true,
								  stateInfo.windowWidth,stateInfo.windowHeight,
								  true,false);
	toon_v = new Shader(VERT,"Shaders/toon_v.glsl");
	toon_f = new Shader(FRAG,"Shaders/toon_f.glsl");
	toon_program = new ShaderProgram();
	toon_program->attachShader(toon_v);
	toon_program->attachShader(toon_f);
	toon_program->link();
	toon_inImg_uniform = toon_program->getUniformVarLoc("inputImage");
	toon_inQmap_uniform = toon_program->getUniformVarLoc("qmap");
	
	edges_f = new Shader(FRAG,"Shaders/edge_f.glsl");
	edges_program = new ShaderProgram();
	edges_program->attachShader(edges_f);
	edges_program->link();
	edges_inCol_uniform = edges_program->getUniformVarLoc("inputColour");
	edges_inNorm_uniform = edges_program->getUniformVarLoc("inputNormal");
	edges_inDepth_uniform = edges_program->getUniformVarLoc("inputDepth");
	edges_pixSize_uniform = edges_program->getUniformVarLoc("pixelSize");

	loadImage("images/qMap.tga",ramp);
}

void Game::initScrollingTexShader()
{
	scrollTexHor_f = new Shader(FRAG,"Shaders/scrollTexHor_f.glsl");
	scrollingTexHor_program = new ShaderProgram();
	scrollingTexHor_program->attachShader(scrollTexHor_f);
	scrollingTexHor_program->link();
	scrollHor_tex_uniform = scrollingTexHor_program->getUniformVarLoc("tex");
	scrollHor_time_uniform = scrollingTexHor_program->getUniformVarLoc("time");
	scrollHor_speed_uniform = scrollingTexHor_program->getUniformVarLoc("speed");

	scrollTexHor2_f = new Shader(FRAG,"Shaders/scrollTexHor2_f.glsl");
	scrollingTexHor2_program = new ShaderProgram();
	scrollingTexHor2_program->attachShader(scrollTexHor2_f);
	scrollingTexHor2_program->link();
	scrollHor2_tex_uniform = scrollingTexHor2_program->getUniformVarLoc("tex");
	scrollHor2_time_uniform = scrollingTexHor2_program->getUniformVarLoc("time");
	scrollHor2_speed_uniform = scrollingTexHor2_program->getUniformVarLoc("speed");
}

void Game::initNormalMappingShader()
{
	objectNormalMap_v = new Shader(VERT,"Shaders/objectNormalMap_v.glsl");
	objectNormalMap_f = new Shader(FRAG,"Shaders/objectNormalMap_f.glsl");
	normalMapping_program = new ShaderProgram();
	normalMapping_program->attachShader(objectNormalMap_v);
	normalMapping_program->attachShader(objectNormalMap_f);
	normalMapping_program->link();
	diffuseMap_uniform = normalMapping_program->getUniformVarLoc("diffuseMap");
	normalMap.texID = normalMapping_program->getUniformVarLoc("normalMap");
	//pos_uniform = normalMapping_program->getUniformVarLoc("position");

	//loadImage("images/Asteroid_ObjectMap.tga", normalMap);
}