#include "mbed.h"
#include "zlib.h"

/** GUNZIP a from src buffer to dst buffer
 @param dst : destination buffer
 @param dst_length : pointer to destination buffer length
 @param src : source buffer
 @param src_length : source buffer length
 @return Z_OK on success, zlib error (<0) on failure
 */
int gzip(unsigned char *dst, unsigned long *dst_length, unsigned char *src, unsigned long src_length)
{
    z_stream        stream;
    memset(&stream, 0, sizeof(stream));

    stream.next_in = src;
    stream.avail_in = src_length;

    stream.next_out = Z_NULL;
    stream.avail_out = 0;

    /* add 16 to MAX_WBITS to specify gzip format - it gets taken off again in defaultInit2 */
    int rv = deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 16 + MAX_WBITS, MAX_MEM_LEVEL, Z_DEFAULT_STRATEGY);
    if (Z_OK == rv) {
        unsigned long dst_bound = deflateBound(&stream, stream.avail_in) + 12; /* 12 bytes for the gzip header */
        if (dst_bound > *dst_length) {
            rv = Z_MEM_ERROR;
        } else {
            stream.next_out   = dst;
            stream.avail_out = dst_bound;
        }
    }

    if (Z_OK == rv) {
        gz_header        header;
        memset(&header, 0, sizeof(header));
        rv = deflateSetHeader(&stream, &header);
    }

    if (Z_OK == rv) {
        rv = deflate(&stream, Z_FINISH);
        if (Z_STREAM_END == rv) {
            rv = deflateEnd(&stream);
        }
    }

    if (Z_OK == rv) {
        *dst_length = stream.total_out;
    } else {
        *dst_length = 0;
    }

    return rv;
}