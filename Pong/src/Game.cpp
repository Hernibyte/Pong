#include "Headers/Game.h"

namespace Pong 
{
	Game::Game(int width, 
		int height, 
		const sf::String& tittle,
		int fps
	) {
		_window.setSize(sf::Vector2u(width, height));
		_window.setTitle(tittle);
		_window.setPosition(sf::Vector2i(0, 0));
		_fps = fps;

		_ball.set_direction(sf::Vector2f(0.4f, 0.6f));
		_player.set_input(sf::Keyboard::W, sf::Keyboard::S);
		_player_two.set_input(sf::Keyboard::I, sf::Keyboard::K);

		_master_volume = 10.f;

		_play_multi_btn.set_volume(_master_volume);
		_play_single_btn.set_volume(_master_volume);
		_resume_btn.set_volume(_master_volume);
		_exit_btn.set_volume(_master_volume);
		_return_to_menu_btn.set_volume(_master_volume);

		set_fonts();
		set_sounds();
	}

	void Game::handle_events() {
		sf::Event _event;

		while (_window.pollEvent(_event)) {
			if (_event.type == sf::Event::Closed)
				_window.close();
		}
	}

	void Game::draw() {
		switch (_scene_type)
		{
		case Pong::SceneType::Menu:
			draw_menu();

			break;
		case Pong::SceneType::Game:
			draw_game();

			break;
		}
	}

	void Game::update() {
		switch (_scene_type)
		{
		case Pong::SceneType::Menu:
			update_menu();

			break;
		case Pong::SceneType::Game:
			update_game();

			break;
		}
	}

	void Game::pause() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			_in_pause = true;
	}

	void Game::check_goals() {
		if (_ball.get_position().x < 0) {
			_player_two.points += 1;
			_point_player_two.setString(std::to_string(_player_two.points));
			_ball.set_position(sf::Vector2f(60, 50));
			_ball.set_direction(sf::Vector2f(-0.4f, -0.6f));
		}

		if (_ball.get_position().x + (_ball.get_radius() * 2) > 120) {
			_player.points += 1;
			_point_player_one.setString(std::to_string(_player.points));
			_ball.set_position(sf::Vector2f(60, 50));
			_ball.set_direction(sf::Vector2f(0.4f, 0.6f));
		}
	}

	void Game::set_fonts() {
		if (!_font.loadFromFile("res/font/BACKTO1982.TTF"))
			std::cout << "Error to load font" << std::endl;
		else {
			_point_player_one.setFont(_font);
			_point_player_one.setString("0");
			_point_player_one.setScale(0.1f, 0.1f);
			_point_player_one.setPosition(50, 2);

			_point_player_two.setFont(_font);
			_point_player_two.setString("0");
			_point_player_two.setScale(0.1f, 0.1f);
			_point_player_two.setPosition(70, 2);

			_tittle_game.setFont(_font);
			_tittle_game.setString("PONG");
			_tittle_game.setScale(0.2f, 0.2f);
			_tittle_game.setPosition(50, 10);

			_win_text.setFont(_font);
			_win_text.setString("");
			_win_text.setScale(0.1f, 0.1f);
			_win_text.setPosition(45, 20);

			_play_single_btn.set_font(_font);
			_play_multi_btn.set_font(_font);
			_resume_btn.set_font(_font);
			_return_to_menu_btn.set_font(_font);
			_exit_btn.set_font(_font);
		}
	}

	void Game::set_sounds() {
		if (!_ballhit_buffer.loadFromFile("res/sounds/ball_hit.wav"))
			std::cout << "Error to load sound buffer" << std::endl;
		else
			_ballhit_sound.setBuffer(_ballhit_buffer);

		if (!_ball_wallhit_buffer.loadFromFile("res/sounds/ball_wallhit.wav"))
			std::cout << "Error to load sound buffer" << std::endl;
		else
			_ball_wallhit_sound.setBuffer(_ball_wallhit_buffer);

		if (!_music_buffer.loadFromFile("res/sounds/music.wav"))
			std::cout << "Error to load sound buffer" << std::endl;
		else
			_music_sound.setBuffer(_music_buffer);

		_music_sound.setLoop(true);
		_music_sound.setVolume(_master_volume * 4.f);
		_ballhit_sound.setVolume(_master_volume);
		_ball_wallhit_sound.setVolume(_master_volume);
	}

	void Game::update_menu() {
		if (_play_single_btn.is_pressed(_window.getPosition())) {
			_type_gameplay = TypeGameplay::Single;
			_scene_type = SceneType::Game;
		}
		if (_play_multi_btn.is_pressed(_window.getPosition())) {
			_type_gameplay = TypeGameplay::Multi;
			_scene_type = SceneType::Game;
		}
		if (_exit_btn.is_pressed(_window.getPosition())) {
			_window.close();
		}
	}

	void Game::update_game() {
		if (_end_game) {
			if (_return_to_menu_btn.is_pressed(_window.getPosition())) {
				_player.points = 0;
				_player_two.points = 0;

				_win_player_one = false;
				_win_player_two = false;
				_end_game = false;
				_scene_type = SceneType::Menu;
				_in_pause = false;
			}
		}

		pause();

		if (!_in_pause && !_end_game)
		{
			if (_player.points >= _max_points) {
				_win_text.setString("Player One Won");
				_end_game = true;
				_win_player_one = true;
			}
			if (_player_two.points >= _max_points) {
				_win_text.setString("Player Two Won");
				_end_game = true;
				_win_player_two = true;
			}

			_ball.update();
			if (_ball.check_wall_coll())
				_ball_wallhit_sound.play();

			_player.input_movement();

			switch (_type_gameplay)
			{
			case Pong::TypeGameplay::Single:
				_player_two.autonomous_movement(_ball.get_position());

				break;
			case Pong::TypeGameplay::Multi:
				_player_two.input_movement();

				break;
			}

			if (_ball.check_rectangle_collision(_player_two.get_position(), _player_two.get_size())) {
				if (_ball.get_position().y < _player_two.get_position().y ||
					_ball.get_position().y > _player_two.get_position().y + _player.get_size().y
					) {
					_ball.set_direction(sf::Vector2f(-_ball.get_direction().x * 1.1f, -_ball.get_direction().y * 1.2f));
					_ballhit_sound.play();
				}
				else {
					_ball.set_direction(sf::Vector2f(-_ball.get_direction().x * 1.2f, _ball.get_direction().y * 1.1f));
						_ballhit_sound.play();
				}
			}

			if (_ball.check_rectangle_collision(_player.get_position(), _player.get_size())) {
				if (_ball.get_position().y < _player.get_position().y || 
					_ball.get_position().y > _player.get_position().y + _player.get_size().y
				) {
					_ball.set_direction(sf::Vector2f(-_ball.get_direction().x * 1.1f, -_ball.get_direction().y * 1.2f));
					_ballhit_sound.play();
				}
				else {
					_ball.set_direction(sf::Vector2f(-_ball.get_direction().x * 1.2f, _ball.get_direction().y * 1.1f));
					_ballhit_sound.play();
				}
			}

			check_goals();
		}
		else if (_in_pause && !_end_game)
		{
			if (_resume_btn.is_pressed(_window.getPosition()))
				_in_pause = false;
			if (_return_to_menu_btn.is_pressed(_window.getPosition())) {
				_player.points = 0;
				_player_two.points = 0;
				_scene_type = SceneType::Menu;
				_in_pause = false;
			}
		}
	}

	void Game::draw_menu() {
		_window.draw(_play_single_btn.draw());
		_window.draw(_play_multi_btn.draw());
		_window.draw(_exit_btn.draw());
		_window.draw(_tittle_game);
	}

	void Game::draw_game() {
		if (_end_game) {
			_window.draw(_win_text);
			_window.draw(_return_to_menu_btn.draw());
		}
		else {
			_window.draw(_ball.draw());
			_window.draw(_player.draw());
			_window.draw(_player_two.draw());

			_window.draw(_point_player_one);
			_window.draw(_point_player_two);

			if (_in_pause)
			{
				_window.draw(_resume_btn.draw());
				_window.draw(_return_to_menu_btn.draw());
			}
		}
	}

	void Game::main_loop(sf::Color color) noexcept {
		srand(time(NULL));

		_music_sound.play();

		while (_window.isOpen()) {
			handle_events();

			if (_time.asSeconds() > static_cast<float>(1) / _fps) {
				update();
				_time = _clock.restart();
			}
			_time = _clock.getElapsedTime();

			_window.clear(color);

			draw();

			_window.display();
		}
	}
}