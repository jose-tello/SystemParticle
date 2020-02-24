#pragma once

#include "p2Defs.h"
#include "Globals.h"
#include "p2Log.h"
#include "Timer.h"
#include "PerfTimer.h"
#include "p2SString.h"
#include "vector"

class Module;
class ModuleRender;
class ModuleWindow;
class ModuleInput;
class ModuleScene;
class ModuleTextures;
class ModuleParticles;

class Application
{
public:
	
	ModuleInput* input;
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleScene* scene;
	ModuleTextures* textures;
	ModuleParticles* particles;

	j1Timer* gameTimer = nullptr;
	j1PerfTimer* gamePerfTimer = nullptr;
	j1Timer* lastSecFrames = nullptr;
	j1Timer lastFrameTimer;


	uint64 frame_count = 0u;
	uint last_second_frame_count = 0u;

	uint32 last_frame_ms = 0u;
	uint32 frames_on_last_update = 0u;

	float avg_fps = 0.0f;
	float dt = 0.0f;

	uint capTime = 0u;


private:

	vector<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void FinishUpdate();
	void PrepareUpdate();


private:

	void AddModule(Module* mod);

};