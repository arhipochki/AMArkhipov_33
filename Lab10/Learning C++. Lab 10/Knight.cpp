#include "Knight.h"

void Knight::canAttack(char(*chess_map)[N], Figure* figure)
{
	if (team != figure->getTeam())
	{
		if (map_y + 2 == figure->getMapY() && map_x + 1 == figure->getMapX())
		{
			figure->setAttacked(true);
			possible_ways.push_back(std::make_pair(map_y + 2, map_x + 1));
		}

		if (map_y + 2 == figure->getMapY() && map_x - 1 == figure->getMapX())
		{
			figure->setAttacked(true);
			possible_ways.push_back(std::make_pair(map_y + 2, map_x - 1));
		}

		if (map_y + 1 == figure->getMapY() && map_x + 2 == figure->getMapX())
		{
			figure->setAttacked(true);
			possible_ways.push_back(std::make_pair(map_y + 1, map_x + 2));
		}

		if (map_y + 1 == figure->getMapY() && map_x - 2 == figure->getMapX())
		{
			figure->setAttacked(true);
			possible_ways.push_back(std::make_pair(map_y + 1, map_x - 2));
		}

		if (map_y - 2 == figure->getMapY() && map_x + 1 == figure->getMapX())
		{
			figure->setAttacked(true);
			possible_ways.push_back(std::make_pair(map_y - 2, map_x + 1));
		}

		if (map_y - 2 == figure->getMapY() && map_x - 1 == figure->getMapX())
		{
			figure->setAttacked(true);
			possible_ways.push_back(std::make_pair(map_y - 2, map_x - 1));
		}

		if (map_y - 1 == figure->getMapY() && map_x + 2 == figure->getMapX())
		{
			figure->setAttacked(true);
			possible_ways.push_back(std::make_pair(map_y - 1, map_x + 2));
		}

		if (map_y - 1 == figure->getMapY() && map_x - 2 == figure->getMapX())
		{
			figure->setAttacked(true);
			possible_ways.push_back(std::make_pair(map_y - 1, map_x - 2));
		}
	}
}

void Knight::checkAllPossibleWays(char(*chess_map)[N])
{
	if (chess_map[map_y + 2][map_x + 1] == '0' && map_y + 2 < N && map_x + 1 < N)
		possible_ways.push_back(std::make_pair(map_y + 2, map_x + 1));

	if (chess_map[map_y + 2][map_x - 1] == '0' && map_y + 2 < N && map_x - 1 >= 0)
		possible_ways.push_back(std::make_pair(map_y + 2, map_x - 1));

	if (chess_map[map_y + 1][map_x + 2] == '0' && map_y + 1 < N && map_x + 2 < N)
		possible_ways.push_back(std::make_pair(map_y + 1, map_x + 2));

	if (chess_map[map_y + 1][map_x - 2] == '0' && map_y + 1 < N && map_x - 2 >= 0)
		possible_ways.push_back(std::make_pair(map_y + 1, map_x - 2));

	if (chess_map[map_y - 2][map_x + 1] == '0' && map_y - 2 >= 0 && map_x + 1 < N)
		possible_ways.push_back(std::make_pair(map_y - 2, map_x + 1));

	if (chess_map[map_y - 2][map_x - 1] == '0' && map_y - 2 >= 0 && map_x - 1 >= 0)
		possible_ways.push_back(std::make_pair(map_y - 2, map_x - 1));

	if (chess_map[map_y - 1][map_x + 2] == '0' && map_y - 1 >= 0 && map_x + 2 < N)
		possible_ways.push_back(std::make_pair(map_y - 1, map_x + 2));

	if (chess_map[map_y - 1][map_x - 2] == '0' && map_y - 1 >= 0 && map_x - 2 >= 0)
		possible_ways.push_back(std::make_pair(map_y - 1, map_x - 2));
}
