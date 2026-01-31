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
		
		void do_parsing(std::vector<uint8_t>& _b);
		void parse_png(std::vector<uint8_t>& _b);
		void parse_pcapng(std::vector<uint8_t>& _b);
		void mbyte_validation(const std::vector<uint8_t>& _b);

		const Data& data() const { return _d; }

		File& operator=(const File& f) = delete;
};

#endif 
