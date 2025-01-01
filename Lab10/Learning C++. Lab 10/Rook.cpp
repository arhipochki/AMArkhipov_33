#include "Rook.h"

void Rook::canAttack(char(*chess_map)[N], Figure* figure)
{
	if (team != figure->getTeam())
	{
		if (map_x == figure->getMapX())
		{
			int k = 1;

			// check down
			while (chess_map[map_y + k][map_x] == '0' && map_y + k < N) k++;
			
			if (map_y + k == figure->getMapY())
			{
				possible_ways.push_back(std::make_pair(map_y + k, map_x));
				figure->setAttacked(true);
			}

			// check up
			k = 1;
			while (chess_map[map_y - k][map_x] == '0' && map_y - k >= 0) k++;

			if (map_y - k == figure->getMapY())
			{
				possible_ways.push_back(std::make_pair(map_y - k, map_x));
				figure->setAttacked(true);
			}
		}
		
		if (map_y == figure->getMapY())
		{
			int k = 1;

			// check right
			while (chess_map[map_y][map_x + k] == '0' && map_x + k < N) k++;

			if (map_x + k == figure->getMapX())
			{
				possible_ways.push_back(std::make_pair(map_y, map_x + k));
				figure->setAttacked(true);
			}

			// check left
			k = 1;
			while (chess_map[map_y][map_x - k] == '0' && map_x - k >= 0) k++;

			if (map_x - k == figure->getMapX())
			{
				possible_ways.push_back(std::make_pair(map_y, map_x - k));
				figure->setAttacked(true);
			}
		}
	}
}

void Rook::checkAllPossibleWays(char(*chess_map)[N])
{
	possible_ways.clear();

	// check right way
	int k = 1;
	while (chess_map[map_y][map_x + k] == '0' && map_x + k < N)
	{
		possible_ways.push_back(std::make_pair(map_y, map_x + k));

		k++;
	}

	// check left way
	k = 1;
	while (chess_map[map_y][map_x - k] == '0' && map_x - k >= 0)
	{
		possible_ways.push_back(std::make_pair(map_y, map_x - k));

		k++;
	}
	
	// check up way
	k = 1;
	while (chess_map[map_y - k][map_x] == '0' && map_y - k >= 0)
	{
		possible_ways.push_back(std::make_pair(map_y - k, map_x));

		k++;
	}

	// check down way
	k = 1;
	while (chess_map[map_y + k][map_x] == '0' && map_y + k < N)
	{
		possible_ways.push_back(std::make_pair(map_y + k, map_x));

		k++;
	}
}