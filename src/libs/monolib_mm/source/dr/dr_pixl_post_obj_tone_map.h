#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "grlib/cglib_one_uniform_block.h"
#include "types.h"

namespace grlib {
class CGLibRenderTarget;
} // namespace grlib

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObjToneMap : public DrPixlPostObj {
public:
  DrPixlPostObjToneMap(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjToneMap();
  void update();
  void fastRender();
  void updateByCompute();
  void updateByRenderTarget();
  void createSclDow();
  void createMeasureLuminance();
  void createMeasureLuminanceByCompute();
  void creaetMeasureLuminaceByRenderTarget();
  void debugRender();

  grlib::CGLibRenderTarget *unknown18[6]; // Inferred role: scale down targets; original member name unknown.
  grlib::CGLibOneUniformBlock unknown48;  // Inferred role: measured luminance buffer; original member name unknown.
  grlib::CGLibOneUniformBlock unknown70;  // Inferred role: measured luminance buffer; original member name unknown.
  grlib::CGLibRenderTarget *unknown98;    // Inferred role: measured luminance target; original member name unknown.
  grlib::CGLibRenderTarget *unknowna0;    // Inferred role: measured luminance target; original member name unknown.
  grlib::CGLibRenderTarget *unknowna8;    // Inferred role: current measured luminance target; original member name unknown.
  f32 unknownb0;                          // Inferred role: adapted luminance; original member name unknown.
  u32 unknownb4;                          // Inferred role: state flags; original member name unknown.
  s32 unknownb8;                          // Inferred role: luminance reset frames; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjToneMap, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjToneMap, unknown48) == 0x48, "");
static_assert(offsetof(DrPixlPostObjToneMap, unknown70) == 0x70, "");
static_assert(offsetof(DrPixlPostObjToneMap, unknown98) == 0x98, "");
static_assert(offsetof(DrPixlPostObjToneMap, unknowna0) == 0xa0, "");
static_assert(offsetof(DrPixlPostObjToneMap, unknowna8) == 0xa8, "");
static_assert(offsetof(DrPixlPostObjToneMap, unknownb0) == 0xb0, "");
static_assert(offsetof(DrPixlPostObjToneMap, unknownb4) == 0xb4, "");
static_assert(offsetof(DrPixlPostObjToneMap, unknownb8) == 0xb8, "");

} // namespace ml
