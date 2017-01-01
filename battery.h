// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_BATTERY_H
#define XSTATUS_BATTERY_H
#include <xcb/xcb.h>
#include "Font.h"
#include "Widget.h"
namespace xstatus {
	class Battery : public XData {
		public:
			typedef int8_t percent_t;
			typedef uint8_t gc_index_t;
		private:
			const Font & font;
			JBDim range;
			percent_t percent;
			// Selects a gc to use based on ac/battery status
			gc_index_t get_gc_index(void) const;
			void set_gc(gc_t * i, const char * color);
		protected:
			// index into gc array, keeps gc array private
			enum BATGCs {
				BATTERY_GC_BACKGROUND, BATTERY_GC_AC,
				BATTERY_GC_BATTERY, BATTERY_GC_CRITICAL,
				BATTERY_GC_SIZE };
			gc_t * get_gcs(void);
		public:
			Battery(xcb_connection_t * xc, const Font & f,
				const int16_t start, const int16_t end);
			void draw(void);
			percent_t get_percent(void);
	};
}
#endif//!XSTATUS_BATTERY_H
