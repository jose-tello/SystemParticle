#include "Particle.h"
#include "Textures.h"
#include "Application.h"
#include "Render.h"

Particle::Particle() 
{}


Particle::Particle(std::vector<int>& position, std::vector<int>& speed, std::vector<int>& acceleration, float angle, float angularSpeed, float life, SDL_Texture* texture) :
	position(position),
	speed(speed),
	acceleration(acceleration),
	angle(angle),
	angularSpeed(angularSpeed),
	life(life),
	texture(texture)
{}


Particle::Particle(int positionX, int positionY, int speedX, int speedY, int accelerationX, int accelerationY, float angle, float angularSpeed, float life, SDL_Texture* texture) :
	position(positionX, positionY),
	speed(speedX, speedY),
	acceleration(accelerationX, accelerationY),
	angle(angle),
	angularSpeed(angularSpeed),
	life(life),
	texture(texture)
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


void Particle::Update(float dt) {

	Move(dt);
	CheckLife(dt);
}


void Particle::PostUpdate() {

	Draw();
}


void Particle::Draw() {

	

}

void Particle::Move(float dt) {

	speed[0] += acceleration[0] * dt;
	speed[1] += acceleration[1] * dt;

	position[0] += speed[0] * dt;
	position[1] += speed[1] * dt;

	angle += angularSpeed * dt;
}

void Particle::CheckLife(float dt) {
	
	life -= dt;

	if (life < 0)
	{
		//do things, i dont fucking know yet XD
	}
}