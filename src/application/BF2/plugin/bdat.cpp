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

// Inferred role: header of a bdat sheet; original name unknown. Packed (file format layout): with the natural alignment of 4 the
// flags byte at 0x04 and the u16 at 0x06 are merged into one 32-bit load in decodeScramble, where the game (0x71006b45c4) has
// a byte load, so the game's type is not 4-aligned. Alignment 1 follows the precedent of the vm unknown004 (decision 15 of
// 2026-11-14); alignment 2 matches too, and no access of the game tells the two apart (every sheet offset of the game's
// archives is a multiple of 4).
#pragma pack(push, 1)
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
#pragma pack(pop)

// Inferred role: entry of the member table and of the member hash chains; original name unknown.
struct unknown003 {
  u16 unknown00; // Inferred role: offset of the variable description; original member name unknown.
  u16 unknown02; // Inferred role: offset of the next member of the hash chain; original member name unknown.
  u16 unknown04; // Inferred role: offset of the member name; original member name unknown.
};

// Inferred role: variable description (1 scalar, 2 array, 3 flag); original name unknown. Packed (file format layout): with
// the natural alignment of 2 clang widens the kind byte load into one 16 bit load that also covers the type byte (GVN),
// where the game (0x71006b5020 getVar) loads the two bytes separately, so the game's type is not 2-aligned (same case
// as unknown002, decision 15 of 2026-11-14).
#pragma pack(push, 1)
struct unknown004 {
  u8 unknown00;  // Inferred role: kind; original member name unknown.
  u8 unknown01;  // Inferred role: value type, or shift of a flag; original member name unknown.
  u16 unknown02; // Inferred role: offset in the row, or the first half of the 32 bit mask of a flag (read as a u32 at 0x02 by getShiftMask); original member name unknown.
  u16 unknown04; // Inferred role: array count, or the second half of the mask of a flag; original member name unknown.
  u16 unknown06; // Inferred role: offset of the parent member of a flag, compared by getShiftMask; unused otherwise; original member name unknown.
};
#pragma pack(pop)

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

// Inferred role: address of the sheet with a signed index in an archive; original name unknown. The game reads the
// offset table as bytes at (index << 2) + 8, never as an array of u32 (0x71006b4980 getFileName, 0x71006b4b60 getFP and
// the binary searches): a u32 array member gives a scaled address mode instead (P1, decision of 2026-11-14). The 32 bit
// shift is sign extended and the 8 stays in the load.
u8 *unknown005(u8 *bin, int index) { return bin + *reinterpret_cast<u32 *>(bin + ((index << 2) + 8)); }

// Inferred role: address of the sheet with an unsigned index in an archive; original name unknown. Same byte offset
// table as unknown005, but the loops of 0x71006b45c4 decodeScramble and 0x71006b47b4 calcCheckSum add the 8 in 32 bits
// before the zero extension (P1).
u8 *unknown006(u8 *bin, u32 index) { return bin + *reinterpret_cast<u32 *>(bin + ((index << 2) + 8)); }

} // namespace

void *m_pBin[BDAT_FILE_MAX];

// Inferred type: object of the function static of getInstance (0x71006b4518; object 0x71014ae9d0, guard 0x71014ae9d8). The game takes the guard with
// ldarb, calls __cxa_guard_acquire and __cxa_guard_release, and never touches the object: no store, no member access, and no caller of getInstance
// reads it (no bl or b to it in the executable), so its real type and constructor are unknown (original name unknown). The only evidence is the
// guard, which needs a constructor that clang cannot fold into constant data. Forms tried: a plain `static bool` (no guard: 3 instructions), a
// defaulted constructor (constant data: 3), a bool initialised from a runtime value (24 instructions, a store the game does not have); an empty
// user constructor gives the game's 17 instructions (a type with one pointer member and the same constructor also matches, but no access shows a
// member).
struct unknown007 {
  unknown007() {}
};

unknown007 *getInstance() {
  static unknown007 instance;
  return &instance;
}

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

void decodeScramble(void *data) {
  unknown001 *archive = static_cast<unknown001 *>(data);
  u8 *bin = static_cast<u8 *>(data);
  u32 count = archive->unknown00;
  for (int i = 0; i < count; i++) {
    unknown002 *header = reinterpret_cast<unknown002 *>(unknown006(bin, i));
    u16 key = header->unknown16;
    if (header->unknown04 & 2) {
      u8 *bdat = reinterpret_cast<u8 *>(header);
      decodeScrambleSub(bdat, key, header->unknown18, header->unknown18 + header->unknown1c);
      decodeScrambleSub(bdat, key, header->unknown06, header->unknown0a);
      header->unknown04 &= ~2;
    }
  }
}

void unregist(int idx) {
#line 43
  assert(idx < BDAT_FILE_MAX);
  m_pBin[idx] = nullptr;
}

bool calcCheckSum(int idx) {
#line 55
  assert(idx < BDAT_FILE_MAX);
  unknown001 *archive = static_cast<unknown001 *>(m_pBin[idx]);
  u8 *bin = static_cast<u8 *>(m_pBin[idx]);
  for (int i = 0; i < archive->unknown00; i++) {
    if (!calcCheckSumSub(unknown006(bin, i))) {
      return false;
    }
  }
  return true;
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

const char *getFileName(int idx, int fileIdx) {
#line 79
  assert(idx < BDAT_FILE_MAX);
  unknown001 *archive = static_cast<unknown001 *>(m_pBin[idx]);
  u8 *bin = static_cast<u8 *>(m_pBin[idx]);
  if (static_cast<u32>(fileIdx) < archive->unknown00) {
    return getSheetName(unknown005(bin, fileIdx));
  }
  return nullptr;
}

unsigned char *getFP(const char *name) {
  unsigned char *bdat = getFPSub(name);
  // The game keeps the null test of the sheet address (0x71006b4a80, cbnz x20) although errFile is empty; with a
  // plain `if (bdat == nullptr) { errFile(name); }` the test is removed.
  if (bdat == nullptr) {
    errFile(name);
    return nullptr;
  }
  return bdat;
}

unsigned char *getFPSub(const char *name) {
  for (int i = 0; i < BDAT_FILE_MAX; i++) {
    unknown001 *archive = static_cast<unknown001 *>(m_pBin[i]);
    u8 *bin = static_cast<u8 *>(m_pBin[i]);
    if (archive != nullptr) {
      int low = 0;
      int high = archive->unknown00;
      while (low < high) {
        int mid = (low + high) / 2;
        u8 *bdat = unknown005(bin, mid);
        int cmp = __builtin_strcmp(getSheetName(bdat), name);
        if (cmp < 0) {
          low = mid + 1;
        } else if (cmp == 0) {
          return bdat;
        } else {
          high = mid;
        }
      }
    }
  }
  return nullptr;
}

void errFile(const char *name) {}

unsigned char *getFP(int fileIdx, int idx) {
#line 105
  assert(idx < BDAT_FILE_MAX);
  u32 binCount = getFileCount(idx);
#line 110
  assert((u32)fileIdx < binCount);
  return unknown005(static_cast<u8 *>(m_pBin[idx]), fileIdx);
}

unsigned char *isExistFP(const char *name) { return getFPSub(name); }

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

uVal getVal(unsigned char *pBdat, unsigned char *pVarName, int id) {
#line 206
  assert(pVarName != 0L);
#line 209
  assert(pBdat != 0L);
  if (calcId(pBdat, &id)) {
    return getVar(pBdat, pVarName, id);
  }
  uVal value;
  clearVal(&value);
  return value;
}

bool calcId(unsigned char *bdat, int *id) {
  unknown002 *header = reinterpret_cast<unknown002 *>(bdat);
  if (static_cast<u32>(*id - header->unknown12) < header->unknown10) {
    *id -= header->unknown12;
    return true;
  }
  return false;
}

uVal getVar(unsigned char *bdat, unsigned char *member, int row) {
  unknown004 *var = reinterpret_cast<unknown004 *>(bdat + reinterpret_cast<unknown003 *>(member)->unknown00);
  if (var->unknown00 == 1) {
    unknown002 *header = reinterpret_cast<unknown002 *>(bdat);
    return getVarVal(bdat, bdat + header->unknown0e + header->unknown08 * row + var->unknown02, var->unknown01);
  }
  uVal value;
  clearVal(&value);
  return value;
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

uVal getArrayVal(unsigned char *pBdat, unsigned char *pVarName, int id, int index) {
#line 243
  assert(pVarName != 0L);
#line 246
  assert(pBdat != 0L);
  if (calcId(pBdat, &id)) {
    return getArray(pBdat, pVarName, id, index);
  }
  uVal value;
  clearVal(&value);
  return value;
}

uVal getArray(unsigned char *bdat, unsigned char *member, int row, int index) {
  unknown004 *var = reinterpret_cast<unknown004 *>(bdat + reinterpret_cast<unknown003 *>(member)->unknown00);
  if (var->unknown00 == 2 && index < var->unknown04) {
    unknown002 *header = reinterpret_cast<unknown002 *>(bdat);
    unsigned char *data = bdat + header->unknown0e + header->unknown08 * row + var->unknown02;
    switch (var->unknown01) {
    case 1:
    case 4:
      data += index;
      break;
    case 2:
    case 5:
      data += index * 2;
      break;
    case 3:
    case 6:
    case 7:
    case 8:
      data += index * 4;
      break;
    }
    return getVarVal(bdat, data, var->unknown01);
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

int getFlagVal(unsigned char *pBdat, unsigned char *pVarName, int id, unsigned char *pFlagName) {
#line 376
  assert(pBdat != 0L);
#line 377
  assert(pVarName != 0L);
#line 378
  assert(pFlagName != 0L);
  if (!calcId(pBdat, &id)) {
    return 0;
  }
  unknown004 *flag = reinterpret_cast<unknown004 *>(pBdat + reinterpret_cast<unknown003 *>(pFlagName)->unknown00);
  if (flag->unknown00 != 3) {
    return 0;
  }
  if (flag->unknown06 != static_cast<u16>(pVarName - pBdat)) {
    return 0;
  }
  unknown004 *parent = reinterpret_cast<unknown004 *>(pBdat + reinterpret_cast<unknown003 *>(pBdat + flag->unknown06)->unknown00);
  // The game keeps one inlined copy of getVar per mask of the parent type (0x71006b582c, 171 instructions). An if/else chain on the type merges two of
  // the copies (137 instructions); a switch with the case 1 written before the case 2 keeps the three and the game's order of tests.
  u32 value;
  switch (parent->unknown01) {
  case 1:
    value = getVar(pBdat, pVarName, id).valueU32 & 0xff;
    break;
  case 2:
    value = getVar(pBdat, pVarName, id).valueU32 & 0xffff;
    break;
  default:
    value = getVar(pBdat, pVarName, id).valueU32;
    break;
  }
  // The mask is read as one unaligned 32-bit word at 0x02 (`ldur w10, [x8, #2]` at 0x71006b59e4), like getShiftMask (decision 38 of 2026-11-14,
  // blob read); `unknown02 | (unknown04 << 16)` gives two 16-bit loads (173 instructions).
  return (*reinterpret_cast<u32 *>(&flag->unknown02) & value) >> flag->unknown01;
}

void errFlagParent(unsigned char *bdat, const char *name, const char *flag) {}

int getFlagVal(unsigned char *bdat, int column, int id, int flag) { return getFlagVal(bdat, getMember(bdat, column), id, getMember(bdat, flag)); }

bool getShiftMask(unsigned char *pBdat, const char *name, const char *flag, int *shift, u32 *mask) {
#line 422
  assert(pBdat != 0L);
  unsigned char *member = getMember(pBdat, name);
  if (member == nullptr) {
    return false;
  }
  unsigned char *flagMember = getMember(pBdat, flag);
  if (flagMember == nullptr) {
    return false;
  }
  unknown004 *var = reinterpret_cast<unknown004 *>(pBdat + reinterpret_cast<unknown003 *>(flagMember)->unknown00);
  if (var->unknown00 == 3 && var->unknown06 == static_cast<u16>(member - pBdat)) {
    *shift = var->unknown01;
    *mask = *reinterpret_cast<u32 *>(&var->unknown02);
    return true;
  }
  return false;
}

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
