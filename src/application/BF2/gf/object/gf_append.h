#pragma once
#include <stddef.h>

#include "gf/game/gf_game_mount.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GF_OBJ_HANDLE;

class GfAppend {
public:
  static const u32 MOUNT_MAX = 4;

  struct MOUNT_INFO {
    mm::mtl::FixStr<16> unknown00; // Inferred role: bone; original member name unknown.
    OPTMNT unknown14;              // Inferred role: mount; original member name unknown.
  };

  GfAppend();
  GfAppend(const char *modelName, const char *motionName, u16 mountIndex, u16 rscID, f32 scale, bool multiMount);
  const char *getBone(OPTMNT mount) const;
  void addMount(MOUNT_INFO &info);
  const char *getModelName() const;
  const char *getMotionName() const;
  const char *getResourceName() const;
  const char *getAsmFileName() const;
  u16 getMountIndex() const;
  u16 getRscID() const;

  mm::mtl::FixedVector<MOUNT_INFO, MOUNT_MAX> unknown00; // Inferred role: mounts; original member name unknown.
  const char *m_modelName;
  const char *m_motionName;
  u16 m_mountIndex;
  u16 m_rscID;
  f32 unknown7c;  // Inferred role: scale; original member name unknown.
  bool unknown80; // Inferred role: multi mount; original member name unknown.
};

static_assert(sizeof(GfAppend::MOUNT_INFO) == 0x18, "");
static_assert(offsetof(GfAppend, m_modelName) == 0x68, "");
static_assert(offsetof(GfAppend, m_motionName) == 0x70, "");
static_assert(offsetof(GfAppend, m_mountIndex) == 0x78, "");
static_assert(offsetof(GfAppend, m_rscID) == 0x7a, "");
static_assert(offsetof(GfAppend, unknown7c) == 0x7c, "");
static_assert(offsetof(GfAppend, unknown80) == 0x80, "");
static_assert(sizeof(GfAppend) == 0x88, "");

class GfAppendWire {
public:
  GfAppendWire(GF_OBJ_HANDLE *wire, GF_OBJ_HANDLE *owner);
  void endWire(f32 time);
  ~GfAppendWire();
  void startWire(GF_OBJ_HANDLE *target, f32 time);
  void startWireWithClose(GF_OBJ_HANDLE *target, f32 time, f32 closeTime, f32 closeDistance);
  void startWireWithBone(GF_OBJ_HANDLE *target, const char *bone, f32 time);
  void update(const fw::UpdateInfo &info);

  GF_OBJ_HANDLE *unknown00; // Inferred role: wire; original member name unknown.
  GF_OBJ_HANDLE *unknown08; // Inferred role: owner; original member name unknown.
  u8 _10[0x50 - 0x10];
};

static_assert(offsetof(GfAppendWire, unknown08) == 0x08, "");
static_assert(sizeof(GfAppendWire) == 0x50, "");

} // namespace gf
