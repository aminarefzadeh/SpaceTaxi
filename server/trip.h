#ifndef __TRIP_H_INCLUDED__
#define __TRIP_H_INCLUDED__
#define waiting 1
#define accepted 2
#define arrived 3
#define not_rated 4
#include <iostream>
#include <vector>
#include <string>

class driver;
class trip
{
    private:
		int status;
		bool VIP;
		driver* trip_driver;
		int distance;
		std::vector<std::string> road;
    public:
		trip(bool VIP,std::vector<std::string> road,int distance);
		void set_distance(int a){distance=a;}
		int get_status(){return status;}
		bool get_VIP(){return VIP;}
		void set_driver(driver* trip_driver){this->trip_driver=trip_driver;}
		void set_status(int a){status=a;}
		driver* get_driver(){return trip_driver;}
		int get_distance(){return distance;}
		std::string get_last_destination();
		std::vector<std::string> get_road(){return road;}
};
std::ostream& operator<<(std::ostream& out,trip a);
#endif
