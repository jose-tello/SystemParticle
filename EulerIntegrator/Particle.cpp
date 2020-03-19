#include "Particle.h"
#include "Textures.h"
#include "Application.h"
#include "Render.h"

Particle::Particle() 
{}


Particle::Particle(std::vector<float> &position, std::vector<float> &speed, std::vector<float> &acceleration, float angle, float angularSpeed, float life, SDL_Texture* texture) :
	position(position),
	originalPosition(position),
	speed(speed),
	originalSpeed(speed),
	acceleration(acceleration),
	angle(angle),
	angularSpeed(angularSpeed),
	life(life),
	originalLife(life),
	texture(texture),
	active(false)
{}


Particle::Particle(float positionX, float positionY, float speedX, float speedY, float accelerationX, float accelerationY, float angle, float angularSpeed, float life, SDL_Texture* texture) :
	position{ positionX, positionY },
	originalPosition{ positionX, positionY },
	speed{ speedX, speedY},
	originalSpeed{ speedX, speedY },
	acceleration{ accelerationX, accelerationY },
	angle(angle),
	angularSpeed(angularSpeed),
	life(life),
	originalLife(life),
	texture(texture),
	active(false)
{}


Particle::~Particle()
{
	position.clear();
	speed.clear();
	acceleration.clear();
	
	texture = nullptr;
}


std::vector<float> Particle::GetPosition() {
	return position;
}

std::vector<float> Particle::GetSpeed() {
	return speed;
}

std::vector<float> Particle::GetAcceleration() {
	return acceleration;
}

float Particle::GetAngle() {
	return angle;
}

float Particle::GetAngularSpeed() {
	return angularSpeed;
}

float Particle::GetLife() {
	return life;
}

SDL_Texture* Particle::GetTexture() {
	return texture;
}

void Particle::SetPosition(std::vector<float> &pos) {
	position = pos;
}

void Particle::SetSpeed(std::vector<float>& spd) {
	speed = spd;
}

void Particle::SetAcceleration(std::vector<float>& acc) {
	acceleration = acc;
}

void Particle::SetAngle(float ang) {
	angle = ang;
}

void Particle::SetAngularSpeed(float aspd) {
	angularSpeed = aspd;
}


void Particle::Update(float dt)
{
	if (active)
	{
		Move(dt);
		CheckLife(dt);
	}
}


void Particle::PostUpdate() 
{
	if (active)
		Draw();
}


void Particle::Draw() 
{
	App->renderer->Blit(texture, position[0], position[1], nullptr, 0, angle);
}

void Particle::Move(float dt) 
{
	speed[0] += acceleration[0] * dt * TIME_CONST;
	speed[1] += acceleration[1] * dt * TIME_CONST;

	position[0] += speed[0] * dt * TIME_CONST;
	position[1] += speed[1] * dt * TIME_CONST;

	angle += angularSpeed * dt * TIME_CONST;
}

void Particle::CheckLife(float dt) 
{
	life -= dt;

	if (life < 0)
	{
		Desactivate();
	}
}


void Particle::Desactivate() 
{
	active = false;
}


void Particle::Restart(float x, float y)
{
	position[0] = x;
	position[1] = y;
	speed = originalSpeed;

	life = originalLife;
}


bool Particle::Activate(float x, float y) {

	if (active)
		return false;

	else
	{
		Restart(x, y);
		active = true;
		return true;
	}
}