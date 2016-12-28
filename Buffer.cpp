// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#include "Buffer.h"
#include <string>
xstatus::Buffer::Buffer(const Buffer &obj) // copy
{
	std::string s(obj.buffer);
	size = s.size();
	buffer = new char [size];
	s.copy(buffer, size);
}
