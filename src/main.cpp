#include "file.hpp"
#include "file_r.h"
#include <memory>
#include <iostream>

int main() {
	auto buf = f_read("./1MB.png");
	auto b = std::move(buf);
	auto F = File::mbyte_validation(std::move(b));
	F->parse(buf);
	
}
