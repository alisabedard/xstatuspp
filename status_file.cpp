// Copyright 2016, Jeffrey E. Bedard
#include "status_file.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/file.h"
#include "libjb/util.h"
}
#include <cstdio>
#include <sys/stat.h> // include per man page of fchmod()
#include <unistd.h> // include per man page of read()
#include "Buffer.h"
#include "config.h"
#include "font.h"
#include "xdata.h"
using namespace xstatus;
namespace {
	class StatusBuffer : public Buffer {
		private:
			const char * filename;
			void warn_no_data(void);
			ssize_t poll_status_file(void);
		public:
			bool poll(void);
			StatusBuffer(const char * filename)
				: Buffer(XSTATUS_CONST_BUFFER_SIZE),
				filename(filename)
		{}
	};
	void StatusBuffer::warn_no_data(void)
	{
		static bool warned;
		if (warned)
			return;
		fprintf(stderr, "No data in status file: %s\n", filename);
		warned = true;
	}
	ssize_t StatusBuffer::poll_status_file(void)
	{
		fd_t fd = jb_open(filename, O_RDONLY | O_CREAT);
		if (fd < 0)
			return -1;
		fchmod(fd, 0600);
		// Subtract 1 to avoid display of null terminator.
		ssize_t r = read(fd, buffer, XSTATUS_CONST_BUFFER_SIZE) - 1;
		jb_check(r != -1, "Could not read status file");
		close(fd);
		return r;
	}
	bool StatusBuffer::poll(void)
	{
		const ssize_t s = poll_status_file();
		if (s <= 0) {
			size = 0;
			warn_no_data();
			return false;
		}
		size = s;
		return true;
	}
	void draw_text(xcb_connection_t * xc, Buffer * b, const int x)
	{
		xcb_image_text_8(xc, b->get_size(), get_window(xc),
			get_gc(xc), x + (XSTATUS_CONST_PAD << 1),
			get_font_size().h, b->buffer);
	}
	uint16_t get_offset(const int x, const size_t len)
	{
		return get_font_size().w * len + x
			+ (XSTATUS_CONST_PAD << 2);
	}
}
// Returns offset for next widget
uint16_t draw_status_file(xcb_connection_t * xc,
	const uint16_t x_offset,
	const char * filename)
{
	StatusBuffer b(filename);
	if (!b.poll())
		return x_offset + XSTATUS_CONST_PAD;
	draw_text(xc, &b, x_offset);
	return get_offset(x_offset, b.get_size());
}
