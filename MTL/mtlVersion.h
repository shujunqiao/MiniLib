#ifndef MTL_VERSION_H_INCLUDED__
#define MTL_VERSION_H_INCLUDED__

#include <limits.h>
#include <stdint.h>

#if sizeof(unsigned int) != 4
#error "sizeof(unsigned int) != 4"
#endif

static const union
{
	char bits8[4];
	unsigned int bits32;
} mtlEndian = { { 0, 1, 2, 3 } };

#define MTL_BIG_ENDIAN	0x03020100ul
#define MTL_LITTLE_ENDIAN 0x00010203ul
#define MTL_PDP_ENDIAN 0x01000302ul

#define MTL_ENDIAN (mtlEndian.bits32)

#define MTL_CPP_XX 0
#define MTL_CPP_98 1
#define MTL_CPP_11 2

#if __cplusplus == 199711L
// Common, even for compilers with C++11 features
#define MTL_CPP_VER MTL_CPP_98
#else if __cplusplus == 201103L
// I think this is very rare (only compilers with 100% support will have it, others might never implement it due to compatibility)
#define MTL_CPP_VER MTL_CPP_11
#else
// We need a fallback, the programmer must find out the C++ version some other way
#define MTL_CPP_VER MTL_CPP_XX
#endif

#endif