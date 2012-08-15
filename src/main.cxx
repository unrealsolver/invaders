#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "Entity.h"
#include "Particle.h"
#include "Ship.h"
#include "Gui.h"
#include "Grid.h"
#include "Background.h"
#include <boost/lexical_cast.hpp>

#define OBJECTS(TARGET)\
			for (object = objects.begin(); object != objects.end(); object++)\
				object->second->TARGET;

int
main (void)
{	
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Invaders");//, sf::Style::Resize | sf::Style::Close, Settings);
	
	std::multimap<float, Entity*> objects;
	std::multimap<float, Entity*>::iterator object;
	sf::Clock clock;
	
	sf::Font MyFont;
	MyFont.loadFromFile ("../resources/fonts/visitor1.ttf");
	sf::Text text  ("", MyFont, 32);
	text.setPosition (600, 20);//592.f, 165.f);
	text.setColor (sf::Color (255,255,255));
	
	sf::Vector2f Center(500, 300);
	sf::Vector2f HalfSize(400, 300);
	sf::View follow_view (Center,HalfSize);
	sf::View View (Center, HalfSize);
	
	App.setView (View);
	Grid grid (App);
	
	object = objects.insert (std::pair <float, Entity*> (0, new Entity (App)));
	object->second->SetTextureFromFile("../resources/pics/invader_1.png");
	object->second->setPosition (400.f, 300.f);
	object->second->SetVelocity (sf::Vector2f (1,0));
	
	Ship *Player = new Ship (App);
	object =  objects.insert (std::pair <float, Entity*> (0, Player));
	Player->setObjMan (&objects);
	Player->SetTextureFromFile ("../resources/pics/ship_w.png");
	Player->setPosition (400.f, 400.f);
	Player->SetMass (10.f);
	Player->SetMarchEngineForce (10.f);
	
	sf::Vector2f mouse_pos;
	sf::Vector2f scroll_view_pos;
	sf::Vector2f scroll_mouse_pos;
	
	GUIWindow mywindow = GUIWindow (575, 25, 200, 200, sf::Color (200, 255,200, 40));
	GUICheckBox check_grid = GUICheckBox (600, 50, "Draw grid");
	GUICheckBox check_invader = GUICheckBox (600, 80, "Spin");
	GUICheckBox check_day = GUICheckBox (600, 110, "Day/Night");
	GUICheckBox check_follow = GUICheckBox (600, 140, "Follow");
	
	bool key_pressed_lock = false;
	while (App.isOpen())
	{
		clock.restart();
		
		sf::Event Event;
		while (App.pollEvent(Event))
		{
			if (Event.type == sf::Event::MouseWheelMoved)
			{
				View.zoom (1 - Event.mouseWheel.delta*0.01);
				grid.adjust ();
			}
			if (Event.type == sf::Event::Closed)
				App.close();
			if (Event.type == sf::Event::KeyPressed)
			{
				key_pressed_lock = false;
				switch (Event.key.code)
				{
					case sf::Keyboard::Escape:
						App.close();
				}
			}
		}
		
		/* Начиная отсюда и до секции GAME идёт невообразимая хуита. Переписать. */
		
		mouse_pos =  (sf::Vector2f) sf::Mouse::getPosition (App);
		mouse_pos /= App.getSize().x/View.getSize().x; //Correction of zoom-factor
		/* Вычисление орта указателя мыши относительно игрока */
		sf::Vector2f mouse_ort = mouse_pos - Player->getPosition() + View.getCenter() - View.getSize()/2.f;
		
		sf::RectangleShape marker;
		marker.setSize (sf::Vector2f (10, 10));
		marker.setPosition (mouse_ort + Player->getPosition());
		marker.setFillColor (sf::Color (40, 255, 90));
		
		Player->setRotation (atan2 (mouse_ort.x, - mouse_ort.y) * 180 /M_PI);
		
		if (sf::Mouse::isButtonPressed (sf::Mouse::Right))
		{
			/* TODO: Rewrite */
			View.setCenter (scroll_view_pos - mouse_pos + scroll_mouse_pos);
		}
		else
		{
			scroll_view_pos = View.getCenter();
			scroll_mouse_pos = mouse_pos;
		}
		
		bool up_key_down  = sf::Keyboard::isKeyPressed (sf::Keyboard::Up);
		bool left_key_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool right_key_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
		
		if (up_key_down)
			Player->SetMarchEngine (true);
		else 
		{
			if (key_pressed_lock == false)
			{
				Player->SetForce (sf::Vector2f (0, 0));
				key_pressed_lock = true;
				Player->SetMarchEngine (false);
			}
		}
		
		if (left_key_down)
		{
			Player->setRotation (Player->getRotation() - 2);
		}
		else if (right_key_down)
		{
			Player->setRotation (Player->getRotation() + 2);
		}
		
		/* **** *
		 * GAME *
		 * **** */

		App.setView (View); //Камера
		sf::Color back_color;
		back_color = sf::Color(0x37, 0x8F, 0xAB);//10,10,10);
		App.clear (back_color); //Свет
			
		sf::Time time = clock.getElapsedTime();
		float dt = time.asSeconds();
		OBJECTS(OnIdle(dt));
		
		grid.draw();
		
		OBJECTS(draw());
		App.draw (marker);
		
		/* ********* *
		 * INTERFACE *
		 * ********* */	
		App.setView (App.getDefaultView());
		
		int fps_scale = 5; //GOVNOKOD
		static int nframe; //GOVNOKOD
		nframe++; //GOVNOKOD. Дальше тоже, писать лень...
		if (nframe == fps_scale)
		{
			nframe = 0;
			text.setString ("FPS: " + boost::lexical_cast<std::string> (floor (1.f/dt)));
		}
		App.draw (text);
		
		App.display();
		App.setView (View); //Камера
	}
	
	return 0;
}
