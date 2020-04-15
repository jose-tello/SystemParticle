#include "Application.h"
#include "Globals.h"
#include "Module.h"


class ModuleScene : public Module
{

public:
	ModuleScene(bool start_enabled = true);
	~ModuleScene();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

private:
	
};