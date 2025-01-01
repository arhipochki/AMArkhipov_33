#include "Player.h"

void Player::moveFigure(Figure* figure, int move_to_x, int move_to_y, 
		bool* was_moved, char (*chess_map)[N], std::vector<Figure*>& figures)
{
	figure->move(chess_map, figures, move_to_x, move_to_y, was_moved, true, &eaten_figures);
	figure->clearPossibleWays();
}

std::string Player::getGameTime()
{ 	
	int secs = round(game_time.count() % (60 * 1000) / 1000);
	return std::to_string(game_time.count() / (60 * 1000)) + ":" + (secs < 10 ? "0" + std::to_string(secs) : std::to_string(secs)).substr(0, 2);
}