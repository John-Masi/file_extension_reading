#include <cstdint>
#include <vector>
#include <algorithm>
#include <span>

#ifndef GENERAL_FUNCS_H
#define GENERAL_FUNCS_H

namespace MagicBytes {
	const uint8_t m_pcapng[4] = {0x0A,0x0D,0x0D,0x0A}; 
	const uint8_t m_png[8] = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};

};


void hexdump(const std::vector<uint8_t>& _b) {
	for(std::size_t i = 0; i < 8; i++) {
		unsigned char byte = _b[i];
		uint8_t high = byte >> 4;
		uint8_t low = byte & 0x0F;
		printf("%X %X \n",high,low);
	}
};

constexpr bool _validPCAPNG(const std::vector<uint8_t>& buffer){
	std::span<const uint8_t> p1(MagicBytes::m_pcapng);
	return std::equal(p1.begin(),p1.end(),buffer.begin(),buffer.begin() + 4);

}

constexpr bool _validPNG(const std::vector<uint8_t>& buffer){
	std::vector<uint8_t> p1 = {0x89,0x50,0x4E,0x47,0x0D,0x0A,0x1A,0x0A};
	return std::equal(p1.begin(),p1.end(),buffer.begin(),buffer.begin() + 8);
}

bool _validIHDR(const std::vector<uint8_t>&buffer){


	const uint8_t h[8] = {0x49,0x48,0x44,0x52};
		

	return true;
}

uint32_t to_u32(uint8_t b0,uint8_t b1,uint8_t b2,uint8_t b3) {
	return (uint32_t(b0) << 24) | (uint32_t(b1) << 16) | (uint32_t(b2) << 8) | b3;
}

// Conversion specifically for little endian files (pcapng)
uint32_t to_u32l(uint8_t b0,uint8_t b1,uint8_t b2,uint8_t b3){
	return b0 | (uint32_t(b1) << 8) | (uint32_t(b2) << 16) | (uint32_t(b3) << 24);
}

#endif
