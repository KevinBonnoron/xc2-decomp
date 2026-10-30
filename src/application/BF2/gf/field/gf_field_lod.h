#pragma once
#include <stddef.h>

#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace mm {
struct Mat44;
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GfSetupParam;

class GfFieldLod : public mm::mtl::PtrSingleton<GfFieldLod> {
public:
  struct unknown001 {
    u8 _00[0x04];
    f32 unknown04; // Inferred role: fade in speed; original member name unknown.
    f32 unknown08; // Inferred role: fade out speed; original member name unknown.
  };

  int findBdatIdByLodId(u16 lodId) const;
  const unknown001 *findBdatInfo(int bdatId) const;
  bool isAnimReverse(int bdatId) const;
  bool isPlayAnimEnd(int bdatId) const;
  void setFade(int bdatId, bool isFadeIn, bool isImmediate);
  void setLodSwitchId(int bdatId, u32 switchId);
  bool setAnimReverse(int bdatId, bool isReverse, bool isSkip);
  bool isFadeOut(int bdatId) const;
  bool findTransform(mm::Mat44 &matrix, int bdatId) const;
  void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  void gevPlayEvent(GEV event, u32 value);
  static bool isAnimReverseOfInit(int bdatId);
  static bool isVisibleOfInit(int bdatId);
  static void validateByInitData();
  static void build(const GfSetupParam &param);
  static void destroy();
  static void update(const fw::UpdateInfo &info);

  u16 unknown08[0x400]; // Inferred role: lod id of each bdat entry; original member name unknown.
  int unknown808;       // Inferred role: first bdat id; original member name unknown.
  bool unknown80c;      // Inferred role: lod data ready; original member name unknown.
  u8 _80d[0x840 - 0x80d];
  void *unknown840; // Role and original member name unknown.
  u8 _848[0x850 - 0x848];
  void *unknown850; // Role and original member name unknown.
};

static_assert(offsetof(GfFieldLod, unknown808) == 0x808, "");
static_assert(offsetof(GfFieldLod, unknown80c) == 0x80c, "");
static_assert(offsetof(GfFieldLod, unknown840) == 0x840, "");
static_assert(offsetof(GfFieldLod, unknown850) == 0x850, "");

} // namespace gf
