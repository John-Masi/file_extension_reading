#include "file.hpp"
#include "general_funcs.h"
#include <iostream>

void File::do_parsing(std::vector<uint8_t>& _b) {
	if(this->_e == FileExten::png ) {
		this->parse_png(_b);
	}
	else if(this->_e == FileExten::pcapng) {
		this->parse_pcapng(_b);
	}
}

void File::parse_png(const std::vector<uint8_t>& _b) {
	std::size_t j{};

	while(j + 8 < _b.size()) {
		uint32_t len = to_u32(_b[j+1],_b[j+2],_b[j+3],_b[j+4]);

		if(_validIHDR(_b)) {
			this->_d.height = to_u32(_b[j+16],_b[j+17],_b[j+18],_b[j+19]);
		}

		
		if(j + len + 12 > _b.size()){
			break;
		}
		j = j + len + 12;

	}

}

void File::read_block(const std::vector<uint8_t>& _b,std::size_t b_size) {
	uint32_t len = to_u32l(_b[b_size + 4],_b[b_size + 5],_b[b_size + 6],_b[b_size + 7]);
	uint32_t b_type = to_u32l(_b[b_size],_b[b_size + 1],_b[b_size + 2],_b[b_size + 3]);

	if(b_type == 0x00000006) {
		std::size_t offset = b_size + 8;
		std::size_t body_len = len - 12;

		if(body_len >= 14 + 20 + 20) {
			std::size_t tcp = offset + 14 + 20;
			uint8_t tcp_flags = _b[tcp + 13];
			bool syn = tcp_flags & 0x02;
			bool ack = tcp_flags & 0x10;

			bool syn_ack = tcp_flags & 0x12;

			std::cout << "Syn: " << syn << "Ack: " << ack << "Syn-Ack: " << syn_ack;
		}

	}
}
void File::parse_pcapng(const std::vector<uint8_t>& _b) {

	std::size_t j{};
	std::size_t chunk = 188;
	
	while(j + 8 <= _b.size()) {

		uint32_t len = to_u32l(_b[j+4],_b[j+5],_b[j+6],_b[j+7]);	
		j += len;
		if(j < _b.size()){
			this->read_block(_b,j);
		}
	}
}


void File::mbyte_validation(const std::vector<uint8_t>& _b) {
	//if(_validPNG(_b)){ this->_e = FileExten::png; }
	//else { this->_e = FileExten::pcapng; }
	//
	this->_e = FileExten::pcapng;
}
