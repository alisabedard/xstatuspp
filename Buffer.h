// Copyright 2017, Jeffrey E. Bedard <jefbed@gmail.com>
#ifndef XSTATUS_BUFFER_H
#define XSTATUS_BUFFER_H
#include <string>
namespace xstatus {
	class Buffer {
		private:
			static int instances;
			const size_t max_size;
			size_t size;
		public:
			char * buffer;
			Buffer(size_t sz);
			Buffer(const Buffer &obj); // copy constructor
			~Buffer(void);
			size_t get_max_size(void) const { return max_size; }
			void set_size(const size_t s);
			operator unsigned int() const { return size; }
			operator char *() const { return buffer; }
	};
}
#endif//!XSTATUS_BUFFER_H
