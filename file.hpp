#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <fstream>
#include <cstdint>
#include <iostream>

enum FileExten {
	png,
	pcapng,
	nill,
};

struct Data{
	uint32_t height;
	uint32_t width;
	uint16_t color;
	// TODO Turn into bitmap or vector<bool> to hold all flags
	bool syn{};
	bool ack{};
	bool syn_ack{};
};

class File{
	private:
		File() {}
		~File() {}

		Data _d;
		enum FileExten _e;
	public:
		File(const File& file) = delete;
		static File& getFile() {
			static File file;
			return file;
		}
		
		void read_block(const std::vector<uint8_t>& _buff,std::size_t block_size);
		void do_parsing(std::vector<uint8_t>& _buff);
		void parse_png(const std::vector<uint8_t>& _buff);
		void parse_pcapng(const std::vector<uint8_t>& _buff);
		void mbyte_validation(const std::vector<uint8_t>& _buff);

		const Data& data() const { return _d; }

		File& operator=(const File& f) = delete;
};

#endif 
