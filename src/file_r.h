#include <vector> 
#include <cstdint> 
#include <cstdio>

#ifndef FILE_R_H
#define FILE_R_H

inline std::vector<uint8_t> f_read(const char* _fname){
	FILE* f = fopen(_fname,"rb");
	fseek(f,0,SEEK_END);
	size_t size = ftell(f);
	fseek(f,0,SEEK_SET);

	std::vector<uint8_t> buff(size);
	fread(buff.data(),1,size,f);
	const size_t chunk_size = 64 * 1024;
	uint8_t _t[chunk_size];

	size_t n;
	while((n = fread(_t,1,chunk_size,f) > 0)) {
		buff.insert(buff.end(),_t,_t+n);
		
	}
	return buff;

}

#endif 
