#include "Module.h"
#include "Application.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Input.h"
#include "Textures.h"
//include header of all existing modules

Application::Application() {

	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene = new ModuleScene(this);
	textures = new ModuleTextures(this);

	gameTimer = new j1Timer();
	gamePerfTimer = new j1PerfTimer();
	lastSecFrames = new j1Timer();

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules (reverse order for cleanUp)
	AddModule(window);
	AddModule(input);
	AddModule(textures);
	AddModule(scene);

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
	int num_modules = list_modules.capacity() - 1;

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

	list_modules.shrink_to_fit(); //Ask Marc why
	int num_modules = list_modules.capacity();
	
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
	dt = lastFrameTimer.ReadSec();

	if (dt > 0.16f)
		dt = 0.16f;

	lastFrameTimer.Start();

}

void Application::FinishUpdate() {

	// Amount of time since game start (use a low resolution timer)
	float seconds_since_startup = gameTimer->ReadSec();

	// Average FPS for the whole game life
	avg_fps = float(frame_count) / seconds_since_startup;

	// Amount of ms took the last update
	last_frame_ms = lastFrameTimer.Read();

	// Amount of frames during the last second
	if (lastSecFrames->Read() >= 1000)
	{
		frames_on_last_update = last_second_frame_count;
		last_second_frame_count = 0;
		lastSecFrames->Start();
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

	for (int i = list_modules.capacity() - 1; i > 0; i--) {

		list_modules[i]->CleanUp();
	}

	return true;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}