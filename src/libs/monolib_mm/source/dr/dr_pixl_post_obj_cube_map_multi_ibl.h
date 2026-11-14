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
class DrMan;
class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObjCubeMapMultiIBL : public DrPixlPostObj {
public:
  DrPixlPostObjCubeMapMultiIBL(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
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
  // Evidence for unknown5dc, unknown64c, unknown6dc, unknown6e0: the constructor (0x71008b8fe0) stores 0 byte-wide at
  // +0x5dc, 2 at +0x64c, then 0x90 at +0x6e0 and (+0x64c)^2 * 6 * 0x90 at +0x6dc (create the stream out work buffers).
  bool unknown5dc; // Inferred role: unknown, cleared by the constructor; original member name unknown.
  u8 _5dd[0x64c - 0x5dd];
  u32 unknown64c;                      // Inferred role: edge length in texels of the cube faces sampled for the spherical harmonics (the
                                       // constructor loops over 6 faces of that edge); original member name unknown.
  grlib::CGLibVtxVertex unknown650;    // Inferred role: vertex; original member name unknown.
  grlib::CGLibVtxStmOut unknown678[2]; // Inferred role: stream outs; original member name unknown.
  grlib::CGLibVtxFetch unknown6c8;     // Inferred role: vertex fetch; original member name unknown.
  u32 unknown6d8;                      // Inferred role: buffer index toggled by render; original member name unknown.
  u32 unknown6dc;                      // Inferred role: byte size of each stream out work buffer (passed to createWorkBuff); original member name unknown.
  u32 unknown6e0;                      // Inferred role: byte size of the stream out data of one texel (0x90); original member name unknown.
  u8 _6e4[0x6e8 - 0x6e4];
  DrShdCubeCapFilter *unknown6e8; // Inferred role: cube cap filter; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown5c8) == 0x5c8, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, m_premMipCount) == 0x5d8, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown5dc) == 0x5dc, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown64c) == 0x64c, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown650) == 0x650, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown678) == 0x678, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown6c8) == 0x6c8, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown6dc) == 0x6dc, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown6e0) == 0x6e0, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown6e8) == 0x6e8, "");
static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, unknown6d8) == 0x6d8, "");

} // namespace ml
