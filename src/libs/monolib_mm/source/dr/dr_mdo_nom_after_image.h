#pragma once
#include <stddef.h>

#include "dr/dr_mdo_nom_clone.h"
#include "mm_math/mm_col3.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace ml {
class DrMdoCtlNom;

class DrMdoNomAfterImage : public DrMdoNomClone {
public:
  struct wrkObjList {
    mm::Vec3 unknown00;     // Inferred role: captured position; original member name unknown.
    DrMdoCtlNom *unknown10; // Inferred role: cloned model; original member name unknown.
    f32 unknown18;          // Inferred role: age; original member name unknown.
    u8 _1c[0x20 - 0x1c];
  };

  DrMdoNomAfterImage();
  ~DrMdoNomAfterImage();
  void release();
  u32 isReleaseCall() const;
  void update(const DrMdoCtlNom *model, f32 delta);
  void releaseCall();
  void create(const DrMdoCtlNom *model, f32 span, f32 life, f32 fade, const mm::Col3 &headColor, f32 headPower, f32 headBlackRatio, f32 headEmissive, const mm::Col3 &tailColor, f32 tailPower,
              f32 tailBlackRatio, f32 tailEmissive);
  void updateParam(wrkObjList *obj, const DrMdoCtlNom *model, f32 delta, const mm::Vec3 &position);
  void captureObj(const DrMdoCtlNom *model);

  wrkObjList *unknown00;          // Inferred role: captured models; original member name unknown.
  s16 unknown08;                  // Inferred role: captured model count; original member name unknown.
  s16 unknown0a;                  // Inferred role: next capture index; original member name unknown.
  f32 unknown0c;                  // Inferred role: capture span; original member name unknown.
  f32 unknown10;                  // Inferred role: time since the last capture; original member name unknown.
  f32 unknown14;                  // Inferred role: age at which the fade starts; original member name unknown.
  f32 unknown18;                  // Inferred role: life; original member name unknown.
  f32 unknown1c;                  // Inferred role: unknown value set to 5 by create; original member name unknown.
  u32 unknown20;                  // Inferred role: release flags; original member name unknown.
  mm::Col3 unknown24;             // Inferred role: rim bloom color of a new capture; original member name unknown.
  f32 unknown30;                  // Inferred role: rim bloom power of a new capture; original member name unknown.
  f32 unknown34;                  // Inferred role: rim bloom black ratio of a new capture; original member name unknown.
  f32 unknown38;                  // Inferred role: rim bloom emissive of a new capture; original member name unknown.
  mm::Col3 unknown3c;             // Inferred role: rim bloom color at the end of the life; original member name unknown.
  f32 unknown48;                  // Inferred role: rim bloom power at the end of the life; original member name unknown.
  f32 unknown4c;                  // Inferred role: rim bloom black ratio at the end of the life; original member name unknown.
  f32 unknown50;                  // Inferred role: rim bloom emissive at the end of the life; original member name unknown.
  mm::mtl::FixStr<128> unknown54; // Inferred role: model path; original member name unknown.
};

static_assert(sizeof(DrMdoNomAfterImage::wrkObjList) == 0x20, "");
static_assert(offsetof(DrMdoNomAfterImage::wrkObjList, unknown10) == 0x10, "");
static_assert(offsetof(DrMdoNomAfterImage::wrkObjList, unknown18) == 0x18, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown0a) == 0x0a, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown0c) == 0x0c, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown14) == 0x14, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown20) == 0x20, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown24) == 0x24, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown30) == 0x30, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown3c) == 0x3c, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown48) == 0x48, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown54) == 0x54, "");
static_assert(sizeof(DrMdoNomAfterImage) == 0xd8, "");

} // namespace ml
