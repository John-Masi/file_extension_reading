#include "png.cpp" 
#include <cassert>

//TESTS TO IMPLEMENT 
//
// Correct magic byte order for said file extension 



int main() {
	const uint8_t g_png[8];
	const uint8_t b_png;


	assert(_validPNG(g_png));
	assert(!_validPNG(b_png));
	
}


