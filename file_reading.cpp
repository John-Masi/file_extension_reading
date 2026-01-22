#include <vector>
#include <memory>
#include <iostream>
#include <cstdint>
#include <fstream>
#include <string> 

// Read a single 4 byte chunk from single bytes 
uint32_t u8_to_u32(uint8_t b0,uint8_t b1,uint8_t b2, uint8_t b3) {
	return (uint32_t(b0) << 24) | (uint32_t(b1) << 16) | (uint32_t(b2) << 8) | b3;	

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

void read_pcapng(std::vector<uint8_t> buffer) {
	size_t j = 0;
	while(j + 8 < buffer.size()) {
		uint32_t len = u8_to_u32(buffer[j+4],buffer[j+5],buffer[6],buffer[7]);
		uint32_t type = u8_to_u32(buffer[j],buffer[j+1],buffer[j+2],buffer[j+3]);

		printf("len=%u\n",len);
		printf("type=%u",type);
		if(j + len > buffer.size()){
			break;
		}
		j = j + len;
	
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
	std::ifstream file(file2,std::ios::binary);
	file.seekg(0, std::ios::end);
	std::size_t size = file.tellg();
	file.seekg(0, std::ios::beg);
	
	// To avoid reinterpret cast we can just do std::vector<char> buff instead
	std::vector<uint8_t> buff(size);

	// reinterpret_cast will let us read the file as vector of chars instead 
	// Because std::ifstream wants a char* we use reinterpret cast 
	file.read(reinterpret_cast<char*>(buff.data()),size);

	//IHDR_DAT d = convert(buff);
	read_pcapng(buff);
} 
