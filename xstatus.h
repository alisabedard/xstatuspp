#ifndef XSTATUS_XSTATUS_H
#define XSTATUS_XSTATUS_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#ifdef __cplusplus
}
#endif
struct XStatusOptions {
	char * filename;
	uint8_t delay;
};
#ifdef __cplusplus
namespace xstatus {
	void start(struct XStatusOptions * opt);
}
#endif//__cplusplus
#endif//!XSTATUS_XSTATUS_H
