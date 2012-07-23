#include "Gui.h"

GUIWidget::GUIWidget (int x, int y, bool visible = true)
{
	this->x = x;
	this->y = y;
	this->is_visible = visible;
}

int
GUIWidget::GetX (void) {return x;};

int
GUIWidget::GetY (void) {return y;};

bool
GUIWidget::IsVisible (void)
{
	return is_visible;
}

GUIWindow::GUIWindow ( int x, int y, int width, int height, sf::Color fill_color) : GUIWidget (x, y)
{
	//std::cout << x << " | " << y << " || " << width << " | " << height << std::endl;
	this->width =  x + width;
	this->height = y + height;
	this->fill_color = fill_color;
}

int
GUIWindow::GetWidth (void) { return width; }

int
GUIWindow::GetHeight (void) { return height; }

void
GUIWindow::OnIdle (float dt)
{
	
}

void
GUIWindow::Draw (sf::RenderWindow &App)
{
	if (IsVisible())
	{
		/*
		sf::Shape window = sf::Shape::Rectangle (GetX(), GetY(), GetWidth(), GetHeight(), fill_color);
		App.draw (window);
		*/
	}
}

GUICheckBox::GUICheckBox (int x, int y, std::string text_str) : GUIWindow (x, y, x + 1, y + 1)
{
	/*
	font.LoadFromFile ("../resources/fonts/DejaVuSans.ttf");
	text.SetText (text_str);
	text.SetX (x + 20);
	text.SetY (y);
	text.SetFont (font);
	text.SetColor (sf::Color (0,0,0));
	text.SetSize (24);
	state = false;
	*/
} 

bool
GUICheckBox::GetState (void) { return state; };

void
GUICheckBox::ChangeState (void)
{
	state = (state==true)?false:true;
}

void
GUICheckBox::OnIdle (float dt)
{
	
}

void
GUICheckBox::Draw (sf::RenderWindow &App)
{	
	if (IsVisible())
	{
	/*	
		int y_offset = 9;
		int outline = 3;
		int a = 12; //box size
		int d = 3; //dot offset
		sf::Color default_color;
		sf::Vector2f mouse_pos;
		

		const sf::Input& Input = App.GetInput();
		mouse_pos = App.ConvertCoords(Input.GetMouseX(), Input.GetMouseY());
		if (mouse_pos.x > GetX() - outline && mouse_pos.x < GetX() + a + outline && mouse_pos.y > GetY() + y_offset - outline && mouse_pos.y < GetY() + a + y_offset + outline)
		{
			//box.SetRotation (3.f);
			default_color = sf::Color (32,128,64);
			if (Input.IsMouseButtonDown (sf::Mouse::Left))
			{
				if (mouse_lock == false)
				{
					this->ChangeState ();
					mouse_lock = true;
				}
			}
			else
			{
				mouse_lock = false;
			}
		}
		else
		{
		//	box.SetRotation (0);
			default_color = sf::Color (0,0,0);
		}
		
		
		sf::Shape box = sf::Shape::Rectangle (GetX(), GetY() + y_offset, GetX() + a, GetY() + y_offset + a, sf::Color (255,255,255,0), outline, default_color);	
		
		if (GetState())
		{
			sf::Shape dot = sf::Shape::Rectangle (GetX() + d , GetY() + y_offset + d, GetX() + a - d, GetY() + y_offset + a - d, default_color);
			App.Draw (dot);
		}
		
		App.Draw (box);
		App.Draw (text);
	*/
	}
	
}
