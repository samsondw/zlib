#ifndef __GZIP_UTILS_H__
#define __GZIP_UTILS_H__

#include "mbed.h"
#include "zlib.h"

// external declarations
extern "C" int gzip(unsigned char *dst, unsigned long *dst_length, unsigned char *src, unsigned long src_length);
extern "C" int gunzip(unsigned char *dst, unsigned long *dst_length, unsigned char *src, unsigned long src_length);

#endif // __GZIP_UTILS_H__