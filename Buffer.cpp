// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Buffer.h"
xstatus::Buffer::Buffer(const Buffer &obj) // copy
{
	buffer = new char [size = obj.size];
	((std::string)obj).copy(buffer, size);
}
