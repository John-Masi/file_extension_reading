#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <fstream>
#include <cstdint>
#include <iostream>
#include <variant>
#include <memory>

enum class FileExten {
	png,
	pcapng,
	nill,
};

struct IHDR {
	uint32_t height;
	uint32_t width;
	uint16_t color;
};

struct TCP_Packet {
	bool syn{};
	bool ack{};
	bool syn_ack{};
};

class File{
	private:
		enum FileExten _e;
	public:
		std::vector<uint8_t> b;
		File() {};
		File(std::vector<uint8_t>&& _b) {
			b = std::move(_b);
		};
		~File() = default;
		static std::unique_ptr<File> mbyte_validation(std::vector<uint8_t>&& _b);	
		virtual void parse(const std::vector<uint8_t>& _b) = 0;
		// Refactor into using a <span>
		
		void do_parsing(std::vector<uint8_t>& _buff);
	
};

class PNG : public File {
	public:
		std::vector<uint8_t> b;
		PNG() {};
		PNG(std::vector<uint8_t>&& _b) {
			b = std::move(_b);
		};
		~PNG() = default;
		virtual void parse(const std::vector<uint8_t>& _b) override;
};
class PCAPNG : public File {
	public:
		std::vector<uint8_t> b;
		PCAPNG() {};
		PCAPNG(std::vector<uint8_t>&& _b) {
			b = std::move(_b);
		};
		~PCAPNG() = default;
		virtual void parse(const std::vector<uint8_t>& _b) override;
		void read_block(const std::vector<uint8_t>& _buff,std::size_t b_size);
};

class UNKNOWN : public File {
	public:
		std::vector<uint8_t> b;
		UNKNOWN() {};
		UNKNOWN(std::vector<uint8_t>&& _b) {
			b = std::move(_b);
		};
		~UNKNOWN() = default;
		virtual void parse(const std::vector<uint8_t>& _b) override; 

};



#endif 
