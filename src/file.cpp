#include "file.hpp"
#include "general_funcs.h"
#include <iostream>
#include <memory>
#include <variant>

std::unique_ptr<File> File::mbyte_validation(std::vector<uint8_t>&& _b) {
	if(_validPNG(_b)) { return std::make_unique<PNG>(); }
	else if(_validPCAPNG(_b)) { return std::make_unique<PNG>(); }

								

	return std::make_unique<PNG>(std::move(_b));
}

void File::do_parsing(std::vector<uint8_t>& _b) {

}

void PNG::parse(const std::vector<uint8_t>& _b) {
	std::size_t j{};

	while(j + 8 < _b.size()) {
		uint32_t len = to_u32(_b[j+1],_b[j+2],_b[j+3],_b[j+4]);

		if(_validIHDR(_b)) {
			std::cout << "Hey!";	
		}

		
		if(j + len + 12 > _b.size()){
			break;
		}
		j = j + len + 12;

	}

}

void PCAPNG::read_block(const std::vector<uint8_t>& _b,std::size_t b_size) {
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

void PCAPNG::parse(const std::vector<uint8_t>& _b) {
	std::size_t j{};
	std::size_t chunk = 188;
	
	while(j + 8 <= _b.size()) {
		
		uint32_t len = to_u32l(_b[j+4],_b[j+5],_b[j+6],_b[j+7]);	
		this->read_block(_b,j);
		j += len;	
		

	}
}
