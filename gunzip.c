#include "mbed.h"
#include "zlib.h"

/** GUNZIP a from src buffer to dst buffer
 @param dst : destination buffer
 @param dst_length : pointer to destination buffer length
 @param src : source buffer
 @param src_length : source buffer length
 @return Z_OK on success, zlib error (<0) on failure
 */
int gunzip(unsigned char *dst, unsigned long *dst_length, unsigned char *src, unsigned long src_length)
{
    z_stream stream;
    memset(&stream, 0, sizeof(stream));

    stream.next_in = src;
    stream.avail_in = src_length;

    stream.next_out = dst;
    stream.avail_out = *dst_length;

    int rv = inflateInit2(&stream, 15 + 16);
    if (Z_OK == rv) {
        rv = inflate(&stream, Z_NO_FLUSH);
        if (Z_STREAM_END == rv) {
            inflateEnd(&stream);
            rv = Z_OK;
        }
    }

    if (Z_OK == rv) {
        *dst_length = stream.total_out;
    } else {
        *dst_length = 0;
    }

    return rv;
}