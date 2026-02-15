#include "file.hpp"
#include "general_funcs.h"
#include <memory>
#include <iostream>
#include <typeinfo>

int main() {
	std::vector<uint8_t>&& buf = read_file("./1MB.png");
	auto F = File::mbyte_validation(std::move(buf));
	F->parse(buf);
	
}
