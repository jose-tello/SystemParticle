#include "Particle.h"
#include "Textures.h"
#include "Application.h"
#include "Render.h"

Particle::Particle() 
{}


Particle::Particle(std::vector<int> &position, std::vector<int> &speed, std::vector<int> &acceleration, float angle, float angularSpeed, float life, SDL_Texture* texture) :
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


Particle::Particle(int positionX, int positionY, int speedX, int speedY, int accelerationX, int accelerationY, float angle, float angularSpeed, float life, SDL_Texture* texture) :
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


std::vector<int> Particle::GetPosition() {
	return position;
}

std::vector<int> Particle::GetSpeed() {
	return speed;
}

std::vector<int> Particle::GetAcceleration() {
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

void Particle::SetPosition(std::vector<int> &pos) {
	position = pos;
}

void Particle::SetSpeed(std::vector<int>& spd) {
	speed = spd;
}

void Particle::SetAcceleration(std::vector<int>& acc) {
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
	speed[0] += round(acceleration[0] * dt);
	speed[1] += round(acceleration[1] * dt);

	position[0] += round(speed[0] * dt);
	position[1] += round(speed[1] * dt);

	angle += round(angularSpeed * dt);
}

void Particle::CheckLife(float dt) 
{
	//life -= dt;
	life--;
	if (life < 0)
	{
		Desactivate();
	}
}


void Particle::Desactivate() 
{
	active = false;
}


void Particle::Restart() 
{
	position = originalPosition;
	speed = originalSpeed;

	life = originalLife;
}


bool Particle::Activate() {

	if (active)
		return false;

	else
	{
		Restart();
		active = true;
		return true;
	}
}