#include "date.h"
using namespace std;

int string_to_int(string a)
{
    int ret=0;
    int ten_pow=1;
    if(a.size()==0)
		throw "empty input";
    for(int i=a.size()-1;i>=0;i--)
    {
        if(a[i]>'9'||a[i]<'0')
            throw "non integer error";
        ret+=(a[i]-48)*ten_pow;
        ten_pow*=10;
    }
    return ret;
}
date::date(string input)
{
    string num;
    int i=0;
    int n=0;
    int m=0;
    for(;i<input.size();i++)
    {
        if(input[i]=='_')
            m++;
        if(input[i]==':')
            n++;
    }
    if(n!=2||m!=1)
        throw "undefined date format";
    for(i=0;input[i]!='_';i++)
        num.push_back(input[i]);

    this->day=string_to_int(num);
    num.clear();
    i++;
    n=0;
    for(;i<input.size();i++)
    {
        if(input[i]==':')
        {
            if(n)
                this->minute=string_to_int(num);
            else
                this->hour=string_to_int(num);
            i++;
            n++;
            num.clear();
        }
        num.push_back(input[i]);
    }
    this->second=string_to_int(num);
    if(hour>23||minute>59||second>59)
        throw "illegal time";
}
date::date()
{
	this->day=1;
	this->hour=0;
	this->minute=0;
	this->second=0;
}
bool date::operator==(date b)
{
    if(day==b.day&&hour==b.hour&&minute==b.minute&&second==b.second)
        return true;
    else
        return false;
}
bool date::operator<(date b)
{
    if(b.day>day)
        return true;
    else
	{
        if(b.hour>hour)
            return true;
        else
		{
            if(b.minute>minute)
                return true;
            else
			{
                if(b.second>second)
                    return true;
                else
                    return false;
			}
        }
    }
}
bool date::operator>(date b)
{
    return (b<*(this));
}
date date::operator-(date b)
{
	date ret;
	ret.day=0;
	ret.second=this->get_second()-b.get_second();
	ret.minute=this->get_minute()-b.get_minute();
	ret.hour=this->get_hour()-b.get_hour();
	ret.day=this->get_day()-b.get_day();
	if(ret.get_second()<0)
	{
		ret.second+=60;
		ret.minute--;
	}
	if(ret.get_minute()<0)
	{
		ret.minute+=60;
		ret.hour--;
	}
	if(ret.get_hour()<0)
	{
		ret.hour+=24;
		ret.day--;
	}
	if(ret.day<0)
		throw "bad subtraction of dates";
	return ret;
}
ostream& operator<<(ostream& out,date a)
{
	out<<a.get_day()<<'_'<<a.get_hour()<<':'<<a.get_minute()<<':'<<a.get_second();
    return out;
}
bool operator==(string a,string b)
{
	if(a.size()!=b.size())
		return false;
	for(int i=0;i<a.size();i++)
		if(a[i]!=b[i])
			return false;
	return true;
}
