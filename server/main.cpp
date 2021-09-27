#include "server.h"
#include "taxy_system.h"
#include "output.h"
#include <sstream>
#include <cstdlib>
using namespace std;
class driver;
class passenger;
struct identify {
	string name;
	int identifier;
	bool customer;
};

class MyServer : public Server {
	public:
		MyServer(int port) : Server(port) { main_sys.get_data(); }
		void on_standard_input(string line);
		void on_new_connection(int identifier);
		void on_new_message(int identifier, string message);
		void on_terminated_connection(int identifier);
	private:
		taxy_system main_sys;
		vector<identify*> client_list;
		void console_answer();
		void send_massage(int identifier);
		string get_id_name(int identifier);
		identify* find_identify(int identifier);
};

void MyServer::on_standard_input(string line){
 	if (line == ":q"){
		stop();
		return;
	}
	vector<string> input;
	input=main_sys.standard_input(line);
	stringstream oss;
	oss<<"admin";
	for(int i=0;i<input.size();i++)
		oss<<" "<<input[i];
	main_sys.get_input(oss.str());
	console_answer();
}

void MyServer::on_new_connection(int identifier) {
  cout << "NEW CONNECTION: " << identifier << endl;
}

void MyServer::on_new_message(int identifier, string message) {
	if(message=="TAXI CLIENT"){
		identify* new_id=new identify;
		new_id->name="admin";
		new_id->identifier=identifier;
		new_id->customer=false;
		client_list.push_back(new_id);
		return;
	}
	if(message=="CUSTOMER CLIENT"){
		identify* new_id=new identify;
		new_id->name="admin";
		new_id->identifier=identifier;
		new_id->customer=true;
		client_list.push_back(new_id);
		return;
	}
	
	cout<<"from "<<identifier<<" : "<<message<<endl;
	vector<string> input;
	input=main_sys.standard_input(message);
	stringstream oss;
	try{
		//find the exeptions
		if(input[0]=="register"){
			if(get_id_name(identifier)=="admin"){
				identify* cur=find_identify(identifier);
				if(((input.size()==4 || input.size()==5) && cur->customer) || ((input.size()==7 || input.size()==8) && !cur->customer)){
					oss<<input[1]<<" "<<input[0];
					for(int i=2;i<input.size();i++)
						oss<<" "<<input[i];
					main_sys.get_input(oss.str());
				}
				else{
					send(identifier,"EROR : undefined order format\n");
					cout<<"to   "<<identifier<<" : "<<"EROR : undefined order format"<<endl;
					return;
				}
			}
			else{
				oss<<"EROR : you should logout first\n";
				send(identifier,oss.str());
				cout<<"to   "<<identifier<<" : "<<oss.str();
				return;
			}
		}
		if(input[0]=="login"){
			if(get_id_name(identifier)=="admin"){
				identify* cur=find_identify(identifier);
				if((cur->customer && main_sys.existent_passenger(input[1])) || (!cur->customer && main_sys.existent_driver(input[1]))){
					if(input.size()==3){
						string a(cur->customer?"passenger_":"driver_");
						a.append("login");
						oss<<input[1]<<" "<<a<<" "<<input[2];
						main_sys.get_input(oss.str());
						if(output::get_output().find("EROR :")==string::npos)
							cur->name=input[1];
					}
					else{
						send(identifier,"EROR : undefined order format\n");
						cout<<"to   "<<identifier<<" : "<<"EROR : undefined order format\n";
						return;
					}
				}
				else{
					if(cur->customer){
						send(identifier,"EROR : you are not register as passenger yet\n");
						cout<<"to   "<<identifier<<" : "<<"EROR : you are not register as passenger yet\n";
					}
					else{
						send(identifier,"EROR : you are not register as driver yet\n");
						cout<<"to   "<<identifier<<" : "<<"EROR : you are not register as driver yet\n";
					}
					return;
				}
			}
			else {
				oss<<"EROR : you should logout first\n";
				send(identifier,oss.str());
				cout<<"to   "<<identifier<<" : "<<oss.str();
				return;
			}
		}
		if(input[0]=="logout"){
			string name=get_id_name(identifier);
			if(name=="admin"){
				send(identifier,"EROR : you are not login yet \n");
				cout<<"to   "<<identifier<<" : EROR : you are not login yet\n";
				return;
			}
			identify* cur=find_identify(identifier);
			string SendMessage;
			SendMessage.append(name);
			SendMessage.append(" logout");
			SendMessage.append(cur->customer? " Passenger" : " Taxi");
			main_sys.get_input(SendMessage);
			if(output::get_output()=="you log out\n"){
				cur->name="admin";
				send_massage(identifier);
				return;
			}
		}
		if(input[0]!="login" && input[0]!="register" && input[0]!="logout"){
			string name=get_id_name(identifier);
			if(name=="admin"){
				send(identifier,"EROR : you are not login yet \n");
				cout<<"to   "<<identifier<<" : EROR : you are not login yet\n";
				return;
			}
			oss<<name;
			for(int i=0;i<input.size();i++)
				oss<<" "<<input[i];
			main_sys.get_input(oss.str());
		}
		send_massage(identifier);
	}
	catch(const char* e){
		string a("EROR : ");
		a.append(e);
		a.append("\n");
		send(identifier,a);
		cout<<"to   "<<identifier<<" : "<<a<<endl;
	}
}

void MyServer::on_terminated_connection(int identifier) {
	for(int i=0;i<client_list.size();i++)
	{
		if((client_list[i])->identifier==identifier){
			stringstream oss;
			oss<<(client_list[i])->name<<" logout";
			main_sys.get_input(oss.str());
			client_list.erase(client_list.begin()+i);
			output::clear_output();
			return;
		}
	}
}

void MyServer::console_answer() {
	cout<<output::get_output();
	output::clear_output();
}

void MyServer::send_massage(int identifier)  {

	string output_string;
	output_string=output::get_output();
	cout<<"to   "<<identifier<<" : "<<output_string;
	send(identifier,output_string);
	output::clear_output();
}

string MyServer::get_id_name(int identifier)  {

	for(int i=0;i<client_list.size();i++)
		if((client_list[i])->identifier==identifier)
			return (client_list[i])->name;
	return "admin";
}

identify* MyServer::find_identify(int identifier){
	for(int i=0;i<client_list.size();i++)
		if((client_list[i])->identifier==identifier)
			return client_list[i];
	return NULL;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "valid operation: " << argv[0] << " [port number]\n";
    exit(-1);
  }
	try{
		MyServer server(Tools::mystoi(argv[1]));
		server.run();
	}
	catch(NetworkException& e){
		cout<<e.get_message()<<endl;
	}
	catch(const char* e){
		cout<<e<<endl;
	}
	
  return 0;
}
