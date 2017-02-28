#ifndef __GZIP_UTILS_H__
#define __GZIP_UTILS_H__

#include "mbed.h"
#include "zlib.h"

// external declarations
extern int gzip(unsigned char *dst, unsigned long *dst_length, unsigned char *src, unsigned long src_length);
extern int gunzip(unsigned char *dst, unsigned long *dst_length, unsigned char *src, unsigned long src_length);

#endif // __GZIP_UTILS_H__