#pragma once
#include <stddef.h>

#include "gf/game/gf_game_mount.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;

class GfAppend {
public:
  static const u32 MOUNT_MAX = 4;

  struct MOUNT_INFO {
    mm::mtl::FixStr<16> bone;
    OPTMNT mount;
  };

  GfAppend();
  const char *getBone(OPTMNT mount) const;
  void addMount(MOUNT_INFO &info);
  const char *getModelName() const;
  const char *getMotionName() const;
  const char *getResourceName() const;
  const char *getAsmFileName() const;
  u16 getMountIndex() const;
  u16 getRscID() const;

  mm::mtl::FixedVector<MOUNT_INFO, MOUNT_MAX> mounts;
  const char *modelName;
  const char *motionName;
  u16 mountIndex;
  u16 rscId;
  f32 scale;
  bool isMultiMount;
};

static_assert(sizeof(GfAppend::MOUNT_INFO) == 0x18, "");
static_assert(offsetof(GfAppend, modelName) == 0x68, "");
static_assert(offsetof(GfAppend, motionName) == 0x70, "");
static_assert(offsetof(GfAppend, mountIndex) == 0x78, "");
static_assert(offsetof(GfAppend, rscId) == 0x7a, "");
static_assert(offsetof(GfAppend, scale) == 0x7c, "");
static_assert(offsetof(GfAppend, isMultiMount) == 0x80, "");
static_assert(sizeof(GfAppend) == 0x88, "");

class GfAppendWire {
public:
  void startWire(GF_OBJ_HANDLE *target, f32 time);
  void startWireWithClose(GF_OBJ_HANDLE *target, f32 time, f32 closeTime, f32 closeDistance);
  void startWireWithBone(GF_OBJ_HANDLE *target, const char *bone, f32 time);
  void endWire(f32 time);
};

} // namespace gf
