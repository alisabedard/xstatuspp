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
#include "Renderer.h"
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
}
class StatusRenderer : public Renderer {
	private:
		enum { PAD = XSTATUS_CONST_PAD << 1 };
		Buffer b;
		int x;
		JBDim f;
		int offset(void)
		{
			return f.w * b.get_size() + x + PAD + PAD;
		}
	public:
		int draw(void)
		{
			xcb_image_text_8(xc, b.get_size(), win, gc, x + PAD,
				f.h, b.buffer);
			return offset();
		}
		StatusRenderer(xcb_connection_t * xc, Buffer b, int x)
			: Renderer(xc), b(b), x(x), f(get_font_size()) {}
};
// Returns offset for next widget
uint16_t xstatus::status_file::draw(xcb_connection_t * xc,
	const uint16_t x_offset,
	const char * filename)
{
	StatusBuffer b(filename);
	if (!b.poll())
		return x_offset + XSTATUS_CONST_PAD;
	StatusRenderer r(xc, b, x_offset);
	return r.draw();
}
