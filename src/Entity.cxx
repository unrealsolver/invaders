#include "Entity.h"


void
Entity::SetTextureFromFile (const std::string& path)
{
	texture.loadFromFile (path);
	setTexture (texture);
	setOrigin (texture.getSize().x / 2 + 1, texture.getSize().y / 2 + 1);
	texture.setSmooth (false);
	setScale (10, 10);
	setColor (sf::Color (64,64,64, 192));
	//font.loadFromFile ("../resources/fonts/visitor1.ttf");//tmp
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
Entity::Draw (sf::RenderWindow &target)
{
	//sf::Font MyFont;
	//
	/*sf::String text  ("sample", font, 24);
	text.SetX (GetPosition().x+50);
	text.SetY (GetPosition().y-80);
	text.SetColor (sf::Color (255,255,255));
	text.SetText (boost::lexical_cast<std::string> (floor (sqrt(V.x*V.x + V.y*V.y))));
	sf::Shape box = sf::Shape::Circle (GetPosition().x, GetPosition().y, 12, sf::Color(0,0,0,0) , 4, sf::Color (255,0,0, 190));
	sf::Shape cross_v = sf::Shape::Line (GetPosition().x, GetPosition().y-100, GetPosition().x, GetPosition().y+100, 2, sf::Color (255,32,0, 190));
	sf::Shape cross_h = sf::Shape::Line (GetPosition().x -100, GetPosition().y, GetPosition().x+100, GetPosition().y, 2, sf::Color (255,32,0, 190));
	sf::Shape arrow = sf::Shape::Line (GetPosition().x, GetPosition().y, GetPosition().x+50, GetPosition().y-50, 2, sf::Color (255,32,0, 190));
	sf::Shape arrow_2 = sf::Shape::Line (GetPosition().x+50, GetPosition().y-50, GetPosition().x+75, GetPosition().y-50, 2, sf::Color (255,32,0, 190));
	
	
	target.Draw (box);
	target.Draw (cross_v);
	target.Draw (cross_h);
	target.Draw (arrow);
	target.Draw (arrow_2);
	target.Draw (text);
	*/
}

void
Entity::OnIdle (float dt)
{

	
	//std::cout << "Force is :" << F.x << " | " << F.y << std::endl;
	
	
	SetVelocity (V + F/m);
	move (V * (sqrtf(prevdt*prevdt + dt*dt))); //tmp
	prevdt = dt;
	F.x = F.y = 0;
}



