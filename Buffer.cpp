// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Buffer.h"
#include <iostream>
using namespace xstatus;
int Buffer::instances = 0;
//#define DEBUG_BUFFER
#ifdef DEBUG_BUFFER
#define log_init(msg, op) std::cerr << #msg << " Buffer "\
	<< op instances << '\n';
#else//!DEBUG_BUFFER
#define log_init(msg, op)
#endif//DEBUG_BUFFER
Buffer::Buffer(size_t sz) : size(sz), max_size(sz), buffer(new char [sz])
{
	log_init(new, ++);
}
Buffer::Buffer(const Buffer &obj) // copy
	// make sure it can hold max_size
	: max_size(obj.max_size), size(obj.size),
	buffer(new char[obj.max_size])
{
	log_init(copy, ++);
	std::string(obj).copy(buffer, size);
}
Buffer::~Buffer(void)
{
	log_init(delete, --);
	delete[] buffer;
}
