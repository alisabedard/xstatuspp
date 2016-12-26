// Copyright 2016, Jeffrey E. Bedard
#include "temperature.h"
extern "C" {
#include "libjb/JBDim.h"
}
#include <cstdio>
#include "Buffer.h"
#include "config.h"
#include "font.h"
#include "Renderer.h"
#include "util.h"
#include "xdata.h"
using namespace xstatus;
namespace {
	int32_t get_temp_raw(void)
	{
		return xstatus_system_value(XSTATUS_SYSFILE_TEMPERATURE);
	}
	uint8_t get_temp(void)
	{
		// may only fail once:
		static bool get_temp_failed;
		if (get_temp_failed)
			return 0; // 0 indicates unsupported
		// type must hold at least 100000, signed
		int32_t temp = get_temp_raw();
		if (temp == -1) { // could not open system file
			get_temp_failed = true;
			return 0;
		}
		return temp / 1000;
	}
	uint8_t format(char *  buf, const uint8_t sz)
	{
		const uint8_t temp = get_temp();
		if (temp)
			return snprintf(buf, sz, "%dC", temp);
		else
			return 0;
	}
	class TempBuf : public Buffer {
		public:
			TempBuf(void) : Buffer(4) {
				size = format(buffer, size);
			}
	};
	class TempRenderer : public Renderer {
		private:
			JBDim f;
			Buffer * b;
			int x;
		public:
			TempRenderer(xcb_connection_t * xc, Buffer * b, int x)
				: Renderer(xc), f(get_font_size()),
				b(b), x(x) {}
			int draw(void)
			{
				const size_t sz = b->get_size();
				xcb_image_text_8(xc, sz, win, gc, x, f.h,
					b->buffer);
				return x + f.w * sz;
			}
	};
}
// Returns x offset for next item
uint16_t temperature::draw(xcb_connection_t * xc, const uint16_t offset)
{
	TempBuf b;
	TempRenderer r(xc, &b, offset + XSTATUS_CONST_PAD);
	return r.draw();
}
