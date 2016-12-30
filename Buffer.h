// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSTATUS_BUFFER_H
#define XSTATUS_BUFFER_H
#include <string>
namespace xstatus {
	class Buffer {
		private:
			static int instances;
		protected:
			size_t size;
			const size_t max_size;
		public:
			char * buffer;
			Buffer(size_t sz);
			Buffer(const Buffer &obj); // copy constructor
			~Buffer(void);
			operator unsigned int() const { return size; }
			operator char *() const { return buffer; }
	};
}
#endif//!XSTATUS_BUFFER_H
