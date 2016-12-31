// Copyright 2016, Jeffrey E. Bedard
#include "XStatus.h"
#include "battery.h"
#include "config.h"
#include "clock.h"
#include "libjb/cpp.h"
#include "libjb/log.h"
#include "libjb/xcb.h"
#include "libjb/util.h"
#include "load.h"
#include "status_file.h"
#include "temperature.h"
#include "util.h"
using namespace xstatus;
using namespace std;
int8_t XStatus::instances = 0;
unsigned short XStatus::poll(void)
{
	unsigned short offset = widget_start + XSTATUS_CONST_PAD;
	Font f = *font;
	offset = Load(xc, f, offset);
	offset = temperature::draw(xc, offset, f);
	offset = status_file::draw(xc, offset, opt.filename, f);
	return offset;
}
void XStatus::update(void)
{
	const Font f = *font;
	battery::draw(xc, f, poll(), clock::draw(xc, f));
}

// returns if update needed
bool XStatus::handle_events(xcb_generic_event_t * e)
{
	bool keep_going = true;
	switch (e->response_type) {
	case XCB_ENTER_NOTIFY:
	case XCB_LEAVE_NOTIFY:
		tb->focus(((xcb_enter_notify_event_t*)e)->event);
		break;
	case XCB_EXPOSE:
		if (!tb->expose(((xcb_expose_event_t*)e)->window))
			update();
		break;
	case XCB_BUTTON_PRESS:
		tb->button(((xcb_button_press_event_t *)e)->event,
			keep_going);
		break;
	default:
		LOG("event: %d", e->response_type);
	}
	free(e);
	return keep_going;
}
XStatus::XStatus(Options opt)
	: XData(jb_get_xcb_connection(NULL, NULL)), opt(opt)
{
	JB_LOG_ADD(XStatus, instances);
	xcb_window_t w = Window::create_main_window(this);
	font = new Font(xc);
	jb_require(font->open(XSTATUS_FONT), "Could not load a font");
	const Font f = *font;
	create_gc(xc, get_gc(), w, XSTATUS_PANEL_FOREGROUND,
		XSTATUS_PANEL_BACKGROUND, f);
	const uint32_t v = XCB_GX_INVERT;
	xcb_create_gc(xc, get_invert_gc(), main_window, XCB_GC_FUNCTION, &v);
	tb = new Toolbar(xc, font);
	widget_start = tb->get_offset();
}
XStatus::~XStatus(void)
{
	JB_LOG_DEL(XStatus, instances);
	delete tb;
	delete font;
	xcb_destroy_window(xc, main_window);
	xcb_disconnect(xc);
}
void XStatus::run(void)
{
	JB_LOG_OP(XStatus, "run()");
	bool keep_going =  true;
	while (keep_going) {
		xcb_generic_event_t * e;
		if (jb_next_event_timed(xc, &e, opt.get_delay()
			* 1000000) && e)
			keep_going = handle_events(e);
		else
			update();
	}
}
