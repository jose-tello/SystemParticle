#include "Particle.h"
#include "Textures.h"
#include "Application.h"


Particle::Particle() :

	position{ NULL, NULL },
	speed{ NULL, NULL },
	acceleration{ NULL, NULL },
	angle(0),
	angularSpeed(0),

	life(0.0f)
{}



Particle::Particle(float positionX, float positionY, float speedX, float speedY, float accelerationX, float accelerationY,
	float angle, float angularSpeed, float life, bool fade) :

	position{ positionX, positionY },
	speed{ speedX, speedY },
	acceleration{ accelerationX, accelerationY },
	angle(angle),
	angularSpeed(angularSpeed),

	life(life)
{}


Particle::~Particle()
{
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


bool Particle::Update(float dt)
{
	if (life > 0)
	{
		Move(dt);
		CheckLife(dt);

		if (life > 0)
			return true;

		else
			return false;
	}
}


void Particle::GetDrawVariables(fMPoint &pos, float &ang, float &lifeTime)
{
	pos = position;
	ang = angle;
	lifeTime = life;
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
}


bool Particle::IsActive()
{
	if (life > 0)
		return true;

	else
		return false;
}


void Particle::Deactivate()
{
	life = 0.0f;
}


void Particle::Reset(float x, float y, float speedX, float speedY, float accX, float accY, float angSpeed, float lifeTime)
{
	life = lifeTime;

	position.x = x;
	position.y = y;

	speed.x = speedX;
	speed.y = speedY;

	acceleration.x = accX;
	acceleration.y = accY;

	angularSpeed = angSpeed;

}


void Particle::operator=(Particle p)
{
	position = p.position; 
	speed = p.speed;
	acceleration = p.acceleration;

	angle = p.angle;
	angularSpeed = p.angularSpeed;

	life = p.life;
}