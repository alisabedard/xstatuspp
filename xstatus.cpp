// Copyright 2016, Jeffrey E. Bedard
#include "xstatus.h"
extern "C" {
#include "libjb/log.h"
#include "libjb/xcb.h"
}
#include "battery.h"
#include "clock.h"
#include "config.h"
#include "font.h"
#include "load.h"
#include "status_file.h"
#include "temperature.h"
#include "toolbar.h"
#include "util.h"
#include "window.h"
#include "xdata.h"
using namespace xstatus;
namespace {
	static uint16_t poll_status(xcb_connection_t * xc,
		const char * filename, const uint16_t widget_start)
	{
		uint16_t offset = widget_start + XSTATUS_CONST_PAD;
		offset = load::draw(xc, offset);
		offset = temperature::draw(xc, offset);
		offset = status_file::draw(xc, offset, filename);
		return offset;
	}
	static void setup_invert_gc(xcb_connection_t * xc,
		const xcb_window_t w)
	{
		xcb_gcontext_t gc = get_invert_gc(xc);
		uint32_t v = XCB_GX_INVERT;
		xcb_create_gc(xc, gc, w, XCB_GC_FUNCTION, &v);
	}
}
// returns if update needed
void XStatus::handle_events(xcb_generic_event_t * e)
{
	switch (e->response_type) {
	case XCB_ENTER_NOTIFY:
		toolbar::handle_button_enter(
			((xcb_enter_notify_event_t*)e)->event);
		break;
	case XCB_LEAVE_NOTIFY:
		toolbar::handle_button_leave(
			((xcb_leave_notify_event_t*)e)->event);
		break;
	case XCB_EXPOSE:
		if (!toolbar::handle_expose(((xcb_expose_event_t*)e)
			->window))
			update();
		break;
	case XCB_BUTTON_PRESS:
		toolbar::handle_button_press(
			((xcb_button_press_event_t *)e)->event);
		break;
	default:
		LOG("event: %d", e->response_type);
	}
	free(e);
}
void XStatus::update(void)
{
	Battery::draw(xc, poll_status(xc, opt->filename, widget_start),
		clock::draw(xc));
}
XStatus::XStatus(XStatusOptions * opt)
	: XData(jb_get_xcb_connection(NULL, NULL)), opt(opt)
{
	xstatus_create_window(xc);
	if (!open_font(xc, XSTATUS_FONT)) // default
		if (!open_font(xc, "fixed")) // fallback
			LIBJB_ERROR("Could not load any font");
	xstatus_create_gc(xc, get_gc(xc), win,
		XSTATUS_PANEL_FOREGROUND, XSTATUS_PANEL_BACKGROUND);
	xstatus_create_gc(xc, get_button_gc(xc), win,
		XSTATUS_BUTTON_FG, XSTATUS_BUTTON_BG);
	setup_invert_gc(xc, win);
	widget_start = toolbar::initialize(xc);
}
XStatus::~XStatus(void)
{
	xcb_disconnect(xc);
}
void XStatus::run(void)
{
	for (;;) {
		xcb_generic_event_t * e;
		if (jb_next_event_timed(xc, &e, opt->delay * 1000000) && e)
			handle_events(e);
		else
			update();
	}
}
void XStatus::instance(struct XStatusOptions * opt)
{
	XStatus x(opt);
	x.run();
}
