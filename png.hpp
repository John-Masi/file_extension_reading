#pragma once 

#include <string>
#include <cstdint>
#include <vector>
#include <fstream>
#include <optional>
#include <variant>

struct PNGData{
	uint32_t height; 
	uint32_t width;
	uint16_t color;
};

class PNG {
	private:

		PNGData _data; 

	public:
		PNG() = default;
		PNG(PNGData&& d) : _data(d) {
			_data = std::move(d);
	
		};
		~PNG() = default;
		void setHeight() {}
		void setWidth() {}
		void setColor() {}

		static std::optional<PNG> parse_png(const std::vector<uint8_t>&& buffer);
		const PNGData& data() const { return _data; }
};

