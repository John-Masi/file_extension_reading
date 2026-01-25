#include <vector>
#include <memory>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <arpa/inet.h>
#include <cassert>

// Read a single 4 byte chunk from single bytes 
uint32_t u8_to_u32(uint8_t b0,uint8_t b1,uint8_t b2, uint8_t b3) {
	return b0 | (uint32_t(b1) << 8) | (uint32_t(b2) << 16) | (uint32_t(b3) << 24);	

}

std::string to_string(const unsigned char str[]) {
	std::string s;
	s.resize(4);

	for(int i = 0; i < s.size(); i++){
		s[i] = str[i];
	}
	return s;
}

struct IHDR_DAT {
	uint32_t width;
	uint32_t height;
	uint8_t bit_depth;
	uint8_t color;
	uint8_t compression;
	uint8_t filter;
	uint8_t interlace;

};

void print_hex(std::vector<uint8_t>& buffer,size_t i){
	unsigned char byte = buffer[i];
	uint8_t high = byte >> 4;
	uint8_t low = byte & 0x0F;

	printf("%X %X",high,low);
}

void read_block(const std::vector<uint8_t>&buffer,size_t block_size){
	uint32_t len = u8_to_u32(buffer[block_size+4],buffer[block_size+5],buffer[block_size+6],buffer[block_size+7]);

	uint32_t type = u8_to_u32(buffer[block_size],buffer[block_size+1],buffer[block_size+2],buffer[block_size+3]);

	

	if(type == 0x00000006){
		size_t offset = block_size + 8;
		size_t body_len = len - 12;

		std::cout << "Offset " << offset << " ";
		std::cout << "Len " << body_len << "\n";


		if(body_len >= 14 + 20 + 20){
			size_t tcp = offset + 14 + 20;
			uint8_t tcp_flags = buffer[tcp + 13];
			bool syn = tcp_flags & 0x02;
			bool ack = tcp_flags & 0x10;
			std::cout <<" SYN: " << syn << " ACK: " << ack << "\n";

		}
	}
	

//	for(size_t i = 0; i < body_len; i++){
//		printf("%02X",buffer[offset + i]);
//		if((i + 1) % 16 == 0) {
//			std::cout << "\n";
//		}
//	}



}

void read_pcapng(std::vector<uint8_t>& buffer) {
	size_t j = 0;
	size_t g = 188; // 2nd Block start 
	while(j  + 8 <= buffer.size()) {
		
		uint32_t len = u8_to_u32(buffer[j+4],buffer[j+5],buffer[j+6],buffer[j+7]);
		
		
				
		j += len;
		if(j < buffer.size()){
			read_block(buffer,j);
		}
	
	}
}

IHDR_DAT convert(std::vector<uint8_t> buffer) {
	
	IHDR_DAT data;
	size_t j = 8;
	while(j + 8 < buffer.size()) { 
		//uint8_t* p_len;
		//p_len[0] = buffer[j];
		//p_len[1] = buffer[j+1];
		//p_len[2] = buffer[j+2];
		//p_len[3] = buffer[j+3];
		uint32_t len = u8_to_u32(buffer[j],buffer[j+1],buffer[j+2],buffer[j+3]);
		auto len_2 = [](uint8_t ptr[]) -> uint32_t {
			 return (uint32_t(ptr[0])<< 24) | uint32_t(ptr[1]) << 16 | uint32_t(ptr[2]) << 8 | ptr[3];
		};
		

		uint8_t width[] = {buffer[j+8],buffer[j+9],buffer[j+10],buffer[j+11]};
		uint8_t height[] = {buffer[j+12],buffer[j+13],buffer[j+14],buffer[j+15]};
		
		// Take the pointer of this byte and cast it to a char* then copy the 4 bytes into the string
		std::string t(reinterpret_cast<char*>(&buffer[j+4]),4);

		if(t == "IHDR"){
			data.width = len_2(width);
			data.height = len_2(height);
			data.bit_depth = buffer[j+16];
			data.color = buffer[j+17];
			data.compression = buffer[j+18];
			data.filter = buffer[j+19];
			data.interlace = buffer[j+20];
			std::cout << "Creating data for you"; 
		}

		if(j + 12 + len > buffer.size()){
			break;
		}

		j = j + 12 + len;
	}

	return data;

}

int main(){
	
	std::string file1 = "img.png";
	std::string file2 = "capture_1.pcapng";

	// Basic c++ file reading 
	std::ifstream file("capture_1.pcapng",std::ios::binary);
	file.seekg(0, std::ios::end);
	std::size_t size = file.tellg();
	file.seekg(0, std::ios::beg);
	
	// To avoid reinterpret cast we can just do std::vector<char> buff instead
	std::vector<uint8_t> buff(size);

	file.read(reinterpret_cast<char*>(buff.data()),size);
	
	std::streamsize read = file.gcount();

	buff.resize(read);

	read_pcapng(buff);
	//htonl(length);
	//printf("%u",length);
} 
