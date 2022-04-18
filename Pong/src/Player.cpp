#include "Headers/Player.h"

namespace Pong
{
	Player::Player(
		sf::Vector2f size,
		sf::Vector2f position,
		sf::Color color,
		sf::Color outline_color
	) {
		_rectangle_shape.setSize(size);
		_rectangle_shape.setPosition(position);
		_rectangle_shape.setFillColor(color);
		_rectangle_shape.setOutlineColor(outline_color);
		_rectangle_shape.setOutlineThickness(0.5f);
	}

	void Player::set_input(sf::Keyboard::Key up, sf::Keyboard::Key down) {
		_up = up;
		_down = down;
	}

	void Player::autonomous_movement(sf::Vector2f position) {
		if (position.y > _rectangle_shape.getPosition().y)
			_rectangle_shape.move(0, 1.f);
		if (position.y < _rectangle_shape.getPosition().y)
			_rectangle_shape.move(0, -1.f);

		check_limit_movement();
	}

	void Player::input_movement() {
		if (sf::Keyboard::isKeyPressed(_up))
			_rectangle_shape.move(0, -1.f);
		if (sf::Keyboard::isKeyPressed(_down))
			_rectangle_shape.move(0, 1.f);

		check_limit_movement();
	}

	void Player::check_limit_movement() {
		if (_rectangle_shape.getPosition().y < 0)
			_rectangle_shape.setPosition(sf::Vector2f(get_position().x, 0));
		if (_rectangle_shape.getPosition().y + _rectangle_shape.getSize().y > 100)
			_rectangle_shape.setPosition(sf::Vector2f(get_position().x, 100 - get_size().y));
	}

	sf::Vector2f Player::get_position() {
		return _rectangle_shape.getPosition();
	}

	sf::Vector2f Player::get_size() {
		return _rectangle_shape.getSize();
	}

	sf::RectangleShape& Player::draw() {
		return _rectangle_shape;
	}
}