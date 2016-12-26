// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Buffer.h"
#include <string>
xstatus::Buffer::Buffer(const Buffer &obj) // copy
{
	size = obj.size;
	buffer = new char [size];
	std::string(obj.buffer).copy(buffer, size);
}
