#include <cstdint>
#include <vector>

#pragma once 



inline bool is_equal(int n,const std::vector<uint8_t>& v1,const std::vector<uint8_t> v2) {
	bool _r{};
	for(std::size_t i = 0; i < n; i++) {
		if(v1[i] == v2[i]) {
			_r = true;	
		}
		else {
			_r = false;
		}
	}

	return _r;
}


inline bool _validPNG(const std::vector<uint8_t>&& buffer){
	const uint8_t p[8] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
	return true;
}

inline bool _validIHDR(const std::vector<uint8_t>&buffer){


	const uint8_t h[8] = {0x49,0x48,0x44,0x52};
	

	return true;
}

uint32_t to_u32(uint8_t b0,uint8_t b1,uint8_t b2,uint8_t b3) {
	return (uint32_t(b0) << 24) | (uint32_t(b1) << 16) | (uint32_t(b2) << 8) | b3;
}
