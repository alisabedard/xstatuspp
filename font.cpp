// Copyright 2016, Jeffrey E. Bedard
#include "font.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/log.h"
#include "libjb/xcb.h"
}
#include <cstdlib>
#include <cstring>
namespace {
#if 0
	static struct JBDim font_size;
	void charinfo_to_size(xcb_charinfo_t * ci)
	{
		font_size.width = ci->character_width;
		font_size.height = ci->ascent + ci->descent;
	}
	void finish_query(xcb_connection_t * xc,
		const xcb_query_font_cookie_t fc)
	{
		xcb_query_font_reply_t * r = xcb_query_font_reply(xc, fc, NULL);
		charinfo_to_size(&r->max_bounds);
		free(r);
	}
#endif
}
namespace xstatus {
#if 0
	xcb_font_t get_font(xcb_connection_t * xc)
	{
		static xcb_font_t f;
		return f ? f : (f = xcb_generate_id(xc));
	}
	struct JBDim get_font_size(void)
	{
		return font_size;
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
#endif
	// Returns true if successful.
	bool Font::open(const char * font_name)
	{
		if (!jb_open_font(xc, fid, font_name))
			if (!jb_open_font(xc, fid, "fixed"))
				return false;
		xcb_query_font_cookie_t c = xcb_query_font(xc, fid);
		xcb_query_font_reply_t * r = xcb_query_font_reply(xc, c,
			NULL);
		if (!r)
			return false;
		xcb_charinfo_t & i = r->max_bounds;
		sz.width = i.character_width;
		sz.height = i.ascent + i.descent;
		free(r);
		return true;
	}
}
