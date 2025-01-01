#include "Bishop.h"

void Bishop::canAttack(char(*chess_map)[N], Figure* figure)
{
	if (team != figure->getTeam())
	{
		// check right - down
		int k = 1;
		while (chess_map[map_y + k][map_x + k] == '0' && map_y + k < N && map_x + k < N) k++;

		if (map_y + k == figure->getMapY() && map_x + k == figure->getMapX())
		{
			possible_ways.push_back(std::make_pair(map_y + k, map_x + k));
			figure->setAttacked(true);
		}

		// check left - down
		k = 1;
		while (chess_map[map_y + k][map_x - k] == '0' && map_y + k < N && map_x - k >= 0) k++;
		
		if (map_y + k == figure->getMapY() && map_x - k == figure->getMapX())
		{
			possible_ways.push_back(std::make_pair(map_y + k, map_x - k));
			figure->setAttacked(true);
		}

		// check right - up
		k = 1;
		while (chess_map[map_y - k][map_x + k] == '0' && map_y - k >= 0 && map_x + k < N) k++;

		if (map_y - k == figure->getMapY() && map_x + k == figure->getMapX())
		{
			possible_ways.push_back(std::make_pair(map_y - k, map_x + k));
			figure->setAttacked(true);
		}

		// check left - up
		k = 1;
		while (chess_map[map_y - k][map_x - k] == '0' && map_y - k >= 0 && map_x - k >= 0) k++;

		if (map_y - k == figure->getMapY() && map_x - k == figure->getMapX())
		{
			possible_ways.push_back(std::make_pair(map_y - k, map_x - k));
			figure->setAttacked(true);
		}
	}
}

void Bishop::checkAllPossibleWays(char(*chess_map)[N])
{
	possible_ways.clear();

	// check right - down
	int k = 1;
	while (chess_map[map_y + k][map_x + k] == '0' && map_y + k < N && map_x + k < N)
	{
		possible_ways.push_back(std::make_pair(map_y + k, map_x + k));

		k++;
	}

	// check left - down
	k = 1;
	while (chess_map[map_y + k][map_x - k] == '0' && map_y + k < N && map_x - k >= 0)
	{
		possible_ways.push_back(std::make_pair(map_y + k, map_x - k));

		k++;
	}

	// check right - up
	k = 1;
	while (chess_map[map_y - k][map_x + k] == '0' && map_y - k >= 0 && map_x + k < N)
	{
		possible_ways.push_back(std::make_pair(map_y - k, map_x + k));

		k++;
	}

	// check left - up
	k = 1;
	while (chess_map[map_y - k][map_x - k] == '0' && map_y - k >= 0 && map_x - k >= 0)
	{
		possible_ways.push_back(std::make_pair(map_y - k, map_x - k));

		k++;
	}
}