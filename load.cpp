// Copyright 2016, Jeffrey E. Bedard
#include "load.h"
extern "C" {
#include "libjb/JBDim.h"
}
#include <cstdio>
#include "Buffer.h"
#include "config.h"
#include "font.h"
#include "Renderer.h"
using namespace xstatus;
namespace {
	static uint8_t get_load(char *  buf, const uint8_t sz)
	{
		double l;
		getloadavg(&l, 1);
		return snprintf(buf, sz, "%.2f", l);
	}
	class LoadBuffer : public Buffer {
		public:
			LoadBuffer(void)
				: Buffer(6)
			{ set_size(get_load(buffer, get_max_size())); }
	};
	class LoadRenderer : public Renderer {
		private:
			int x;
		public:
			LoadRenderer(xcb_connection_t * xc, Buffer & buffer,
				const Font & font, int x)
				: Renderer(xc, buffer, font), x(x) {}
			int draw(void);
	};
	int LoadRenderer::draw(void)
	{
		const JBDim fs = font;
		xcb_image_text_8(xc, buffer, main_window, get_gc(),
			x, fs.height, buffer);
		return x + fs.width * buffer + XSTATUS_CONST_PAD;
	}
}
// Returns x offset for next item
int load::draw(xcb_connection_t * xc, const Font & f, const int x)
{
	LoadBuffer b;
	return LoadRenderer(xc, b, f, x).draw();
}
