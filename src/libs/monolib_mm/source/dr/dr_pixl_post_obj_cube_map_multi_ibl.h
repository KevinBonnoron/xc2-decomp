#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "dr/dr_requet_ibl.h"
#include "grlib/cglib_vtx_fetch.h"
#include "grlib/cglib_vtx_stm_out.h"
#include "grlib/cglib_vtx_vertex.h"
#include "mm_mtl/fixed_queue.h"
#include "types.h"

namespace ml {

class DrPixlRenderCubeMapMipMap;
class DrShdCubeCapFilter;

class DrPixlPostObjCubeMapMultiIBL : public DrPixlPostObj {
public:
  ~DrPixlPostObjCubeMapMultiIBL();
  void render();
  bool requestIBL(DrRequetIBL &request);
  void cancelIBL(u64 id);
  void outputPremToDDS();
  void update();
  void debugRender() const;
  u32 getPremMipCount() const;
  void relightCubeMap2(DrRequetIBL &request);
  void generateSH2(DrRequetIBL &request);

  mm::mtl::FixedQueue<DrRequetIBL, 30> unknown18; // Inferred role: IBL requests; original member name unknown.
  DrPixlRenderCubeMapMipMap *unknown5c8[2];       // Inferred role: prem textures; original member name unknown.
  u32 m_premMipCount;
  u8 _5dc[0x650 - 0x5dc];
  grlib::CGLibVtxVertex unknown650;    // Inferred role: vertex; original member name unknown.
  grlib::CGLibVtxStmOut unknown678[2]; // Inferred role: stream outs; original member name unknown.
  grlib::CGLibVtxFetch unknown6c8;     // Inferred role: vertex fetch; original member name unknown.
  u32 unknown6d8;                      // Inferred role: buffer index toggled by render; original member name unknown.
  u8 _6dc[0x6e8 - 0x6dc];
  DrShdCubeCapFilter *unknown6e8; // Inferred role: cube cap filter; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown5c8) == 0x5c8, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, m_premMipCount) == 0x5d8, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown650) == 0x650, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown678) == 0x678, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown6c8) == 0x6c8, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown6e8) == 0x6e8, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown6d8) == 0x6d8, "");

} // namespace ml
