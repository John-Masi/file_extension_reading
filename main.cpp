#include "file.hpp"
#include "general_funcs.h"
#include <iostream>


int main() {

	File& f = File::getFile();
	auto buf = read_file("img.png");
	f.mbyte_validation(buf);
	f.do_parsing(buf);

}
