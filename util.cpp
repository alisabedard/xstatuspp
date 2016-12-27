// Copyright 2016, Jeffrey E. Bedard
#include "util.h"
extern "C" {
#include "libjb/xcb.h"
}
#include <fstream>
#include <iostream>
#include "font.h"
void xstatus_create_gc(xcb_connection_t * xc, const xcb_gcontext_t gc,
	const xcb_window_t win, const char * fg,
	const char * bg)
{
	jb_create_gc(xc, gc, win, fg, bg);
	uint32_t v = xstatus::get_font(xc);
	xcb_change_gc(xc, gc, XCB_GC_FONT, &v);
}
// returns -1 on error
int xstatus_system_value(const char *filename)
{
	std::ifstream f;
	f.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string s;
	try {
		f.open(filename);
		std::getline(f, s);
	}
	catch (std::ifstream::failure e) {
		std::cerr << "Cannot get value from " << filename << '\n';
		return -1;
	}
	return std::stoi(s);
}
