#pragma once
#include "mm_mtl/bitflag.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct GfSetupParam;

struct GameFlag {
  mm::mtl::BitFlag<0x10000> oneBitFlags;
  u32 twoBitFlags[0x1000];
  u32 fourBitFlags[0x400];
  u8 byteFlags[0x2000];
  u16 shortFlags[0xc00];
  u32 wordFlags[0xd08];
};

static_assert(offsetof(GameFlag, twoBitFlags) == 0x2000, "");
static_assert(offsetof(GameFlag, fourBitFlags) == 0x6000, "");
static_assert(offsetof(GameFlag, byteFlags) == 0x7000, "");
static_assert(offsetof(GameFlag, shortFlags) == 0x9000, "");
static_assert(offsetof(GameFlag, wordFlags) == 0xa800, "");
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
