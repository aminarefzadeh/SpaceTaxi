#ifndef __OUTPUT_H_INCLUDED__
#define __OUTPUT_H_INCLUDED__
#include <string>
#include <iostream>
#include <sstream>

class output
{
	public:
        static std::stringstream out;
        static std::string get_output();
        static void clear_output();
};

#endif
