#include "output.h"
using namespace std;

string output::get_output()
{
	return out.str();
}
void output::clear_output()
{
	out.str(std::string());
}

stringstream output::out;
