#include "Emiter.h"
#include "Textures.h"
#include "Render.h"

Emiter::Emiter(vector<Particle> &particleSamples, vector<int> &position, vector<int> &, vector<int>&, SDL_Rect&, SDL_Texture*);
~Emiter();

void Update();
void PostUpdate();