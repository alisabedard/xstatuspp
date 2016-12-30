// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Buffer.h"
#include "libjb/log.h"
#include "libjb/macros.h"
using namespace xstatus;
int Buffer::instances = 0;
#define DEBUG_BUFFER
#ifdef DEBUG_BUFFER
#define log_init(msg, op) LOG("%s Buffer %d", #msg, op instances);
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
void Buffer::set_size(const size_t s)
{
	// validate the input first, restrict to max_size
	size = JB_MIN(s, max_size);
}
