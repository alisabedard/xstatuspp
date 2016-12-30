// Copyright 2016, Jeffrey E. Bedard
#include "status_file.h"
#include <fstream>
#include <iostream>
#include "Buffer.h"
#include "config.h"
#include "font.h"
#include "Renderer.h"
using namespace std;
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
		cerr << "No data in status file " << filename << '\n';
		warned = true;
	}
	ssize_t StatusBuffer::poll_status_file(void)
	{
		ifstream f;
		string s;
		f.open(filename);
		if (f.rdstate())
			return -1; // Could not open file.
		getline(f, s);
		f.close();
		return s.copy(buffer, get_max_size());
	}
	bool StatusBuffer::poll(void)
	{
		const ssize_t s = poll_status_file();
		if (s <= 0) {
			set_size(0);
			warn_no_data();
			return false;
		}
		set_size(s);
		return true;
	}
}
class StatusRenderer : public Renderer {
	private:
		enum { PAD = XSTATUS_CONST_PAD << 1 };
		int x;
		JBDim f;
		int offset(void)
		{
			return f.w * buffer + x + PAD + PAD;
		}
	public:
		int draw(void)
		{
			xcb_image_text_8(xc, buffer, main_window,
				get_gc(), x + PAD, f.h, buffer);
			return offset();
		}
		StatusRenderer(xcb_connection_t * xc, Buffer & b,
			const Font & font, const int x)
			: Renderer(xc, b, font), x(x), f(font) {}
};
// Returns offset for next widget
unsigned short xstatus::status_file::draw(xcb_connection_t * xc,
	const unsigned short x_offset,
	const char * filename, const Font & font)
{
	StatusBuffer b(filename);
	if (!b.poll())
		return x_offset + XSTATUS_CONST_PAD;
	StatusRenderer r(xc, b, font, x_offset);
	return r.draw();
}
