#include "png.hpp" 
#include "general_funcs.h"
#include <optional> 
#include <vector> 
#include <cstdint> 
#include <algorithm>
#include <utility>

std::optional<PNG> PNG::parse_png(const std::vector<uint8_t>&& buffer){
	std::size_t j = 0;


	PNGData data;


	while(j + 8 < buffer.size()) {
		uint32_t len = to_u32(buffer[j],buffer[j+1],buffer[j+2],buffer[j+3]);

		if(_validIHDR(buffer)) {
			data.width = to_u32(buffer[j+16],buffer[j+17],buffer[j+18],buffer[j+19]);
			data.height = to_u32(buffer[j+20],buffer[j+21],buffer[j+22],buffer[j+23]);
			data.color = buffer[j+17];
		
		}
		if(j + 12 + len > buffer.size()){
			break;
		}

		j = j + 12 + len;

	}


	return PNG(std::move(data));
}



