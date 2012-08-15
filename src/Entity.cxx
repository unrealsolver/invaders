#include "Entity.h"


void
Entity::SetTextureFromFile (const std::string& path)
{
	texture.loadFromFile (path);
	setTexture (texture);
	setOrigin (texture.getSize().x / 2 + 1, texture.getSize().y / 2 + 1);
	texture.setSmooth (false);
	setScale (10, 10);
	setColor (sf::Color (192,192,192, 192));
	m = 100.f;
	V.x = V.y = 0;
	//font.loadFromFile ("../resources/fonts/visitor1.ttf");//tmp
}

void
Entity::setObjMan (std::multimap<float, Entity*> *objects)
{
	this->objects = objects;
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
	/*unsigned x,y;
	for (x = 0; x < texture.GetWidth(); x++)
		for (y = 0; y < texture.GetHeight(); y++)
			if (texture.GetPixel(x, y) == col_1)
				texture.SetPixel (x, y, col_2);
	*/
}

void
Entity::OnIdle (float dt)
{
	
	V += F/m;
	move (V * dt);
	F.x = F.y = 0;
}



