#include "trip.h"
using namespace std;
trip::trip(bool VIP , vector<string> road,int distance)
{
	this->VIP=VIP;
	this->road=road;
	this->distance=distance;
	this->status=waiting;
	this->trip_driver=NULL;
}
string trip::get_last_destination()
{
	return road[road.size()-1];
}
ostream& operator<<(ostream& out,trip a)
{
	int cost=a.get_distance();
	if(a.get_VIP())
		cost*=2;
	vector<string> addresses=a.get_road();
	for(int i=0;i<addresses.size();i++)
		out<<addresses.at(i)<<"  ";
	out<<cost<<"  "<<a.get_distance();
	return out;
}
