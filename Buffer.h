// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSTATUS_BUFFER_H
#define XSTATUS_BUFFER_H
#include <stddef.h>
namespace xstatus {
	class Buffer {
		protected:
			size_t size;
		public:
			char * buffer;
			Buffer(size_t sz) : size(sz), buffer(new char [sz]) {}
			Buffer(const Buffer &obj); // copy constructor
			~Buffer(void) { delete buffer; }
			size_t get_size(void) {return size;}
	};
}
#endif//!XSTATUS_BUFFER_H
