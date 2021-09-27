#ifndef __DRIVER_H_INCLUDED__
#define __DRIVER_H_INCLUDED__
#include "date.h"
#include <vector>
#define unavailable 0
#define available 1
#define on_trip 2
struct trip_amount
{
	date a;
	int amount;
	int total_distance;
};
class trip;
class passenger;
class driver
{
    private:
        std::vector<trip_amount*> driver_report;
        std::string name;
        std::string pass;
        std::string model;
        std::string color;
        int year;
        int number;
        int total_income;
        passenger* cur;
        std::vector <passenger*> request;
        int total_rate;
        date register_date;
        std::string last_place;
        bool VIP;
        bool active;
        int status;
    public:
        driver(std::string name,std::string pass,std::string model,std::string color,int year,int number,date register_date,bool VIP);
        std::string get_name(){return name;}
        std::string get_pass(){return pass;}
        std::string get_model(){return model;}
        std::string get_color(){return color;}
        int get_year(){return year;}
        int get_number(){return number;}
        int get_total_rate(){return total_rate;}
        date get_register_date(){return register_date;}
        std::string get_last_place(){return last_place;}
        bool get_VIP(){return VIP;}
        bool get_active(){return active;}
        void set_active(bool a);
        int get_status(){return status;}
        int get_total_income(){return total_income;}
        passenger* get_request(){return cur;}
        void end_trip(date end_time);
        void add_request(passenger* new_request);
        void accept_request(passenger* a);
        void reject_request(passenger* a);
        void show_requests();
        void set_status(int a);
        void set_last_place(std::string rec){last_place=rec;}
        void change_rate(int dx){total_rate+=dx;}
        void change_income(int dx){total_income+=dx;}
        int get_amount_trip(date first,date last);
        int get_amount_trip();
        int get_distance(int day);
};
std::ostream& operator<<(std::ostream& out,driver a);
#endif
