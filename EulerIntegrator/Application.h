#pragma once

#define TIME_CONST 50
#define MAX_DT 3

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

	j1Timer gameTimer;
	j1PerfTimer gamePerfTimer;
	j1Timer lastSecFrames;
	j1Timer lastFrameTimer;


	uint64 frame_count = 0u;
	uint last_second_frame_count = 0u;

	uint32 last_frame_ms = 0u;
	uint32 frames_on_last_update = 0u;

	float avg_fps;
	float dt;

	uint capTime;


private:
	vector<Module*> list_modules;
	int	argc;
	char**	args;

public:

	Application(int argc, char* args[]);
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();
	void FinishUpdate();
	void PrepareUpdate();

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;

private:

	void AddModule(Module* mod);

};

extern Application* App;