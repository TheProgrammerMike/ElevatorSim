// elevator.h
#include <iostream>
using namespace std;

const int UP = 0;
const int DOWN = 1;
const int DONTCARE = 2;

const int MAX_FLOOR = 5;

class Passenger; // foreward declaration

class Elevator
{
public:
	Elevator();
	void call(int fromFloor, int direction);
	void tick();
	void printStatus(ostream&);
	int getFloor();
	int getDirection();
	void board(Passenger*);
private:
	int floor;
	int direction;
};