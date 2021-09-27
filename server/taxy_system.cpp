#include "taxy_system.h"
#include "date.h"
#include "passenger.h"
#include "driver.h"
#include "trip.h"
using namespace std;
		taxy_system::taxy_system()
		{
			date* a=new date;
			dates.push_back(a);
			current= (dates[0]);
			date_credit* b=new date_credit;
			b->credit=0;
			b->d=current;
			credits.push_back(b);
			admin_activation=false;
		}
		vector<string> taxy_system::standard_input(string input_array)
		{
			vector<string> ret;
			int i=0;
			while(i<input_array.size())
			{
				string s;
				for(;i<input_array.size() && input_array[i]!=32 && input_array[i]!=10 && input_array[i];i++){
					if((input_array[i]<33) || (input_array[i]>126))
						throw "input string contain bad characters";
					s.push_back(input_array[i]);
				}
				for(;i<input_array.size() && (input_array[i]==32 || input_array[i]==10);i++);
				ret.push_back(s);
			}
			return ret;
		}
		passenger* taxy_system::find_passenger(string name)
		{
			for(int i=0;i<passengers.size();i++)
				if((passengers[i])->get_name()==name)
					return (passengers[i]);
			return NULL;
		}
		driver* taxy_system::find_driver(string name)
		{
			for(int i=0;i<drivers.size();i++)
				if((drivers[i])->get_name()==name)
					return (drivers[i]);
			return NULL;
		}
        bool taxy_system::existent_phone(string phone)
		{
			for(int i=0;i<passengers.size();i++)
				if((passengers[i])->get_phone()==phone)
					return true;
			return false;
		}
		bool taxy_system::existent_num(int num)
		{
			for(int i=0;i<drivers.size();i++)
				if((drivers[i])->get_number()==num)
					return true;
			for(int i=0;i<register_list.size();i++)
				if((register_list[i])->get_number()==num)
					return true;
			return false;
		}
		bool taxy_system::existent_driver(string name)
		{
			for(int i=0;i<drivers.size();i++)
				if((drivers[i])->get_name()==name)
					return true;
			for(int i=0;i<register_list.size();i++)
				if((register_list[i])->get_name()==name)
					return true;
			return false;
		}
		bool taxy_system::existent_passenger(string name)
		{
			for(int i=0;i<passengers.size();i++)
				if((passengers[i])->get_name()==name)
					return true;
			return false;
		}
		bool taxy_system::is_it_acceptable_model(string model_name)
		{
			for(int i=0;i<acceptable_model.size();i++)
				if((acceptable_model[i])==model_name)
					return true;
			return false;
		}
		date* taxy_system::find_date(std::string date_name)
		{
			date a(date_name);
			for(int i=0;i<dates.size();i++)
				if(*(dates.at(i))==a)
					return (dates[i]);
			return NULL;
		}
		passenger* taxy_system::is_passenger_active(string name)
		{
			passenger* a=find_passenger(name);
			if(a==NULL)
			{
				output::out<<"EROR : you are not register as passenger yet"<<endl;
				return NULL;
			}
			if(a->get_active()==false)
			{
				output::out<<"EROR : you are not login yet"<<endl;
				return NULL;
			}
			return a;
		}
		driver* taxy_system::is_driver_active(string name)
		{
			driver* a=find_driver(name);
			if(a==NULL)
			{
				if(existent_driver(name))
					output::out<<"EROR : waiting for admin acception ..."<<endl;
				else
					output::out<<"EROR : you are not register as driver yet"<<endl;
				return NULL;
			}
			if(a->get_active()==false)
			{
				output::out<<"EROR : you are not login yet"<<endl;
				return NULL;
			}
			return a;
		}
		bool taxy_system::is_admin_active(string name)
		{
			if(name=="admin"){
				if(!admin_activation)
					output::out<<"EROR : you're not login"<<endl;
				return admin_activation;
			}
			else{
				output::out<<"EROR : you are not admin"<<endl;
				return false;
			}
		}
		passenger* taxy_system::find_discount(int discount_code)
		{
			for(int i=0;i<passengers.size();i++)
				if((passengers[i])->get_current_code()==discount_code)
					return (passengers[i]);
			return NULL;
		}
		vector<string> taxy_system::show_all_driver(bool VIP)
		{
			vector<string> ret;
			for(int i=0;i<drivers.size();i++)
				if((drivers[i])->get_VIP()==VIP && (drivers[i])->get_status()==available)
					ret.push_back((drivers[i])->get_last_place());
			return ret;
		}
		void taxy_system::send_request(vector<string> best_drivers_place,passenger* a,bool VIP)
		{
			for(int i=0;i<best_drivers_place.size();i++){
				driver* finded=find_placed_driver(best_drivers_place[i],VIP);
				if(finded)
					finded->add_request(a);
			}
		}
		driver* taxy_system::find_placed_driver(string place,bool VIP)
		{
			for(int i=0;i<drivers.size();i++)
				if((drivers[i])->get_last_place()==place && (drivers[i])->get_status()==available && (drivers[i])->get_VIP()==VIP)
					return (drivers[i]);
			return NULL;
		}
		void taxy_system::payment(int day)
		{
			for(int i=0;i<drivers.size();i++)
			{
				int cost=(drivers[i])->get_distance(day);
				if((drivers[i])->get_VIP())
					cost*=2;
				this->credits[credits.size()-1]->credit-=cost;
				(drivers[i])->change_income(cost);
			}
		}
		void taxy_system::register_passenger(string name,string pass,string phone_num,int discount_code)
		{
			if(existent_passenger(name) || name=="admin")
			{
				output::out<<"EROR : this user name chosen"<<endl;
				return;
			}
			if(existent_phone(phone_num))
			{
				output::out<<"EROR : this phone number used before"<<endl;
				return;
			}
				passenger* a=new passenger(name,pass,phone_num,*current);
				passengers.push_back(a);
				if(discount_code!=0)
				{
					passenger* b=find_discount(discount_code);
					if(b==NULL)
					{
						output::out<<"the discount code is not correct but you register succesfully\n";
						return;
					}
					a->change_credit(10);
					b->use_code();
				}
				output::out<<"you register succesfully\n"<<endl;
		}
		void taxy_system::register_driver(string name,string pass,string model,string color,int year,int num,bool VIP)
		{
			if(existent_driver(name) || name=="admin")
			{
				output::out<<"EROR : this user name chosen"<<endl;
				return;
			}
			if(existent_num(num))
			{
				output::out<<"EROR : this number used before"<<endl;
				return;
			}
			if(!is_it_acceptable_model(model))
			{
				output::out<<"EROR : you're model is not acceptable"<<endl;
				return;
			}
			driver* a=new driver(name,pass,model,color,year,num,*current,VIP);
			register_list.push_back(a);
			output::out<<"you register succesfully now waiting for acception ..."<<endl;
		}
        void taxy_system::show_register_requests(string name)
		{
			if(is_admin_active(name))
				for(int i=0;i<register_list.size();i++)
					output::out<<*(register_list[i])<<endl;
		}
		void taxy_system::accept_registration(string admin_name,string name)
		{
			if(is_admin_active(admin_name))
			{
				for(int i=0;i<register_list.size();i++)
					if((register_list[i])->get_name()==name)
					{
						drivers.push_back(register_list[i]);
						register_list.erase(register_list.begin()+i);
						output::out<<"request of \""<<name<<"\" accepted"<<endl;
						return;
					}
					output::out<<"EROR : this name not exist in list"<<endl;
			}
		}
		void taxy_system::reject_registration(string admin_name,string name)
		{
			if(is_admin_active(admin_name))
			{
				for(int i=0;i<register_list.size();i++)
					if((register_list[i])->get_name()==name)
					{
						delete register_list[i];
						register_list.erase(register_list.begin()+i);
						output::out<<"the request of \""<<name<<"\" rejected"<<endl;
						return;
					}
				output::out<<"EROR : this name not exist in list"<<endl;
			}
		}
		void taxy_system::get_discount_code(string name)
		{
			if(passenger* a=is_passenger_active(name))
				a->get_new_code();
		}
		void taxy_system::login(string name,string pass)
		{
			if(name=="admin")
			{
				if(pass=="s3cret"){
					admin_activation=true;
					output::out<<"you login succesfully"<<endl;
				}
				else
					output::out<<"EROR : wrong password"<<endl;
				return;
			}
			output::out<<"EROR : you are not register yet"<<endl;
		}
		void taxy_system::passenger_login(string name,string pass)
		{
			if(passenger* a=find_passenger(name))
			{
				if(a->get_pass()==pass){
					a->set_active(true);
					output::out<<"you login succesfully"<<endl;
				}
				else
					output::out<<"EROR : wrong password"<<endl;
				return;
			}
			output::out<<"EROR : you are not register yet"<<endl;
		}
		void taxy_system::driver_login(string name,string pass)
		{
			if(driver* a=find_driver(name))
			{
				if(a->get_pass()==pass){
					a->set_active(true);
					output::out<<"you login succesfully"<<endl;
				}
				else
					output::out<<"EROR : wrong password"<<endl;
				return;
			}
			
			if(existent_driver(name)){
				output::out<<"EROR : waiting for admin acception ..."<<endl;
				return;
			}
			output::out<<"EROR : you are not register yet"<<endl;
		}
		void taxy_system::logout(string name,string kind)
		{
			if(name=="admin")
				if(is_admin_active(name))
				{
					admin_activation=false;
					output::out<<"you log out\n";
					return;
				}
			driver* a=find_driver(name);
			if(kind=="Taxi" && a!=NULL)
				if(is_driver_active(name))
				{
					a->set_active(false);
					output::out<<"you log out\n";
					return;
				}
			passenger* b=find_passenger(name);
			if(kind=="Passenger" && b!=NULL)
				if(is_passenger_active(name))
				{
					b->set_active(false);
					output::out<<"you log out\n";
					return;
				}
			if(existent_driver(name)){
				output::out<<"EROR : waiting for admin acception"<<endl;
				return;
			}
			output::out<<"EROR : you're not login yet"<<endl;
		}
		void taxy_system::set_status(string name , bool is_available , string address)
		{
			driver* a=is_driver_active(name);
			if(a!=NULL)
			{
				if(is_available)
				{
					if(roads.check_address(address)){
						a->set_status(available);
						a->set_last_place(address);
						output::out<<"you're status changed succesfully"<<endl;
					}
					else
						output::out<<"EROR : address is not acceptable"<<endl;
				}
				else{
					a->set_status(unavailable);
					output::out<<"you're status changed succesfully"<<endl;
				}
			}
		}
		void taxy_system::estimate_trip(string name,vector<string> addresses,bool VIP)
		{
			if(passenger* a=is_passenger_active(name))
			{
				int distance=roads.find_distance(addresses);
				int cost=distance;
				if(VIP)
					cost*=2;
				if(a->get_tripy())
					cost/=2;
				output::out<<cost<<" "<<distance<<endl;
			}
		}
		void taxy_system::request_trip(string name,vector<string> addresses,bool VIP)
		{
			if(passenger* a=is_passenger_active(name))
			{
				int distance=roads.find_distance(addresses);
				int cost=distance;
				if(VIP)
					cost*=2;
				if(a->get_tripy())
					cost/=2;
				if(a->get_credit()-cost<-10)
					output::out<<"EROR : you have not enough money"<<endl;
				else
				{
					if(!(a->get_request()))
					{
						vector<string> drivers_place=show_all_driver(VIP);
						if(drivers_place.size()==0){
							output::out<<"EROR : there isn't available driver right now .try later"<<endl;
							return;
						}
						a->make_request(addresses,VIP,distance);
						vector<string> best_drivers_place=roads.find_best_driver(addresses[0],drivers_place);
						send_request(best_drivers_place,a,VIP);
						output::out<<cost<<" "<<distance<<endl;
					}
					else
						output::out<<"EROR : you already have a unfinished trip"<<endl;
				}
			}
		}
		void taxy_system::cancel_request(string name)
		{
			if(passenger* a=is_passenger_active(name))
			{
				if(a->get_request()->get_status()==waiting)
				{
					a->cancel_request();
					for(int i=0;i<drivers.size();i++)
						(drivers[i])->reject_request(a);
					output::out<<"the request canceled"<<endl;
				}
				else
					output::out<<"EROR : you're request accepted you can't cancel it"<<endl;
			}
		}
		void taxy_system::show_requests(string name)
		{
			if(driver* a=is_driver_active(name))
				a->show_requests();
		}
		void taxy_system::accept_request(string user_name,string passenger_name)
		{
			if(driver* a=is_driver_active(user_name))
			{
				if(passenger* b=find_passenger(passenger_name)){
					a->accept_request(b);
					output::out<<"request of \""<<passenger_name<<"\" accepted"<<endl;
					return;
				}
				else{
					output::out<<"EROR : you haven't any request from \""<<passenger_name<<"\""<<endl;
				}
			}
		}
		void taxy_system::trip_status(string name)
		{
			if(passenger* a=is_passenger_active(name))
			{
				trip* req=a->get_request();
				if(req==NULL){
					output::out<<"EROR : you dont have any request"<<endl;
					return;
				}
				if(req->get_status()==waiting)
					output::out<<"waiting ..."<<endl;
				else
				{
					switch(req->get_status())
					{
					case accepted:
					output::out<<"accepted ";
						break;
					case arrived:
						output::out<<"arrived  ";
						break;
					case not_rated:
						output::out<<"not_rated  ";
						break;
					}
					driver* b=req->get_driver();
					if(b==NULL){
						throw "EROR : system crashed please try later (code 31)";
					}
					output::out<<b->get_name()<<" ";
					output::out<<b->get_last_place()<<" ";
					output::out<<b->get_model()<<" ";
					output::out<<b->get_color()<<endl;
				}
			}
		}
        void taxy_system::set_arrived(string name)
		{
			if(driver* a=is_driver_active(name))
			{
				if(passenger* b=a->get_request()){
					if(trip* cur=b->get_request()){
						cur->set_status(arrived);
						output::out<<"done !"<<endl;
					}
					else
						throw "system crashed please try later (code 32)";
				}
				else{
					output::out<<"EROR : you dont have any passenger"<<endl;
					return;
				}
			}
		}
		void taxy_system::end_trip(string name)
		{
			if(driver* a=is_driver_active(name))
			{
				if(passenger* b=a->get_request()){
					if(trip* cur=b->get_request()){
						cur->set_status(not_rated);
						int cost=cur->get_distance();
						if(cur->get_VIP())
							cost*=2;
						if(b->get_tripy())
							cost/=2;
						b->change_credit(-1*cost);
						this->credits[credits.size()-1]->credit+=cost;
						a->end_trip(*(dates[dates.size()-1]));
						b->set_date(*(dates[dates.size()-1]));
						output::out<<"trip ended . you're now available"<<endl;
					}
					else
						throw "system crashed please try later (code 33)";
				}
				else{
					output::out<<"EROR : you dont have any passenger"<<endl;
				}
			}
		}
		void taxy_system::rate_driver(string name,int rate)
		{
			if(passenger* a=is_passenger_active(name))
			{
				if(rate>0 && rate<11)
				{
					if(trip* req=a->get_request()){
						if(driver* b=req->get_driver()){
							b->change_rate(rate);
							a->end_trip();
							output::out<<"you rate "<<rate<<" to \""<<b->get_name()<<"\" . thanks for you're rating"<<endl;
						}
						else
							throw "system crashed please try later (code 35)";
					}
					else
						output::out<<"EROR : you dont have trip request"<<endl;
				}
				else
					output::out<<"EROR : the rate should be from 1 to 10"<<endl;
			}
		}
		void taxy_system::charge_account(string name,int amount)
		{
			if(passenger* a=is_passenger_active(name))
			{
				a->change_credit(amount);
				output::out<<"new amoun : "<<amount<<"   current credit : "<<a->get_credit()<<endl;
			}
		}
		void taxy_system::get_credit(string name)
		{
			if(passenger* a=is_passenger_active(name))
				output::out<<a->get_credit();
		}
		void taxy_system::set_time(string name,string date_time)
		{
			if(is_admin_active(name))
			{
				date* new_time=new date(date_time);
				dates.push_back(new_time);
				this->current=(dates[dates.size()-1]);
				date_credit* a=new date_credit;
				a->credit=0;
				a->d=this->current;
				this->credits.push_back(a);
				output::out<<"the date changed succesfully"<<endl;
				if((dates[dates.size()-2])->get_day()!=new_time->get_day()){
					payment((dates[dates.size()-2])->get_day());
					output::out<<"the payment of driver payed . it was about "<<-1*(a->credit)<<endl;
				}
			}
		}
		void taxy_system::driver_report(string admin_name,string name,string first_time,string last_time)
		{
			if(is_admin_active(admin_name))
			{
				if(driver* a=find_driver(name))
				{
					date* first=find_date(first_time);
					date* last=find_date(last_time);
					if(first&&last)
					{
						output::out<<a->get_amount_trip(*first,*last)<<" "<<a->get_total_income()<<" "<<a->get_total_rate()<<endl;
					}
					else
						output::out<<"EROR : illegal dates"<<endl;
				}
				else
					output::out<<"EROR : driver not found"<<endl;
			}
		}
		void taxy_system::passenger_report(string admin_name,string name)
		{
			if(is_admin_active(admin_name))
			{
				if(passenger* a=find_passenger(name))
					output::out<<a->get_credit()<<endl;
				else
					output::out<<"EROR : passenger not found"<<endl;
			}
		}
		void taxy_system::system_report(string name)
		{
			if(is_admin_active(name))
			{
				int credit=0;
				for(int i=0;i<credits.size();i++)
				{
					credit+=(credits[i])->credit;
				}
				int trip_count=0;
				for(int i=0;i<drivers.size();i++)
				{
					trip_count+=(drivers[i])->get_amount_trip();
				}
				output::out<<credit<<" "<<trip_count<<" "<<drivers.size()<<" "<<passengers.size()<<endl;
			}
		}
		void taxy_system::system_report(string name,string first_time,string last_time)
		{
			if(is_admin_active(name))
			{
				date* first=find_date(first_time);
				date* last=find_date(last_time);
				if(first && last){
					int credit=0;
					for(int i=0;i<credits.size();i++)
					{
						if(((credits[i])->d->operator>(*first) || (credits[i])->d->operator==(*first)) && (credits[i])->d->operator<(*last))
							credit+=(credits[i])->credit;
					}
					int trip_count=0;
					for(int i=0;i<drivers.size();i++)
					{
						trip_count+=(drivers[i])->get_amount_trip(*first,*last);
					}
					int driver_count=0;
					for(int i=0;i<drivers.size();i++)
						if(((drivers[i])->get_register_date()==(*first) || (drivers[i])->get_register_date()>(*first)) && (drivers[i])->get_register_date()<(*last))
							driver_count++;
					int passenger_count=0;
					for(int i=0;i<passengers.size();i++)
						if(((passengers[i])->get_register_date()==(*first) || (passengers[i])->get_register_date()>(*first)) && (passengers[i])->get_register_date()<(*last))
							passenger_count++;
						output::out<<credit<<" "<<trip_count<<" "<<driver_count<<" "<<passenger_count<<endl;
				}
				else
					output::out<<"EROR : illegal dates"<<endl;
			}
		}
        void taxy_system::get_data()
		{
			ifstream input_file("topology.cfg");
			if(!input_file.is_open())
				throw "can not read datas";
			char input_array[100]={0};
			vector<string> input;
			input_file.getline(input_array,100);
			input=standard_input(input_array);
			int galaxy_count=string_to_int(input[0]);
			while(galaxy_count)
			{
				input.clear();
				input_file.getline(input_array,100);
				input=standard_input(input_array);
				string galaxy_name=input[0];
				roads.add_galaxy(galaxy_name);

				int planet_count=string_to_int(input[1]);
				int planet_count2=planet_count;
				ios::streampos cur=input_file.tellg();
				while(planet_count2)
				{
					input.clear();
					input_file.getline(input_array,100);
					input=standard_input(input_array);
					string planet_name=input[0];
					roads.add_planet(galaxy_name,planet_name);
					if(planet_count2==planet_count)
						roads.chose_gate(galaxy_name,planet_name);
					int near_planet=string_to_int(input[1]);
					for(int i=0;i<near_planet;i++)
						input_file.getline(input_array,100);
					planet_count2--;
				}

				input_file.seekg(cur);
				while(planet_count)
				{
					input.clear();
					input_file.getline(input_array,100);
					input=standard_input(input_array);
					string planet_name=input[0];

					int near_planet=string_to_int(input[1]);
					for(int i=0;i<near_planet;i++)
					{
						input.clear();
						input_file.getline(input_array,100);
						input=standard_input(input_array);
						string near_name=input[0];
						roads.add_near_planet(galaxy_name,planet_name,near_name);
					}
					planet_count--;
				}
				galaxy_count--;
			}
			input_file.close();


			input_file.open("vehicles.cfg");     						//Krennics_Imperial_Shuttle --> it contain bad char
			if(!input_file.is_open())
				throw "can not read datas";
			while(input_file.getline(input_array,100))
			{
				input.clear();
				input=standard_input(input_array);
				for(int i=0;i<input.size();i++)
					this->acceptable_model.push_back(input[0]);
			}
		}
        void taxy_system::get_input(std::string input_array)
        {
			vector<string> input=standard_input(input_array);
			string order=input[1];
			string name=input[0];
			if(order=="register")
			{
				if(input.size()==4){
					register_passenger(name,input[2],input[3],0);
					return;
				}
				if(input.size()==5){
					register_passenger(name,input[2],input[3],string_to_int(input[4]));
					return;
				}
				if(input.size()==7){
					register_driver(name,input[2],input[4],input[6],string_to_int(input[5]),string_to_int(input[3]),false);
					return;
				}
				if(input.size()==8){
					register_driver(name,input[2],input[4],input[6],string_to_int(input[5]),string_to_int(input[3]),true);
					return;
				}
			}
			if(order=="show_registration_requests")
			{
				if(input.size()==2){
					show_register_requests(name);
					return;
				}
			}
			if(order=="accept_registration")
			{
				if(input.size()==3){
					accept_registration(name,input[2]);
					return;
				}
			}
			if(order=="reject_registration")
			{
				if(input.size()==3){
					reject_registration(name,input[2]);
					return;
				}
			}
			if(order=="get_discount_code")
			{
				if(input.size()==2){
					get_discount_code(name);
					return;
				}
			}
			if(order=="passenger_login")
			{
				if(input.size()==3){
					passenger_login(name,input[2]);
					return;
				}
			}
			if(order=="driver_login"){
				if(input.size()==3){
					driver_login(name,input[2]);
					return;
				}
			}
			if(order=="login"){
				if(input.size()==3){
					login(name,input[2]);
					return;
				}
			}
			if(order=="logout")
			{
				if(input.size()==3){
					logout(name,input[2]);
					return;
				}
				if(input.size()==2){
					logout(name,string(""));
					return;
				}
			}
			if(order=="set_status")
			{
				if(input.size()==3 || input.size()==4){
					if(input[2]=="available")
						set_status(name,true,input[3]);
					if(input[2]=="unavailable")
						set_status(name,false,"");
					return;
					}
			}
			if(order=="estimate_trip")
			{
				if(input.size()>=4){
					int count=input.size();
					vector<string> addresses;
					for(int i=2;i<count;i++)
						addresses.push_back(input[i]);
					if(input[2]=="VIP")
					{
						addresses.erase(addresses.begin());
						estimate_trip(name,addresses,true);
					}
					else
						estimate_trip(name,addresses,false);
						return;
				}
			}
			if(order=="request_trip")
			{
				if(input.size()>=4){
					int count=input.size();
					vector<string> addresses;
					for(int i=2;i<count;i++)
						addresses.push_back(input[i]);
					if(input[2]=="VIP")
					{
						addresses.erase(addresses.begin());
						request_trip(name,addresses,true);
					}
					else
						request_trip(name,addresses,false);
					return;
				}
			}
			if(order=="cancel_trip_request")
			{
				if(input.size()==2){
					cancel_request(name);
					return;
				}
			}
			if(order=="show_trip_requests")
			{
				if(input.size()==2){
					show_requests(name);
					return;
				}
			}
			if(order=="accept_trip_request")
			{
				if(input.size()==3){
					accept_request(name,input[2]);
					return;
				}
			}
			if(order=="trip_status")
			{
				if(input.size()==2){
					trip_status(name);
					return;
				}
			}
			if(order=="arrived")
			{
				if(input.size()==2){
					set_arrived(name);
					return;
				}
			}
			if(order=="end_trip")
			{
				if(input.size()==2){
					end_trip(name);
					return;
				}
			}
			if(order=="rate_driver")
			{
				if(input.size()==3){
					rate_driver(name,string_to_int(input[2]));
					return;
				}
			}
			if(order=="charge_account")
			{
				if(input.size()==3){
					charge_account(name,string_to_int(input[2]));
					return;
				}
			}
			if(order=="get_credit")
			{
				if(input.size()==2){
					get_credit(name);
					return;
				}
			}
			if(order=="set_time")
			{
				if(input.size()==3){
					set_time(name,input[2]);
					return;
				}
			}
			if(order=="driver_report")
			{
				if(input.size()==5){
					driver_report(name,input[2],input[3],input[4]);
					return;
				}
			}
			if(order=="passenger_report")
			{
				if(input.size()==3){
					passenger_report(name,input[2]);
					return;
				}
			}
			if(order=="system_report")
			{
				if(input.size()==2){
					system_report(name);
					return;
				}
				if(input.size()==4){
					system_report(name,input[2],input[3]);
					return;
				}
			}
			if(order=="GET_TIME"){
				output::out<<*(this->current);
				return;
			}
			output::out<<"EROR : an undefinet order format . rerquest fail"<<endl;
		}
