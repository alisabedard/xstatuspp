// Copyright 2016, Jeffrey E. Bedard
#include "font.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/log.h"
#include "libjb/xcb.h"
}
#include <cstdlib>
#include <cstring>
namespace xstatus {
	static struct JBDim font_size;
	xcb_font_t get_font(xcb_connection_t * xc)
	{
		static xcb_font_t f;
		return f ? f : (f = xcb_generate_id(xc));
	}
	struct JBDim get_font_size(void)
	{
		return font_size;
	}
	static void charinfo_to_size(xcb_charinfo_t * ci)
	{
		font_size.width = ci->character_width;
		font_size.height = ci->ascent + ci->descent;
	}
	static void finish_query(xcb_connection_t * xc,
		const xcb_query_font_cookie_t fc)
	{
		xcb_query_font_reply_t * r = xcb_query_font_reply(xc, fc, NULL);
		charinfo_to_size(&r->max_bounds);
		free(r);
	}
	// returns true if successful
	bool open_font(xcb_connection_t * xc,
		const char * fn)
	{
		xcb_font_t f = get_font(xc);
		if(!jb_open_font(xc, f, fn))
			return false;
		finish_query(xc, xcb_query_font(xc, f));
		return true;
	}
}
