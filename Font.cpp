// Copyright 2016, Alisa Bedard
#include "Font.h"
extern "C" {
#include "libjb/xcb.h"
}
#include <cstdlib>
// Returns true if successful.
bool xstatus::Font::open(const char * font_name)
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
