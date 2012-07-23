#include "Misc.h"

void
draw_grid (sf::RenderWindow &App, sf::View &View, int grid_scale, int grid_tint)
{
		sf::Color color = sf::Color (100, 100, 255, 32);
		sf::FloatRect grid_rect = View.getViewport();

		int i = floor (grid_rect.top/grid_scale);
		
		for (i *= grid_scale; i < grid_rect.height; i += grid_scale)
		{
		//	sf::Shape Line = sf::Shape::Line (grid_rect.left, i, grid_rect.width, i, grid_tint, color);
			//App.Draw(Line);

		}
		
		/*i = floor (grid_rect.Left/grid_scale);
		for (i *= grid_scale; i < grid_rect.Right; i += grid_scale)
		{

			sf::Shape Line = sf::Shape::Line (i, grid_rect.Top, i, grid_rect.Bottom, grid_tint, color);
			App.Draw(Line);

		}*/
}
