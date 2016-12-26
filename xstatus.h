#ifndef XSTATUS_XSTATUS_H
#define XSTATUS_XSTATUS_H
#include "xdata.h"
namespace xstatus {
	class XStatusOptions {
		public:
			XStatusOptions(char * filename);
			XStatusOptions(const XStatusOptions& obj);
			~XStatusOptions(void);
			void set_filename(char * filename);
			char * filename;
			uint8_t delay = 1;
	};
	class XStatus : public XData{
		private:
			unsigned int widget_start;
			XStatusOptions opt;
			void update(void);
			void handle_events(xcb_generic_event_t * e);
			uint16_t poll(void);
			void setup_invert_gc(void);
		public:
			XStatus(XStatusOptions opt);
			~XStatus(void);
			void run(void);
	};
	void start(XStatusOptions * opt);
}
#endif//!XSTATUS_XSTATUS_H
