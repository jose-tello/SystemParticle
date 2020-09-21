#include "Emiter.h"
#include "Application.h"
#include "Textures.h"
#include "Render.h"
#include "Particle.h"
#include "math.h"

Emiter::Emiter(fMPoint& position, fMPoint& particleSpeed, iMPoint& particleVariationSpeed, fMPoint& particleAcceleration,
	iMPoint& particleVariationAcceleration, float particleAngularSpeed, int particleVariableAngularSpeed, float particlesRate,
	float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture, Animation particleAnimation, bool fade, int r, int g, int b) :

	state(particleSpeed, particleAcceleration, particleAngularSpeed, particlesRate, particlesLifeTime, areaOfSpawn, particleVariationSpeed, particleVariationAcceleration, particleVariableAngularSpeed, fade, r, g, b),
	
	position(position),

	particleTexture(texture),
	particleAnimation(particleAnimation),

	active(true),

	particlesEmited(0.0f),
	activeParticles(0)
{
	Start();
}


Emiter::Emiter(float positionX, float positionY, float particleSpeedX, float particleSpeedY, int particleVariationSpeedX, int particleVariationSpeedY,
	float particleAccelerationX, float particleAccelerationY, int particleVariationAccelerationX, int particleVariationAccelerationY, float particleAngularSpeed,
	int particleVariableAngularSpeed, float particlesRate, float particlesLifeTime, SDL_Rect* areaOfSpawn, SDL_Texture* texture, Animation particleAnimation, bool fade, int r, int g, int b) :

	state(fMPoint(particleSpeedX, particleSpeedY), fMPoint(particleAccelerationX, particleAccelerationY), particleAngularSpeed, particlesRate, particlesLifeTime, 
		  areaOfSpawn, iMPoint(particleVariationSpeedX, particleVariationSpeedY), iMPoint(particleVariationAccelerationX, particleVariationAccelerationY), particleVariableAngularSpeed, fade, r, g, b),

	position{ positionX, positionY },

	particleTexture(texture),
	particleAnimation(particleAnimation),

	active(true),
	
	particlesEmited(0.0f),
	activeParticles(0)
{
	Start();
}


void Emiter::Start()
{
	//TODO 3: Just calculate the max number of particles you will have in screen
	//particles rate * particles life time
	int maxParticles = state.GetParticlesRate() * state.GetParticlesLifeTime() + 1;

	particleVector.reserve(maxParticles);

	for (int i = 0; i < maxParticles; i++)
	{
		particleVector.push_back(Particle());
	}
}


Emiter::~Emiter()
{
	particleVector.clear();

	particleTexture = nullptr;
}


void Emiter::Update(float dt)
{
	if (active)
	{
		ThrowParticles();
	}

	for (int i = 0; i < activeParticles; i++)
	{
		if (particleVector[i].Update(dt) == false)
		{
			activeParticles--;
			particleVector[i] = particleVector[activeParticles];
			particleVector[activeParticles].Deactivate();
		}
	}
}


void Emiter::PostUpdate(float dt)
{
	DrawParticles();
}


void Emiter::Desactivate()
{
	active = false;
}

void Emiter::Activate()
{
	active = true;
}


//This funtions activates the necesary particles and gives them the initial values
void Emiter::ThrowParticles() {

	//You could use delta time instead of particlesPerFrame, but i dont recommend it
	particlesEmited += state.GetParticlesPerFrame();

	if (particlesEmited >= 1)
	{
		int emited = 0;
		int maxParticles = particleVector.size();

		for (int i = activeParticles; i < maxParticles; i++)
		{
			//TODO 2: Call Activate(), use Generate...() functions to get the parameters Activate() needs.
			//Activate returns false if the particle is already active, and true if we activate it.
			float posX, posY, spdX, spdY, accX, accY, aspd;

			state.GenerateValues(position, posX, posY, spdX, spdY, accX, accY, aspd);

			particleVector[i].Reset(posX, posY, spdX, spdY, accX, accY, aspd, state.GetParticlesLifeTime());
			emited++;
			activeParticles++;

			//If we activated the necesary particles this frame, break
			if ((int)particlesEmited == emited)
				break;
		}

		particlesEmited -= emited;
	}
}


void Emiter::DrawParticles()
{
	fMPoint pos;
	float angle;
	float lifeTime;
	SDL_Rect rect;

	Uint8 transparency = 255;
	Uint8 r = 255;
	Uint8 g = 255;
	Uint8 b = 255;
	float maxLife = state.GetParticlesLifeTime();

	for (int i = 0; i < activeParticles; i++)
	{
		particleVector[i].GetDrawVariables(pos, angle, lifeTime);
		rect = particleAnimation.GetFrameBox(state.GetParticlesLifeTime() - lifeTime);

		if (App->renderer->IsInsideCamera(rect))
		{
			particleVector[i].GetDrawVariables(pos, angle, lifeTime);

			if (state.fadeParticles == true)
			{
				transparency = lifeTime / maxLife * 255;
			}

			if (state.fadeColor == true)
			{
				r = lifeTime / maxLife * 255;

				g = lifeTime / maxLife * 255;

				b = lifeTime / maxLife * 255;

				if (r < state.rColor)
					r = state.rColor;

				if (g < state.gColor)
					g = state.gColor;

				if (b < state.bColor)
					b = state.bColor;
			}


			App->renderer->Blit(particleTexture, pos.x, pos.y, &rect, transparency, r, g, b, 0, angle);
		}
	}
}


void Emiter::GetPosition(int& x, int& y)
{
	x = position.x;
	y = position.y;
}

void Emiter::SetPosition(int x, int y)
{
	position.x = x;
	position.y = y;
}