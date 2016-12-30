// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Buffer.h"
#include <iostream>
using namespace xstatus;
int Buffer::instances = 0;
Buffer::Buffer(size_t sz) : size(sz), max_size(sz), buffer(new char [sz])
{
	std::cerr << "new Buffer " << ++instances  << '\n';
}
Buffer::Buffer(const Buffer &obj) // copy
	// make sure it can hold max_size
	: max_size(obj.max_size), size(obj.size),
	buffer(new char[obj.max_size])
{
	std::cerr << "copy Buffer " << ++instances << '\n';
	std::string(obj).copy(buffer, size);
}
Buffer::~Buffer(void)
{
	std::cerr << "delete Buffer " << --instances << '\n';
	delete[] buffer;
}
