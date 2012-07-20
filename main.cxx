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
		sf::Image image[3];
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
	image[layer].LoadFromFile (path);
	image[layer].SetSmooth (false);
	sprite[layer].SetImage (image[layer]);
	sprite[layer].Resize (800,800);
}


void
BackGround::Draw (sf::RenderWindow &App)
{
	const sf::View  *view = &App.GetView();	
	const sf::FloatRect *screen = &view->GetRect();
	
	int i = 1;
	int c = 0;
	int f = 15; 
	//sprite.SetPosition (screen->Left - fmod(screen->Left/f, sprite.GetSize().x), floor(screen->Top/f));
	for (i = 0; i < 2; i++)
	{
		f /= i + 1;
		for (int x = screen->Left - fmod(screen->Left/f, sprite[i].GetSize().x); x < screen->Right; x += sprite[i].GetSize().x) // >10: C++ is magic...
		{	
			for (int y = screen->Top - fmod(screen->Top/f, sprite[i].GetSize().y); y < screen->Bottom; y += sprite[i].GetSize().y)
			{
				if (screen->Left - fmod(screen->Left/f, sprite[i].GetSize().x) > screen->Left) 
				{
					std::cout << "WTF?!" << std::endl;
				//	exit (1);
				}
				sprite[i].SetPosition (x, y);
				App.Draw (sprite[i]);
				c++;
			}
		}
	}
	std::cout << "Total tiles: " << c << std::endl;
	
}


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
	text.SetY (165);
	text.SetColor (sf::Color (0,0,0));
	
	sf::Vector2f Center(500, 300);
	sf::Vector2f HalfSize(400, 300);
	sf::View follow_view (Center,HalfSize);
	sf::View View (Center, HalfSize);
	
	Ship ship;
	Entity invader;
	
	BackGround bg;
	bg.LoadImage ("../resources/pics/background_1.png", 1);
	bg.LoadImage ("../resources/pics/background_2.png", 2);
	
	invader.SetImageFromFile("../resources/pics/invader_1.png");
	invader.SetX (400.f);
	invader.SetY (300.f);
	invader.SetMass (100.f);
	
	ship.SetImageFromFile ("../resources/pics/ship_w.png");
	ship.SetX (400.f);
	ship.SetY (400.f);
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
		if (check_follow.GetState ())
		{
			follow_view.SetCenter (ship.GetPosition());
			App.SetView (follow_view);
		}
		else
			App.SetView (View); //Камера
		sf::Color back_color;
		back_color = (check_day.GetState ())?sf::Color(10,10,10):sf::Color (255,255,255);
		App.Clear (back_color); //Свет
		
		
		
		int spin;
		if (check_invader.GetState ()) 
		{
			spin = 100;
		}
		else
		{
			spin = 0;
		}
		
		
			
		float dt = App.GetFrameTime();
		
		ship.OnIdle (dt);
		invader.OnIdle (dt);
		invader.SetRotation (Clock.GetElapsedTime() * spin);
		
		bg.Draw (App);
		if (check_grid.GetState ()) 
		{
			draw_grid (App, View, 200, 3);
			draw_grid (App, View, 50, 1);
		}
		
		App.Draw (invader); //Кино
		App.Draw (ship);
		
		/* ********* *
		 * INTERFACE *
		 * ********* */	
		App.SetView (App.GetDefaultView());
		mywindow.Draw (App);
		check_grid.Draw (App);
		check_invader.Draw (App);
		check_day.Draw (App);
		check_follow.Draw (App);
		text.SetText ("FPS: " + boost::lexical_cast<std::string> (floor (1.f/App.GetFrameTime())));
		App.Draw (text);
		
		App.Display();
	}
	
	return 0;
}
