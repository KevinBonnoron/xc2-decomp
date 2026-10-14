#pragma once
#include "types.h"

namespace Bdat {

union Value {
  u8 valueU8;
  u16 valueU16;
  u32 valueU32;
  s8 valueS8;
  s16 valueS16;
  f32 valueF32;
  const char *valueString;
};

unsigned char *getFP(const char *name);
int getIdTop(unsigned char *bdat);
int getIdCount(unsigned char *bdat);
unsigned char *getMember(unsigned char *bdat, const char *name);
const char *getMSText(unsigned char *bdat, int id);
unsigned long getValCheck(unsigned char *bdat, const char *name, int id, int type);
Value getValCheck(unsigned char *bdat, unsigned char *member, int id, int type);
int getFlagVal(unsigned char *bdat, unsigned char *member, int id, unsigned char *flag);

} // namespace Bdat
