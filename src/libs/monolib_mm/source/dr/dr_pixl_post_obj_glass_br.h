#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "grlib/cglib_vtl_mem_pool.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "types.h"

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObjGlassBr : public DrPixlPostObj {
public:
  enum Flag {
    FLAG_UNKNOWN_2 = 1 << 2,
    FLAG_UNKNOWN_3 = 1 << 3,
  };

  DrPixlPostObjGlassBr(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjGlassBr();

  grlib::CGLibVtxVertex unknown18;        // Inferred role: vertex; original member name unknown.
  grlib::CGLibVtxIndex unknown40;         // Inferred role: index; original member name unknown.
  grlib::CGLibVtlMemPool unknown68;       // Inferred role: memory pool; original member name unknown.
  grlib::CGLibRenderTarget unknown98;     // Inferred role: render target; original member name unknown.
  grlib::CGLibDblUniformBlock unknown460; // Inferred role: uniform block; original member name unknown.
  u8 _498[0x4e0 - 0x498];
  void *unknown4e0; // Inferred role: unused data; original member name unknown.
  s32 unknown4e8;   // Inferred role: unused value; original member name unknown.
  u8 _4ec[0x4f8 - 0x4ec];
  void *unknown4f8; // Inferred role: work buffer; original member name unknown.
  u8 _500[0x508 - 0x500];
  u32 unknown508; // Inferred role: state flags; original member name unknown.
  u32 unknown50c; // Inferred role: unused value; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjGlassBr, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown40) == 0x40, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown68) == 0x68, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown98) == 0x98, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown460) == 0x460, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown4e0) == 0x4e0, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown4f8) == 0x4f8, "");
static_assert(offsetof(DrPixlPostObjGlassBr, unknown508) == 0x508, "");

} // namespace ml
