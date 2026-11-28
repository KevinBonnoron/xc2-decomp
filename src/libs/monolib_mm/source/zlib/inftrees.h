#pragma once
// inftrees.h of zlib 1.2.8 (see zlib.h for the provenance and the licence): header to use inftrees.c.

/* Structure for decoding tables.  Each entry provides either the information needed to do the operation requested by the code
   that indexed that table entry, or it provides a pointer to another table that indexes more bits of the code. */
typedef struct {
  unsigned char op;   /* operation, extra bits, table bits */
  unsigned char bits; /* bits in this part of the code */
  unsigned short val; /* offset in table or code value */
} code;

#define ENOUGH_LENS 852
#define ENOUGH_DISTS 592
#define ENOUGH (ENOUGH_LENS + ENOUGH_DISTS)

/* Type of code to build for inflate_table() */
typedef enum { CODES, LENS, DISTS } codetype;

extern "C" int inflate_table(codetype type, unsigned short *lens, unsigned codes, code **table, unsigned *bits, unsigned short *work);

#define MAXBITS 15
