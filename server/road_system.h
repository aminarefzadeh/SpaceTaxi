#ifndef __ROAD_SYSTEM_H_INCLUDED__
#define __ROAD_SYSTEM_H_INCLUDED__
#include <iostream>
#include <string>
#include <vector>
class galaxy;
class road_system
{
    private:
        std::vector<galaxy*> galaxies;
		galaxy* find_galaxy(std::string name);
		std::string galaxy_name_in_address(std::string address);
		std::string planet_name_in_address(std::string address);
		std::vector<int> find_lower_num(std::vector<int> distances);
	public:
		bool check_address(std::string address);
        void add_planet(std::string galaxy_name,std::string name);
        void add_galaxy(std::string name);
		void add_near_planet(std::string galaxy_name,std::string source,std::string near_planet);
		void chose_gate(std::string galaxy_name,std::string gate_name);
		int find_space(std::string a,std::string b);
		int find_distance(std::vector<std::string> destinations);
        std::vector<std::string> find_best_driver(std::string source,std::vector<std::string> driver_place);
};
#endif
