#ifndef XSTATUS_XSTATUS_H
#define XSTATUS_XSTATUS_H
#include <list>
#include "Buffer.h"
#include "Font.h"
#include "load.h"
#include "Options.h"
#include "Toolbar.h"
#include "Widget.h"
#include "XData.h"
namespace xstatus {
	class XStatus : public XData {
		private:
			static int8_t instances;
			unsigned short widget_start;
			Options opt;
			void update(void);
			bool handle_events(xcb_generic_event_t * e);
			unsigned short poll(void);
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
