#ifndef BALL_H
#define BALL_H

#include "SFML/Graphics.hpp"

namespace Pong 
{
	class Ball {
	public:
		Ball(
			sf::Vector2f position, 
			float radius,
			sf::Color fill_color,
			sf::Color outline_color
		);

		bool check_rectangle_collision(
			sf::Vector2f position, 
			sf::Vector2f size
		);

		void update();

		bool check_wall_coll();

		void set_direction(sf::Vector2f direction);
		sf::Vector2f get_direction();

		float get_radius();

		void set_position(sf::Vector2f position);
		sf::Vector2f get_position();

		sf::CircleShape& draw();

	private:
		sf::Vector2f _direction;
		sf::CircleShape _circle_shape{10.f};
	};
}

#endif // !BALL_H
