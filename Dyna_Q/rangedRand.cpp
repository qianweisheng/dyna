#include "stdafx.h"
#include "rangedRand.h"

int rangedRand( int rangeMin, int rangeMax )
{
	// Generate random numbers in the half-closed interval
	// [range_min, range_max). In other words,
	// range_min <= random number < range_max
	int u = int((double)rand() / (RAND_MAX + 1) * (rangeMax - rangeMin)
		+ rangeMin);

	return u;
}

