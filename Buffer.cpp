// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Buffer.h"
xstatus::Buffer::Buffer(const Buffer &obj) // copy
{
	size = obj.size;
	buffer = new char [size];
	((std::string)obj).copy(buffer, size);
}
