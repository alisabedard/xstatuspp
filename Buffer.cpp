// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Buffer.h"
#undef DEBUG
#include <iostream>
#include "libjb/cpp.h"
#include "util.h"
using namespace xstatus;
int Buffer::instances = 0;
Buffer::Buffer(size_t sz) : max_size(sz), size(sz),
	buffer(new char [sz])
{
	JB_LOG_ADD(Buffer, instances);
}
Buffer::Buffer(const Buffer &obj) // copy
	// make sure it can hold max_size
	: max_size(obj.max_size), size(obj.size),
	buffer(new char[obj.max_size])
{
	JB_LOG_ADD(Buffer, instances);
	std::string(obj).copy(buffer, size);
}
Buffer::~Buffer(void)
{
	JB_LOG_DEL(Buffer, instances);
	delete[] buffer;
}
void Buffer::set_size(const size_t s)
{
	// validate the input first, restrict to max_size
	size = min(s, max_size);
}
