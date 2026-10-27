#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrMdoCtlNom;

class DrMdoNomAfterImage {
public:
  struct wrkObjList {
    f32 unknown00[3]; // Inferred role: captured position; original member name unknown.
    u8 _0c[0x10 - 0x0c];
    DrMdoCtlNom *unknown10; // Inferred role: cloned model; original member name unknown.
    f32 unknown18;          // Inferred role: age; original member name unknown.
    u8 _1c[0x20 - 0x1c];
  };

  DrMdoNomAfterImage();
  ~DrMdoNomAfterImage();
  void release();
  u32 isReleaseCall() const;
  void releaseCall();

  wrkObjList *unknown00; // Inferred role: captured models; original member name unknown.
  s16 unknown08;         // Inferred role: captured model count; original member name unknown.
  s16 unknown0a;         // Inferred role: next capture index; original member name unknown.
  u8 _0c[0x20 - 0x0c];
  u32 unknown20; // Inferred role: release flags; original member name unknown.
  u8 _24[0x54 - 0x24];
  bool unknown54; // Inferred role: unknown flag cleared by the constructor; original member name unknown.
  u8 _55[0xd4 - 0x55];
  s32 unknownd4; // Inferred role: unknown value cleared by the constructor; original member name unknown.
};

static_assert(sizeof(DrMdoNomAfterImage::wrkObjList) == 0x20, "");
static_assert(offsetof(DrMdoNomAfterImage::wrkObjList, unknown10) == 0x10, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown08) == 0x08, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown0a) == 0x0a, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown20) == 0x20, "");
static_assert(offsetof(DrMdoNomAfterImage, unknown54) == 0x54, "");
static_assert(offsetof(DrMdoNomAfterImage, unknownd4) == 0xd4, "");

} // namespace ml
