// Copyright 2017, Jeffrey E. Bedard
#include "battery.h"
#include "libjb/log.h"
#include "libjb/macros.h"
#include "config.h"
#include "util.h"
#include "XData.h"
//#define XSTATUS_BATTERY_TEST
using namespace xstatus;
namespace {
	void set_gc(xcb_connection_t *  xc, const xcb_window_t w,
		gc_t *  gc, const char *  fg, const Font & f)
	{
		create_gc(xc, *gc = xcb_generate_id(xc), w, fg,
			XSTATUS_BATTERY_BACKGROUND_COLOR, f);
	}
	xcb_rectangle_t get_rectangle(const struct JBDim range)
	{
		const int16_t x = range.start, y
			= (XSTATUS_CONST_HEIGHT >> 2) + 1;
		const unsigned short height = XSTATUS_CONST_HEIGHT >> 1;
		const unsigned short width = range.end - range.start
			- XSTATUS_CONST_PAD;
		const xcb_rectangle_t r = {x, y, width, height};
		return r;
	}
	unsigned short get_width_for_percent(const unsigned short width,
		const uint8_t pct)
	{
		return width * pct / 100;
	}
	void draw_rectangles(xcb_connection_t *  xc,
		const gc_t gc, const gc_t bg_gc,
		const struct JBDim range,
		const uint8_t pct)
	{
		xcb_rectangle_t rect = get_rectangle(range);
		const xcb_window_t w = XData(xc).main_window;
		// clear:
		xcb_poly_fill_rectangle(xc, w, bg_gc, 1, &rect);
		rect.width = get_width_for_percent(rect.width, pct);
		// fill rectangle per percent full:
		xcb_poly_fill_rectangle(xc, w, gc, 1, &rect);
	}
	unsigned short get_x(const struct JBDim range)
	{
		return range.start + (range.end - range.start) / 2;
	}
}
// Selects a gc to use based on ac/battery status
uint8_t Battery::get_gc_index(void) const
{
	return system_value(XSTATUS_SYSFILE_AC)
		? BATTERY_GC_AC : percent
		< XSTATUS_CONST_CRITICAL_PERCENT
		? BATTERY_GC_CRITICAL : BATTERY_GC_BATTERY;
}
Battery::Battery(xcb_connection_t * xc, const Font & f, const int16_t start,
	const int16_t end) : XData(xc), font(f),
	range({.start=start,.end=end}) {}
	// Get percent value, maximum 100. Returns -1 on error. Update percent field.
int8_t Battery::get_percent(void)
{
	percent = JB_MIN(system_value(XSTATUS_SYSFILE_BATTERY), 100);
	return percent;
}
void Battery::draw_for_gc(const gc_t gc, const gc_t bg_gc)
{
	draw_rectangles(xc, gc, bg_gc, range, percent);
	enum {BUF_SZ = 7};
	char buf[BUF_SZ];
	const xcb_window_t w = XData(xc).main_window;
	xcb_image_text_8(xc, snprintf(buf, BUF_SZ, " %d%% ", percent), w, gc,
		get_x(range), font.get_size().h, buf);
}
gc_t * Battery::get_gcs(void)
{
	static gc_t gc[BATTERY_GC_SIZE];
	if (!*gc) {
		const xcb_window_t w = main_window;
#define SETGC(color) set_gc(xc, w, gc + BATTERY_GC_##color, \
	XSTATUS_BATTERY_##color##_COLOR, font);
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
	gc_t * gc = get_gcs();
	const uint8_t i = get_gc_index();
	draw_for_gc(gc[i], gc[BATTERY_GC_BACKGROUND]);
	xcb_flush(xc);
}
