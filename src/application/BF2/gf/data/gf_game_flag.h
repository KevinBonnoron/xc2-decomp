#pragma once
#include "mm_mtl/bitflag.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GfSetupParam;

enum {
  FLAG_SALVAGER_POINT = 0x854,
  FLAG_GAME_CLEAR = 0xbdcd,
};

struct GameFlag {
  mm::mtl::unknown027<0x10000> unknown00; // Inferred role: one bit flags; original member name unknown.
  u32 unknown2000[0x1000];                // Inferred role: two bit flags; original member name unknown.
  u32 unknown6000[0x400];                 // Inferred role: four bit flags; original member name unknown.
  u8 unknown7000[0x2000];                 // Inferred role: byte flags; original member name unknown.
  u16 unknown9000[0xc00];                 // Inferred role: short flags; original member name unknown.
  u32 unknowna800[0xd08];                 // Inferred role: word flags; original member name unknown.
};

static_assert(offsetof(GameFlag, unknown2000) == 0x2000, "");
static_assert(offsetof(GameFlag, unknown6000) == 0x6000, "");
static_assert(offsetof(GameFlag, unknown7000) == 0x7000, "");
static_assert(offsetof(GameFlag, unknown9000) == 0x9000, "");
static_assert(offsetof(GameFlag, unknowna800) == 0xa800, "");
static_assert(sizeof(GameFlag) == 0xdc20, "");

class GfGameFlag : public mm::mtl::PtrSingleton<GfGameFlag> {
public:
  GfGameFlag(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGameFlag();

  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();

  static void setLocal(u32 size, int index, u32 value);
  static u32 getLocal(const GameFlag &gameFlag, u32 size, int index);
  static void setLocal(GameFlag &gameFlag, u32 size, int index, u32 value);
  void sendCallback(u32 size, u32 index, u32 value, u32 oldValue);
  static u32 getLocal(u32 size, int index);

  static void getFlagInfo(int flag, u32 &size, u32 &index);
  static void setFlag(int flag, u32 value);
  static u32 getFlag(int flag);
  static u32 getMaxFlag(int size);
  static void clear();

private:
  bool mInitialized;
};

} // namespace gf
