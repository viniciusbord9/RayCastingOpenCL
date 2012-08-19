#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <stdarg.h>

typedef unsigned char uint8;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef   signed short  int16;
typedef unsigned int   uint32;
typedef   signed int    int32;
typedef unsigned int   uint;

class image
{
public:
	image(void);
	~image(void);
	static int write_bmp(char const *filename, int x, int y, int comp, void *data);
	static int outfile(char const *filename, int rgb_dir, int vdir, int x, int y, int comp, void *data, int alpha, int pad, char *fmt, ...);
	static void write_pixels(FILE *f, int rgb_dir, int vdir, int x, int y, int comp, void *data, int write_alpha, int scanline_pad);
	static void writef(FILE *f, char *fmt, ...);
	static void writefv(FILE *f, char *fmt, va_list v);
	static void write8(FILE *f, int x);
};

