#pragma once
#include "types.h"

namespace Bdat {

// The union is named uVal by the mangled symbols of Bdat::clearVal and Bdat::convertType; its members are not named
// by any symbol.
union uVal {
  u8 valueU8;
  u16 valueU16;
  u32 valueU32;
  s8 valueS8;
  s16 valueS16;
  f32 valueF32;
  const char *valueString;
};

// Name used by the callers written before the mangled name uVal was known.
typedef uVal Value;

void init();
void regist(int idx, void *data);
void decodeScramble(void *data);
void unregist(int idx);
bool calcCheckSum(int idx);
bool calcCheckSumSub(unsigned char *bdat);
u32 getFileCount(int idx);
const char *getFileName(int idx, int fileIdx);
unsigned char *getFP(const char *name);
unsigned char *getFPSub(const char *name);
void errFile(const char *name);
unsigned char *getFP(int fileIdx, int idx);
unsigned char *isExistFP(const char *name);
const char *getSheetName(unsigned char *bdat);
unsigned char *getMember(unsigned char *bdat, const char *name);
int calcHash(const char *name, int size);
unsigned char *getMember(unsigned char *bdat, int member);
unsigned short getMemberSize(unsigned char *bdat);
const char *getMemberName(unsigned char *bdat, int member);
uVal getVal(unsigned char *bdat, const char *name, int id);
void errMember(unsigned char *bdat, const char *name);
void clearVal(uVal *value);
uVal getVal(unsigned char *bdat, unsigned char *member, int id);
bool calcId(unsigned char *bdat, int *id);
uVal getVar(unsigned char *bdat, unsigned char *member, int row);
uVal getVal(unsigned char *bdat, int column, int id);
uVal getArrayVal(unsigned char *bdat, const char *name, int id, int index);
uVal getArrayVal(unsigned char *bdat, unsigned char *member, int id, int index);
uVal getArray(unsigned char *bdat, unsigned char *member, int row, int index);
uVal getArrayVal(unsigned char *bdat, int column, int id, int index);
int getArrayCount(unsigned char *bdat, const char *name);
int getArrayCount(unsigned char *bdat, unsigned char *member);
unsigned short getArrayCountSub(unsigned char *bdat, unsigned char *member);
int getArrayCount(unsigned char *bdat, int column);
int getIdCount(unsigned char *bdat);
int getIdTop(unsigned char *bdat);
int getIdEnd(unsigned char *bdat);
int getVarType(unsigned char *bdat, const char *name);
int getVarType(unsigned char *bdat, unsigned char *member);
unsigned char getVarTypeSub(unsigned char *bdat, unsigned char *member);
int getVarType(unsigned char *bdat, int column);
int getFlagVal(unsigned char *bdat, const char *name, int id, const char *flag);
void errFlag(unsigned char *bdat, const char *name, const char *flag);
int getFlagVal(unsigned char *bdat, unsigned char *member, int id, unsigned char *flag);
void errFlagParent(unsigned char *bdat, const char *name, const char *flag);
int getFlagVal(unsigned char *bdat, int column, int id, int flag);
bool getShiftMask(unsigned char *bdat, const char *name, const char *flag, int *shift, u32 *mask);
unsigned long getValCheck(unsigned char *bdat, const char *name, int id, int type);
bool getValCheckSub(unsigned char *bdat, unsigned char *member, int type);
void convertType(unsigned char *bdat, unsigned char *member, int type, uVal *value);
uVal getValCheck(unsigned char *bdat, int column, int id, int type);
uVal getValCheck(unsigned char *bdat, unsigned char *member, int id, int type);
uVal getArrayValCheck(unsigned char *bdat, const char *name, int id, int index, int type);
uVal getArrayValCheck(unsigned char *bdat, int column, int id, int index, int type);
uVal getArrayValCheck(unsigned char *bdat, unsigned char *member, int id, int index, int type);
const char *getMSText(unsigned char *bdat, int id);
const char *getMSTextIndirect(unsigned char *bdat, unsigned char *indirect, const char *name, int id);
int getMSStyle(unsigned char *bdat, int id);
const char *getMSLabel(unsigned char *bdat, int id);
void errId(unsigned char *bdat, int id);
void errScalar(char *name);
uVal getVarVal(unsigned char *bdat, unsigned char *data, unsigned char type);
void errArray(char *name);
int errArrayIdx(int index);
void errType(unsigned char *bdat, const char *name);
void decodeScrambleSub(unsigned char *bdat, unsigned short key, int start, int end);
void errOutput(const char *format, ...);

} // namespace Bdat
