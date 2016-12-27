// Copyright 2017, Jeffrey E. Bedard
#include "battery.h"
extern "C" {
#include "libjb/JBDim.h"
#include "libjb/log.h"
#include "libjb/macros.h"
#include "libjb/util.h"
}
#include "config.h"
#include "font.h"
#include "util.h"
#include "xdata.h"
#include "xstatus.h"
//#define XSTATUS_DEBUG_BATTERY
#ifndef XSTATUS_DEBUG_BATTERY
#undef LOG
#define LOG(...)
#endif//!XSTATUS_DEBUG_BATTERY
//#define XSTATUS_BATTERY_TEST
namespace xstatus {
	// get percent value, maximum 100, -1 on error
	static int8_t get_percent(void)
	{
		return JB_MIN(xstatus::system_value(XSTATUS_SYSFILE_BATTERY),
			100);
	}
	// index into gc array, keeps gc array private
	enum BATGCs { BATTERY_GC_BACKGROUND, BATTERY_GC_AC, BATTERY_GC_BATTERY,
		BATTERY_GC_CRITICAL, BATTERY_GC_SIZE };
	// Selects a gc to use based on ac/battery status
	static uint8_t get_gc(const uint8_t pct)
	{
		return xstatus::system_value(XSTATUS_SYSFILE_AC)
			? BATTERY_GC_AC : pct
			< XSTATUS_CONST_CRITICAL_PERCENT
			? BATTERY_GC_CRITICAL : BATTERY_GC_BATTERY;
	}
	static uint8_t format(char * buf, const uint8_t sz, const uint8_t pct)
	{
		return snprintf(buf, sz, " %d%% ", pct);
	}
	static void draw_percent(xcb_connection_t *  xc, const xcb_gcontext_t gc,
		const uint8_t pct, const int16_t x, const Font & f)
	{
		enum {BUF_SZ = 7};
		char buf[BUF_SZ];
		xcb_image_text_8(xc, format(buf, BUF_SZ, pct),
			xstatus::get_window(xc), gc, x,
			f.get_size().h, buf);
	}
	static void set_gc(xcb_connection_t *  xc, const xcb_window_t w,
		xcb_gcontext_t *  gc, const char *  fg, const Font & f)
	{
		xstatus::create_gc(xc, *gc = xcb_generate_id(xc), w, fg,
			XSTATUS_BATTERY_BACKGROUND_COLOR, f);
	}
	static void initialize_gcs(xcb_connection_t *  xc,
		const xcb_window_t w, xcb_gcontext_t *  gc, const Font & f)
	{
#define SETGC(color) set_gc(xc, w, gc + BATTERY_GC_##color, \
	XSTATUS_BATTERY_##color##_COLOR, f);
		SETGC(BACKGROUND); SETGC(AC); SETGC(BATTERY); SETGC(CRITICAL);
#undef SETGC
	}
	static xcb_rectangle_t get_rectangle(const struct JBDim range)
	{
		const int16_t x = range.start, y = (XSTATUS_CONST_HEIGHT >> 2) + 1;
		const uint16_t height = XSTATUS_CONST_HEIGHT >> 1;
		const uint16_t width = range.end - range.start - XSTATUS_CONST_PAD;
		const xcb_rectangle_t r = {x, y, width, height};
		return r;
	}
	__attribute__((const))
		static uint16_t get_width_for_percent(const uint16_t width, const uint8_t pct)
		{
			return width * pct / 100;
		}
	static void draw_rectangles(xcb_connection_t *  xc,
		const xcb_gcontext_t gc, const xcb_gcontext_t bg_gc, const struct JBDim range,
		const uint8_t pct)
	{
		xcb_rectangle_t rect = get_rectangle(range);
		const xcb_window_t w = xstatus::get_window(xc);
		// clear:
		xcb_poly_fill_rectangle(xc, w, bg_gc, 1, &rect);
		rect.width = get_width_for_percent(rect.width, pct);
		// fill rectangle per percent full:
		xcb_poly_fill_rectangle(xc, w, gc, 1, &rect);
	}
	__attribute__((const))
		static uint16_t get_x(const struct JBDim range)
		{
			return range.start + (range.end - range.start) / 2;
		}
	static void draw_for_gc(xcb_connection_t * xc, const xcb_gcontext_t gc,
		const xcb_gcontext_t bg_gc, const struct JBDim range,
		const uint8_t pct, const Font & f)
	{
		draw_rectangles(xc, gc, bg_gc, range, pct);
		draw_percent(xc, gc, pct, get_x(range), f);
	}
	static xcb_gcontext_t * get_gcs(xcb_connection_t *  xc, const Font & f)
	{
		static xcb_gcontext_t gc[BATTERY_GC_SIZE];
		if (!*gc)
			initialize_gcs(xc, xstatus::get_window(xc), gc, f);
		return gc;
	}
	static void draw_for_percent(xcb_connection_t *  xc,
		const Font & f, const struct JBDim range, const uint8_t pct)
	{
		xcb_gcontext_t * gc = get_gcs(xc, f);
		const uint8_t i = get_gc(pct);
		draw_for_gc(xc, gc[i],
			gc[BATTERY_GC_BACKGROUND],
			range, pct, f);
	}
	void battery::draw(xcb_connection_t * xc, const Font & f,
		const uint16_t start, const uint16_t end)
	{
		const int8_t pct = get_percent();
		if (pct < 0) { // error getting percent
			// likely no battery or non-linux
			LOG("Could not get percent, returning");
			return;
		}
		struct JBDim range = {{start}, {end}};
		draw_for_percent(xc, f, range, pct);
		xcb_flush(xc);
	}
}
