#include "Figure.h"

#include <sstream>

Figure::Figure(Figure* fig)
{
	ren = fig->ren;
	tex = fig->tex;
	
	map_x = fig->map_x;
	map_y = fig->map_y;

	texture_x = fig->texture_x;
	texture_y = fig->texture_y;
	size = fig->size;
	
	type = fig->type;
	team = fig->team;
	
	possible_ways = fig->possible_ways;
	possible_attacks = fig->possible_attacks;
	
	first_move = fig->first_move;
	is_attacked = fig->is_attacked; // only for king
}

void Figure::move(char(*chess_map)[N], std::vector<Figure*>& figures, int move_to_x, int move_to_y, bool* was_moved, bool hand_move, std::vector<Figure*>* eaten_figures)
{
	try {
		auto it = std::find(possible_ways.begin(), possible_ways.end(), std::make_pair(move_to_y, move_to_x));

		if (it != possible_ways.end() && it->second == move_to_x && it->first == move_to_y)
		{
			if (first_move)
				first_move = false;

			// check if move is to kill a figure
			for (int i = 0; i < figures.size(); i++)
			{
				if (move_to_x == figures[i]->getMapX() && move_to_y == figures[i]->getMapY())
				{
					if (figures[i]->getTeam() == team)
					{
						eraseMove(std::make_pair(move_to_y, move_to_x));
						throw "Cannot eat a teammate!";
					}
					else
					{
						if (eaten_figures != nullptr)
							eaten_figures->push_back(figures[i]);

						this->eaten_figures.push_back(figures[i]);
						
						figures.erase(figures.begin() + i);
						break;
					}
				}
			}

			chess_map[map_y][map_x] = '0';

			if (hand_move)
			{
				std::stringstream ss;
				ss << (char)type << FIELD_LETTERS.at(map_x) << map_y + 1 << "-" << FIELD_LETTERS.at(move_to_x) << move_to_y + 1;
				logger.information(ss.str());
			}
			
			map_x = move_to_x;
			map_y = move_to_y;

			texture_x = map_x * size + FIELD_X;
			texture_y = map_y * size + FIELD_Y;

			chess_map[map_y][map_x] = (char)type;

			is_attacked = false;

			if (hand_move)
			{
				history_of_moves.push_back(std::make_pair(move_to_y, move_to_x));
				*was_moved = true;
			}
		}
		else
			throw std::make_pair(map_x, map_y);
	}
	catch (std::pair<int, int> coords)
	{
		if (hand_move)
		{
			std::stringstream s;
			s << "An impossible position for " << (char)type << " with coords x, y: " << coords.first << " " << coords.second;
			logger.error(s.str());

			*was_moved = false;
		}
	}
	catch (const char* message)
	{
		if (hand_move)
		{
			logger.warning(message);
			*was_moved = false;
		}
	}
}

void Figure::drawWays()
{
	for (auto way : possible_ways)
	{
		int x = FIELD_X + size * way.second + TILE_SIZE / 4;
		int y = FIELD_Y + size * way.first + TILE_SIZE / 4;
		if (x < FIELD_X + FIELD_WIDTH && x > FIELD_X && y < FIELD_Y + FIELD_HEIGHT && y > FIELD_Y)
			drawRect(ren, x, y, TILE_SIZE / 2, TILE_SIZE / 2);
	}
}

void Figure::printInfo()
{
	std::cout << "Map PosX: " << map_x << " Map PosY: " << map_y << "\n";
	std::cout << "Tex PosX: " << texture_x << " Tex PosY: " << texture_y << "\n";
	std::cout << "ChessTeam: " << (char)team << "\n";
}

void Figure::eraseMove(std::pair<int, int> move)
{
	for (int i = 0; i < possible_ways.size(); i++)
	{
		if (possible_ways[i].first == move.first &&
			possible_ways[i].second == move.second)
		{
			possible_ways.erase(possible_ways.begin() + i);
			break;
		}
	}
}

void Figure::removeIntersectedWays(Figure* figure)
{
	removeDuplicatedWays();
	figure->removeDuplicatedWays();

	if (team != figure->getTeam())
	{
		for (auto way : figure->getPossibleWays())
			if (std::find(possible_ways.begin(), possible_ways.end(), way) != possible_ways.end())
				eraseMove(way);
		for (auto way : figure->getPossibleAttacks())
			if (std::find(possible_ways.begin(), possible_ways.end(), way) != possible_ways.end())
				eraseMove(way);
	}
}

void Figure::removeDuplicatedWays()
{
	std::sort(possible_ways.begin(), possible_ways.end());
	possible_ways.erase(unique(possible_ways.begin(), possible_ways.end()), possible_ways.end());
}
