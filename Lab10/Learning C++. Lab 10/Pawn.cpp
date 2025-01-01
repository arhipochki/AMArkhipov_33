#include "Pawn.h"

void Pawn::canAttack(char(*chess_map)[N], Figure* figure)
{
	possible_attacks.clear();
	
	if (team != figure->getTeam())
	{
		if (map_y + way == figure->getMapY() && map_x + way == figure->getMapX())
		{
			possible_ways.push_back(std::make_pair(map_y + way, map_x + way));
			figure->setAttacked(true);
		}
		else if (map_y + way == figure->getMapY() && map_x - way == figure->getMapX())
		{
			possible_ways.push_back(std::make_pair(map_y + way, map_x - way));
			figure->setAttacked(true);
		}

		possible_attacks.push_back(std::make_pair(map_y + way, map_x + way));
		possible_attacks.push_back(std::make_pair(map_y + way, map_x - way));
	}
}

void Pawn::checkAllPossibleWays(char(*chess_map)[N])
{
	possible_ways.clear();

	// Check front way
	int count = 0;

	if (first_move && chess_map[map_y + way][map_x] == '0')
		count = 2;
	else
		count = 1;

	for (int i = 0; i < count; i++)
		if (chess_map[map_y + (i + 1) * way][map_x] == '0' && map_y > -1 && map_y < N - 1)
			possible_ways.push_back(std::make_pair(map_y + (i + 1) * way, map_x));
}
