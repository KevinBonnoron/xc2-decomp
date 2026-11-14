#pragma once
#include "gf/object/gf_obj_handle.h"
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
struct Message;
class MessageObject;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
enum OPTMNT : u32;

class GfAppend {
public:
  static const u32 MOUNT_UNKNOWN_4 = 4; // Inferred role: mount max; original name unknown.

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

  mm::mtl::FixedVector<MOUNT_INFO, MOUNT_UNKNOWN_4> unknown00; // Inferred role: mounts; original member name unknown.
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

class GfAppendHandles {
public:
  GfAppendHandles() : unknowna8(false) {
    unknown08.assign(unknown020);
    unknown58.assign(unknown020);
  }
  virtual ~GfAppendHandles() {}
  void destroy();
  void destroy(mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> &handles);
  void eraseHandle(GF_OBJ_HANDLE *handle);
  void eraseHandle(mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> &handles, GF_OBJ_HANDLE *handle);
  void sendMessage(fw::MessageObject *sender, fw::Message &message) const;
  void setAlpha(f32 alpha);

  const mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> &getCurrentHandles() const { return unknowna8 ? unknown58 : unknown08; }

  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> unknown08; // Inferred role: handles; original member name unknown.
  mm::mtl::FixedArray<GF_OBJ_HANDLE *, 10> unknown58; // Inferred role: alternate handles; original member name unknown.
  bool unknowna8;                                     // Inferred role: selects the alternate handles; original member name unknown.
};

static_assert(offsetof(GfAppendHandles, unknown08) == 0x08, "");
static_assert(offsetof(GfAppendHandles, unknown58) == 0x58, "");
static_assert(offsetof(GfAppendHandles, unknowna8) == 0xa8, "");
static_assert(sizeof(GfAppendHandles) == 0xb0, "");

class GfAppendWire {
public:
  GfAppendWire(GF_OBJ_HANDLE *wire, GF_OBJ_HANDLE *owner);
  void endWire(f32 time);
  ~GfAppendWire();
  void startWire(GF_OBJ_HANDLE *target, f32 time);
  void startWireWithClose(GF_OBJ_HANDLE *target, f32 time, f32 closeTime, f32 closeDistance);
  void startWireWithBone(GF_OBJ_HANDLE *target, const char *bone, f32 time);
  void checkAndSetupSalvagePoint();
  void update(const fw::UpdateInfo &info);
  static GF_OBJ_HANDLE *getWireObject(GF_OBJ_HANDLE *handle);

  GF_OBJ_HANDLE *unknown00; // Inferred role: wire; original member name unknown.
  GF_OBJ_HANDLE *unknown08; // Inferred role: owner; original member name unknown.
  u8 _10[0x18 - 0x10];
  GF_OBJ_HANDLE *unknown18; // Inferred role: target; original member name unknown.
  mm::Vec3 unknown20;       // Inferred role: target position; original member name unknown.
  s16 unknown30;            // Inferred role: target bone; original member name unknown.
  u8 _32[0x34 - 0x32];
  s32 unknown34;  // Inferred role: state; original member name unknown.
  f32 unknown38;  // Inferred role: elapsed time; original member name unknown.
  f32 unknown3c;  // Inferred role: duration; original member name unknown.
  f32 unknown40;  // Inferred role: close time; original member name unknown.
  f32 unknown44;  // Inferred role: close distance; original member name unknown.
  bool unknown48; // Inferred role: keeps the position; original member name unknown.
  u8 _49[0x50 - 0x49];
};

static_assert(offsetof(GfAppendWire, unknown08) == 0x08, "");
static_assert(offsetof(GfAppendWire, unknown18) == 0x18, "");
static_assert(offsetof(GfAppendWire, unknown20) == 0x20, "");
static_assert(offsetof(GfAppendWire, unknown30) == 0x30, "");
static_assert(offsetof(GfAppendWire, unknown34) == 0x34, "");
static_assert(offsetof(GfAppendWire, unknown48) == 0x48, "");
static_assert(sizeof(GfAppendWire) == 0x50, "");

} // namespace gf
