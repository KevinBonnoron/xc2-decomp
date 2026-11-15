#include <stddef.h>
// Script VM of monolib_mm. The assertion strings of the game name its source
// `C:/Monolithsoft/BF2/prog/libs/monolib_mm/source/vm/yvm2.c`: it is a C file. VMData-like values of the stack hold
// 8-byte pointers at 4-byte aligned offsets (12-byte elements), so that type is packed.
//
// Layout evidence: the pool getters (vmIdPoolGet 0x7100786c74 ...), vmThreadCreate 0x71007873b0, vmPush 0x7100787e2c
// and the opcode table at 0x71011b05a0 (96 entries, the strings of the table name every VMC_ opcode).
#include <assert.h>
#include <string.h>

#include "types.h"
#include "vm/vm.h"

#line 1 "C:/Monolithsoft/BF2/prog/libs/monolib_mm/source/vm/yvm2.c"

// sSbHeader of the original: header of a script binary, the magic is "SB  ".
struct sSbHeader {
  char unknown00[4]; // Inferred role: magic "SB  "; original member name unknown.
  u8 unknown04;      // Inferred role: version, at least 2; original member name unknown.
  u8 unknown05;      // Inferred role: unused; original member name unknown.
  u8 unknown06;      // Inferred role: flags, bit 1 asks for the scrambled code; original member name unknown.
  u8 unknown07;      // Inferred role: flags, bit 0 is set once linked; original member name unknown.
  int codeOfs;       // offset of the code block, named by the assertion text of vmCodeExecSub
  int unknown0c;     // Inferred role: offset of the id pool; original member name unknown.
  int unknown10;     // Inferred role: offset of the int pool; original member name unknown.
  int unknown14;     // Inferred role: offset of the fixed pool; original member name unknown.
  int unknown18;     // Inferred role: offset of the string pool; original member name unknown.
  int unknown1c;     // Inferred role: offset of the function pool; original member name unknown.
  int unknown20;     // Inferred role: offset of the plugin pool; original member name unknown.
  int unknown24;     // Inferred role: offset of the object class pool; original member name unknown.
  int unknown28;     // Inferred role: offset of the far function pool; original member name unknown.
  int unknown2c;     // Inferred role: offset of the static data pool; original member name unknown.
  int unknown30;     // Inferred role: offset of the local pool; original member name unknown.
  u32 unknown34;     // Inferred role: offset of the system attribute pool; original member name unknown.
  int unknown38;     // Inferred role: offset of the user attribute pool; original member name unknown.
};

// Inferred role: header of a pool of a script binary (data offset, entry count, entry size); original name unknown.
struct unknown001 {
  int unknown00; // Inferred role: offset of the entries from the pool; original member name unknown.
  int num;       // member named by the assertion texts ("pId->num > no")
  int unknown08; // Inferred role: entry size; original member name unknown.
};

// Inferred role: header of the local pool of a script binary, whose counts are unsigned; original name unknown.
struct unknown002 {
  u32 unknown00; // Inferred role: offset of the entries from the pool; original member name unknown.
  u32 num;       // member named by the assertion text ("(s32)pLocal->num > no")
  int unknown08; // Inferred role: entry size; original member name unknown.
};

// Inferred role: entry of the function pool of a script binary; original name unknown.
struct unknown003 {
  u16 unknown00; // Inferred role: id of the name; original member name unknown.
  u16 unknown02; // Inferred role: number of arguments; original member name unknown.
  u16 unknown04; // Inferred role: minimum number of arguments; original member name unknown.
  u16 unknown06; // Inferred role: unused here; original member name unknown.
  u16 unknown08; // Inferred role: local pool index, 0xffff for none; original member name unknown.
  u16 unknown0a; // Inferred role: unused here; original member name unknown.
  int unknown0c; // Inferred role: entry address of the code; original member name unknown.
  int unknown10; // Inferred role: unused here; original member name unknown.
};

// sSbCode of the original: header of the code block of a script binary.
struct sSbCode {
  int unknown00; // Inferred role: offset of the code from the block; original member name unknown.
  int unknown04; // Inferred role: function index run by vmStart; original member name unknown.
};

// The game stores 8-byte pointers at 4-byte aligned offsets in the 12-byte stack value (ldur x0, [x1, #4]), so the type
// is packed to 4 or less. Decision 2026-11-14 #15: pack(1). The game's loads exclude 4: vmArgFunctionGet and vmOCNameGet
// test the type byte, call the error function and then read the halfword at offset 2 with a separate load (`ldrb w8, [x19]`
// at 0x7100787aa8, `ldrh w8, [x19, #2]` at 0x7100787ab8; 0x7100787d78 and 0x7100787d9c), whereas with pack(4) clang 3.9 knows
// the byte is 4-aligned and widens its load to 32 bits (17 and 26 instructions instead of 14 and 23). pack(2) matches too
// (78 of 78 functions of the file match with 4, 2 and 1 alike); size and offsets are the same, only the alignment differs,
// and nothing in the game separates 2 from 1.
#pragma pack(push, 1)

// Inferred role: value of the VM stack (a VMData of the original is the 4-byte operand read by vmDataGet); original
// name unknown.
struct unknown004 {
  u8 unknown00;  // Inferred role: type; original member name unknown.
  u8 unknown01;  // Inferred role: unused here; original member name unknown.
  u16 unknown02; // Inferred role: array size or function package; original member name unknown.
  union {
    struct {
      s32 unknown04; // Inferred role: integer value; original member name unknown.
      s32 unknown08; // Inferred role: unused here; original member name unknown.
    };
    f32 unknown04_1;         // Inferred role: fixed value; original member name unknown.
    const char *unknown04_2; // Inferred role: string value; original member name unknown.
    u8 unknown04_3;          // Inferred role: argument count of a call; original member name unknown.
  };
};

#pragma pack(pop)

// VMData of the original: the operand read from the code by vmDataGet (its assertion text compares with sizeof).
typedef u32 VMData;

// Inferred role: registers of a VM thread; original name unknown ("reg" is named by the assertion texts).
struct unknown006 {
  int pc;        // program counter, named by the assertion texts
  int sp;        // stack pointer, named by the assertion texts
  int unknown08; // Inferred role: base pointer; original member name unknown.
};

// Inferred role: thread of the script VM (pThread of the assertion texts); original type name unknown.
struct unknown007 {
  unknown006 reg;
  int unknown0c;         // Inferred role: exception kind; original member name unknown.
  int unknown10;         // Inferred role: pc of the exception; original member name unknown.
  unknown004 unknown14;  // Inferred role: first value of the exception; original member name unknown.
  unknown004 unknown20;  // Inferred role: second value of the exception; original member name unknown.
  s16 unknown2c;         // Inferred role: package index; original member name unknown.
  int unknown30;         // Inferred role: function index; original member name unknown.
  s16 unknown34;         // Inferred role: package index; original member name unknown.
  sSbHeader *pSb;        // script binary, named by the assertion texts
  const u8 *unknown40;   // Inferred role: code; original member name unknown.
  unknown004 *unknown48; // Inferred role: static data; original member name unknown.
  unknown004 *unknown50; // Inferred role: stack; original member name unknown.
  int stackSize;         // named by the assertion texts
  int unknown5c;         // Inferred role: thread id; original member name unknown.
  u32 unknown60;         // Inferred role: state, bit 31 set when asleep; original member name unknown.
  u16 unknown64;         // Inferred role: wait mode; original member name unknown.
  s16 unknown66;         // Inferred role: work index; original member name unknown.
  void *unknown68[3];    // Inferred role: work slots; original member name unknown.
  u16 unknown80;         // Inferred role: unused; original member name unknown.
};

// Inferred role: slot of the package table; original name unknown.
struct unknown008 {
  sSbHeader *unknown00;  // Inferred role: script binary of the package; original member name unknown.
  const char *unknown08; // Inferred role: name of the package; original member name unknown.
};

// Inferred role: function of a plugin table, which ends with an entry without name; original name unknown.
struct unknown009 {
  const char *unknown00; // Inferred role: name of the function; original member name unknown.
  void *unknown08;       // Inferred role: function; original member name unknown.
};

// Inferred role: slot of the plugin table; original name unknown.
struct unknown010 {
  const char *unknown00; // Inferred role: name of the plugin; original member name unknown.
  unknown009 *unknown08; // Inferred role: functions of the plugin; original member name unknown.
};

// Inferred role: property of an object class, the table ends with an entry without name; original name unknown.
struct unknown011 {
  const char *unknown00; // Inferred role: name of the property; original member name unknown.
  void *unknown08;       // Inferred role: unused here; original member name unknown.
  void *unknown10;       // Inferred role: unused here; original member name unknown.
  int unknown18;         // Inferred role: length of the name; original member name unknown.
  int unknown1c;         // Inferred role: unused here; original member name unknown.
};

// Inferred role: selector of an object class, the table ends with an entry without name; original name unknown.
struct unknown012 {
  const char *unknown00; // Inferred role: name of the selector; original member name unknown.
  void *unknown08;       // Inferred role: unused here; original member name unknown.
  int unknown10;         // Inferred role: length of the name; original member name unknown.
  int unknown14;         // Inferred role: unused here; original member name unknown.
};

// Inferred role: object class of the script VM; original name unknown.
struct unknown013 {
  const char *unknown00; // Inferred role: name of the object class; original member name unknown.
  void *unknown08;       // Inferred role: unused here; original member name unknown.
  unknown011 *unknown10; // Inferred role: properties; original member name unknown.
  unknown012 *unknown18; // Inferred role: selectors; original member name unknown.
};

// Inferred role: state of the script VM, cleared by vmInit and vmDestory; original name unknown.
struct unknown014 {
  unknown008 unknown00[32];         // Inferred role: package table; original member name unknown.
  unknown007 *unknown200;           // Inferred role: running thread; original member name unknown.
  int unknown208;                   // Inferred role: id of the next thread; original member name unknown.
  unknown007 *unknown210[32];       // Inferred role: threads to run this frame; original member name unknown.
  unknown007 unknown310[32];        // Inferred role: threads; original member name unknown.
  unknown004 unknown1410[32][0x80]; // Inferred role: stack of each thread; original member name unknown.
  unknown010 unknownd410[0x30];     // Inferred role: plugin table; original member name unknown.
  unknown013 *unknownd710[0x30];    // Inferred role: object class table; original member name unknown.
  unknown013 *unknownd890;          // Inferred role: builtin object class; original member name unknown.
};

static_assert(sizeof(unknown004) == 0xc, "stack value size");
static_assert(offsetof(unknown004, unknown04) == 4, "stack value");
static_assert(sizeof(unknown003) == 0x14, "function pool entry size");
static_assert(offsetof(unknown003, unknown0c) == 0xc, "function pool entry");
static_assert(sizeof(sSbHeader) == 0x3c, "script binary header size");
static_assert(offsetof(sSbHeader, unknown38) == 0x38, "script binary header");
static_assert(sizeof(unknown001) == 0xc, "pool header size");
static_assert(sizeof(unknown002) == 0xc, "local pool header size");
static_assert(sizeof(sSbCode) == 8, "code header size");
static_assert(offsetof(unknown007, pSb) == 0x38, "thread");
static_assert(offsetof(unknown007, unknown40) == 0x40, "thread");
static_assert(offsetof(unknown007, unknown50) == 0x50, "thread");
static_assert(offsetof(unknown007, stackSize) == 0x58, "thread");
static_assert(sizeof(unknown007) == 0x88, "thread size");
static_assert(offsetof(unknown014, unknown200) == 0x200, "VM state");
static_assert(offsetof(unknown014, unknown310) == 0x310, "VM state");
static_assert(offsetof(unknown014, unknown1410) == 0x1410, "VM state");
static_assert(offsetof(unknown014, unknownd410) == 0xd410, "VM state");
static_assert(offsetof(unknown014, unknownd710) == 0xd710, "VM state");
static_assert(offsetof(unknown014, unknownd890) == 0xd890, "VM state");
static_assert(sizeof(unknown014) == 0xd898, "VM state size");

// Inferred role: the state of the script VM; original name unknown.
static unknown014 unknown017;

// Inferred macro name; macros leave no trace in the binary.
#define VM_OFFSET(type, base, offset) reinterpret_cast<type *>(reinterpret_cast<char *>(base) + (offset))

// Inferred macro name; macros leave no trace in the binary. The original is a C file: its assertion texts show NULL
// expanded to ((void*)0), which a C++ file cannot spell through the assert macro.
#define VM_ASSERT_TEXT(condition, text) ((condition) || (__assert_fail(text, __FILE__, __LINE__, __func__), 0))

extern "C" {

int vmCodeExecSub(unknown007 *pThread);

int vmPluginModuleSearch(const char *mName);
void vmHalt();

#line 401
int vmPluginRegist(const char *mName, unknown009 *pPlugin) {
  VM_ASSERT_TEXT(mName != 0 && pPlugin != 0, "mName != ((void*)0) && pPlugin != ((void*)0)");
  if (vmPluginModuleSearch(mName)) {
    return 1;
  }
  for (int i = 0; i < 0x30; i++) {
    if (unknown017.unknownd410[i].unknown00 == 0) {
      unknown017.unknownd410[i].unknown00 = mName;
      unknown017.unknownd410[i].unknown08 = pPlugin;
      return 1;
    }
  }
  return 0;
}

#line 597
void **vmWkGet(unknown007 *pThread, int idx) {
  assert(idx >= 0 && idx < 3);
  return &pThread->unknown68[idx];
}

#line 1493
char *vmIdPoolGet(sSbHeader *pSb, int no) {
  unknown001 *pId = VM_OFFSET(unknown001, pSb, pSb->unknown0c);
  assert(pId->num > no);
  char *entries = VM_OFFSET(char, pId, pId->unknown00);
  int offset;
  if (pId->unknown08 == 2) {
    offset = *reinterpret_cast<u16 *>(entries + pId->unknown08 * no);
  } else {
    offset = *reinterpret_cast<int *>(entries + pId->unknown08 * no);
  }
  return entries + offset;
}

#line 1509
int vmIntPoolGet(sSbHeader *pSb, int no) {
  unknown001 *pInt = VM_OFFSET(unknown001, pSb, pSb->unknown10);
  assert(pInt->num > no);
  int *entries = VM_OFFSET(int, pInt, pInt->unknown00);
  return entries[no];
}

#line 1519
f32 vmFixedPoolGet(sSbHeader *pSb, int no) {
  unknown001 *pFixed = VM_OFFSET(unknown001, pSb, pSb->unknown14);
  assert(pFixed->num > no);
  f32 *entries = VM_OFFSET(f32, pFixed, pFixed->unknown00);
  return entries[no];
}

#line 1531
char *vmStringPoolGet(sSbHeader *pSb, int no) {
  unknown001 *pStr = VM_OFFSET(unknown001, pSb, pSb->unknown18);
  assert(pStr->num > no);
  char *entries = VM_OFFSET(char, pStr, pStr->unknown00);
  int offset;
  if (pStr->unknown08 == 2) {
    offset = *reinterpret_cast<u16 *>(entries + pStr->unknown08 * no);
  } else {
    offset = *reinterpret_cast<int *>(entries + pStr->unknown08 * no);
  }
  return entries + offset;
}

#line 1547
unknown003 *vmFunctionPoolGet(sSbHeader *pSb, int no) {
  unknown001 *pFunc = VM_OFFSET(unknown001, pSb, pSb->unknown1c);
  assert(pFunc->num > no);
  unknown003 *entries = VM_OFFSET(unknown003, pFunc, pFunc->unknown00);
  return &entries[no];
}

#line 1559
char *vmLocalPoolGet(sSbHeader *pSb, int no) {
  unknown002 *pLocal = VM_OFFSET(unknown002, pSb, pSb->unknown30);
  assert((s32)pLocal->num > no);
  char *entries = VM_OFFSET(char, pLocal, pLocal->unknown00);
  int offset;
  if (pLocal->unknown08 == 2) {
    offset = *reinterpret_cast<u16 *>(entries + pLocal->unknown08 * no);
  } else {
    offset = *reinterpret_cast<int *>(entries + pLocal->unknown08 * no);
  }
  return entries + offset;
}

#line 1576
char *vmSysAtrPoolGet(sSbHeader *pSb, int no) {
  unknown001 *pAtr = VM_OFFSET(unknown001, pSb, pSb->unknown34);
  assert(pAtr->num > no);
  return VM_OFFSET(char, pAtr, pAtr->unknown00) + pAtr->unknown08 * no;
}

#line 1588
char *vmUsrAtrPoolGet(sSbHeader *pSb, int no) {
  unknown001 *pAtr = VM_OFFSET(unknown001, pSb, pSb->unknown38);
  assert(pAtr->num > no);
  return VM_OFFSET(char, pAtr, pAtr->unknown00) + pAtr->unknown08 * no;
}

#line 1702
void vmPush(unknown007 *pThread, unknown004 *pData) {
  assert(pThread->reg.sp < pThread->stackSize);
  pThread->unknown50[pThread->reg.sp++] = *pData;
}

#line 1716
unknown004 *vmStackNextGet(unknown007 *pThread) {
  assert(pThread->reg.sp < pThread->stackSize);
  return &pThread->unknown50[pThread->reg.sp++];
}

#line 1729
unknown004 *vmStackPrevGet(unknown007 *pThread) {
  assert(pThread->reg.sp > 0);
  return &pThread->unknown50[--pThread->reg.sp];
}

void vmWaitModeSet(unknown007 *pThread) { pThread->unknown64 = 1; }

int vmWkIdxGet(unknown007 *pThread) { return pThread->unknown66; }

void vmWkIdxSet(unknown007 *pThread, s16 idx) { pThread->unknown66 = idx; }

void vmRetValSet(unknown007 *pThread, unknown004 *pData) {
  if (pThread->unknown64 == 0) {
    vmPush(pThread, pData);
  }
}

unknown004 *vmOCPropertyGet(unknown007 *pThread) { return &pThread->unknown50[pThread->reg.sp - 1]; }

u8 vmArgCntGet(unknown007 *pThread) { return pThread->unknown50[pThread->reg.sp - 1].unknown04_3; }

int vmCodeExec(unknown007 *pThread) { return vmCodeExecSub(pThread); }

void vmCodePut() {}

void vmPackageDump() {}

void vmStackDump() {}

void vmThreadDump() {}

void vmInit() { memset(&unknown017, 0, sizeof(unknown017)); }

void vmDestory() { memset(&unknown017, 0, sizeof(unknown017)); }

u8 vmDataGet1(unknown007 *pThread, int pc) { return pThread->unknown40[pc]; }

u16 vmDataGet2(unknown007 *pThread, int pc) {
  const u8 *code = pThread->unknown40 + pc;
  return (code[0] << 8) | code[1];
}

u32 vmDataGet4(unknown007 *pThread, int pc) {
  const u8 *code = pThread->unknown40 + pc;
  return (code[0] << 24) | (code[1] << 16) | (code[2] << 8) | code[3];
}

VMData vmDataGet(unknown007 *pThread, int pc, u32 size) {
  switch (size) {
  case 1:
    return vmDataGet1(pThread, pc);
  case 2:
    return vmDataGet2(pThread, pc);
  case 4:
    return vmDataGet4(pThread, pc);
  default:
#line 1678
    assert(size <= sizeof(VMData));
    return 0;
  }
}

// Inferred role: type names indexed by script object type; no game symbol, original name unknown.
static const char *const unknown018[] = {"nil", "true", "false", "int", "fixed", "string", "array", "function", "plugin", "OC", "sys"};

const char *getScTypeName(int type) {
  if (static_cast<unsigned int>(type) > 10) {
    return "invalid";
  }
  return unknown018[type];
}

void vmHalt() {
#line 4066
  vmMlAssert("[VM] INFINITY_LOOP", __FILE__, __LINE__);
}

int vmSbChk(const char *pSb) {
  if (pSb == 0) {
    return 0;
  }
  if (pSb[0] != 'S') {
    return 0;
  }
  if (pSb[1] != 'B') {
    return 0;
  }
  if (pSb[2] != ' ') {
    return 0;
  }
  if (pSb[3] != ' ') {
    return 0;
  }
  return static_cast<u8>(pSb[4]) > 1;
}

// Inferred role: finds a package of the package table by its script binary; original name unknown.
unknown008 *vmPackageSearch(sSbHeader *pSb) {
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown00[i].unknown00 == pSb) {
      return &unknown017.unknown00[i];
    }
  }
  return 0;
}

int vmPackageSearchIdx(sSbHeader *pSb) {
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown00[i].unknown00 == pSb) {
      return i;
    }
  }
  return -1;
}

int vmPackageRegist(sSbHeader *pSb) {
  if (vmPackageSearch(pSb) != 0) {
    return 1;
  }
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown00[i].unknown00 == 0) {
      unknown017.unknown00[i].unknown00 = pSb;
      return 1;
    }
  }
  return 0;
}

int vmPluginModuleSearch(const char *mName) {
  for (int i = 0; i < 0x30; i++) {
    if (unknown017.unknownd410[i].unknown00 != 0 && strcmp(unknown017.unknownd410[i].unknown00, mName) == 0) {
      return 1;
    }
  }
  return 0;
}

int vmPluginSearch(const char *mName, const char *fName) {
  for (int i = 0; i < 0x30; i++) {
    if (unknown017.unknownd410[i].unknown00 != 0 && strcmp(unknown017.unknownd410[i].unknown00, mName) == 0) {
      unknown009 *pFunc = unknown017.unknownd410[i].unknown08;
      for (int j = 0; pFunc[j].unknown00 != 0; j++) {
        if (strcmp(pFunc[j].unknown00, fName) == 0) {
          return (i << 16) | j;
        }
      }
    }
  }
  return -1;
}

int vmOCSearch(const char *name) {
  for (int i = 0; i < 0x30; i++) {
    if (unknown017.unknownd710[i] != 0 && strcmp(unknown017.unknownd710[i]->unknown00, name) == 0) {
      return i;
    }
  }
  return -1;
}

char *vmSysAtrSearch(sSbHeader *pSb, int no) {
  u16 id = *reinterpret_cast<u16 *>(vmSysAtrPoolGet(pSb, no));
  if (id != 0xffff) {
    return vmIdPoolGet(pSb, id);
  }
  return 0;
}

char *vmUsrAtrSearch(sSbHeader *pSb, const char *name);

char *vmAttributeGet(unknown007 *pThread, const char *name) { return vmUsrAtrSearch(pThread->pSb, name); }

int vmThreadNextIdGet() {
  if (unknown017.unknown208 == -1) {
    unknown017.unknown208 = 0;
  }
  return unknown017.unknown208++;
}

unknown007 *vmThreadSearch(int id) {
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown310[i].pSb != 0 && unknown017.unknown310[i].unknown5c == id) {
      return &unknown017.unknown310[i];
    }
  }
  return 0;
}

int vmThreadIsAlive(int id) { return vmThreadSearch(id) != 0; }

int vmThreadRemove(int id);

int vmThreadEnd(int id) { return vmThreadRemove(id); }

int vmThreadRemove(int id) {
  unknown007 *pThread = vmThreadSearch(id);
  if (pThread == 0) {
    return 0;
  }
  pThread->pSb = 0;
  return 1;
}

int vmThreadSleep(int id) {
  unknown007 *pThread = vmThreadSearch(id);
  if (pThread == 0) {
    return 0;
  }
  pThread->unknown60 |= 0x80000000;
  return 1;
}

int vmThreadWakeup(int id) {
  unknown007 *pThread = vmThreadSearch(id);
  if (pThread == 0) {
    return 0;
  }
  pThread->unknown60 &= 0x7fffffff;
  return 1;
}

int vmThreadNumGet() {
  int num = 0;
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown310[i].pSb != 0) {
      num++;
    }
  }
  return num;
}

void vmThreadSleepAll(void *vm) {
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown310[i].pSb == vm) {
      unknown017.unknown310[i].unknown60 |= 0x80000000;
    }
  }
}

void vmThreadWakeupAll(void *vm) {
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown310[i].pSb == vm) {
      unknown017.unknown310[i].unknown60 &= 0x7fffffff;
    }
  }
}

int vmThreadIsFinish(void *vm) {
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown310[i].pSb == vm) {
      return 0;
    }
  }
  return 1;
}

int vmUnlink(void *vm) {
  unknown008 *pPackage = vmPackageSearch(static_cast<sSbHeader *>(vm));
  if (pPackage == 0) {
    return 0;
  }
  int package = vmPackageSearchIdx(static_cast<sSbHeader *>(vm));
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown310[i].unknown2c == package) {
      unknown017.unknown310[i].pSb = 0;
    }
  }
  pPackage->unknown00 = 0;
  return 1;
}

void vmSchedule() {
  int num = 0;
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown310[i].pSb != 0) {
      unknown017.unknown210[num++] = &unknown017.unknown310[i];
    }
  }
  for (int i = num; i < 32; i++) {
    unknown017.unknown210[i] = 0;
  }
}

void vmThreadExec(unknown007 *pThread) {
  if (vmCodeExecSub(pThread) == 3) {
    vmThreadRemove(pThread->unknown5c);
  }
}

void vmExec() {
  vmSchedule();
  unknown017.unknown200 = 0;
  for (int i = 0; i < 32; i++) {
    unknown007 *pThread = unknown017.unknown210[i];
    if (pThread != 0 && pThread->pSb != 0 && pThread->unknown60 < 0x80000000) {
      unknown017.unknown200 = pThread;
      vmThreadExec(pThread);
    }
  }
}

unknown007 *vmThreadCreate(sSbHeader *pSb, int func);

void vmStart(void *vm) {
  sSbHeader *pSb = static_cast<sSbHeader *>(vm);
  vmThreadCreate(pSb, VM_OFFSET(sSbCode, pSb, pSb->codeOfs)->unknown04);
  vmSysAtrSearch(pSb, 0);
}

sSbHeader *vmThreadSBGet(const char *name) {
  for (int i = 0; i < 32; i++) {
    sSbHeader *pSb = unknown017.unknown00[i].unknown00;
    if (pSb != 0) {
      char *id = vmSysAtrSearch(pSb, 0);
      if (id != 0 && strcmp(id, name) == 0) {
        return pSb;
      }
    }
  }
  return 0;
}

void vmArgErr();

u8 vmArrayLocalChk(unknown004 *pData) {
  if (pData->unknown00 == 6) {
    return static_cast<u32>(pData->unknown04) >> 31;
  }
  return 0;
}

void splitFixed(float value, int *sign, int *integer, int *fraction) {
  *sign = value < 0.0 ? -1 : 0;
  *integer = static_cast<int>(value);
  *fraction = static_cast<int>((value - static_cast<float>(*integer)) * 1000.0f);
}

int vmArgBoolGet(unknown007 *pThread, unknown004 *pData) {
  u8 type = pData->unknown00;
  if (type != 1 && type != 2) {
    vmArgErr();
  }
  return type != 2;
}

int vmArgIntGet(unknown007 *pThread, unknown004 *pData) {
  if (pData->unknown00 != 3) {
    if (pData->unknown00 == 4) {
      return pData->unknown04_1;
    }
    vmArgErr();
  }
  return pData->unknown04;
}

f32 vmArgFixedGet(unknown007 *pThread, unknown004 *pData) {
  if (pData->unknown00 != 4) {
    if (pData->unknown00 == 3) {
      return pData->unknown04;
    }
    vmArgErr();
  }
  return pData->unknown04_1;
}

const char *vmArgStringGet(unknown007 *pThread, unknown004 *pData) {
  if (pData->unknown00 != 5) {
    vmArgErr();
  }
  return pData->unknown04_2;
}

unknown004 *vmArgArrayGet(unknown007 *pThread, unknown004 *pData) {
  if (pData->unknown00 != 6) {
    vmArgErr();
  }
  return pData;
}

unknown004 *vmArgOCGet(unknown007 *pThread, unknown004 *pData) {
  if (pData->unknown00 != 9) {
    vmArgErr();
  }
  return pData;
}

int vmArgOmitChk(unknown007 *pThread, int no) {
  u8 cnt = vmArgCntGet(pThread);
  if (no == 0) {
    vmHalt();
  }
  if (cnt < no) {
    return 1;
  }
  return pThread->unknown50[pThread->reg.sp - no - 1].unknown00 == 0;
}

int vmPropertySearch(unknown013 *pOC, const char *name) {
  int len = strlen(name);
  unknown011 *pProperty = pOC->unknown10;
  if (pProperty != 0) {
    for (int i = 0; pProperty->unknown00 != 0; i++, pProperty++) {
      if (len == pProperty->unknown18 && strcmp(name, pProperty->unknown00) == 0) {
        return i;
      }
    }
  }
  return -1;
}

int vmSelectorSearch(unknown013 *pOC, const char *name) {
  int len = strlen(name);
  unknown012 *pSelector = pOC->unknown18;
  if (pSelector != 0) {
    for (int i = 0; pSelector->unknown00 != 0; i++, pSelector++) {
      if (len == pSelector->unknown10 && strcmp(name, pSelector->unknown00) == 0) {
        return i;
      }
    }
  }
  return -1;
}

void vmBuiltinOCRegist(unknown013 *pOC) {
  unknown012 *pSelector = pOC->unknown18;
  if (pSelector != 0) {
    for (; pSelector->unknown00 != 0; pSelector++) {
      pSelector->unknown10 = strlen(pSelector->unknown00);
    }
  }
  unknown017.unknownd890 = pOC;
}

#line 636
int vmOCRegist(unknown013 *pOC) {
  VM_ASSERT_TEXT(pOC != 0, "pOC != ((void*)0)");
  if (vmOCSearch(pOC->unknown00) != -1) {
    return 1;
  }
  for (int i = 0; i < 0x30; i++) {
    if (unknown017.unknownd710[i] == 0) {
      unknown017.unknownd710[i] = pOC;
      unknown011 *pProperty = pOC->unknown10;
      if (pProperty != 0) {
        for (; pProperty->unknown00 != 0; pProperty++) {
          pProperty->unknown18 = strlen(pProperty->unknown00);
        }
      }
      unknown012 *pSelector = pOC->unknown18;
      if (pSelector != 0) {
        for (; pSelector->unknown00 != 0; pSelector++) {
          pSelector->unknown10 = strlen(pSelector->unknown00);
        }
      }
      return 1;
    }
  }
  return 0;
}

const char *vmOCNameGet(unknown004 *pData) {
  if (pData->unknown00 != 9) {
    vmHalt();
  }
  return unknown017.unknownd710[pData->unknown02]->unknown00;
}

unknown004 *vmArgPtrGet(unknown007 *pThread, int no) {
  u8 cnt = vmArgCntGet(pThread);
  if (no == 0 || cnt < no) {
    vmHalt();
  }
  return &pThread->unknown50[pThread->reg.sp - no - 1];
}

int vmArgFunctionGet(unknown007 *pThread, unknown004 *pData) {
  if (pData->unknown00 != 7) {
    vmArgErr();
  }
  return (pData->unknown02 << 16) | (pData->unknown04 & 0xffff);
}

// Decision 2026-11-14 #16: `package` and `function` place the `add` of the package index before the `sbfiz`
// (0x71007883c4); with both expressions written in the call, or with `package` alone, the `add` comes after the `sbfiz`
// (20 instructions); with `function` alone it is 21. The game never reads its first argument.
int vmThreadGetOC(void *vm, int func, int *id) {
  int package = func >> 16;
  int function = func & 0xffff;
  unknown007 *pThread = vmThreadCreate(unknown017.unknown00[package].unknown00, function);
  if (pThread == 0) {
    return 0;
  }
  pThread->unknown60 |= 0x80000000;
  *id = pThread->unknown5c;
  return 1;
}

char *vmUsrAtrSearch(sSbHeader *pSb, const char *name) {
  unknown001 *pAtr = VM_OFFSET(unknown001, pSb, pSb->unknown38);
  for (int i = 0; i < pAtr->num; i++) {
    char *id = vmIdPoolGet(pSb, *reinterpret_cast<u16 *>(vmUsrAtrPoolGet(pSb, i)));
    if (strcmp(name, id) == 0) {
      return id;
    }
  }
  return 0;
}

int vmFuncFarSearch(const char *mName, const char *fName) {
  for (int i = 0; i < 32; i++) {
    if (unknown017.unknown00[i].unknown08 != 0 && strcmp(unknown017.unknown00[i].unknown08, mName) == 0) {
      sSbHeader *pSb = unknown017.unknown00[i].unknown00;
      unknown001 *pFunc = VM_OFFSET(unknown001, pSb, pSb->unknown1c);
      unknown003 *pEntry = VM_OFFSET(unknown003, pFunc, pFunc->unknown00);
      for (int j = 0; j < pFunc->num; pEntry++, j++) {
        if (strcmp(vmIdPoolGet(pSb, pEntry->unknown00), fName) == 0) {
          return (i << 16) | j;
        }
      }
      return -1;
    }
  }
  return -1;
}

unknown007 *vmThreadCreate(sSbHeader *pSb, int func) {
  for (int idx = 0; idx < 32; idx++) {
    if (unknown017.unknown310[idx].pSb == 0) {
      unknown007 *pThread = &unknown017.unknown310[idx];
      for (int i = 0; i < 32; i++) {
        if (unknown017.unknown210[i] == 0) {
          unknown017.unknown210[i] = pThread;
          break;
        }
      }
      pThread->reg.pc = vmFunctionPoolGet(pSb, func)->unknown0c;
      pThread->reg.sp = 0;
      pThread->reg.unknown08 = 0;
      pThread->unknown0c = 0;
      pThread->unknown10 = 0;
      int package = vmPackageSearchIdx(pSb);
      pThread->unknown2c = package;
      pThread->unknown30 = func;
      pThread->unknown34 = package;
      pThread->pSb = pSb;
      sSbCode *pCode = VM_OFFSET(sSbCode, pSb, pSb->codeOfs);
      pThread->unknown40 = VM_OFFSET(const u8, pCode, pCode->unknown00);
      unknown002 *pStatic = VM_OFFSET(unknown002, pSb, pSb->unknown2c);
      pThread->unknown48 = VM_OFFSET(unknown004, pStatic, pStatic->unknown00);
      pThread->unknown50 = unknown017.unknown1410[idx];
      pThread->stackSize = 0x80;
      pThread->unknown5c = vmThreadNextIdGet();
      pThread->unknown60 = 0;
      pThread->unknown64 = 0;
      pThread->unknown66 = 0;
      pThread->unknown68[0] = 0;
      pThread->unknown68[1] = 0;
      pThread->unknown68[2] = 0;
      pThread->unknown80 = 0;
      return pThread;
    }
  }
  return 0;
}
}
