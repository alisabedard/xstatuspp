#ifndef XSTATUS_XSTATUS_H
#define XSTATUS_XSTATUS_H
#include "xdata.h"
namespace xstatus {
	struct XStatusOptions {
		char * filename;
		uint8_t delay;
	};
	class XStatus : public XData{
		private:
			unsigned int widget_start;
			XStatusOptions * opt;
		public:
			XStatus(XStatusOptions * opt);
			~XStatus(void);
			void run(void);
			static void instance(XStatusOptions * opt);
	};
	void start(XStatusOptions * opt);
}
#endif//!XSTATUS_XSTATUS_H
