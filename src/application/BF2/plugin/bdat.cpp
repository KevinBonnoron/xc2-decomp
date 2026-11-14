#include <assert.h>
#include <stdarg.h>
#include <stddef.h>

#include "bdat.h"
#include "types.h"

namespace Bdat {

namespace {

enum {
  BDAT_FILE_MAX = 16, // Name from the assertion string "idx < BDAT_FILE_MAX".
};

// Inferred role: header of a bdat archive, which holds several sheets; original name unknown.
struct unknown001 {
  u32 unknown00;    // Inferred role: sheet count; original member name unknown.
  u32 unknown04;    // Inferred role: unused here; original member name unknown.
  u32 unknown08[1]; // Inferred role: offsets of the sheets from the archive start; original member name unknown.
};

// Inferred role: header of a bdat sheet; original name unknown.
struct unknown002 {
  u8 unknown00[4];
  u8 unknown04;  // Inferred role: flags, bit 1 is set while the sheet is scrambled; original member name unknown.
  u8 unknown05;  // Inferred role: unused here; original member name unknown.
  u16 unknown06; // Inferred role: offset of the sheet name; original member name unknown.
  u16 unknown08; // Inferred role: row size; original member name unknown.
  u16 unknown0a; // Inferred role: offset of the member hash table; original member name unknown.
  u16 unknown0c; // Inferred role: size of the member hash table; original member name unknown.
  u16 unknown0e; // Inferred role: offset of the row data; original member name unknown.
  u16 unknown10; // Inferred role: row count; original member name unknown.
  u16 unknown12; // Inferred role: first row id; original member name unknown.
  u16 unknown14; // Inferred role: unused here; original member name unknown.
  u16 unknown16; // Inferred role: checksum and scramble key; original member name unknown.
  int unknown18; // Inferred role: start of the scrambled string data; original member name unknown.
  int unknown1c; // Inferred role: size of the scrambled string data; original member name unknown.
  u16 unknown20; // Inferred role: offset of the member table; original member name unknown.
  u16 unknown22; // Inferred role: member count; original member name unknown.
};

// Inferred role: entry of the member table and of the member hash chains; original name unknown.
struct unknown003 {
  u16 unknown00; // Inferred role: offset of the variable description; original member name unknown.
  u16 unknown02; // Inferred role: offset of the next member of the hash chain; original member name unknown.
  u16 unknown04; // Inferred role: offset of the member name; original member name unknown.
};

// Inferred role: variable description (1 scalar, 2 array, 3 flag); original name unknown. The 16 and 32 bit values
// are stored unaligned in the data, so they are read through the byte arrays.
struct unknown004 {
  u8 unknown00;  // Inferred role: kind; original member name unknown.
  u8 unknown01;  // Inferred role: value type, or shift of a flag; original member name unknown.
  u16 unknown02; // Inferred role: offset in the row; original member name unknown.
  u16 unknown04; // Inferred role: array count; original member name unknown.
  u16 unknown06; // Inferred role: unused here; original member name unknown.
};

static_assert(offsetof(unknown001, unknown08) == 0x08, "");
static_assert(offsetof(unknown002, unknown04) == 0x04, "");
static_assert(offsetof(unknown002, unknown06) == 0x06, "");
static_assert(offsetof(unknown002, unknown08) == 0x08, "");
static_assert(offsetof(unknown002, unknown0a) == 0x0a, "");
static_assert(offsetof(unknown002, unknown0c) == 0x0c, "");
static_assert(offsetof(unknown002, unknown0e) == 0x0e, "");
static_assert(offsetof(unknown002, unknown10) == 0x10, "");
static_assert(offsetof(unknown002, unknown12) == 0x12, "");
static_assert(offsetof(unknown002, unknown16) == 0x16, "");
static_assert(offsetof(unknown002, unknown18) == 0x18, "");
static_assert(offsetof(unknown002, unknown1c) == 0x1c, "");
static_assert(offsetof(unknown002, unknown20) == 0x20, "");
static_assert(offsetof(unknown002, unknown22) == 0x22, "");
static_assert(sizeof(unknown003) == 0x06, "");
static_assert(offsetof(unknown004, unknown02) == 0x02, "");
static_assert(offsetof(unknown004, unknown04) == 0x04, "");
static_assert(offsetof(unknown004, unknown06) == 0x06, "");

} // namespace

void *m_pBin[BDAT_FILE_MAX];

void init() {
  for (int i = 0; i < BDAT_FILE_MAX; i++) {
    m_pBin[i] = nullptr;
  }
}

void regist(int idx, void *data) {
#line 34
  assert(idx < BDAT_FILE_MAX);
  m_pBin[idx] = data;
  decodeScramble(data);
}

void unregist(int idx) {
#line 43
  assert(idx < BDAT_FILE_MAX);
  m_pBin[idx] = nullptr;
}

bool calcCheckSumSub(unsigned char *bdat) {
  unknown002 *header = reinterpret_cast<unknown002 *>(bdat);
  u16 sum = 0;
  u32 end = header->unknown18 + header->unknown1c;
  for (int i = 0x20; i < end; i++) {
    sum += (bdat[i] << (i & 3)) & 0xff;
  }
  return sum == header->unknown16;
}

u32 getFileCount(int idx) {
#line 71
  assert(idx < BDAT_FILE_MAX);
  return static_cast<unknown001 *>(m_pBin[idx])->unknown00;
}

void errFile(const char *name) {}

const char *getSheetName(unsigned char *bdat) { return reinterpret_cast<const char *>(bdat + reinterpret_cast<unknown002 *>(bdat)->unknown06); }

unsigned char *getMember(unsigned char *pBdat, const char *name) {
#line 136
  assert(pBdat != 0L);
  unknown002 *header = reinterpret_cast<unknown002 *>(pBdat);
  u16 *table = reinterpret_cast<u16 *>(pBdat + header->unknown0a);
  int index = calcHash(name, header->unknown0c);
  for (u32 offset = table[index]; offset != 0;) {
    unknown003 *member = reinterpret_cast<unknown003 *>(pBdat + offset);
    if (__builtin_strcmp(name, reinterpret_cast<const char *>(pBdat + member->unknown04)) == 0) {
      return reinterpret_cast<u8 *>(member);
    }
    offset = member->unknown02;
  }
  return nullptr;
}

int calcHash(const char *name, int size) {
  u32 hash = 0;
  int length = __builtin_strlen(name);
  if (length > 8) {
    length = 8;
  }
  for (int i = 0; i < length; i++) {
    hash = hash * 7 + static_cast<u8>(name[i]);
  }
  return hash % size;
}

unsigned char *getMember(unsigned char *fp, int member) {
#line 163
  assert(member < getMemberSize(fp));
  return fp + reinterpret_cast<unknown002 *>(fp)->unknown20 + member * static_cast<int>(sizeof(unknown003));
}

unsigned short getMemberSize(unsigned char *bdat) { return reinterpret_cast<unknown002 *>(bdat)->unknown22; }

const char *getMemberName(unsigned char *bdat, int member) {
  if (member < getMemberSize(bdat)) {
    unknown003 *entry = reinterpret_cast<unknown003 *>(bdat + reinterpret_cast<unknown002 *>(bdat)->unknown20 + member * static_cast<int>(sizeof(unknown003)));
    return reinterpret_cast<const char *>(bdat + entry->unknown04);
  }
  return nullptr;
}

void errMember(unsigned char *bdat, const char *name) {}

void clearVal(uVal *value) { value->valueString = nullptr; }

bool calcId(unsigned char *bdat, int *id) {
  unknown002 *header = reinterpret_cast<unknown002 *>(bdat);
  if (static_cast<u32>(*id - header->unknown12) < header->unknown10) {
    *id -= header->unknown12;
    return true;
  }
  return false;
}

uVal getVal(unsigned char *bdat, int column, int id) { return getVal(bdat, getMember(bdat, column), id); }

uVal getArrayVal(unsigned char *bdat, const char *name, int id, int index) {
  unsigned char *member = getMember(bdat, name);
  if (member != nullptr) {
    return getArrayVal(bdat, member, id, index);
  }
  uVal value;
  clearVal(&value);
  return value;
}

uVal getArrayVal(unsigned char *bdat, int column, int id, int index) { return getArrayVal(bdat, getMember(bdat, column), id, index); }

int getArrayCount(unsigned char *bdat, const char *name) {
  unsigned char *member = getMember(bdat, name);
  if (member != nullptr) {
    return getArrayCount(bdat, member);
  }
  return 0;
}

int getArrayCount(unsigned char *pBdat, unsigned char *pVarName) {
#line 277
  assert(pVarName != 0L);
#line 280
  assert(pBdat != 0L);
  return getArrayCountSub(pBdat, pVarName);
}

unsigned short getArrayCountSub(unsigned char *bdat, unsigned char *member) {
  unknown004 *var = reinterpret_cast<unknown004 *>(bdat + reinterpret_cast<unknown003 *>(member)->unknown00);
  if (var->unknown00 == 2) {
    return var->unknown04;
  }
  return 0;
}

int getArrayCount(unsigned char *bdat, int column) { return getArrayCount(bdat, getMember(bdat, column)); }

int getIdCount(unsigned char *pBdat) {
#line 296
  assert(pBdat != 0L);
  return reinterpret_cast<unknown002 *>(pBdat)->unknown10;
}

int getIdTop(unsigned char *pBdat) {
#line 307
  assert(pBdat != 0L);
  return reinterpret_cast<unknown002 *>(pBdat)->unknown12;
}

int getIdEnd(unsigned char *bdat) { return getIdTop(bdat) + getIdCount(bdat) - 1; }

int getVarType(unsigned char *bdat, const char *name) {
  unsigned char *member = getMember(bdat, name);
  if (member != nullptr) {
    return getVarType(bdat, member);
  }
  return 0;
}

int getVarType(unsigned char *pBdat, unsigned char *pVarName) {
#line 334
  assert(pVarName != 0L);
#line 337
  assert(pBdat != 0L);
  return getVarTypeSub(pBdat, pVarName);
}

unsigned char getVarTypeSub(unsigned char *bdat, unsigned char *member) { return reinterpret_cast<unknown004 *>(bdat + reinterpret_cast<unknown003 *>(member)->unknown00)->unknown01; }

int getVarType(unsigned char *bdat, int column) { return getVarType(bdat, getMember(bdat, column)); }

int getFlagVal(unsigned char *bdat, const char *name, int id, const char *flag) {
  unsigned char *member = getMember(bdat, name);
  if (member != nullptr) {
    unsigned char *flagMember = getMember(bdat, flag);
    if (flagMember != nullptr) {
      return getFlagVal(bdat, member, id, flagMember);
    }
  }
  return 0;
}

void errFlag(unsigned char *bdat, const char *name, const char *flag) {}

void errFlagParent(unsigned char *bdat, const char *name, const char *flag) {}

int getFlagVal(unsigned char *bdat, int column, int id, int flag) { return getFlagVal(bdat, getMember(bdat, column), id, getMember(bdat, flag)); }

bool getValCheckSub(unsigned char *bdat, unsigned char *member, int type) {
  if (member == nullptr) {
    return false;
  }
  return getVarType(bdat, member) == type;
}

void convertType(unsigned char *bdat, unsigned char *member, int type, uVal *value) {
  int sourceType = getVarType(bdat, member);
  if (type == 7 || sourceType == 7) {
    clearVal(value);
    return;
  }
  if (type == 8 || sourceType == 8) {
    clearVal(value);
    return;
  }
  switch (sourceType) {
  case 1:
    switch (type) {
    case 2:
    case 5:
      value->valueU16 = value->valueU8;
      break;
    case 3:
    case 6:
      value->valueU32 = value->valueU8;
      break;
    }
    break;
  case 2:
    switch (type) {
    case 1:
    case 4:
      value->valueU8 = static_cast<u8>(value->valueU16);
      break;
    case 3:
    case 6:
      value->valueU32 = value->valueU16;
      break;
    }
    break;
  case 3:
    switch (type) {
    case 1:
    case 4:
      value->valueU8 = static_cast<u8>(value->valueU32);
      break;
    case 2:
      value->valueU32 = value->valueU16;
      break;
    case 5:
      value->valueU16 = static_cast<u16>(value->valueU32);
      break;
    }
    break;
  case 4:
    switch (type) {
    case 2:
    case 5:
      value->valueU16 = static_cast<u16>(value->valueS8);
      break;
    case 3:
    case 6:
      value->valueU32 = value->valueS8;
      break;
    }
    break;
  case 5:
    switch (type) {
    case 1:
    case 4:
      value->valueU8 = static_cast<u8>(value->valueS16);
      break;
    case 3:
    case 6:
      value->valueU32 = value->valueS16;
      break;
    }
    break;
  case 6:
    switch (type) {
    case 1:
    case 4:
      value->valueU8 = static_cast<u8>(value->valueU32);
      break;
    case 2:
    case 5:
      value->valueU16 = static_cast<u16>(value->valueU32);
      break;
    }
    break;
  }
}

void errId(unsigned char *bdat, int id) {}

void errScalar(char *name) {}

uVal getVarVal(unsigned char *bdat, unsigned char *data, unsigned char type) {
  uVal value;
  clearVal(&value);
  switch (type) {
  case 1:
    value.valueU8 = *data;
    break;
  case 2:
    value.valueU16 = *reinterpret_cast<u16 *>(data);
    break;
  case 3:
  case 6:
  case 8:
    value.valueU32 = *reinterpret_cast<u32 *>(data);
    break;
  case 4:
    value.valueS8 = *reinterpret_cast<s8 *>(data);
    break;
  case 5:
    value.valueS16 = *reinterpret_cast<s16 *>(data);
    break;
  case 7:
    value.valueString = reinterpret_cast<const char *>(bdat + *reinterpret_cast<u32 *>(data));
    break;
  }
  return value;
}

void errArray(char *name) {}

int errArrayIdx(int index) { return index; }

void errType(unsigned char *bdat, const char *name) {}

void decodeScrambleSub(unsigned char *bdat, unsigned short key, int start, int end) {
  u16 evenKey = static_cast<u8>(key >> 8) ^ 0xff;
  u16 oddKey = key ^ 0xff;
  for (int i = start; i < end; i += 2) {
    u8 even = bdat[i];
    bdat[i] = even ^ static_cast<u8>(evenKey);
    evenKey = even + static_cast<u8>(evenKey);
    u8 odd = bdat[i + 1];
    bdat[i + 1] = odd ^ static_cast<u8>(oddKey);
    oddKey = odd + static_cast<u8>(oddKey);
  }
}

void errOutput(const char *format, ...) {
  va_list arguments;
  va_start(arguments, format);
  va_end(arguments);
}

} // namespace Bdat
