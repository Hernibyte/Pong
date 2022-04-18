#include "Headers/Button.h"

namespace Pong 
{
	Button::Button(sf::Vector2f position,
		sf::Vector2f size,
		sf::Vector2f scale,
		sf::String sound_effect,
		sf::String text
	) {
		_position = position;
		_size = size;
		_text.setPosition(_position);
		_text.setString(text);

		_text.setScale(sf::Vector2f(scale.x / 150, scale.y / 150));

		if (!_audio_buffer.loadFromFile(sound_effect))
			std::cout << "Error to load file" << std::endl;
		_sound_press.setBuffer(_audio_buffer);
	}

	void Button::set_font(sf::Font& font) {
		_text.setFont(font);
	}

	void Button::set_volume(float volume) {
		_sound_press.setVolume(volume);
	}

	bool Button::is_mouse_over(sf::Vector2i window_position) {
		float mouse_x = sf::Mouse::getPosition().x - window_position.x;
		float mouse_y = sf::Mouse::getPosition().y - window_position.y - 30;

		mouse_x /= 8.7f;
		mouse_y /= 7.1f;

		if (
			mouse_x > _position.x &&
			mouse_x < _position.x + _size.x && 
			mouse_y > _position.y &&
			mouse_y < _position.y + _size.y
		) {
			return true;
		}
		return false;
	}

	bool Button::is_pressed(sf::Vector2i window_position) {
		if (is_mouse_over(window_position)) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				_sound_press.play();
				return true;
			}
		}
		return false;
	}

	sf::Text& Button::draw() {
		return _text;
	}
}