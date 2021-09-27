#include "road_system.h"
#include "galaxy.h"
using namespace std;
string road_system::galaxy_name_in_address(string address)
{
	string ret;
	int i=0;
	for(;i<address.size() && address[i]!=',';i++)
		ret.push_back(address[i]);
	if(i==address.size() || i==0)
		throw "undefined place formation . it should be \"galaxy,planet\"";
	return ret;
}
string road_system::planet_name_in_address(string address)
{
	int i=0;
	string ret;
	for(;i<address.size() && address[i]!=',';i++);
	if(i==address.size() || i==(address.size()-1))
		throw "undefined place formation . it should be \"galaxy,planet\"";
	i++;
	for(;i<address.size();i++)
		ret.push_back(address[i]);
	return ret;
}
galaxy* road_system::find_galaxy(std::string name)
{
	for(int i=0;i<galaxies.size();i++)
		if((galaxies[i])->get_name()==name)
			return (galaxies[i]);
}
vector<int> road_system::find_lower_num(vector<int> distances)
{
	vector<int> ret;
	ret.push_back(0);
	for(int i=1;i<distances.size();i++)
	{
		if(int num=ret.size()<4)
		{
			int j;
			for(j=0;j<num;j++)
				if(distances[i]<distances[ret[j]])
					break;
			if(j==num)
				ret.push_back(i);
			else
				ret.insert(ret.begin()+j,i);
		}
		else
		{
			int j;
			for(j=0;j<4;j++)
			{
				if(distances[i]<distances[ret[j]])
					break;
				ret.insert(ret.begin()+j,i);
				ret.pop_back();
			}
		}
	}
	return ret;
}
void road_system::add_planet(string galaxy_name,string name)
{
	galaxy* a=find_galaxy(galaxy_name);
	a->add_planet(name);
}
void road_system::add_galaxy(string name)
{
	galaxy* a=new galaxy(name);
	galaxies.push_back(a);
}
void road_system::add_near_planet(string galaxy_name,string source,string near_planet)
{
	galaxy* a=find_galaxy(galaxy_name);
	a->add_near_planet(source,near_planet);
}
void road_system::chose_gate(string galaxy_name,string gate_name)
{
	galaxy* a=find_galaxy(galaxy_name);
	a->set_gate(gate_name);
}
int road_system::find_space(string a,string b)
{
	int ret=0;
	string galaxy_a=galaxy_name_in_address(a);
	string galaxy_b=galaxy_name_in_address(b);
	if(galaxy_a==galaxy_b)
	{
		galaxy* first=find_galaxy(galaxy_a);
		ret=first->find_distance(planet_name_in_address(a),planet_name_in_address(b));
		return ret;
	}
	else
	{
		galaxy* first=find_galaxy(galaxy_a);
		galaxy* second=find_galaxy(galaxy_b);
		ret+=first->find_distance(first->get_gate_name(),planet_name_in_address(a));
		ret+=second->find_distance(second->get_gate_name(),planet_name_in_address(b));
		return ret;
	}
}
int road_system::find_distance(vector<string> destinations)
{
	int distance=0;
	int i=0;
	if(!check_address(destinations[0]))
		throw "the address is not acceptable";
	for(;i<destinations.size()-1;i++)
	{
		if(!check_address(destinations[i+1]))
			throw "the address is not acceptable";
		distance+=find_space(destinations[i],destinations[i+1]);	
	}
	return distance;
}
vector<string> road_system::find_best_driver(string source,vector<string> driver_place)
{
	vector<int> distances;
	for(int i=0;i<driver_place.size();i++)
		distances.push_back(find_space(source,driver_place[i]));
	vector<int> number=find_lower_num(distances);
	vector<string> ret;
	for(int i=0;i<number.size();i++)
		ret.push_back(driver_place[number[i]]);
	return ret;

}
bool road_system::check_address(std::string address)
{
	string galaxy_name=galaxy_name_in_address(address);
	string planet_name=planet_name_in_address(address);
	if(galaxy* a=find_galaxy(galaxy_name))
		return a->existent_planet(planet_name);
	else
		return false;
}
