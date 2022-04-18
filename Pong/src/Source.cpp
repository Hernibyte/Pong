#include "Headers/Game.h"

int main() {
	Pong::Game game{ 1024, 720, "Pong", 60 };

	game.main_loop(sf::Color::Black);

	return 0;
}