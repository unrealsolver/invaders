#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Particle.h"
#include "Ship.h"
#include "Gui.h"
#include "Grid.h"
#include "Background.h"
#include <boost/lexical_cast.hpp>

int
main (void)
{
	/*sf::WindowSettings Settings;
	Settings.DepthBits         = 24; // Request a 24 bits depth buffer
	Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
	Settings.AntialiasingLevel = 2;  // Request 2 levels of antialiasing*/
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "Invaders");//, sf::Style::Resize | sf::Style::Close, Settings);
	//sf::Clock Clock;
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
	
	Ship ship;
	Entity invader;
	
	BackGround bg;
	bg.LoadImage ("../resources/pics/background_1.png", 1);
	bg.LoadImage ("../resources/pics/background_2.png", 2);
	
	invader.SetTextureFromFile("../resources/pics/invader_1.png");
	invader.setPosition (400.f, 300.f);
	invader.SetMass (100.f);
	
	ship.SetTextureFromFile ("../resources/pics/ship_w.png");
	ship.setPosition (400.f, 400.f);
	ship.SetMass (10.f);
	ship.SetMarchEngineForce (10.f);
	
	
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
		sf::Vector2f mouse_ort = mouse_pos - ship.getPosition() + View.getCenter() - View.getSize()/2.f;
		
		sf::RectangleShape marker;
		marker.setSize (sf::Vector2f (10, 10));
		marker.setPosition (mouse_ort + ship.getPosition());
		marker.setFillColor (sf::Color (40, 255, 90));
		//std::cout << mouse_ort.x << std::endl;
		//std::cout << << std::endl;
		//mouse_ort.x /= sqrt (mouse_ort.x*mouse_ort.x + mouse_ort.y*mouse_ort.y);
		//mouse_ort.y /= sqrt (mouse_ort.x*mouse_ort.x + mouse_ort.y*mouse_ort.y);
		
		ship.setRotation (atan2 (mouse_ort.x, - mouse_ort.y) * 180 /M_PI);
		//mouse_pos = App.ConvertCoords(Input.GetMouseX(), Input.GetMouseY());
		
		if (sf::Mouse::isButtonPressed (sf::Mouse::Left))
		{
			/* TODO: Rewrite */
			View.setCenter (scroll_view_pos - mouse_pos + scroll_mouse_pos);
			//text.SetText (boost::lexical_cast<std::string> (Input.GetMouseX() - last_mouse_x));//View.GetCenter().x));
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
			//View.zoom (1.01);
			ship.setRotation (ship.getRotation() - 2);
		}
		else if (right_key_down)
		{
			ship.setRotation (ship.getRotation() + 2);
		}
		
		/* **** *
		 * GAME *
		 * **** */
		 /*
		if (check_follow.GetState ())
		{
			follow_view.setCenter (ship.getPosition());
			App.setView (follow_view);
			std::cout << follow_view.getCenter().x - ship.getPosition().x << std::endl;
		}
		else
			App.setView (View); //Камера
		sf::Color back_color;
		back_color = (check_day.GetState ())?sf::Color(10,10,10):sf::Color (255,255,255);
		App.clear (back_color); //Свет
		*/
		//View.setCenter (ship.getPosition());
		App.setView (View); //Камера
		sf::Color back_color;
		back_color = sf::Color(0x37, 0x8F, 0xAB);//10,10,10);
		App.clear (back_color); //Свет
		
		int spin = 1;
		/*
		if (check_invader.GetState ()) 
		{
			spin = 100;
		}
		else
		{
			spin = 0;
		}
		*/
		
			
		sf::Time time = clock.getElapsedTime();
		float dt = time.asSeconds();
		ship.OnIdle (dt);
		invader.OnIdle (dt);
		invader.rotate (dt * spin);
		
		//bg.Draw (App); //WARNING! BREAK WHOLE APP!
		/*
		if (check_grid.GetState ()) 
		{
			draw_grid (App, View, 200, 3);
			draw_grid (App, View, 50, 1);
		}
		*/
		
		grid.draw();
		App.draw (invader);
		App.draw (ship);
		App.draw (marker);
		
		/* ********* *
		 * INTERFACE *
		 * ********* */	
		App.setView (App.getDefaultView());

		/*mywindow.Draw (App);
		check_grid.Draw (App);
		check_invader.Draw (App);
		check_day.Draw (App);
		check_follow.Draw (App);
		*/
		
		text.setString ("FPS: " + boost::lexical_cast<std::string> (floor (1.f/dt)));
		App.draw (text);
		
		App.display();
		App.setView (View); //Камера
	}
	
	return 0;
}
