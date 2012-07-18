#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Particle.h"
#include "Ship.h"
#include "Misc.h"
#include "Gui.h"
#include <boost/lexical_cast.hpp>
//#include <map>

int
main (void)
{
	sf::WindowSettings Settings;
	Settings.DepthBits         = 24; // Request a 24 bits depth buffer
	Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
	Settings.AntialiasingLevel = 2;  // Request 2 levels of antialiasing
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Invaders", sf::Style::Resize | sf::Style::Close, Settings);
	sf::Clock Clock;
	
	sf::Font MyFont;
	MyFont.LoadFromFile ("../resources/fonts/DejaVuSans.ttf", 50);
	sf::String text  ("", MyFont, 24);
	text.SetX (592);
	text.SetY (85);
	text.SetColor (sf::Color (0,0,0));
	
	sf::Vector2f Center(500, 300);
	sf::Vector2f HalfSize(400, 300);
	sf::View View (Center, HalfSize);
	
	Ship ship;
	Entity invader;
	
	invader.SetImageFromFile("../resources/pics/invader_1.png");
	invader.SetX (400.f);
	invader.SetY (300.f);
	invader.SetMass (100.f);
	
	ship.SetImageFromFile ("../resources/pics/ship.png");
	ship.SetX (400.f);
	ship.SetY (400.f);
	ship.SetMass (10.f);
	ship.SetMarchEngineForce (10.f);
		
	sf::Vector2f mouse_pos;
	sf::Vector2f scroll_view_pos;
	sf::Vector2f scroll_mouse_pos;
	
	//objects_to_draw.insert (::pair<int,sf::Sprite>(1, ship));
	
	GUIWindow mywindow = GUIWindow (575, 25, 200, 200, sf::Color (128, 128,64, 128));
	GUICheckBox checkbox = GUICheckBox (600, 50, "Draw grid");
	
	bool key_pressed_lock = false;
	
	while (App.IsOpened())
	{
		sf::Event Event;
		while (App.GetEvent(Event))
		{
			if (Event.Type == sf::Event::Closed)
				App.Close();
			if (Event.Type == sf::Event::KeyPressed)
			{
				key_pressed_lock = false;
				switch (Event.Key.Code)
				{
					case sf::Key::Escape:
						App.Close();
				}
			}
		}
		/* Начиная отсюда и до секции GAME идёт невообразимая хуита. Переписать. */
		const sf::Input& Input = App.GetInput();
		
		mouse_pos = App.ConvertCoords(Input.GetMouseX(), Input.GetMouseY());
		
		if (Input.IsMouseButtonDown (sf::Mouse::Middle))
		{
			/* TODO: Rewrite */
			View.SetCenter (scroll_view_pos - mouse_pos + scroll_mouse_pos);
			//text.SetText (boost::lexical_cast<std::string> (Input.GetMouseX() - last_mouse_x));//View.GetCenter().x));
		}
		else
		{
			scroll_view_pos = View.GetCenter();
			scroll_mouse_pos = mouse_pos;
		}
		
		bool up_key_down  = Input.IsKeyDown(sf::Key::Up);
		bool left_key_down = Input.IsKeyDown(sf::Key::Left);
		bool right_key_down = Input.IsKeyDown(sf::Key::Right);
		
		if (up_key_down)
			ship.SetMarchEngine (true);
		else 
		{
			if (key_pressed_lock ==false)
			{
				ship.SetForce (sf::Vector2f (0, 0));
				key_pressed_lock = true;
				ship.SetMarchEngine (false);
			}
		}
		
		if (left_key_down)
		{
			ship.SetRotation (ship.GetRotation() + 2);
		}
		else if (right_key_down)
		{
			ship.SetRotation (ship.GetRotation() - 2);
		}
		
		/* **** *
		 * GAME *
		 * **** */
		App.SetView (View); //Камера
		App.Clear (sf::Color(255, 255, 255)); //Свет
		
		if (checkbox.GetState ()) 
		{
			draw_grid (App, View, 200, 3);
			draw_grid (App, View, 50, 1);
		}
		
		float dt = App.GetFrameTime();
		
		ship.OnIdle (dt);
		invader.OnIdle (dt);
		invader.SetRotation (Clock.GetElapsedTime() * 100);
		
		
		App.Draw (invader); //Кино
		App.Draw (ship);
		
		/* ********* *
		 * INTERFACE *
		 * ********* */	
		App.SetView (App.GetDefaultView());
		mywindow.Draw (App);
		checkbox.Draw (App);
		text.SetText ("FPS: " + boost::lexical_cast<std::string> (floor (1.f/App.GetFrameTime())));
		App.Draw (text);
		
		App.Display();
	}
	
	return 0;
}
