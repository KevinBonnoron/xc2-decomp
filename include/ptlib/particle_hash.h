#pragma once
#include <stddef.h>

#include "types.h"

namespace ptlib {

namespace emitter {
class EmitterObj;
} // namespace emitter

class HashManager {
public:
  static const u32 TABLE_MAX = 4000;

  struct unknown001 {
    const char *unknown00; // Inferred role: name; original member name unknown.
    u32 unknown08;         // Inferred role: hash; original member name unknown.
    u8 _0c[0x10 - 0x0c];
  };

  struct unknown002 {
    u32 unknown00; // Inferred role: hash; original member name unknown.
    int unknown04; // Inferred role: dead value; original member name unknown.
  };

  static void init();
  static void term();
  void build(emitter::EmitterObj *emitter);
  static HashManager *get();
  static HashManager *&getPtr();
  static bool isValid();
  void reset();
  void add_core(u32 hash, const char *name);
  void addDead(u32 hash, int value);
  void add(u32 hash);
  bool check(u32 hash);
  u32 check_core(u32 hash);
  u32 get_create_key();
  void dump();
  int searchDead(u32 hash);

  unknown001 unknown00[TABLE_MAX];
  unknown002 unknownfa00[TABLE_MAX];
  u32 unknown17700; // Inferred role: dead count; original member name unknown.
  u32 unknown17704; // Inferred role: table count; original member name unknown.
  u32 unknown17708; // Inferred role: next create key; original member name unknown.
  u8 _1770c[0x17710 - 0x1770c];
};

static_assert(offsetof(HashManager, unknownfa00) == 0xfa00, "");
static_assert(offsetof(HashManager, unknown17700) == 0x17700, "");
static_assert(offsetof(HashManager, unknown17704) == 0x17704, "");
static_assert(offsetof(HashManager, unknown17708) == 0x17708, "");
static_assert(sizeof(HashManager) == 0x17710, "");

} // namespace ptlib
