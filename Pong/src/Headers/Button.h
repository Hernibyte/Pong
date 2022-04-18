#ifndef BUTTON_H
#define BUTTON_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <iostream>

namespace Pong
{
	class Button {
	public:
		Button(
			sf::Vector2f position, 
			sf::Vector2f size,
			sf::Vector2f scale,
			sf::String sound_effect, 
			sf::String text
		);

		void set_font(sf::Font& font);

		void set_volume(float volume);

		bool is_mouse_over(sf::Vector2i window_position);
		
		bool is_pressed(sf::Vector2i window_position);

		sf::Text& draw();
	private:
		sf::Vector2f _position;
		sf::Vector2f _size;

		sf::SoundBuffer _audio_buffer;
		sf::Sound _sound_press;

		sf::Text _text;
	};
}

#endif // !BUTTON_H
