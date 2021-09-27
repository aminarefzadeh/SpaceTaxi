#include "passenger.h"
#include "trip.h"
#include <stdlib.h>
#include <time.h>
using namespace std;

passenger::passenger(string name,string pass,string phone,date register_time)
{
	this->name=name;
	this->pass=pass;
	this->phone=phone;
	this->register_time=register_time;
	this->request=NULL;
	this->credit=0;
	this->code=NULL;
	this->tripy=false;
	this->active=false;
}
void passenger::make_request(vector<string> roads,bool VIP,int distance)
{
	trip* a=new trip(VIP,roads,distance);
	this->request=a;
}
void passenger::cancel_request()
{
	delete this->request;
	this->request=NULL;
}
void passenger::get_new_code()
{
	if(this->code)
	{
		output::out<<this->code->code<<" "<<this->code->number_of_used<<endl;
		return;
	}
	else
	{
		srand(time(0));
		off_code* a=new off_code;
		a->number_of_used=5;
		a->code=((rand()%8+1)*100000+(rand()%10)*10000+(rand()%10)*1000+(rand()%10)*100+(rand()%10)*10+(rand()%10));
		this->code=a;
		output::out<<this->code->code<<" 5"<<endl;
	}
}
int passenger::get_current_code()
{
	if(this->code)
		return this->code->code;
	else
		return 0;
}
void passenger::use_code()
{
	this->credit+=10;
	this->code->number_of_used--;
	if(this->code->number_of_used==0)
	{
		delete this->code;
		this->code=NULL;
	}
}
void passenger::set_date(date end_date)
{
	this->trip_date.push_back(end_date);
}
void passenger::end_trip()
{
	delete this->request;
	this->request=NULL;
}
void passenger::check_tripy()
{
	int i=trip_date.size()-1;
	if(i<2)
	{
		this->tripy=false;
		return;
	}
	date difference=trip_date[i]-trip_date[i-2];
	if(this->tripy)
		if(difference>date("2_00:00:00"))
		{
			this->tripy=false;
			return;
		}
	else
		if(difference<date("1_00:00:01"))
		{
			this->tripy=true;
			return;
		}

}
