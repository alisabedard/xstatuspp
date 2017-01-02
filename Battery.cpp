// Copyright 2017, Jeffrey E. Bedard
#include "Battery.h"
#include <algorithm>
#include "config.h"
#include "libjb/log.h"
#include "util.h"
//#define XSTATUS_BATTERY_TEST
using namespace xstatus;
namespace {
	xcb_rectangle_t get_rectangle(const struct JBDim range)
	{
		const short x = range.start, y
			= (XSTATUS_CONST_HEIGHT >> 2) + 1;
		const unsigned short height = XSTATUS_CONST_HEIGHT >> 1;
		const unsigned short width = range.end - range.start
			- XSTATUS_CONST_PAD;
		const xcb_rectangle_t r = {x, y, width, height};
		return r;
	}
}
// Selects a gc to use based on ac/battery status
Battery::gc_index_t Battery::get_gc_index(void) const
{
	return system_value(XSTATUS_SYSFILE_AC)
		? BATTERY_GC_AC : percent
		< XSTATUS_CONST_CRITICAL_PERCENT
		? BATTERY_GC_CRITICAL : BATTERY_GC_BATTERY;
}
Battery::Battery(xcb_connection_t * xc, const Font & f, const short start,
	const short end) : XData(xc), font(f),
	range({.start=start,.end=end}) {}
	// Get percent value, maximum 100. Returns -1 on error. Update percent
	// field.
Battery::percent_t Battery::get_percent(void)
{
	percent = std::min(system_value(XSTATUS_SYSFILE_BATTERY), 100);
	return percent;
}
void Battery::set_gc(gc_t * i, const char * color)
{
	create_gc(xc, *i = xcb_generate_id(xc), main_window, color,
		XSTATUS_BATTERY_BACKGROUND_COLOR, font);
}
gc_t * Battery::get_gcs(void)
{
	static gc_t gc[BATTERY_GC_SIZE];
	if (!*gc) {
#define SETGC(color) set_gc(gc + BATTERY_GC_##color,\
	XSTATUS_BATTERY_##color##_COLOR)
		SETGC(BACKGROUND); SETGC(AC); SETGC(BATTERY); SETGC(CRITICAL);
#undef SETGC
	}
	return gc;
}
void Battery::draw(void)
{
	const int8_t pct = get_percent();
	if (pct < 0) { // error getting percent
		// likely no battery or non-linux
		LOG("Could not get percent, returning");
		return;
	}
	gc_t * gc_array = get_gcs();
	const gc_t fg_gc = gc_array[get_gc_index()], bg_gc
		= gc_array[BATTERY_GC_BACKGROUND];
	xcb_rectangle_t rect = get_rectangle(range);
	const xcb_window_t w = main_window;
	// clear:
	xcb_poly_fill_rectangle(xc, w, bg_gc, 1, &rect);
	rect.width = rect.width * percent / 100;
	// fill rectangle per percent full:
	xcb_poly_fill_rectangle(xc, w, fg_gc, 1, &rect);
	enum {BUF_SZ = 7};
	char buf[BUF_SZ];
	const int x = range.start + ((range.end - range.start) >> 1);
	xcb_image_text_8(xc, snprintf(buf, BUF_SZ, " %d%% ", percent), w,
		fg_gc, x, font.get_size().h, buf);
	xcb_flush(xc);
}
