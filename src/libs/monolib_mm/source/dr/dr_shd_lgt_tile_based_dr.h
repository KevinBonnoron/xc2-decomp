#pragma once
#include <stddef.h>

#include "dr/dr_shd_lgt_dynamic.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_uniform_array.h"
#include "types.h"

namespace ml {
class DrMan;

class DrShdLgtTileBasedDr : public DrShdLgtDynamic {
public:
  // Inferred role: view info; original type name unknown.
  struct unknown001 {
    grlib::CGLibDblUniformBlock unknown00;                           // Inferred role: pnt light; original member name unknown.
    grlib::CGLibDblUniformBlock unknown38;                           // Inferred role: spt light; original member name unknown.
    grlib::CGLibDblUniformBlock unknown70;                           // Inferred role: param; original member name unknown.
    grlib::CGLibUniformArray<grlib::CGLibDblUniformBlock> unknowna8; // Inferred role: tile uniforms; original member name unknown.
    s32 unknownd0;                                                   // Inferred role: pnt light count; original member name unknown.
    s32 unknownd4;                                                   // Inferred role: spt light count; original member name unknown.
  };

  DrShdLgtTileBasedDr(DrMan *drMan);
  ~DrShdLgtTileBasedDr() override;
  void createWork();
  void stockBegin() override;
  void update() override;
  void addViewInfo(int cate) override;
  void delViewInfo(int cate) override;
  void stockPntList(DrLightObjPnt *light) override;
  void stockSptList(DrLightObjSpt *light) override;
  void render(DrShdLgtMan *shdLgtMan, DrLightMan *lightMan) override;
  void debugRender() override;
  void stockEnd() override;

  unknown001 unknown18[4]; // Inferred role: view infos; original member name unknown.
  void *unknown378;        // Inferred role: allocated work, freed by the destructor; original member name unknown.
  u32 unknown380;          // Inferred role: pnt light buffer size; original member name unknown.
  u32 unknown384;          // Inferred role: spt light buffer size; original member name unknown.
  void *unknown388;        // Inferred role: pnt light buffer; original member name unknown.
  void *unknown390;        // Inferred role: spt light buffer; original member name unknown.
};

static_assert(offsetof(DrShdLgtTileBasedDr::unknown001, unknown38) == 0x38, "");
static_assert(offsetof(DrShdLgtTileBasedDr::unknown001, unknowna8) == 0xa8, "");
static_assert(offsetof(DrShdLgtTileBasedDr::unknown001, unknownd0) == 0xd0, "");
static_assert(sizeof(DrShdLgtTileBasedDr::unknown001) == 0xd8, "");
static_assert(offsetof(DrShdLgtTileBasedDr, unknown18) == 0x18, "");
static_assert(offsetof(DrShdLgtTileBasedDr, unknown380) == 0x380, "");
static_assert(offsetof(DrShdLgtTileBasedDr, unknown388) == 0x388, "");
static_assert(offsetof(DrShdLgtTileBasedDr, unknown390) == 0x390, "");
static_assert(sizeof(DrShdLgtTileBasedDr) == 0x398, "");

} // namespace ml
