#pragma once
// inffast.h of zlib 1.2.8 (see zlib.h for the provenance and the licence): header to use inffast.c.
#include "zlib/zlib.h"

extern "C" void inflate_fast(z_streamp strm, unsigned start);
