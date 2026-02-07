#include "file.hpp"
#include "general_funcs.h"
#include <iostream>

int main() {

	File& f = File::getFile();
	auto buf = read_file("");
	f.mbyte_validation(buf);
	f.do_parsing(buf);

}
