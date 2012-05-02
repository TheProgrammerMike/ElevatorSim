#include "passenger.h"

Passenger::Passenger(int d)
{
	time = 0;
	dest = d;
}

void Passenger::tick()
{
	time++;
}

int Passenger::getDestination()
{
	return dest;
}

int Passenger::getElapsed()
{
	return time;
}

