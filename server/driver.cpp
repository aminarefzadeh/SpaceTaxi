#include "output.h"
#include "driver.h"
#include "trip.h"
#include "passenger.h"

using namespace std;
ostream& operator<<(ostream& out,driver a)
{
	out<<a.get_name()<<"   "<<a.get_number()<<"   "<<a.get_model()<<"   "<<a.get_year()<<"   "<<a.get_color();
	if(a.get_VIP())
		out<<"   "<<"VIP";
	out<<endl;
	return out;
}
driver::driver(string name,string pass,string model,string color,int year,int number,date register_date,bool VIP)
{
	this->name=name;
	this->pass=pass;
	this->model=model;
	this->color=color;
	this->year=year;
	this->number=number;
	this->register_date=register_date;
	this->VIP=VIP;
	this->total_income=0;
	this->total_rate=0;
	this->status=unavailable;
	this->active=false;
	trip_amount* first=new trip_amount;
	first->a=this->register_date;
	first->amount=0;
	first->total_distance=0;
	driver_report.push_back(first);
}
void driver::add_request(passenger* new_request)
{
	this->request.push_back(new_request);
}
void driver::set_status(int a)
{
	this->status=a;
	if(a==unavailable)
	{
		request.clear();
	}
}
void driver::reject_request(passenger* a)
{
	for(int i=0;i<request.size();i++)
		if((request[i])==a)
		{
			request.erase(request.begin()+i);
			return;
		}
}
int driver::get_amount_trip(date first,date last)
{
	int ret=0;
	for(int i=0;i<driver_report.size();i++)
		if(((driver_report[i])->a==first || (driver_report[i])->a>first) && (driver_report[i])->a<last)
			ret+=(driver_report[i])->amount;
	return ret;
}
int driver::get_amount_trip()
{
	int ret=0;
	for(int i=0;i<driver_report.size();i++)
		ret+=(driver_report[i])->amount;
	return ret;
}
int driver::get_distance(int day)
{
	int ret=0;
	for(int i=0;i<driver_report.size();i++)
		if(((driver_report[i])->a).get_day()==day)
			ret+=(driver_report[i])->total_distance;
	return ret;
}
void driver::end_trip(date end_time)
{
	this->set_status(available);
	this->set_last_place(((this->cur)->get_request())->get_last_destination());
	int distance=this->cur->get_request()->get_distance();
	if((driver_report[driver_report.size()-1])->a == end_time)
	{
		(driver_report[driver_report.size()-1])->amount++;
		(driver_report[driver_report.size()-1])->total_distance+=distance;
	}
	else
	{
		trip_amount* a=new trip_amount;
		a->a=end_time;
		a->amount=1;
		a->total_distance=distance;
		driver_report.push_back(a);
	}
	this->cur=NULL;
}
void driver::accept_request(passenger* a)
{
	for(int i=0;i<request.size();i++)
		if((request[i])=a)
		{
			this->cur=a;
			request.clear();
			this->set_status(2);
			(this->cur->get_request())->set_status(accepted);
			(this->cur->get_request())->set_driver(this);
			return;
		}
	output::out<<"EROR : you have not request by this name"<<endl;
}
void driver::show_requests()
{
	if(request.size()==0){
		output::out<<"EROR : you haven't any request"<<endl;
		return;
	}
	if(this->status!=1){
		output::out<<"EROR : you are not available"<<endl;
		return;
	}
	for(int i=0;i<request.size();i++)
	{
		output::out<<(request[i])->get_name()<<" ";
		output::out<<*((request[i])->get_request())<<endl;
	}
}
void driver::set_active(bool a)
{
	active=a;
	if(!a){
		this->set_status(unavailable);
	}
}
