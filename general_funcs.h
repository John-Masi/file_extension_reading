#include <cstdint>
#include <vector>
#include <algorithm>

#pragma once

inline std::vector<uint8_t> read_file(const std::string& _fname){
	std::size_t size;
	std::vector<uint8_t> buffer;

	std::ifstream file(_fname,std::ios::binary);

	if(!file.is_open()){
		std::cout << "File will not open" << "\n";
	}
	else{
		file.seekg(0,std::ios::end);
		size = file.tellg();
		file.seekg(0,std::ios::beg);
		buffer.resize(size);
		file.read(reinterpret_cast<char*>(buffer.data()),size);
	
		std::streamsize r = file.gcount();
		buffer.resize(r);

	}

	return buffer;

}

inline void hexdump(const std::vector<uint8_t>& _b) {
	for(std::size_t i = 0; i < _b.size(); i++) {
		unsigned char byte = _b[i];
		uint8_t high = byte >> 4;
		uint8_t low = byte & 0x0F;
		printf("%X %X \n",high,low);
	}
};

inline bool _validPNG(const std::vector<uint8_t>& buffer){
	if(buffer.size() < 8) { return false; }
	const uint8_t p[8] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
	std::vector<uint8_t> p1 = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
	return std::equal(p1.begin(),p1.end(),buffer.begin(),buffer.begin() + 8);
}

inline bool _validIHDR(const std::vector<uint8_t>&buffer){


	const uint8_t h[8] = {0x49,0x48,0x44,0x52};
	

	return true;
}

inline uint32_t to_u32(uint8_t b0,uint8_t b1,uint8_t b2,uint8_t b3) {
	return (uint32_t(b0) << 24) | (uint32_t(b1) << 16) | (uint32_t(b2) << 8) | b3;
}

// Conversion specifically for little endian files (pcapng)
inline uint32_t to_u32l(uint8_t b0,uint8_t b1,uint8_t b2,uint8_t b3){
	return b0 | (uint32_t(b1) << 8) | (uint32_t(b2) << 16) | (uint32_t(b3) << 24);
}
