// Copyright 2017, Jeffrey E. Bedard
#ifndef XSTATUS_BATTERY_H
#define XSTATUS_BATTERY_H
#include <xcb/xcb.h>
#include "Font.h"
#include "Widget.h"
namespace xstatus {
	class Battery : public XData {
		private:
			const Font & font;
			JBDim range;
			int8_t percent;
			void draw_for_gc(const gc_t gc, const gc_t bg_gc);
			// Selects a gc to use based on ac/battery status
			uint8_t get_gc_index(void) const;
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
			int8_t get_percent(void);
	};
}
#endif//!XSTATUS_BATTERY_H
