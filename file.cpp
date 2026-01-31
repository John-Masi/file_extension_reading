#include "file.hpp"
#include "general_funcs.h"
#include <iostream>

void File::do_parsing(std::vector<uint8_t>& _b) {
	if(this->_e == FileExten::png ) {
		this->parse_png(_b);
	}
}

void File::parse_png(std::vector<uint8_t>& _b) {
	std::cout << "Hello!";
}

void File::parse_pcapng(std::vector<uint8_t>& _b) {
}


void File::mbyte_validation(const std::vector<uint8_t>& _b) {
	if(_validPNG(_b)){ this->_e = FileExten::png; }
	else { this->_e = FileExten::nill; }
}
