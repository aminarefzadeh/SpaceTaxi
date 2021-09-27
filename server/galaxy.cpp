#include "galaxy.h"
#include "planet.h"
using namespace std;

galaxy::galaxy(string name)
{
	this->galaxy_name=name;
}
planet* galaxy::find_planet(string name)
{
    for(int i=0;i<index.size();i++)
        if((index[i])->get_name()==name && (index[i])->get_galaxy()==this->galaxy_name)
            return (index[i]);
}
void galaxy::find_distance(planet* a,planet* b,int& distance)
{
	if(a==b)
		return;
	vector<planet*> near_planet=a->get_near();
	for(int i=0;i<near_planet.size();i++)
		if(near_planet[i]==b)
		{
			distance++;
			return;
		}
	for(int i=0;i<near_planet.size();i++)
	{
		int copy_distance=distance;
		find_distance(near_planet[i],b,copy_distance);
		if(copy_distance!=distance)
		{
			distance=copy_distance+1;
			return;
		}
	}
}
int galaxy::find_distance(string first_planet,string second_planet)
{
	planet* a=find_planet(first_planet);
	planet* b=find_planet(second_planet);
	int distance=0;
	find_distance(a,b,distance);
	return distance;
}
void galaxy::add_planet(string name)
{
	planet* a=new planet(name,this->galaxy_name);
	index.push_back(a);
}
string galaxy::get_gate_name()
{
	return gate->get_name();
}
void galaxy::add_near_planet(string source,string near_planet)
{
	planet* a=find_planet(source);
	a->add_near(find_planet(near_planet));
}
void galaxy::set_gate(string name)
{
	this->gate=find_planet(name);
}
bool galaxy::existent_planet(std::string name)
{
	if(find_planet(name))
		return true;
	else
		return false;
}
