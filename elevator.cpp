#include "elevator.h"

Elevator::Elevator()
{
	floor = 1;
	direction = UP;
}

void Elevator::call(int fromFloor, int direction)
{
}

void Elevator::tick()
{
	if( MAX_FLOOR == floor )
	{
		direction = DOWN;
	}
	if( 1 == floor )
	{
		direction = UP;
	}
	if( UP == direction )
	{
		floor++;
	}
	else
	{
		floor--;
	}
}

void Elevator::printStatus(ostream& os)
{
	os << "Elevator on floor " << floor
		<< " going ";
	switch(direction)
	{
	case UP: os << "UP\n"; break;
	case DOWN: os << "DOWN\n"; break;
	case DONTCARE: os << "??\n"; break;
	}
}

int Elevator::getFloor()
{
	return floor;
}

int Elevator::getDirection()
{
	return direction;
}

void Elevator::board(Passenger*)
{
}

