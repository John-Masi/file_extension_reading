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

	uint32_t epb = 0x00000006;
	// EPB packet from pcapng  
	if(b_type == epb) {
	
		// EPB start 
		std::size_t offset = b_size + 28;
		std::size_t body_len = len - 12;
			
		if(body_len < 14) return;	
		std::size_t ip = offset + 14;

		if(body_len < 14 + 20) return;
		uint8_t ihl = _b[ip] & 0x0F;
		std::size_t ip_len = ihl * 4;

		if(body_len < 14 + ip_len) return;

		if(_b[ip+9] != 6) return;
		std::size_t tcp = ip + ip_len;

		if(body_len < (tcp - offset) + 20) return;
		uint8_t tcp_flags = _b[tcp + 13];
		

		// TCP Flags
		bool syn = tcp_flags & 0x02;
		bool ack = tcp_flags & 0x10;
		bool syn_ack = tcp_flags & 0x12;

	}
}
void File::parse_pcapng(const std::vector<uint8_t>& _b) {

	std::size_t j{};
	std::size_t chunk = 188;
	
	while(j + 8 <= _b.size()) {
		
		uint32_t len = to_u32l(_b[j+4],_b[j+5],_b[j+6],_b[j+7]);	
		this->read_block(_b,j);
		j += len;	
		

	}
}


void File::mbyte_validation(const std::vector<uint8_t>& _b) {
	if(_validPNG(_b)){ this->_e = FileExten::png; }
	else if(_validPCAPNG){ this->_e = FileExten::pcapng; }
	std::cout << this->_e << "\n";
}
