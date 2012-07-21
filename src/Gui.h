#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include <iostream>

class GUIWidget
{
	public:
		GUIWidget () {};
		GUIWidget (int, int, bool);
		virtual ~GUIWidget () {};
		void SetX (int);
		void SetY (int);
		int GetX (void);
		int GetY (void);
		void SetVisible (bool);
		bool IsVisible (void);
		
		virtual void OnIdle (float) {};
	private:
		int x;
		int y;
		bool is_visible;
};

class GUIWindow : public GUIWidget
{
	public:
		GUIWindow (int, int, int, int, sf::Color = sf::Color (128, 128, 128, 128));
		
		int GetWidth (void);
		int GetHeight (void);
		
		void OnIdle (float);
		void Draw (sf::RenderWindow&);
		
	private:
		int width;
		int height;
		sf::Color fill_color;
		
		bool is_border;
		sf::Color border_color;
		int border_tint;
};

class GUICheckBox : public GUIWindow //А надо ли? Использовать GUIWidget
{
	public:	
		GUICheckBox (int, int, std::string = "");
		
		bool GetState (void);
		void ChangeState (void);
		
		void Draw (sf::RenderWindow&); //Хуита. TODO: Исользовать стандартный события. //Или не использовать
		void OnIdle (float);
		
		friend class sf::Sprite;
	private:
		bool state;
		bool mouse_lock;
		sf::String text;
		sf::Font font;
		
};



#endif
