#ifndef __ModuleTextures_H__
#define __ModuleTextures_H__

#include "Module.h"
#include "Globals.h"

#define MAX_TEXTURES 50

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures(bool start_enabled = true);
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	SDL_Texture* const LoadSurface(SDL_Surface* surface);

	bool Unload(SDL_Texture* texture);
	void GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:
	SDL_Texture* textures[MAX_TEXTURES];
};

#endif // __ModuleTextures_H__
