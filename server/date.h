#ifndef __DATE_H_INCLUDED__
#define __DATE_H_INCLUDED__
#include <iostream>
#include <string>
#include <vector>
class date
{
    private:
    int day;
    int hour;
    int minute;
    int second;
    public:
    date(std::string input);
	date();
    bool operator==(date b);
    bool operator<(date b);
    bool operator>(date b);
	date operator-(date b);
	int get_day(){return day;}
	int get_hour(){return hour;}
	int get_minute(){return minute;}
	int get_second(){return second;}
};
std::ostream& operator<<(std::ostream& out,date a);
int string_to_int(std::string a);
bool operator==(std::string a,std::string b);
#endif
