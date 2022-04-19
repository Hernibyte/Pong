#ifndef GAME_H
#define GAME_H

#include "Ball.h"
#include "Player.h"
#include "Button.h"
#include <stdlib.h>
#include <time.h>

namespace Pong 
{
	enum class TypeGameplay {
		Single,
		Multi
	};

	enum class SceneType {
		Menu,
		Game
	};

	class Game {
	public:
		Game(
			int width, 
			int height, 
			const sf::String& tittle, 
			int fps
		);

		void main_loop(sf::Color color) noexcept;
	private:
		void handle_events();
		void draw();
		void update();
		
		void pause();

		void check_goals();

		void set_fonts();
		void set_sounds();

		void update_menu();
		void update_game();

		void draw_menu();
		void draw_game();
		
		sf::RenderWindow _window { 
			sf::VideoMode(100, 100), 
			"Pong",
			sf::Style::Titlebar | sf::Style::Close
		};
		Ball _ball { 
			sf::Vector2f(25.f, 25.f), 
			2.f,
			sf::Color::Black,
			sf::Color::White
		};
		Player _player { 
			sf::Vector2f(6.f, 18.f), 
			sf::Vector2f(1, 20.f), 
			sf::Color::Black,
			sf::Color::White 
		};
		Player _player_two {
			sf::Vector2f(6.f, 18.f),
			sf::Vector2f(113, 20.f),
			sf::Color::Black,
			sf::Color::White
		};

		const int _max_points = 10;
		bool _win_player_one = false;
		bool _win_player_two = false;
		bool _end_game = false;

		sf::Time _time;
		sf::Clock _clock;
		int _fps;
		
		bool _in_pause = false;
		TypeGameplay _type_gameplay = TypeGameplay::Single;
		SceneType _scene_type = SceneType::Menu;

		sf::Font _font;
		sf::Text _point_player_one;
		sf::Text _point_player_two;
		sf::Text _tittle_game;
		sf::Text _win_text;

		float _master_volume;
		sf::SoundBuffer _ballhit_buffer;
		sf::Sound _ballhit_sound;

		sf::SoundBuffer _ball_wallhit_buffer;
		sf::Sound _ball_wallhit_sound;

		sf::SoundBuffer _music_buffer;
		sf::Sound _music_sound;

		Button _play_single_btn{ sf::Vector2f(40, 40), sf::Vector2f(40.5f, 5), sf::Vector2f(20, 10), "res/sounds/button.wav", "SinglePlayer"};
		Button _play_multi_btn{ sf::Vector2f(42, 50), sf::Vector2f(40.5f, 5), sf::Vector2f(20, 10), "res/sounds/button.wav", "MultiPlayer"};
		Button _resume_btn{ sf::Vector2f(50, 40), sf::Vector2f(20, 5), sf::Vector2f(20, 10), "res/sounds/button.wav", "resume" };
		Button _return_to_menu_btn{ sf::Vector2f(53, 55), sf::Vector2f(20, 5), sf::Vector2f(20, 10), "res/sounds/button.wav", "back" };
		Button _exit_btn{ sf::Vector2f(53, 60), sf::Vector2f(20, 5), sf::Vector2f(20, 10), "res/sounds/button.wav", "exit" };
	};
}

#endif // !GAME_H
