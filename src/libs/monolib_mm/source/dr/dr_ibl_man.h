#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_list.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace ml {

class DrIBLObj;
class DrMan;

class DrIBLMan {
public:
  DrIBLMan(DrMan *man, int index);
  ~DrIBLMan();
  DrIBLObj *createObj(const void *data);
  bool isValid() const;
  void releaseObj(DrIBLObj *obj);
  void update();
  grlib::CGLibTextureBuffer *debug_getAlbedoTexture(u32 index) const;
  grlib::CGLibTextureBuffer *debug_getNormalTexture(u32 index) const;

  grlib::CGLibTextureBuffer *getAlbedoTexture() const;
  grlib::CGLibTextureBuffer *getNormalTexture() const;
  DrMan *unknown00; // Inferred role: owner; original member name unknown.
  int unknown08;    // Inferred role: constructor argument; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  mm::mtl::FixedList<DrIBLObj *, 32> unknown10;     // Inferred role: IBL objects; original member name unknown.
  mm::mtl::FixedList<DrIBLObj *, 32> unknown250[2]; // Inferred role: IBL objects stocked per double buffer; original member name unknown.
  mm::mtl::FixedList<DrIBLObj *, 32> unknown6d0;    // Inferred role: IBL objects; original member name unknown.
  u8 _910[0x910 - 0x910];
  DrIBLObj *unknown910; // Inferred role: current IBL object; original member name unknown.
};
static_assert(offsetof(DrIBLMan, unknown10) == 0x10, "");
static_assert(offsetof(DrIBLMan, unknown250) == 0x250, "");
static_assert(offsetof(DrIBLMan, unknown6d0) == 0x6d0, "");
static_assert(offsetof(DrIBLMan, unknown910) == 0x910, "");

} // namespace ml
