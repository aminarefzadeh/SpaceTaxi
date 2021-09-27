#ifndef __GALAXY_H_INCLUDED__
#define __GALAXY_H_INCLUDED__
#include <iostream>
#include <string>
#include <vector>
class planet;
class galaxy
{
    private:
		std::string galaxy_name;
		std::vector <planet*> index;
		planet* gate;
		void find_distance(planet* a,planet* b,int& distance);
		planet* find_planet(std::string name);
    public:
		galaxy(std::string name);
		int find_distance(std::string first_planet,std::string second_planet);
		void add_planet(std::string name);
		void add_near_planet(std::string source,std::string near_planet);
		planet* get_gate(){return gate;}
		std::string get_gate_name();
		void set_gate(std::string name);
		std::string get_name(){return galaxy_name;}
		bool existent_planet(std::string name);
};
#endif
