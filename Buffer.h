// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSTATUS_BUFFER_H
#define XSTATUS_BUFFER_H
#include <string>
namespace xstatus {
	class Buffer {
		protected:
			size_t size;
		public:
			char * buffer;
			Buffer(size_t sz)
				: size(sz), buffer(new char [sz]) {}
			Buffer(const Buffer &obj); // copy constructor
			~Buffer(void) { delete[] buffer; }
			operator unsigned int() const {return size;}
			operator char *() const { return buffer; }
	};
}
#endif//!XSTATUS_BUFFER_H
