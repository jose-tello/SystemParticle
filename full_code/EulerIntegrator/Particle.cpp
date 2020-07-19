#include "Particle.h"
#include "Textures.h"
#include "Application.h"
#include "Render.h"


Particle::Particle()
{}


Particle::Particle(float life, SDL_Texture* texture, Animation animation, bool fade) :

	position{ NULL, NULL },
	speed{ NULL, NULL },
	acceleration{ NULL, NULL },
	angle(0),
	angularSpeed(0),

	life(life),
	originalLife(life),

	texture(texture),
	animation(animation),

	fade(fade),
	active(false)
{}



Particle::Particle(float positionX, float positionY, float speedX, float speedY, float accelerationX, float accelerationY,
	float angle, float angularSpeed, float life, SDL_Texture* texture, Animation animation, bool fade) :

	position{ positionX, positionY },
	speed{ speedX, speedY },
	acceleration{ accelerationX, accelerationY },
	angle(angle),
	angularSpeed(angularSpeed),

	life(life),
	originalLife(life),

	texture(texture),
	animation(animation),

	fade(fade),
	active(false)
{}


Particle::~Particle()
{
	texture = nullptr;
}


fMPoint Particle::GetPosition() {
	return position;
}


fMPoint Particle::GetSpeed() {
	return speed;
}


fMPoint Particle::GetAcceleration() {
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


void Particle::SetPosition(fMPoint &pos) {
	position = pos;
}


void Particle::SetSpeed(fMPoint &spd) {
	speed = spd;
}


void Particle::SetAcceleration(fMPoint &acc) {
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


void Particle::PostUpdate(float dt)
{
	if (active)
		Draw(dt);
}


void Particle::Draw(float dt)
{
	if (fade == true)
	{
		Uint8 transparency = life / originalLife * 255;
		App->renderer->Blit(texture, position.x, position.y, &animation.GetCurrentFrameBox(dt), transparency, 0, angle);
	}

	else
		App->renderer->Blit(texture, position.x, position.y, &animation.GetCurrentFrameBox(dt), 255, 0, angle);

}

void Particle::Move(float dt)
{
	speed.x += acceleration.x * dt * TIME_CONST;
	speed.y += acceleration.y * dt * TIME_CONST;

	//TODO 1: Do the same with position and angles
	position.x += speed.x * dt * TIME_CONST;
	position.y += speed.y * dt * TIME_CONST;

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


bool Particle::Activate()
{
	return !active;
}


void Particle::Reset(float x, float y, float speedX, float speedY, float accX, float accY, float angSpeed)
{
	life = originalLife;

	position.x = x;
	position.y = y;

	speed.x = speedX;
	speed.y = speedY;

	acceleration.x = accX;
	acceleration.y = accY;

	angularSpeed = angSpeed;

	active = true;
}