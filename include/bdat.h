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
unsigned char *getFP(int table, int id);
int getIdTop(unsigned char *bdat);
int getIdEnd(unsigned char *bdat);
int getIdCount(unsigned char *bdat);
unsigned short getMemberSize(unsigned char *bdat);
const char *getMSLabel(unsigned char *bdat, int id);
unsigned char *getMember(unsigned char *bdat, const char *name);
int getVarType(unsigned char *bdat, const char *name);
const char *getMSText(unsigned char *bdat, int id);
Value getVal(unsigned char *bdat, const char *name, int id);
unsigned long getValCheck(unsigned char *bdat, const char *name, int id, int type);
Value getValCheck(unsigned char *bdat, unsigned char *member, int id, int type);
Value getValCheck(unsigned char *bdat, int column, int id, int type);
Value getArrayValCheck(unsigned char *bdat, unsigned char *member, int id, int index, int type);
int getFlagVal(unsigned char *bdat, unsigned char *member, int id, unsigned char *flag);
int getFlagVal(unsigned char *bdat, const char *name, int id, const char *flag);

} // namespace Bdat
