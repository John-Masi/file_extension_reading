#include <cstdint>
#include <vector>
#include <algorithm>

#pragma once


// IMPLEMENT SINGLE TON
// use one struct for data 
// use same byte logic 
// create parsing funcs for each file type in the singleton class 

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
