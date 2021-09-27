#ifndef __PLANET_H_INCLUDE__
#define __PLANET_H_INCLUDE__
#include <iostream>
#include <string>
#include <vector>
class planet
{
    private:
    std::string galaxy_name;
    std::string name;
    std::vector< planet* > near;
    public:
    planet(std::string name,std::string galaxy_name);
    void add_near(planet* a){near.push_back(a);}
    std::string get_name(){return name;}
    std::string get_galaxy(){return galaxy_name;}
    std::vector< planet* > get_near(){return near;}
};
#endif
