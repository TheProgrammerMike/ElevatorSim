// passenger.h
class Passenger
{
public:
	Passenger(int dest);
	void tick();
	int getDestination();
	int getElapsed();
private:
	int time;
	int dest;
};