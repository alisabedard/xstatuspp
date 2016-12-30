// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Buffer.h"
#include <iostream>
#include "libjb/macros.h"
#undef DEBUG
using namespace xstatus;
int Buffer::instances = 0;
Buffer::Buffer(size_t sz) : size(sz), max_size(sz),
	buffer(new char [sz])
{
}
Buffer::Buffer(const Buffer &obj) // copy
	// make sure it can hold max_size
	: max_size(obj.max_size), size(obj.size),
	buffer(new char[obj.max_size])
{
	std::string(obj).copy(buffer, size);
}
Buffer::~Buffer(void)
{
	delete[] buffer;
}
void Buffer::set_size(const size_t s)
{
	// validate the input first, restrict to max_size
	size = JB_MIN(s, max_size);
}
