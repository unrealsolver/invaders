#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Entity.h"
#include "Particle.h"
#include "Ship.h"
#include "Misc.h"
#include "Gui.h"
#include <boost/lexical_cast.hpp>

class BackGround
{
	public:
	
		int LoadImage (std::string, unsigned char); //Щито поделать...
		void Draw (sf::RenderWindow&);
		
		friend class sf::Image;
	private:
		sf::Texture image[3];
		sf::Sprite sprite[3];
};

int
BackGround::LoadImage (std::string path, unsigned char layer)
{
	layer--;
	if (layer > 2)
	{
		std::cout << "Bad layer number " << (unsigned) layer << std::endl;
		return 1;
	}
	image[layer].loadFromFile (path);
	image[layer].setSmooth (false);
	sprite[layer].setTexture (image[layer]);
	sprite[layer].setScale (10,10);
}


void
BackGround::Draw (sf::RenderWindow &App)
{
	const sf::View  *view = &App.getView();	
	const sf::FloatRect *screen = &view->getViewport();
	
	int i = 1;
	int c = 0;
	int f = 15; 
	//sprite.SetPosition (screen->Left - fmod(screen->Left/f, sprite.GetSize().x), floor(screen->Top/f));
	for (i = 0; i < 2; i++)
	{
		f /= i + 1;
		for (int x = screen->left - fmod(screen->left/f, sprite[i].getTextureRect().left); x < screen->width; x += sprite[i].getTextureRect().left) // >10: C++ is magic...
		{	
			for (int y = screen->top - fmod(screen->top/f, sprite[i].getTextureRect().top); y < screen->height; y += sprite[i].getTextureRect().top)
			{
				if (screen->left - fmod(screen->left/f, sprite[i].getTextureRect().left) > screen->left) 
				{
					std::cout << "WTF?!" << std::endl;
				//	exit (1);
				}
				sprite[i].setPosition (x, y);
				App.draw (sprite[i]);
				c++;
			}
		}
	}
	std::cout << "Total tiles: " << c << std::endl;
	
}


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
	text.setPosition (592.f, 165.f);
	text.setColor (sf::Color (128,128,128));
	
	sf::Vector2f Center(500, 300);
	sf::Vector2f HalfSize(400, 300);
	sf::View follow_view (Center,HalfSize);
	sf::View View (Center, HalfSize);
	
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
	
	//objects_to_draw.insert (::pair<int,sf::Sprite>(1, ship));
	
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
		//const sf::Input& Input = App.GetInput();
		
		mouse_pos =  (sf::Vector2f) sf::Mouse::getPosition (App);
		
		//mouse_pos = App.ConvertCoords(Input.GetMouseX(), Input.GetMouseY());
		
		if (sf::Mouse::isButtonPressed (sf::Mouse::Middle))
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
		App.setView (View); //Камера
		sf::Color back_color;
		back_color = sf::Color(10,10,10);
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
		
		App.draw (invader); //Кино
		App.draw (ship);
	
		
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
	}
	
	return 0;
}
