#include "Headers/Ball.h"

namespace Pong 
{
	Ball::Ball(
		sf::Vector2f position, 
		float radius,
		sf::Color fill_color,
		sf::Color outline_color
	) {
		_circle_shape.setRadius(radius);
		_circle_shape.setPosition(position.x, position.y);
		_circle_shape.setFillColor(fill_color);
		_circle_shape.setOutlineColor(outline_color);
		_circle_shape.setOutlineThickness(0.5f);
	}

	bool Ball::check_rectangle_collision(
		sf::Vector2f position,
		sf::Vector2f size
	) {
		if (
			position.y < _circle_shape.getPosition().y + (_circle_shape.getRadius() * 2) &&
			position.y + size.y > _circle_shape.getPosition().y &&
			position.x < _circle_shape.getPosition().x + (_circle_shape.getRadius() * 2) &&
			position.x + size.x > _circle_shape.getPosition().x
		) {
			return true;
		}
		return false;
	}

	void Ball::update() {
		_circle_shape.move(_direction);
	}

	bool Ball::check_wall_coll() {
		if (_circle_shape.getPosition().y < 0) {
			set_direction(sf::Vector2f(get_direction().x, -get_direction().y));
			return true;
		}
		if (_circle_shape.getPosition().y + (_circle_shape.getRadius() * 2) > 100) {
			set_direction(sf::Vector2f(get_direction().x, -get_direction().y));
			return true;
		}
		return false;
	}

	void Ball::set_direction(sf::Vector2f direction) {
		_direction = direction;
	}

	sf::Vector2f Ball::get_direction() {
		return _direction;
	}

	float Ball::get_radius() {
		return _circle_shape.getRadius();
	}

	void Ball::set_position(sf::Vector2f position) {
		_circle_shape.setPosition(position);
	}

	sf::Vector2f Ball::get_position() {
		return _circle_shape.getPosition();
	}

	sf::CircleShape& Ball::draw() {
		return _circle_shape;
	}
}