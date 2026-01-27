#include "general_funcs.h"
#include <cassert>

//TESTS TO IMPLEMENT 
//
// Correct magic byte order for said file extension 

int main() {

	uint32_t dfg = to_u32(0x00,0x00,0x00,0x00);
	const std::vector<uint8_t> _e1 = {0x00,0x01,0x02,0x03};
	const std::vector<uint8_t> _e2 = {0x00,0x01,0x02,0x03}; 
	assert(is_equal(4,_e1,_e2));

	//assert(_validPNG(g_png));
	//assert(!_validPNG(b_png));
	
}


