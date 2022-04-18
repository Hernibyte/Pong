#ifndef PLAYER_H
#define PLAYER_H

#include "SFML/Graphics.hpp"

namespace Pong 
{
	class Player {
	public:
		Player(
			sf::Vector2f size, 
			sf::Vector2f position, 
			sf::Color color, 
			sf::Color outline_color
		);

		void set_input(sf::Keyboard::Key up, sf::Keyboard::Key down);

		void autonomous_movement(sf::Vector2f position);

		void input_movement();
		
		void check_limit_movement();

		sf::Vector2f get_position();

		sf::Vector2f get_size();

		sf::RectangleShape& draw();
		
		int points = 0;
	private:

		sf::Keyboard::Key _up;
		sf::Keyboard::Key _down;

		sf::RectangleShape _rectangle_shape;
	};
}

#endif // !PLAYER_H
