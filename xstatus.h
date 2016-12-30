#ifndef XSTATUS_XSTATUS_H
#define XSTATUS_XSTATUS_H
#include "Font.h"
#include "Options.h"
#include "Toolbar.h"
#include "XData.h"
namespace xstatus {
	class XStatus : public XData {
		private:
			unsigned short widget_start;
			Options opt;
			void update(void);
			bool handle_events(xcb_generic_event_t * e);
			unsigned short poll(void);
			void setup_invert_gc(void);
			Toolbar * tb;
			Font * font;
		public:
			XStatus(Options opt);
			~XStatus(void);
			void run(void);
	};
	void start(Options * opt);
}
#endif//!XSTATUS_XSTATUS_H
