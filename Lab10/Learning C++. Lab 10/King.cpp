#include "King.h"

void King::canAttack(char(*chess_map)[N], Figure* figure)
{
	if (team != figure->getTeam())
	{
		int start_x = map_x - 1;
		int start_y = map_y - 1;

		for (int i = -1; i < 2; i++)
		{
			if (start_x == figure->getMapX() && start_y == figure->getMapY())
				possible_ways.push_back(std::make_pair(start_y, start_x));

			start_x++;
		}

		start_x--;
		start_y++;
		for (int i = 0; i < 2; i++)
		{
			if (start_x == figure->getMapX() && start_y == figure->getMapY())
				possible_ways.push_back(std::make_pair(start_y, start_x));

			start_y++;
		}

		start_y--;
		for (int i = -1; i < 2; i++)
		{
			if (start_x == figure->getMapX() && start_y == figure->getMapY())
				possible_ways.push_back(std::make_pair(start_y, start_x));

			start_x--;
		}

		start_x++;
		start_y--;
		for (int i = 0; i < 2; i++)
		{
			if (start_x == figure->getMapX() && start_y == figure->getMapY())
				possible_ways.push_back(std::make_pair(start_y, start_x));

			start_y--;
		}
	}
}

void King::checkAllPossibleWays(char(*chess_map)[N])
{
	int start_x = map_x - 1;
	int start_y = map_y - 1;

	for (int i = -1; i < 2; i++)
	{
		if (start_x < N && start_x > -1 && start_y > -1 && chess_map[start_y][start_x] == '0')
			possible_ways.push_back(std::make_pair(start_y, start_x));

		start_x++;
	}

	start_x--;
	start_y++;
	for (int i = 0; i < 2; i++)
	{
		if (chess_map[start_y][start_x] == '0' && start_x < N)
			possible_ways.push_back(std::make_pair(start_y, start_x));

		start_y++;
	}

	start_y--;
	for (int i = -1; i < 2; i++)
	{
		if (chess_map[start_y][start_x] == '0' && start_x > -1)
			possible_ways.push_back(std::make_pair(start_y, start_x));

		start_x--;
	}

	start_x++;
	start_y--;
	for (int i = 0; i < 2; i++)
	{
		if (chess_map[start_y][start_x] == '0' && start_x > -1)
			possible_ways.push_back(std::make_pair(start_y, start_x));

		start_y--;
	}
}
