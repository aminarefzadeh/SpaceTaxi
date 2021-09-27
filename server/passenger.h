#ifndef __PASSENGER_H_INCLUDED__
#define __PASSENGER_H_INCLUDED__
#include "date.h"
#include "output.h"
class trip;
struct off_code
{
    int code;
    int number_of_used;
};
class passenger
{
    private:
        std::string name;
        std::string pass;
        std::string phone;
        trip* request;
        date register_time;
        bool active;
        int credit;
        off_code* code;
        bool tripy;
        std::vector<date> trip_date;
        void check_tripy();
    public:
        passenger(std::string name,std::string pass,std::string phone,date register_time);
	void make_request(std::vector<std::string> roads,bool VIP,int distance);
	void cancel_request();
        //for discount code
        void get_new_code();
        int get_current_code();
        void use_code();
        //
        void set_active(bool boolean){active=boolean;}
        bool get_active(){return this->active;}
        std::string get_name(){return name;}
        std::string get_pass(){return pass;}
        std::string get_phone(){return phone;}
        int get_credit(){return credit;}
        trip* get_request(){return request;}
        void change_credit(int d_credit){this->credit += d_credit;}
        bool get_tripy(){ check_tripy();return tripy;}
        void set_date(date end_date);
	void end_trip();
	date get_register_date(){return register_time;}
};
#endif
