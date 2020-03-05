#include "Module.h"
#include "Application.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Input.h"
#include "Textures.h"
#include "Particles.h"
//include header of all existing modules

Application::Application(int argc, char* args[]) : argc(argc), args(args) 
{
	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene = new ModuleScene(this);
	textures = new ModuleTextures(this);
	particles = new ModuleParticles(this);

	gameTimer;
	gamePerfTimer;
	lastSecFrames;

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules (reverse order for cleanUp)
	AddModule(window);
	AddModule(input);
	AddModule(textures);
	AddModule(scene);
	AddModule(particles);

	//Renderer
	AddModule(renderer);

}

//Destructor of aplication, it calls all module destructors
Application::~Application() {

	list_modules.clear();
}

bool Application::Init()
{
	bool ret = true;

	capTime = 60u;

	// Call Init() in all modules
	int num_modules = list_modules.size();

	for (int i = 0; i < num_modules && ret == true; i++) {

		ret = list_modules[i]->Init();
	}
	

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	

	for (int i = 0; i < num_modules && ret == true; i++) {

		if (list_modules[i]->IsEnabled())
			ret = list_modules[i]->Start();
	}

	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	int num_modules = list_modules.size();
	
	PrepareUpdate();
	for (int i = 0; i < num_modules && ret == UPDATE_CONTINUE; i++) {

		if (list_modules[i]->IsEnabled())
			ret = list_modules[i]->PreUpdate();
	}


	for (int i = 0; i < num_modules && ret == UPDATE_CONTINUE; i++) {

		if (list_modules[i]->IsEnabled())
			ret = list_modules[i]->Update(dt);
	}


	for (int i = 0; i < num_modules && ret == UPDATE_CONTINUE; i++) {

		if (list_modules[i]->IsEnabled())
			ret = list_modules[i]->PostUpdate();
	}

	FinishUpdate();

	return ret;
}

void Application::PrepareUpdate() {

	frame_count++;
	last_second_frame_count++;

	//Controls pause of the game
	dt = lastFrameTimer.ReadSec() * TIME_CONST;

	if (dt > MAX_DT)
		dt = MAX_DT;

	lastFrameTimer.Start();

}

void Application::FinishUpdate() {

	// Amount of time since game start (use a low resolution timer)
	float seconds_since_startup = gameTimer.ReadSec();

	// Average FPS for the whole game life
	avg_fps = float(frame_count) / seconds_since_startup;

	// Amount of ms took the last update
	last_frame_ms = lastFrameTimer.Read();

	// Amount of frames during the last second
	if (lastSecFrames.Read() >= 1000)
	{
		frames_on_last_update = last_second_frame_count;
		last_second_frame_count = 0;
		lastSecFrames.Start();
	}

	if (last_frame_ms < 1000 / capTime)
	{
		SDL_Delay((1000 / capTime) - last_frame_ms);
	}

	//Title shown in the window
	p2SString title("%s-%s || FPS: %i Av.FPS: %.2f || Target FPS: %i || Last Frame Ms: %u ",
		TITLE, ORGANIZATION,
		frames_on_last_update, avg_fps,
		capTime,
		last_frame_ms);

	window->SetTitle(title.GetString());

}

//Calls all modules CleanUp()
bool Application::CleanUp() {

	for (int i = list_modules.size() - 1; i > 0; i--) {

		list_modules[i]->CleanUp();
	}

	return true;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

int Application::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* Application::GetArgv(int index) const
{
	if (index < argc)
		return args[index];
	else
		return NULL;
}