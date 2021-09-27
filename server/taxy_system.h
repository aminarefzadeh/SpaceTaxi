#ifndef __SYSTEM_H_INCLUDED__
#define __SYSTEM_H_INCLUDED__
#include <fstream>
#include "road_system.h"
#include "output.h"
class date;
class passenger;
class driver;
class trip;
//ye search bezan chizayi ro ke define kardi ro eshtebahi estefade nakoni
class planet;
struct date_credit
{
    date* d;
    int credit;
};

class taxy_system
{
    private:
        passenger* is_passenger_active(std::string name);
        driver* is_driver_active(std::string name);
        bool is_admin_active(std::string name);
        bool admin_activation;
        std::vector<date*> dates;
        date* current;
        std::vector<driver*> drivers;
        std::vector<passenger*> passengers;
        std::vector<date_credit*> credits;
        std::vector<driver*> register_list;
        std::vector<std::string> acceptable_model;
        road_system roads;
        bool existent_phone(std::string phone);
        bool existent_num(int num);
        passenger* find_passenger(std::string name);
        driver* find_driver(std::string name);
        bool is_it_acceptable_model(std::string model_name);
        passenger* find_discount(int discount_code);
        std::vector<std::string> show_all_driver(bool VIP);
        void send_request(std::vector<std::string> best_drivers_place,passenger* a,bool VIP);
        driver* find_placed_driver(std::string place,bool VIP);
        void payment(int day);
        date* find_date(std::string date_name);


        void register_passenger(std::string name,std::string pass,std::string phone_num,int discount_code);
        void register_driver(std::string name,std::string pass,std::string model,std::string color,int year,int num,bool VIP);
        void show_register_requests(std::string);
        void accept_registration(std::string admin_name,std::string name);
        void reject_registration(std::string admin_name,std::string name);
        void get_discount_code(std::string name);
        void login(std::string name,std::string pass);
        void passenger_login(std::string name,std::string pass);
        void driver_login(std::string name,std::string pass);
        void logout(std::string name,std::string kind);
        void set_status(std::string name,bool is_available,std::string address);
        void estimate_trip(std::string name,std::vector<std::string>addresses,bool VIP);
        void request_trip(std::string name,std::vector<std::string>addresses,bool VIP);
        void cancel_request(std::string name);
        void show_requests(std::string name);
        void accept_request(std::string user_name,std::string passenger_name);
        void trip_status(std::string name);
        void set_arrived(std::string name);
        void end_trip(std::string name);
        void rate_driver(std::string name,int rate);
        void charge_account(std::string name,int amount);
        void get_credit(std::string name);
        void set_time(std::string name,std::string date_time);
        void driver_report(std::string admin_name,std::string name,std::string first_time,std::string last_time);
        void passenger_report(std::string admin_name,std::string name);
        void system_report(std::string name);
        void system_report(std::string name,std::string first_time,std::string last_time);
    public:
        bool existent_passenger(std::string name);
        bool existent_driver(std::string name);
        std::vector<std::string> standard_input(std::string input_array);
        taxy_system();
        void get_data();
        void get_input(std::string input_array);

};

#endif
