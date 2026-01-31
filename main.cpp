#include "file.hpp"
#include "general_funcs.h"
#include <iostream>

std::vector<uint8_t> read_file(const std::string& _fname) {

	std::ifstream file(_fname, std::ios::binary);
	file.seekg(0,std::ios::end);
	std::size_t size = file.tellg();
	file.seekg(0,std::ios::beg);

	std::vector<uint8_t> buffer(size);
	file.read(reinterpret_cast<char*>(buffer.data()),size);
	
	std::streamsize r = file.gcount();
	buffer.resize(r);

	return buffer;
}

int main() {

	File& f = File::getFile();
	auto buf = read_file("img.png");
	f.mbyte_validation(buf);
	f.do_parsing(buf);

}
