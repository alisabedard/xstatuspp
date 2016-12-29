#ifndef XSTATUS_XSTATUS_H
#define XSTATUS_XSTATUS_H
#include "font.h"
#include "Options.h"
#include "toolbar.h"
#include "xdata.h"
namespace xstatus {
	class XStatus : public XData {
		private:
			uint16_t widget_start;
			XStatusOptions opt;
			void update(void);
			bool handle_events(xcb_generic_event_t * e);
			uint16_t poll(void);
			void setup_invert_gc(void);
			Toolbar * tb;
			Font * font;
		public:
			XStatus(XStatusOptions opt);
			~XStatus(void);
			void run(void);
	};
	void start(XStatusOptions * opt);
}
#endif//!XSTATUS_XSTATUS_H
