#include "png.hpp" 
#include <optional> 
#include <vector> 
#include <cstdint> 
#include <algorithm>

std::optional<PNG> PNG::parse_png(const std::vector<uint8_t>&& buffer){
	std::size_t j = 0;


	PNGData data;

	while(j + 8 < buffer.size()) {
		uint32_t len;

		j = j + 12 + len;

	}


	return PNG(std::move(data));
}




bool _validPNG(const std::vector<uint8_t>&& buffer){
	const uint8_t p[8] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
	return true;
}

bool _validIHDR(const std::vector<uint8_t>&buffer){

	const uint8_t h[8] = {0x49,0x48,0x44,0x52};
	

	return true;
}
