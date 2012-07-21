#include "Entity.h"


void
Entity::SetImageFromFile (const std::string& path)
{
	image.LoadFromFile (path);
	SetImage (image);
	SetCenter (image.GetWidth()/2 + 1, image.GetHeight()/2 + 1);
	image.SetSmooth (false);
	SetScaleX (15);
	SetScaleY (15);
	SetColor (sf::Color (64,64,64, 192));
}

void
Entity::SetForce (const sf::Vector2f& force)
{
	this->F = force;
}

const sf::Vector2f&
Entity::GetForce (void)
{
	return F;
}

void
Entity::SetVelocity (const sf::Vector2f& velocity)
{
	this->V = velocity;
}

const sf::Vector2f&
Entity::GetVelocity (void)
{
	return V;
}

void
Entity::SetMass (const float mass)
{
	this->m = mass;
}

const float
Entity::GetMass (void)
{
	return m;
}

void
Entity::SwapColor (const sf::Color& col_1, const sf::Color& col_2)
{
	unsigned x,y;
	for (x = 0; x < image.GetWidth(); x++)
		for (y = 0; y < image.GetHeight(); y++)
			if (image.GetPixel(x, y) == col_1)
				image.SetPixel (x, y, col_2);
}

void
Entity::OnIdle (float dt)
{

	
	//std::cout << "Force is :" << F.x << " | " << F.y << std::endl;
	
	SetVelocity (V + F/m);
	Move (V * dt);
	F.x = F.y = 0;
}



