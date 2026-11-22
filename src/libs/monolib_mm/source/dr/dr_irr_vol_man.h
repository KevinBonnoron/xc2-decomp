#pragma once
#include "dr/dr_irr_vol_allocator.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace mm {
struct Aabb;
} // namespace mm

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrMan;

namespace irrvol {
class DrIrrVolCascade;
struct SGlobalInfo;
} // namespace irrvol

class DrIrrVolMan {
public:
  DrIrrVolMan(DrMan *drMan);
  ~DrIrrVolMan();
  void release();
  void create(void *data, const char *name);
  bool isValid() const;
  void tail();
  void update();
  void createResources();
  void updateIrrVol(bool);
  int getSectorMax(u32 index) const;
  void getVolumeArea(u32 cascade, mm::Aabb &area) const;
  void debugRender();
  grlib::CGLibTextureBuffer *getIrrVolTex(u32 cascade, u32 index) const;
  const mm::Vec3 &getIrrVolUVScale(u32 cascade) const;
  const mm::Vec3 &getUVPerPixl(u32 cascade) const;
  const mm::Vec3 &getIrrVolEyeOffset(u32 cascade) const;
  const mm::Vec3 &getIrrVolUVOffset(u32 cascade) const;

  DrMan *m_drMan;                 // Inferred role: dr man; original member name unknown.
  irrvol::SGlobalInfo *unknown08; // Inferred role: setting; original member name unknown.
  mm::mtl::FixStr<128> unknown10; // Inferred role: resource name; original member name unknown.
  u8 _094[0x098 - 0x094];
  irrvol::DrIrrVolCascade **unknown98;                     // Inferred role: cascades; original member name unknown.
  irrvol::MemHandlebaseAllocator m_memHandlebaseAllocator; // Inferred role: allocator; original member name unknown.
  f32 unknown0b0;                                          // Inferred role: update position along z; original member name unknown.
  u32 unknown0b4;                                          // Inferred role: double buffer flag; original member name unknown.
  u8 _0b8[0x190 - 0x0b8];
  mm::Vec3 unknown190;        // Inferred role: request center pos; original member name unknown.
  mm::Vec3 m_irrVolCenterPos; // Inferred role: center pos; named after the game accessor ml::ScnRenderDrSysParmAcc::getIrrVolCenterPos.
  f32 unknown1b0;             // Inferred role: request scale; original member name unknown.
  f32 unknown1b4;             // Inferred role: scale; original member name unknown.
  f32 unknown1b8;             // Inferred role: request offset; original member name unknown.
  f32 unknown1bc;             // Inferred role: offset; original member name unknown.
  u32 unknown1c0;             // Inferred role: request cascade num; original member name unknown.
  u32 unknown1c4;             // Inferred role: cascade num; original member name unknown.
  bool unknown1c8;            // Inferred role: flag; original member name unknown.
  bool unknown1c9;            // Inferred role: debug draw flag; original member name unknown.
};

static_assert(offsetof(DrIrrVolMan, m_drMan) == 0x000, "");
static_assert(offsetof(DrIrrVolMan, unknown08) == 0x008, "");
static_assert(offsetof(DrIrrVolMan, unknown98) == 0x098, "");
static_assert(offsetof(DrIrrVolMan, m_memHandlebaseAllocator) == 0x0a0, "");
static_assert(offsetof(DrIrrVolMan, unknown0b0) == 0x0b0, "");
static_assert(offsetof(DrIrrVolMan, unknown0b4) == 0x0b4, "");
static_assert(offsetof(DrIrrVolMan, unknown190) == 0x190, "");
static_assert(offsetof(DrIrrVolMan, m_irrVolCenterPos) == 0x1a0, "");
static_assert(offsetof(DrIrrVolMan, unknown1b0) == 0x1b0, "");
static_assert(offsetof(DrIrrVolMan, unknown1c0) == 0x1c0, "");
static_assert(offsetof(DrIrrVolMan, unknown1c4) == 0x1c4, "");
static_assert(offsetof(DrIrrVolMan, unknown1c8) == 0x1c8, "");
static_assert(offsetof(DrIrrVolMan, unknown1c9) == 0x1c9, "");

} // namespace ml
