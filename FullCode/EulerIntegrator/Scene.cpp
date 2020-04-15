#include "Scene.h"
#include "Window.h"
#include "Application.h"
#include "Input.h"
#include "Render.h"


ModuleScene::ModuleScene(bool start_enabled) : Module(start_enabled)
{
	LOG("Contructor of Module Scene has been called");
}

// Destructor
ModuleScene::~ModuleScene()
{
	LOG("Destructor of Module Scene has been called");
}

bool ModuleScene::Start() {
	LOG("Module Scene succesful Start()");

	
	
	return true;
}



update_status ModuleScene::Update(float dt) {

	//spawns new static sphere
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) 
	{
		
	}

	//spawns new dynamic sphere
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		
	}

	return UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp() 
{
	LOG("Scene CleanUp has been called");
	return true;

}

