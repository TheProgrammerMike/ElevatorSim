#include "elevator.h"
#include "passenger.h"
#include <list>
using namespace std;

class Driver
{
public:
	Driver(int ticks);
	void run();
	void issueRequests();
	void tickEverything();
	void updatePassengers();
	void printStatus(ostream&);
private:
	Elevator lift;
	list<Passenger*> waiting[MAX_FLOOR+2];
	list<Passenger*> riding;
	int countdown;
	int totalWait;
};

Driver::Driver(int ticks)
{
	countdown = ticks;
	totalWait = 0;
}

void Driver::run()
{
	while(countdown > 0)
	{
		issueRequests();
		tickEverything();
		updatePassengers();
		countdown--;
		lift.printStatus(cout);
		printStatus(cout);
	}
}

void Driver::tickEverything()
{
	lift.tick();
	for(int f = 1; f <= MAX_FLOOR; f++)
	{
            for(list<Passenger*>::iterator i = waiting[f].begin();
                i != waiting[f].end();
                i++)
            {
                (*i)->tick();
            }
	}
        for(list<Passenger*>::iterator i = riding.begin();
            i != riding.end();
            i++)
        {
            (*i)->tick();
        }
}

void Driver::issueRequests()
{
	if(countdown % 10 == 0)
	{
		// some fixed requests for now
		waiting[1].push_back(new Passenger(MAX_FLOOR));
		waiting[1].push_back(new Passenger(3));
		waiting[MAX_FLOOR].push_back(new Passenger(1));
		// call elevator
		lift.call(1, UP);
		lift.call(1, UP);
		lift.call(MAX_FLOOR, DOWN);
	}
}

void Driver::updatePassengers()
{
	// kick people out of lift
	for(list<Passenger*>::iterator i = riding.begin();
		i != riding.end();
		/* increment omitted */)
	{
		if(lift.getFloor() == (*i)->getDestination())
		{
			totalWait += (*i)->getElapsed();
			i = riding.erase(i);
		}
		else
		{
			i++;
		}
	}
	// load people onto lift
	int f = lift.getFloor();
	for(list<Passenger*>::iterator i = waiting[f].begin();
		i != waiting[f].end();
		/* increment omitted; see erase() below */)
	{
		// TODO: should only load passengers going
		// in same direction as lift.
		Passenger* p = *i;
		riding.push_back(p);
		lift.board(p);
		i = waiting[f].erase(i);
	}
}

void Driver::printStatus(ostream& os)
{
	os << "|";
	for(int f = 1; f <= MAX_FLOOR; f++)
	{
		os << waiting[f].size() << "|";
	}
        os << " riders to: ";
        for(list<Passenger*>::iterator i = riding.begin();
            i != riding.end();
            i++)
        {
            os << (*i)->getDestination() << ',';
        }
	os << " wait: " << totalWait << "\n";
}

int main()
{
	Driver d(1000);
	d.run();
	return 0;
}
