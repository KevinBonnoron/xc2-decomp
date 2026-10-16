#pragma once
#include "mm_mtl/vector.h"
#include "types.h"

namespace gmk {

class GmkNpcIdInfo;

class GmkNpcManager {
public:
  explicit GmkNpcManager(u32 updateNpcNumPerFrame);
  virtual ~GmkNpcManager();

  void create();
  void setUpdateNpcNumPerFrame(u32 num) { updateNpcNumPerFrame = num; }

private:
  mm::mtl::Vector<GmkNpcIdInfo> npcIdInfos;
  u8 _30[0x34 - 0x30];
  u32 updateNpcNumPerFrame;
  u32 updateNpcIndex;
  u8 _3c[0x40 - 0x3c];
};

static_assert(sizeof(GmkNpcManager) == 0x40, "");

} // namespace gmk
